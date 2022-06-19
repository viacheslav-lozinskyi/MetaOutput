# #############################################################################
# SET DEFAULT DATABASE ########################################################
#USE metaoutput_dev;
USE metaoutput;
# #############################################################################
# #############################################################################




# #############################################################################
# CREATING STORED PROCUDURES ##################################################
DROP PROCEDURE IF EXISTS net_crawler_register;

DELIMITER %%
CREATE PROCEDURE net_crawler_register(
    IN __url VARCHAR(256))
BEGIN
    IF (NOT ISNULL(__url) AND NOT EXISTS(SELECT _id FROM net_crawlers WHERE (url = __url))) THEN
        INSERT INTO net_crawlers(url)
        VALUE (__url);
    END IF;
END;%%
DELIMITER ;
# #############################################################################

# #############################################################################
DROP PROCEDURE IF EXISTS net_filter_register;

DELIMITER %%
CREATE PROCEDURE net_filter_register(
    IN __type ENUM("IP", "URL"),
    IN __value VARCHAR(256))
BEGIN
    SET __type = UPPER(__type);
    SET __value = LOWER(__value);
    SET __value = TRIM(__value);

    IF (NOT ISNULL(__type) AND NOT ISNULL(__value) AND NOT EXISTS(SELECT _id FROM net_filters WHERE (type = __type) AND (value = __value))) THEN
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
    IN __netId VARCHAR(16),
    IN __source VARCHAR(64),
    IN __value1 VARCHAR(256),
    IN __value2 VARCHAR(256),
    IN __value3 VARCHAR(256),
    IN __value4 VARCHAR(256))
BEGIN
    SET SQL_SAFE_UPDATES = 0;

    DELETE FROM net_realtime WHERE _time < DATE_SUB(NOW(), INTERVAL 1 HOUR);

    INSERT INTO net_realtime(netId, source, value1, value2, value3, value4)
    VALUE (__netId, __source, __value1, __value2, __value3, __value4);

    SET SQL_SAFE_UPDATES = 1;
END;%%
DELIMITER ;
# #############################################################################

# #############################################################################
DROP PROCEDURE IF EXISTS net_session_register;

