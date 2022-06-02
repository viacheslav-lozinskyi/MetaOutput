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
    IN __type ENUM("IP", "URL"),
    IN __value VARCHAR(256))
BEGIN
    SET __type = UPPER(__type);
    SET __value = LOWER(__value);
    SET __value = TRIM(__value);

    IF (NOT EXISTS(SELECT __value FROM net_filters WHERE (type = __type) AND (value = __value))) THEN
        INSERT INTO net_filters(type, value)
        VALUE (__type, __value);
    END IF;
END;%%
DELIMITER ;
# #############################################################################

# #############################################################################
DROP PROCEDURE IF EXISTS net_realtime_register;

DELIMITER %%
CREATE PROCEDURE net_realtime_register(
    IN __time VARCHAR(32),
    IN __netId VARCHAR(16),
    IN __source VARCHAR(64),
    IN __value1 VARCHAR(256),
    IN __value2 VARCHAR(256),
    IN __value3 VARCHAR(256))
BEGIN
    DELETE FROM net_realtime WHERE __time < DATE_SUB(NOW(), INTERVAL 1 HOUR);

    IF (ISNULL(__time)) THEN
        INSERT INTO net_realtime(netId, source, value1, value2, value3)
        VALUE (__netId, __source, __value1, __value2, __value3);
    ELSE
        INSERT INTO net_realtime(_time, netId, source, value1, value2, value3)
        VALUE (STR_TO_DATE(__time, "%Y-%m-%d %H:%i"), __netId, __source, __value1, __value2, __value3);
    END IF;
END;%%
DELIMITER ;
# #############################################################################

# #############################################################################
DROP PROCEDURE IF EXISTS net_session_register;

DELIMITER %%
CREATE PROCEDURE net_session_register(
    IN __time VARCHAR(32),
    IN __netId VARCHAR(16),
    IN __country VARCHAR(64),
    IN __city VARCHAR(64),
    IN __coordinates VARCHAR(32),
    IN __organization VARCHAR(128),
    IN __browser VARCHAR(64),
    IN __os VARCHAR(64),
    IN __resolution VARCHAR(64),
    IN __language VARCHAR(8),
    IN __ref VARCHAR(256),
    IN __campaignName VARCHAR(64),
    IN __campaignSource VARCHAR(64),
    IN __campaignMedium VARCHAR(64),
    IN __campaignTerm VARCHAR(128),
    IN __campaignContent VARCHAR(128))
BEGIN
    SET @_isFound = EXISTS(SELECT _id FROM net_sessions WHERE netId = __netId);

    IF (NOT ISNULL(__browser)) THEN
        SET __browser = REPLACE(__browser, "/", " ");
    END IF;

    IF (NOT ISNULL(__os)) THEN
        SET __os = REPLACE(__os, "Windows NT", "Windows");
    END IF;

    IF (NOT @_isFound) THEN
        INSERT INTO net_sessions (netId, country, city, coordinates, organization, browser, os, resolution, language, ref)
        VALUE (__netId, __country, __city, __coordinates, __organization, __browser, __os, __resolution, __language, __ref);
    END IF;

    IF (NOT ISNULL(__time)) THEN
        UPDATE net_sessions SET _time = STR_TO_DATE(__time, "%Y-%m-%d %H:%i") WHERE netId = __netId;
    END IF;

    IF (@_isFound AND NOT ISNULL(__country)) THEN
        UPDATE net_sessions SET country = __country WHERE netId = __netId;
    END IF;

    IF (@_isFound AND NOT ISNULL(__city)) THEN
        UPDATE net_sessions SET city = __city WHERE netId = __netId;
    END IF;

    IF (@_isFound AND NOT ISNULL(__coordinates)) THEN
        UPDATE net_sessions SET coordinates = __coordinates WHERE netId = __netId;
    END IF;

    IF (@_isFound AND NOT ISNULL(__organization)) THEN
        UPDATE net_sessions SET organization = __organization WHERE netId = __netId;
    END IF;

    IF (@_isFound AND NOT ISNULL(__browser)) THEN
        UPDATE net_sessions SET browser = __browser WHERE netId = __netId;
    END IF;

    IF (@_isFound AND NOT ISNULL(__os)) THEN
        UPDATE net_sessions SET os = __os WHERE netId = __netId;
    END IF;

    IF (@_isFound AND NOT ISNULL(__resolution)) THEN
        UPDATE net_sessions SET resolution = __resolution WHERE netId = __netId;
    END IF;

    IF (@_isFound AND NOT ISNULL(__language)) THEN
        UPDATE net_sessions SET language = __language WHERE netId = __netId;
    END IF;

    IF (@_isFound AND NOT ISNULL(__ref)) THEN
        UPDATE net_sessions SET ref = __ref WHERE (netId = __netId) AND ISNULL(ref);
    END IF;

    IF (NOT ISNULL(__campaignName)) THEN
        IF (NOT ISNULL(__campaignSource)) THEN
            UPDATE net_sessions SET campaignSource = LOWER(__campaignSource) WHERE (netId = __netId) AND ISNULL(campaignName) AND ISNULL(campaignSource);
        END IF;

        IF (NOT ISNULL(__campaignMedium)) THEN
            UPDATE net_sessions SET campaignMedium = LOWER(__campaignMedium) WHERE (netId = __netId) AND ISNULL(campaignName) AND ISNULL(campaignMedium);
        END IF;

        IF (NOT ISNULL(__campaignTerm)) THEN
            UPDATE net_sessions SET campaignTerm = LOWER(__campaignTerm) WHERE (netId = __netId) AND ISNULL(campaignName) AND ISNULL(campaignTerm);
        END IF;

        IF (NOT ISNULL(__campaignContent)) THEN
            UPDATE net_sessions SET campaignContent = LOWER(__campaignContent) WHERE (netId = __netId) AND ISNULL(campaignName) AND ISNULL(campaignContent);
        END IF;

        UPDATE net_sessions SET campaignName = LOWER(__campaignName) WHERE (netId = __netId) AND ISNULL(campaignName);
    END IF;
