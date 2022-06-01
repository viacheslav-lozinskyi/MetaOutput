# #############################################################################
# SET DEFAULT DATABASE ########################################################
#USE metaoutput_dev;
USE metaoutput;
# #############################################################################
# #############################################################################




# #############################################################################
# CREATING STORED PROCUDURES ##################################################
DROP PROCEDURE IF EXISTS net_filter_register;

DELIMITER %%
CREATE PROCEDURE net_filter_register(
    IN _type ENUM("IP", "URL"),
    IN _value VARCHAR(256))
BEGIN
    SET _type = UPPER(_type);
    SET _value = LOWER(_value);
    SET _value = TRIM(_value);

    IF (NOT EXISTS(SELECT _value FROM net_filters WHERE (type = _type) AND (value = _value))) THEN
        INSERT INTO net_filters(type, value)
        VALUE (_type, _value);
    END IF;
END;%%
DELIMITER ;
# #############################################################################

# #############################################################################
DROP PROCEDURE IF EXISTS net_realtime_register;

DELIMITER %%
CREATE PROCEDURE net_realtime_register(
    IN _netAddress VARCHAR(16),
    IN _source VARCHAR(64),
    IN _value1 VARCHAR(256),
    IN _value2 VARCHAR(256),
    IN _value3 VARCHAR(256))
BEGIN
    DELETE FROM net_realtime WHERE _time < DATE_SUB(NOW(), INTERVAL 1 HOUR);

    INSERT INTO net_realtime(netAddress, source, value1, value2, value3)
    VALUE (_netAddress, _source, _value1, _value2, _value3);
END;%%
DELIMITER ;
# #############################################################################

# #############################################################################
DROP PROCEDURE IF EXISTS net_session_register;

DELIMITER %%
CREATE PROCEDURE net_session_register(
    IN _time TIMESTAMP,
    IN _netAddress VARCHAR(16),
    IN _country VARCHAR(64),
    IN _city VARCHAR(64),
    IN _coordinates VARCHAR(32),
    IN _organization VARCHAR(128),
    IN _browser VARCHAR(64),
    IN _os VARCHAR(64),
    IN _resolution VARCHAR(64),
    IN _language VARCHAR(8),
    IN _ref VARCHAR(256),
    IN _campaignName VARCHAR(64),
    IN _campaignSource VARCHAR(64),
    IN _campaignMedium VARCHAR(64),
    IN _campaignTerm VARCHAR(128),
    IN _campaignContent VARCHAR(128))