DELIMITER %%
CREATE PROCEDURE net_session_register(
    IN __time VARCHAR(32),
    IN __netId VARCHAR(16),
    IN __userId VARCHAR(64),
    IN __country VARCHAR(64),
    IN __city VARCHAR(64),
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
    IF (NOT ISNULL(__netId)) THEN
        IF (NOT ISNULL(__userId) AND (__userId = "")) THEN
            SET __userId = null;
        END IF;

        IF (NOT ISNULL(__browser)) THEN
            SET __browser = REPLACE(__browser, "/", " ");
        END IF;

        IF (NOT ISNULL(__os)) THEN
            SET __os = REPLACE(__os, "Windows NT", "Windows");
        END IF;

        IF (NOT ISNULL(__country) AND (__country = "")) THEN
            SET __country = null;
        END IF;

        IF (NOT ISNULL(__city) AND (__city = "")) THEN
            SET __city = null;
        END IF;

        IF (NOT ISNULL(__organization) AND (__organization = "")) THEN
            SET __organization = null;
        END IF;

        IF (NOT ISNULL(__browser) AND (__browser = "")) THEN
            SET __browser = null;
        END IF;

        IF (NOT ISNULL(__os) AND (__os = "")) THEN
            SET __os = null;
        END IF;

        IF (NOT ISNULL(__resolution) AND (__resolution = "")) THEN
            SET __resolution = null;
        END IF;

        IF (NOT ISNULL(__language) AND (__language = "")) THEN
            SET __language = null;
        END IF;

        IF (NOT ISNULL(__ref) AND (__ref = "")) THEN
            SET __ref = null;
        END IF;

        IF (NOT ISNULL(__campaignName) AND (__campaignName = "")) THEN
            SET __campaignName = null;
        END IF;

        IF (NOT ISNULL(__campaignSource) AND (__campaignSource = "")) THEN
            SET __campaignSource = null;
        END IF;

        IF (NOT ISNULL(__campaignMedium) AND (__campaignMedium = "")) THEN
            SET __campaignMedium = null;
        END IF;

        IF (NOT ISNULL(__campaignTerm) AND (__campaignTerm = "")) THEN
            SET __campaignTerm = null;
        END IF;

        IF (NOT ISNULL(__campaignContent) AND (__campaignContent = "")) THEN
            SET __campaignContent = null;
        END IF;

        IF (NOT EXISTS(SELECT _id FROM net_sessions WHERE netId = __netId LIMIT 1)) THEN
            INSERT INTO net_sessions (netId, userId, country, city, organization, browser, os, resolution, language, ref, campaignName, campaignSource, campaignMedium, campaignTerm, campaignContent)
            VALUE (__netId, __userId, __country, __city, __organization, __browser, __os, __resolution, __language, __ref, LOWER(__campaignName), LOWER(__campaignSource), LOWER(__campaignMedium), LOWER(__campaignTerm), LOWER(__campaignContent));
        ELSE
            SET SQL_SAFE_UPDATES = 0;

            IF (ISNULL(__country) OR ISNULL(__city) OR ISNULL(__organization) OR ISNULL(__os) OR ISNULL(__resolution) OR ISNULL(__language)) THEN
                IF (NOT ISNULL(__country)) THEN
                    UPDATE net_sessions
                    SET country = __country
                    WHERE netId = __netId;
                END IF;

                IF (NOT ISNULL(__city)) THEN
                    UPDATE net_sessions
                    SET city = __city
                    WHERE netId = __netId;
                END IF;

                IF (NOT ISNULL(__organization)) THEN
                    UPDATE net_sessions
                    SET organization = __organization
                    WHERE netId = __netId;
                END IF;

                IF (NOT ISNULL(__os)) THEN
                    UPDATE net_sessions
                    SET os = __os
                    WHERE netId = __netId;
                END IF;

                IF (NOT ISNULL(__resolution)) THEN
                    UPDATE net_sessions
                    SET resolution = __resolution
                    WHERE netId = __netId;
                END IF;

                IF (NOT ISNULL(__language)) THEN
                    UPDATE net_sessions
                    SET language = __language
                    WHERE netId = __netId;
                END IF;
            ELSE
                UPDATE net_sessions
                SET
                    country = __country,
                    city = __city,
                    organization = __organization,
                    os = __os,
                    resolution = __resolution,
                    language = __language
                WHERE netId = __netId;
            END IF;

            IF (NOT ISNULL(__userId)) THEN
                UPDATE net_sessions
                SET userId = __userId
                WHERE netId = __netId;
            END IF;

            IF (NOT ISNULL(__browser)) THEN
                UPDATE net_sessions
                SET browser = __browser
                WHERE netId = __netId;
            END IF;

            SET SQL_SAFE_UPDATES = 1;
        END IF;

        IF (NOT ISNULL(__time) AND (__time != "")) THEN
            SET SQL_SAFE_UPDATES = 0;

            UPDATE net_sessions
            SET _time = STR_TO_DATE(__time, "%Y-%m-%dT%TZ")
            WHERE netId = __netId;

            SET SQL_SAFE_UPDATES = 1;
        END IF;
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
    SET __action = UPPER(__action);
    IF (ISNULL(__time)) THEN
        IF (EXISTS(SELECT _id FROM net_traces WHERE (netId = __netId) AND (DATE(_time) = CURRENT_DATE) AND (source = __source) AND (project = __project) AND (action = __action) AND (message = __message) LIMIT 1)) THEN
            SET SQL_SAFE_UPDATES = 0;

            UPDATE net_traces
            SET _time = CURRENT_TIME, eventCount = eventCount + 1
            WHERE (netId = __netId) AND (DATE(_time) = CURRENT_DATE) AND (source = __source) AND (project = __project) AND (action = __action) AND (message = __message);

            SET SQL_SAFE_UPDATES = 1;
        ELSE
            INSERT INTO net_traces (netId, source, project, action, message)
            VALUE (__netId, __source, __project, __action, __message);
        END IF;

        CALL net_realtime_register(__netId, "TRACE", __source, __project, __action, __message);
    ELSE
        INSERT INTO net_traces (_time, netId, source, project, action, message)
        VALUE (STR_TO_DATE(__time, "%Y-%m-%dT%TZ"), __netId, __source, __project, __action, __message);
    END IF;
END;%%
DELIMITER ;
# #############################################################################

# #############################################################################
DROP PROCEDURE IF EXISTS app_session_register;

DELIMITER %%
CREATE PROCEDURE app_session_register(
    IN __time VARCHAR(32),
    IN __netId VARCHAR(16),
    IN __source VARCHAR(128),
    IN __project VARCHAR(128),
    IN __action VARCHAR(64),
    IN __userId VARCHAR(64),
    IN __sessionCount INTEGER)
BEGIN
    IF (NOT ISNULL(__userId)) THEN
        SET @_context = 0;
        SET @_isFound = false;
        SET __action = UPPER(__action);

        IF (ISNULL(__sessionCount) OR (__sessionCount = 0)) THEN
            SET __sessionCount = 1;
        END IF;

        SELECT MAX(sessionCount) FROM net_sessions WHERE (netId = __netId) OR (userId = __userId) INTO @_context;
        IF (ISNULL(@_context)) THEN
            SET @_context = 1;
        END IF;

        IF (NOT ISNULL(__time) AND (__time = "")) THEN
            SET __time = null;
        END IF;

        IF (ISNULL(__action) OR (__action = "") OR (__action = "UPDATE") OR (__action = "INSTALL")) THEN
            SET __action = "START";
        END IF;

        IF (ISNULL(__time)) THEN
            IF (NOT EXISTS(SELECT _id FROM app_sessions WHERE (userId = __userId) AND (DATE(_time) = CURRENT_DATE) LIMIT 1)) THEN
                IF (__action = "START") THEN
                    IF (EXISTS(SELECT _id FROM app_sessions WHERE (userId = __userId) LIMIT 1)) THEN
                        IF (NOT EXISTS(SELECT _id FROM (SELECT _id, project FROM app_sessions WHERE (netId = __netId) OR (userId = __userId) ORDER BY _time DESC LIMIT 1) AS context WHERE (context.project = __project))) THEN
                            SET __action = "UPDATE";
                        END IF;
                    ELSE
                        SET __action = "INSTALL";
                    END IF;
                END IF;

                INSERT INTO app_sessions (netId, userId, action, source, project)
                VALUE (__netId, __userId, __action, __source, __project);

                IF (NOT ISNULL(@_context) AND NOT ISNULL(__sessionCount) AND (__sessionCount < @_context)) THEN
                    SET __sessionCount = @_context + 1;
                END IF;

                SET @_isFound = true;

                CALL net_realtime_register(__netId, "APPLICATION", __source, __project, __action, null);
            END IF;
        ELSE
            IF (NOT EXISTS(SELECT _id FROM app_sessions WHERE (userId = __userId) AND (DATE(_time) = DATE(__time)) LIMIT 1)) THEN
                IF (__action = "START") THEN
                    IF (NOT EXISTS(SELECT _id FROM app_sessions WHERE (userId = __userId) AND (DATE(_time) < DATE(__time)) LIMIT 1)) THEN
                        SET __action = "INSTALL";
                        UPDATE app_sessions SET action = "START" WHERE (userId = __userId) AND (action = "INSTALL");
                    END IF;

                    IF (EXISTS(SELECT _id FROM (SELECT _id, project FROM app_sessions WHERE (userId = __userId) AND (DATE(_time) < DATE(__time)) ORDER BY _time DESC LIMIT 1) AS context WHERE (context.project != __project))) THEN
                        SET __action = "UPDATE";
                        UPDATE app_sessions SET action = "START" WHERE (userId = __userId) AND (project = __project);
                    END IF;
                END IF;

                INSERT INTO app_sessions (_time, netId, userId, action, source, project)
                VALUE (STR_TO_DATE(__time, "%Y-%m-%dT%TZ"), __netId, __userId, __action, __source, __project);

                IF (NOT ISNULL(@_context) AND NOT ISNULL(__sessionCount) AND (__sessionCount < @_context)) THEN
                    SET __sessionCount = @_context;
                END IF;

                SET @_isFound = true;
            END IF;
        END IF;

        IF (@_isFound = true) THEN
            SET SQL_SAFE_UPDATES = 0;

            UPDATE net_sessions
            SET userId = __userId
            WHERE (netId = __netId);

            UPDATE net_sessions
            SET sessionCount = __sessionCount
            WHERE (userId = __userId);

            SET SQL_SAFE_UPDATES = 1;
        END IF;
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
        SET @_context = __rating;
        SET __action = UPPER(__action);

        IF (NOT ISNULL(__rating)) THEN
            SET __rating = 1;
            IF (@_context >= 1) THEN
                SET __rating = 1;
            END IF;
            IF (@_context >= 2) THEN
                SET __rating = 2;
            END IF;
            IF (@_context >= 3) THEN
                SET __rating = 3;
            END IF;
            IF (@_context >= 4) THEN
                SET __rating = 4;
            END IF;
            IF (@_context >= 5) THEN
                SET __rating = 5;
            END IF;
        END IF;

        IF (NOT ISNULL(__action)) THEN
            SET __action = "REVIEW";
        END IF;

        SET SQL_SAFE_UPDATES = 0;

        DELETE FROM review_sessions WHERE (user = __user) AND (source = __source) AND (project = __project) AND (action = __action) AND (message = __message) AND (url = __url);

        SET SQL_SAFE_UPDATES = 1;

        IF (ISNULL(__time)) THEN
            INSERT INTO review_sessions (netId, source, project, action, user, avatar, email, url, rating, message)
            VALUE (__netId, __source, __project, __action, __user, __avatar, __email, __url, __rating, __message);

            CALL net_realtime_register(__netId, "REVIEW", __source, __project, __action, __rating);
        ELSE
            INSERT INTO review_sessions (_time, netId, source, project, action, user, avatar, email, url, rating, message)
            VALUE (STR_TO_DATE(__time, "%Y-%m-%dT%TZ"), __netId, __source, __project, __action, __user, __avatar, __email, __url, __rating, __message);
        END IF;
    END IF;
END;%%
DELIMITER ;
# #############################################################################

# #############################################################################
DROP PROCEDURE IF EXISTS github_session_register;

DELIMITER %%
CREATE PROCEDURE github_session_register(
    IN __time VARCHAR(32),
    IN __netId VARCHAR(16),
    IN __action VARCHAR(64),
    IN __source VARCHAR(128),
    IN __project VARCHAR(128),
    IN __branch VARCHAR(128),
    IN __url VARCHAR(256),
    IN __message VARCHAR(1024))
BEGIN
    SET __action = UPPER(__action);

    IF (INSTR(__action, "DELETED") > 0) THEN
        SET __action = REPLACE(__action, "DELETED", "CREATED");
        SET SQL_SAFE_UPDATES = 0;

        DELETE FROM github_sessions
        WHERE (netId = __netId) AND (action = __action) AND (project = __project);

        SET SQL_SAFE_UPDATES = 1;
    ELSE
        IF (ISNULL(__time)) THEN
            INSERT INTO github_sessions (netId, action, source, project, branch, url, message)
            VALUE (__netId, __action, __source, __project, __branch, __url, __message);

            CALL net_realtime_register(__netId, "GITHUB", __project, __source, __action, __message);
        ELSE
            INSERT INTO github_sessions (_time, netId, action, source, project, branch, url, message)
            VALUE (STR_TO_DATE(__time, "%Y-%m-%dT%TZ"), __netId, __action, __source, __project, __branch, __url, __message);
        END IF;
    END IF;
END;%%
DELIMITER ;
# #############################################################################

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
    IN __url VARCHAR(256))
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
            INSERT INTO watch_sessions (netId, source, project, action, user, url)
            VALUE (__netId, __source, __project, __action, __user, __url);

            CALL net_realtime_register(__netId, "WATCH", __source, __project, __action, __user);
        ELSE
            INSERT INTO watch_sessions (_time, netId, source, project, action, user, url)
            VALUE (STR_TO_DATE(__time, "%Y-%m-%dT%TZ"), __netId, __source, __project, __action, __user, __url);
        END IF;
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
        DELETE FROM net_sessions WHERE (userId LIKE "TEST-%") OR (netId = "54.86.50.139");
        DELETE FROM app_sessions WHERE (userId LIKE "TEST-%");
        DELETE FROM watch_sessions WHERE (netId = "54.86.50.139");
    ELSE
        DELETE FROM net_sessions WHERE ((userId LIKE "TEST-%") OR (netId = "54.86.50.139")) AND (_time < DATE_SUB(NOW(), INTERVAL __daysIgnore DAY));
        DELETE FROM app_sessions WHERE ((userId LIKE "TEST-%")) AND (_time < DATE_SUB(NOW(), INTERVAL __daysIgnore DAY));
        DELETE FROM watch_sessions WHERE ((netId = "54.86.50.139")) AND (_time < DATE_SUB(NOW(), INTERVAL __daysIgnore DAY));
    END IF;

    SET SQL_SAFE_UPDATES = 1;