END;%%
DELIMITER ;
# #############################################################################

# #############################################################################
DROP PROCEDURE IF EXISTS net_trace_register;

DELIMITER %%
CREATE PROCEDURE net_trace_register(
    IN __time VARCHAR(32),
    IN __netId VARCHAR(16),
    IN __source VARCHAR(128),
    IN __project VARCHAR(128),
    IN __action VARCHAR(32),
    IN __message VARCHAR(1024))
BEGIN
    IF (ISNULL(__time)) THEN
        IF (EXISTS(SELECT _id FROM net_traces WHERE (DATE(_time) = CURRENT_DATE) AND (netId = __netId) AND (source = __source) AND (project = __project) AND (action = __action) AND (message = __message) LIMIT 1)) THEN
            UPDATE net_traces
            SET _time = CURRENT_TIME, eventCount = eventCount + 1
            WHERE (DATE(_time) = CURRENT_DATE) AND (netId = __netId) AND (source = __source) AND (project = __project) AND (action = __action) AND (message = __message);
        ELSE
            INSERT INTO net_traces (netId, source, project, action, message)
            VALUE (__netId, __source, __project, UPPER(__action), __message);
        END IF;
    ELSE
        INSERT INTO net_traces (_time, netId, source, project, action, message)
        VALUE (STR_TO_DATE(__time, "%Y-%m-%d %H:%i"), __netId, __source, __project, UPPER(__action), __message);
    END IF;

    CALL net_realtime_register(__time, __netId, "TRACE", __source, __project, __action);
END;%%
DELIMITER ;
# #############################################################################

# #############################################################################
DROP PROCEDURE IF EXISTS app_session_register;

DELIMITER %%
CREATE PROCEDURE app_session_register(
    IN __time VARCHAR(32),
    IN __netId VARCHAR(16),
    IN __userId VARCHAR(64),
    IN __source VARCHAR(128),
    IN __project VARCHAR(128),
    IN __sessionCount INTEGER)
BEGIN
    IF (NOT ISNULL(__userId)) THEN
        SET @__action = "START";
        SET @_maxSession = 0;

        IF (ISNULL(__sessionCount) OR (__sessionCount = 0)) THEN
            SET __sessionCount = 1;
        END IF;

        IF (EXISTS(SELECT _id FROM app_sessions WHERE userId = __userId LIMIT 1)) THEN
            IF (NOT EXISTS(SELECT * FROM (SELECT * FROM app_sessions WHERE userId = __userId ORDER BY _id DESC LIMIT 1) AS context WHERE context.project = __project)) THEN
                SET @__action = "UPDATE";
            END IF;
        ELSE
            SET @__action = "INSTALL";
        END IF;

        IF ((@__action != "START") OR NOT EXISTS(SELECT _id FROM app_sessions WHERE (userId = __userId) AND (DATE(_time) = CURRENT_DATE) LIMIT 1)) THEN
            IF (ISNULL(__time)) THEN
                INSERT INTO app_sessions (netId, userId, action, source, project)
                VALUE (__netId, __userId, @__action, __source, __project);
            ELSE
                INSERT INTO app_sessions (_time, netId, userId, action, source, project)
                VALUE (STR_TO_DATE(__time, "%Y-%m-%d %H:%i"), __netId, __userId, @__action, __source, __project);
            END IF;

            CALL net_realtime_register(__time, __netId, "APPLICATION", __source, __project, NULL);
        END IF;

        SELECT MAX(sessionCount) FROM net_sessions WHERE (netId = __netId) OR (userId = __userId) INTO @_maxSession;
        IF (ISNULL(@_maxSession)) THEN
            SET @_maxSession = 1;
        END IF;
        IF (__sessionCount < @_maxSession) THEN
            SET __sessionCount = @_maxSession + 1;
        END IF;

        UPDATE net_sessions SET userId = __userId WHERE netId = __netId;
        UPDATE net_sessions SET sessionCount = __sessionCount WHERE (netId = __netId) OR (userId = __userId);
    END IF;