BEGIN
    SET @_isFound = EXISTS(SELECT _id FROM net_sessions WHERE netAddress = _netAddress);

    IF (NOT ISNULL(_browser)) THEN
        SET _browser = REPLACE(_browser, "/", " ");
    END IF;
    
    IF (NOT ISNULL(_os)) THEN
        SET _os = REPLACE(_os, "Windows NT", "Windows");
    END IF;

    IF (NOT @_isFound) THEN
        INSERT INTO net_sessions (netAddress, country, city, coordinates, organization, browser, os, resolution, language, ref)
        VALUE (_netAddress, _country, _city, _coordinates, _organization, _browser, _os, _resolution, _language, _ref);
    END IF;

    IF (@_isFound AND NOT ISNULL(_time)) THEN
        UPDATE net_sessions SET time = _time WHERE netAddress = _netAddress;
    END IF;

    IF (@_isFound AND NOT ISNULL(_country)) THEN
        UPDATE net_sessions SET country = _country WHERE netAddress = _netAddress;
    END IF;

    IF (@_isFound AND NOT ISNULL(_city)) THEN
        UPDATE net_sessions SET city = _city WHERE netAddress = _netAddress;
    END IF;

    IF (@_isFound AND NOT ISNULL(_coordinates)) THEN
        UPDATE net_sessions SET coordinates = _coordinates WHERE netAddress = _netAddress;
    END IF;

    IF (@_isFound AND NOT ISNULL(_organization)) THEN
        UPDATE net_sessions SET organization = _organization WHERE netAddress = _netAddress;
    END IF;

    IF (@_isFound AND NOT ISNULL(_browser)) THEN
        UPDATE net_sessions SET browser = _browser WHERE netAddress = _netAddress;
    END IF;

    IF (@_isFound AND NOT ISNULL(_os)) THEN
        UPDATE net_sessions SET os = _os WHERE netAddress = _netAddress;
    END IF;

    IF (@_isFound AND NOT ISNULL(_resolution)) THEN
        UPDATE net_sessions SET resolution = _resolution WHERE netAddress = _netAddress;
    END IF;

    IF (@_isFound AND NOT ISNULL(_language)) THEN
        UPDATE net_sessions SET language = _language WHERE netAddress = _netAddress;
    END IF;

    IF (@_isFound AND NOT ISNULL(_ref)) THEN
        UPDATE net_sessions SET ref = _ref WHERE (netAddress = _netAddress) AND ISNULL(ref);
    END IF;

    IF (NOT ISNULL(_campaignName)) THEN
        IF (NOT ISNULL(_campaignSource)) THEN
            UPDATE net_sessions SET campaignSource = LOWER(_campaignSource) WHERE (netAddress = _netAddress) AND ISNULL(campaignName) AND ISNULL(campaignSource);
        END IF;

        IF (NOT ISNULL(_campaignMedium)) THEN
            UPDATE net_sessions SET campaignMedium = LOWER(_campaignMedium) WHERE (netAddress = _netAddress) AND ISNULL(campaignName) AND ISNULL(campaignMedium);
        END IF;

        IF (NOT ISNULL(_campaignTerm)) THEN
            UPDATE net_sessions SET campaignTerm = LOWER(_campaignTerm) WHERE (netAddress = _netAddress) AND ISNULL(campaignName) AND ISNULL(campaignTerm);
        END IF;

        IF (NOT ISNULL(_campaignContent)) THEN
            UPDATE net_sessions SET campaignContent = LOWER(_campaignContent) WHERE (netAddress = _netAddress) AND ISNULL(campaignName) AND ISNULL(campaignContent);
        END IF;

        UPDATE net_sessions SET campaignName = LOWER(_campaignName) WHERE (netAddress = _netAddress) AND ISNULL(campaignName);
    END IF;
END;%%
DELIMITER ;
# #############################################################################

# #############################################################################
DROP PROCEDURE IF EXISTS net_trace_register;

DELIMITER %%
CREATE PROCEDURE net_trace_register(
    IN _netAddress VARCHAR(16),
    IN _source VARCHAR(128),
    IN _project VARCHAR(128),
    IN _action VARCHAR(32),
    IN _message VARCHAR(1024))
BEGIN
    INSERT INTO net_traces (netAddress, source, project, action, message)
    VALUE (_netAddress, _source, _project, UPPER(_action), _message);

    CALL net_realtime_register(_netAddress, "TRACE", _source, _project, _action);
END;%%
DELIMITER ;
# #############################################################################

# #############################################################################
DROP PROCEDURE IF EXISTS app_session_register;

DELIMITER %%
CREATE PROCEDURE app_session_register(
    IN _netAddress VARCHAR(16),
    IN _userId VARCHAR(64),
    IN _source VARCHAR(128),
    IN _project VARCHAR(128),
    IN _sessionCount INTEGER)