END;%%
DELIMITER ;
# #############################################################################

# #############################################################################
DROP PROCEDURE IF EXISTS service_update_session_count;

DELIMITER %%
CREATE PROCEDURE service_update_session_count(
    IN __userId varchar(64))
BEGIN
    SET SQL_SAFE_UPDATES = 0;
    SET @__count = null;
    SELECT COUNT(*) FROM app_sessions_view WHERE (userId = __userId) INTO @__count;
    if (NOT ISNULL(@__count)) THEN
        UPDATE net_sessions SET sessionCount = @__count WHERE (userId = __userId);
        #SELECT * FROM app_sessions_view WHERE (userId = __userId) ORDER BY _time ASC;
    END IF;
    SET SQL_SAFE_UPDATES = 1;
END;%%
DELIMITER ;
# #############################################################################

# #############################################################################
DROP PROCEDURE IF EXISTS service_update_app_session_user;

DELIMITER %%
CREATE PROCEDURE service_update_app_session_user(
    IN __netId varchar(16))
BEGIN
    SET SQL_SAFE_UPDATES = 0;
    SET @__userId = null;
    SELECT userId FROM app_sessions_view WHERE (netId = __netId) LIMIT 1 INTO @__userId;
    if (NOT ISNULL(@__userId)) THEN
        UPDATE net_sessions SET userId = @__userId WHERE (netId = __netId);
        CALL service_update_session_count(@__userId);
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