END;%%
DELIMITER ;
# #############################################################################

# #############################################################################
DROP PROCEDURE IF EXISTS review_session_register;

DELIMITER %%
CREATE PROCEDURE review_session_register(
    IN __time VARCHAR(32),
    IN __netId VARCHAR(16),
    IN __source VARCHAR(128),
    IN __project VARCHAR(128),
    IN __action VARCHAR(32),
    IN __user VARCHAR(256),
    IN __avatar VARCHAR(256),
    IN __email VARCHAR(256),
    IN __url VARCHAR(256),
    IN __rating FLOAT,
    IN __message VARCHAR(1024))
BEGIN
    IF (NOT ISNULL(__user) AND NOT ISNULL(__source) AND NOT ISNULL(__project)) THEN
        SET @_context1 = __rating;
        SET __action = UPPER(__action);

        IF (NOT ISNULL(__rating)) THEN
            SET __rating = 1;
            IF (@_context1 >= 1) THEN
                SET __rating = 1;
            END IF;
            IF (@_context1 >= 2) THEN
                SET __rating = 2;
            END IF;
            IF (@_context1 >= 3) THEN
                SET __rating = 3;
            END IF;
            IF (@_context1 >= 4) THEN
                SET __rating = 4;
            END IF;
            IF (@_context1 >= 5) THEN
                SET __rating = 5;
            END IF;
        END IF;

        IF (NOT ISNULL(__action)) THEN
            SET __action = "REVIEW";
        END IF;

        DELETE FROM review_sessions WHERE (user = __user) AND (source = __source) AND (project = __project) AND (action = __action) AND (message = __message) AND (url = __url);

        IF (ISNULL(__time)) THEN
            INSERT INTO review_sessions (netId, source, project, action, user, avatar, email, url, rating, message)
            VALUE (__netId, __source, __project, __action, __user, __avatar, __email, __url, __rating, __message);
        ELSE
            INSERT INTO review_sessions (_time, netId, source, project, action, user, avatar, email, url, rating, message)
            VALUE (STR_TO_DATE(__time, "%Y-%m-%d %H:%i"), __netId, __source, __project, __action, __user, __avatar, __email, __url, __rating, __message);
        END IF;

        CALL net_realtime_register(__time, __netId, "REVIEW", __source, __project, __rating);
    END IF;
END;%%
DELIMITER ;
# #############################################################################

# #############################################################################
DROP PROCEDURE IF EXISTS github_session_register;

DELIMITER %%
CREATE PROCEDURE github_session_register(
    IN __time VARCHAR(32),
    IN __country VARCHAR(64),
    IN __city VARCHAR(64),
    IN __event VARCHAR(64),
    IN __action VARCHAR(64),
    IN __project VARCHAR(128),
    IN __branch VARCHAR(128),
    IN __user VARCHAR(128),
    IN __avatar VARCHAR(256),
    IN __url VARCHAR(256),
    IN __message VARCHAR(1024))
BEGIN
    IF (ISNULL(__time)) THEN
        INSERT INTO github_sessions (country, city, event, action, project, branch, user, avatar, url, message)
        VALUE (__country, __city, UPPER(__event), UPPER(__action), __project, __branch, __user, __avatar, __url, __message);
    ELSE
        INSERT INTO github_sessions (_time, country, city, event, action, project, branch, user, avatar, url, message)
        VALUE (STR_TO_DATE(__time, "%Y-%m-%d %H:%i"), __country, __city, UPPER(__event), UPPER(__action), __project, __branch, __user, __avatar, __url, __message);
    END IF;

    CALL net_realtime_register(__time, null, "GITHUB", __event, __action, __project);
END;%%
DELIMITER ;
# #############################################################################

# #############################################################################
DROP PROCEDURE IF EXISTS github__project_register;

DELIMITER %%
CREATE PROCEDURE github__project_register(
    IN __project VARCHAR(128),
    IN __owner VARCHAR(128),
    IN __url VARCHAR(256),
    IN __starCount INTEGER,
    IN __watchCount INTEGER,
    IN __forkCount INTEGER,
    IN __issueCount INTEGER)