BEGIN
    IF (NOT ISNULL(_userId)) THEN
        SET @_action = "START";
        SET @_maxSession = 0;

        IF (ISNULL(_sessionCount) OR (_sessionCount = 0)) THEN
            SET _sessionCount = 1;
        END IF;

        IF (EXISTS(SELECT _id FROM app_sessions WHERE userId = _userId LIMIT 1)) THEN
            IF (NOT EXISTS(SELECT * FROM (SELECT * FROM app_sessions WHERE userId = _userId ORDER BY _id DESC LIMIT 1) AS context WHERE context.project = _project)) THEN
                SET @_action = "UPDATE";
            END IF;
        ELSE
            SET @_action = "INSTALL";
        END IF;

        IF ((@_action != "START") OR NOT EXISTS(SELECT _id FROM app_sessions WHERE (userId = _userId) AND (DATE(_time) = CURRENT_DATE) LIMIT 1)) THEN
            INSERT INTO app_sessions (netAddress, userId, action, source, project)
            VALUE (_netAddress, _userId, @_action, _source, _project);

            CALL net_realtime_register(_netAddress, "APPLICATION", _source, _project, NULL);
        END IF;

        SELECT MAX(sessionCount) FROM net_sessions WHERE (netAddress = _netAddress) OR (userId = _userId) INTO @_maxSession;
        IF (ISNULL(@_maxSession)) THEN
            SET @_maxSession = 1;
        END IF;
        IF (_sessionCount < @_maxSession) THEN
            SET _sessionCount = @_maxSession + 1;
        END IF;
        UPDATE net_sessions SET userId = _userId WHERE netAddress = _netAddress;
        UPDATE net_sessions SET sessionCount = _sessionCount WHERE (netAddress = _netAddress) OR (userId = _userId);
    END IF;
END;%%
DELIMITER ;
# #############################################################################

# #############################################################################
DROP PROCEDURE IF EXISTS review_session_register;

DELIMITER %%
CREATE PROCEDURE review_session_register(
    IN _time VARCHAR(32),
    IN _netId VARCHAR(16),
    IN _source VARCHAR(128),
    IN _project VARCHAR(128),
    IN _action VARCHAR(32),
    IN _user VARCHAR(256),
    IN _avatar VARCHAR(256),
    IN _email VARCHAR(256),
    IN _url VARCHAR(256),
    IN _rating FLOAT,
    IN _message VARCHAR(1024))
BEGIN
    IF (NOT ISNULL(_user) AND NOT ISNULL(_source) AND NOT ISNULL(_project)) THEN
        SET @_context1 = _rating;
        SET @_context2 = _time;
        SET _action = UPPER(_action);

        IF (NOT ISNULL(_rating)) THEN
            SET _rating = 1;
            IF (@_context1 >= 1) THEN
                SET _rating = 1;
            END IF;
            IF (@_context1 >= 2) THEN
                SET _rating = 2;
            END IF;
            IF (@_context1 >= 3) THEN
                SET _rating = 3;
            END IF;
            IF (@_context1 >= 4) THEN
                SET _rating = 4;
            END IF;
            IF (@_context1 >= 5) THEN
                SET _rating = 5;
            END IF;
        END IF;

        IF (NOT ISNULL(_action)) THEN
            SET _action = "REVIEW";
        END IF;

        DELETE FROM review_sessions WHERE (user = _user) AND (source = _source) AND (project = _project) AND (action = _action) AND (message = _message) AND (url = _url);

        IF (ISNULL(_time)) THEN
            INSERT INTO review_sessions (netId, source, project, action, user, avatar, email, url, rating, message)
            VALUE (_netId, _source, _project, _action, _user, _avatar, _email, _url, _rating, _message);
        ELSE
            INSERT INTO review_sessions (_time, netId, source, project, action, user, avatar, email, url, rating, message)
            VALUE (STR_TO_DATE(@_context2, "%Y-%m-%d %H:%i"), _netId, _source, _project, _action, _user, _avatar, _email, _url, _rating, _message);
        END IF;

        CALL net_realtime_register(_netId, "REVIEW", _source, _project, _rating);
    END IF;
END;%%
DELIMITER ;
# #############################################################################

# #############################################################################
DROP PROCEDURE IF EXISTS github_session_register;

DELIMITER %%
CREATE PROCEDURE github_session_register(
    IN _country VARCHAR(64),
    IN _city VARCHAR(64),
    IN _event VARCHAR(64),
    IN _action VARCHAR(64),
    IN _project VARCHAR(128),
    IN _branch VARCHAR(128),
    IN _user VARCHAR(128),
    IN _avatar VARCHAR(256),
    IN _url VARCHAR(256),
    IN _message VARCHAR(1024))