CALL net_crawler_register("https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.MetaOutput-2019");
CALL net_crawler_register("https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.MetaOutput-2022");
CALL net_crawler_register("https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.MetaProject");
CALL net_crawler_register("https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.MetaProject-2022");
CALL net_crawler_register("https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-AUDIO");
CALL net_crawler_register("https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-CS");
CALL net_crawler_register("https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-CSV");
CALL net_crawler_register("https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-DLL");
CALL net_crawler_register("https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-HTML");
CALL net_crawler_register("https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-INI");
CALL net_crawler_register("https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-JS");
CALL net_crawler_register("https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-JSON");
CALL net_crawler_register("https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-MD");
CALL net_crawler_register("https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-PDF");
CALL net_crawler_register("https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-PICTURE");
CALL net_crawler_register("https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-SQL");
CALL net_crawler_register("https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-TOML");
CALL net_crawler_register("https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-VB");
CALL net_crawler_register("https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-VIDEO");
CALL net_crawler_register("https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-XML");
CALL net_crawler_register("https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-YAML");
CALL net_crawler_register("https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-ZIP");
# #############################################################################
# #############################################################################




# #############################################################################
# VIEW TABLES #################################################################
SET PROFILING_HISTORY_SIZE = 100;
SET PROFILING = 1;

#SELECT * FROM net_filters LIMIT 50000;
#SELECT * FROM net_traces LIMIT 50000;
#SELECT * FROM net_traces_view LIMIT 50000;
#SELECT * FROM net_realtime LIMIT 50000;
#SELECT * FROM net_realtime_view LIMIT 50000;
#SELECT * FROM net_sessions LIMIT 50000;
#SELECT * FROM app_sessions LIMIT 50000;
#SELECT * FROM app_sessions_view LIMIT 50000;
#SELECT * FROM watch_sessions LIMIT 50000;
#SELECT * FROM watch_sessions_view LIMIT 50000;
#SELECT * FROM github_sessions LIMIT 50000;
#SELECT * FROM github_projects LIMIT 50000;

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