BEGIN
    SET @_isFound = EXISTS(SELECT _id FROM github__projects WHERE project = __project);

    IF (NOT @_isFound) THEN
        INSERT INTO github__projects (project, owner, url, starCount, watchCount, forkCount, issueCount)
        VALUE (__project, __owner, __url, __starCount, __watchCount, __forkCount, __issueCount);
    END IF;

    IF (@_isFound AND NOT ISNULL(__owner)) THEN
        UPDATE github__projects SET owner = __owner WHERE project = __project;
    END IF;

    IF (@_isFound AND NOT ISNULL(__url)) THEN
        UPDATE github__projects SET url = __url WHERE project = __project;
    END IF;

    IF (@_isFound AND NOT ISNULL(__starCount)) THEN
        UPDATE github__projects SET starCount = __starCount WHERE project = __project;
    END IF;

    IF (@_isFound AND NOT ISNULL(__watchCount)) THEN
        UPDATE github__projects SET watchCount = __watchCount WHERE project = __project;
    END IF;

    IF (@_isFound AND NOT ISNULL(__forkCount)) THEN
        UPDATE github__projects SET forkCount = __forkCount WHERE project = __project;
    END IF;

    IF (@_isFound AND NOT ISNULL(__issueCount)) THEN
        UPDATE github__projects SET issueCount = __issueCount WHERE project = __project;
    END IF;
END;%%
DELIMITER ;

# #############################################################################
DROP PROCEDURE IF EXISTS watch_session_register;

DELIMITER %%
CREATE PROCEDURE watch_session_register(
    IN __time VARCHAR(32),
    IN __netId VARCHAR(16),
    IN __source VARCHAR(128),
    IN __project VARCHAR(128),
    IN __action VARCHAR(64),
    IN __user VARCHAR(128),
    IN __url VARCHAR(256),
    IN __message VARCHAR(256))
BEGIN
    SET @isFound =
        (NOT EXISTS(SELECT _id FROM watch_sessions WHERE (netId = __netId) AND (_time > DATE_SUB(NOW(), INTERVAL 1 DAY)) AND ((ISNULL(__url) AND (project = __project)) OR (NOT ISNULL(__url) AND (url = __url))) LIMIT 1)) AND
        (NOT EXISTS(SELECT _id FROM net_filters WHERE (type = "URL") AND (__url LIKE value) LIMIT 1));

    IF (@isFound AND ISNULL(__project)) THEN
        SET __project = __url;
        IF (ISNULL(__project)) THEN
            SET __project = "unknown";
        END IF;
        SET __project = TRIM(__project);
        IF (POSITION("://" IN __project) > 0) THEN
            SET __project = MID(__project, POSITION("://" IN __project) + 3, LENGTH(__project));
        END IF;
        IF (POSITION("www." IN __project) = 1) THEN
            SET __project = MID(__project, 5, LENGTH(__project));
        END IF;
        IF (POSITION("/" IN __project) > 0) THEN
            SET __project = LEFT(__project, POSITION("/" IN __project) - 1);
        END IF;
    END IF;

    IF (@isFound) THEN
        IF (ISNULL(__source)) THEN
            SET __source = "WEB-SITE";
        END IF;
        IF (ISNULL(__action)) THEN
            SET __action = "VIEW";
        END IF;

        SET __source = UPPER(__source);
        SET __action = UPPER(__action);

        IF (ISNULL(__time)) THEN
            INSERT INTO watch_sessions (netId, source, project, action, user, url, message)
            VALUE (__netId, __source, __project, __action, __user, __url, __message);
        ELSE
            INSERT INTO watch_sessions (_time, netId, source, project, action, user, url, message)
            VALUE (STR_TO_DATE(__time, "%Y-%m-%d %H:%i"), __netId, __source, __project, __action, __user, __url, __message);
        END IF;

        CALL net_realtime_register(__time, __netId, "WATCH", __source, __project, __action);
    END IF;
END;%%
DELIMITER ;
# #############################################################################

# #############################################################################
DROP PROCEDURE IF EXISTS service_cleanup_debug;

DELIMITER %%
CREATE PROCEDURE service_cleanup_debug(
    IN __daysIgnore INTEGER)
BEGIN
    SET SQL_SAFE_UPDATES = 0;
    IF ISNULL(__daysIgnore) THEN
        DELETE FROM app_sessions WHERE (userId LIKE "TEST-%");
    ELSE
        DELETE FROM app_sessions WHERE (userId LIKE "TEST-%") AND (_time < DATE_SUB(NOW(), INTERVAL __daysIgnore DAY));
    END IF;
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