BEGIN
    INSERT INTO github_sessions (country, city, event, action, project, branch, user, avatar, url, message)
    VALUE (_country, _city, UPPER(_event), UPPER(_action), _project, _branch, _user, _avatar, _url, _message);

    CALL net_realtime_register(NULL, "GITHUB", _event, _action, _project);
END;%%
DELIMITER ;
# #############################################################################

# #############################################################################
DROP PROCEDURE IF EXISTS github_project_register;

DELIMITER %%
CREATE PROCEDURE github_project_register(
    IN _project VARCHAR(128),
    IN _owner VARCHAR(128),
    IN _url VARCHAR(256),
    IN _starCount INTEGER,
    IN _watchCount INTEGER,
    IN _forkCount INTEGER,
    IN _issueCount INTEGER)
BEGIN
    SET @_isFound = EXISTS(SELECT _id FROM github_projects WHERE project = _project);

    IF (NOT @_isFound) THEN
        INSERT INTO github_projects (project, owner, url, starCount, watchCount, forkCount, issueCount)
        VALUE (_project, _owner, _url, _starCount, _watchCount, _forkCount, _issueCount);
    END IF;

    IF (@_isFound AND NOT ISNULL(_owner)) THEN
        UPDATE github_projects SET owner = _owner WHERE project = _project;
    END IF;

    IF (@_isFound AND NOT ISNULL(_url)) THEN
        UPDATE github_projects SET url = _url WHERE project = _project;
    END IF;

    IF (@_isFound AND NOT ISNULL(_starCount)) THEN
        UPDATE github_projects SET starCount = _starCount WHERE project = _project;
    END IF;

    IF (@_isFound AND NOT ISNULL(_watchCount)) THEN
        UPDATE github_projects SET watchCount = _watchCount WHERE project = _project;
    END IF;

    IF (@_isFound AND NOT ISNULL(_forkCount)) THEN
        UPDATE github_projects SET forkCount = _forkCount WHERE project = _project;
    END IF;

    IF (@_isFound AND NOT ISNULL(_issueCount)) THEN
        UPDATE github_projects SET issueCount = _issueCount WHERE project = _project;
    END IF;
END;%%
DELIMITER ;

# #############################################################################
DROP PROCEDURE IF EXISTS watch_session_register;

DELIMITER %%
CREATE PROCEDURE watch_session_register(
    IN _netAddress VARCHAR(16),
    IN _source VARCHAR(128),
    IN _project VARCHAR(128),
    IN _action VARCHAR(64),
    IN _user VARCHAR(128),
    IN _url VARCHAR(256),
    IN _message VARCHAR(256))
BEGIN
    SET @isFound =
        (NOT EXISTS(SELECT _id FROM watch_sessions WHERE (netAddress = _netAddress) AND (_time > DATE_SUB(NOW(), INTERVAL 1 DAY)) AND ((ISNULL(_url) AND (project = _project)) OR (NOT ISNULL(_url) AND (url = _url))) LIMIT 1)) AND
        (NOT EXISTS(SELECT _id FROM net_filters WHERE (type = "URL") AND (_url LIKE value) LIMIT 1));

    IF (@isFound AND ISNULL(_project)) THEN
        SET _project = _url;
        IF (ISNULL(_project)) THEN
            SET _project = "unknown";
        END IF;
        SET _project = TRIM(_project);
        IF (POSITION("://" IN _project) > 0) THEN
            SET _project = MID(_project, POSITION("://" IN _project) + 3, LENGTH(_project));
        END IF;
        IF (POSITION("www." IN _project) = 1) THEN
            SET _project = MID(_project, 5, LENGTH(_project));
        END IF;
        IF (POSITION("/" IN _project) > 0) THEN
            SET _project = LEFT(_project, POSITION("/" IN _project) - 1);
        END IF;
    END IF;

    IF (@isFound) THEN
        IF (ISNULL(_source)) THEN
            SET _source = "WEB-SITE";
        END IF;
        IF (ISNULL(_action)) THEN
            SET _action = "VIEW";
        END IF;

        SET _source = UPPER(_source);
        SET _action = UPPER(_action);

        INSERT INTO watch_sessions (netAddress, source, project, action, user, url, message)
        VALUE (_netAddress, _source, _project, _action, _user, _url, _message);

        CALL net_realtime_register(_netAddress, "WATCH", _source, _project, _action);
    END IF;
END;%%
DELIMITER ;
# #############################################################################

# #############################################################################
DROP PROCEDURE IF EXISTS service_cleanup_debug;

DELIMITER %%
CREATE PROCEDURE service_cleanup_debug(
    IN _daysIgnore INTEGER)
BEGIN
    SET SQL_SAFE_UPDATES = 0;
    IF ISNULL(_daysIgnore) THEN
        DELETE FROM app_sessions WHERE (userId LIKE "TEST-%");
    ELSE
        DELETE FROM app_sessions WHERE (userId LIKE "TEST-%") AND (_time < DATE_SUB(NOW(), INTERVAL _daysIgnore DAY));        
    END IF;

    #DELETE FROM web_sessions WHERE action = "TEST";
    #DELETE FROM watch_sessions WHERE project = "unknown";
    SET SQL_SAFE_UPDATES = 1;
END;%%
DELIMITER ;
# #############################################################################
# #############################################################################




# #############################################################################
# ADDING DEFAULT DATA #########################################################
CALL net_filter_register("URL", "https://www.metaoutput.net/admin%");
CALL net_filter_register("URL", "https://www.metaoutput.net/accountant%");
CALL net_filter_register("URL", "https://www.metaoutput.net/developer%");
CALL net_filter_register("URL", "https://www.metaoutput.net/marketer%");
CALL net_filter_register("URL", "https://www.metaoutput.net/observer%");
CALL net_filter_register("URL", "https://www.metaoutput.net/owner%");
CALL net_filter_register("URL", "https://www.metaoutput.net/recruiter%");
CALL net_filter_register("URL", "https://www.metaoutput.net/support%");
CALL net_filter_register("URL", "https://www.metaoutput.net/test%");
CALL net_filter_register("URL", "https://www.metaoutput.net/tester%");
CALL net_filter_register("URL", "https://www.metaoutput.net/?requestedBy=screenshoter%");
CALL net_filter_register("URL", "https://www.metaoutput.net//%");
CALL net_filter_register("URL", "%&suppressbi=true%");
#CALL net_filter_register("IP", "127.0.0.1");
# #############################################################################
# #############################################################################




# #############################################################################
# VIEW TABLES #################################################################
SET PROFILING_HISTORY_SIZE = 100;
SET PROFILING = 1;

SELECT * FROM net_filters LIMIT 50000;
SELECT * FROM net_traces LIMIT 50000;
SELECT * FROM net_traces_view LIMIT 50000;
SELECT * FROM net_realtime LIMIT 50000;
SELECT * FROM net_realtime_view LIMIT 50000;
SELECT * FROM net_sessions LIMIT 50000;
SELECT * FROM app_sessions LIMIT 50000;
SELECT * FROM app_sessions_view LIMIT 50000;
SELECT * FROM watch_sessions LIMIT 50000;
SELECT * FROM watch_sessions_view LIMIT 50000;
SELECT * FROM github_sessions LIMIT 50000;
SELECT * FROM github_projects LIMIT 50000;

SET PROFILING = 0;
#SET GLOBAL MAX_CONNECTIONS = 200;
#SET GLOBAL interactive_timeout = 100;

SHOW PROFILE FOR QUERY 30;
SHOW PROFILES;
SHOW VARIABLES LIKE "max_connections";
SHOW VARIABLES LIKE "interactive_timeout";
SHOW FULL PROCESSLIST;
# #############################################################################
# #############################################################################


# #############################################################################
# QUERIES #####################################################################

SET SQL_SAFE_UPDATES = 0;
#SELECT * FROM net_sessions WHERE NOT ISNULL(country) ORDER BY _id DESC LIMIT 50000;
SET SQL_SAFE_UPDATES = 1;

# #############################################################################
# #############################################################################
