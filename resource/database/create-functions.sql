# #############################################################################
# SET DEFAULT DATABASE ########################################################
#USE metaoutput_dev;
USE metaoutput;
# #############################################################################
# #############################################################################



# #############################################################################
# CREATING PROCEDURES #########################################################
# #############################################################################

# #############################################################################
# net_detector_register #######################################################
# #############################################################################
DROP PROCEDURE IF EXISTS net_detector_register;

DELIMITER %%
CREATE PROCEDURE net_detector_register(
    IN __project VARCHAR(128),
    IN __url VARCHAR(256))
BEGIN
    IF (NOT ISNULL(__url) AND NOT EXISTS(SELECT _id FROM net_detectors WHERE (url = __url))) THEN
        INSERT INTO net_detectors(project, url)
        VALUE (__project, __url);
    ELSE
        SET SQL_SAFE_UPDATES = 0;
        UPDATE net_detectors
        SET project = __project
        WHERE (url = __url);
        SET SQL_SAFE_UPDATES = 1;
    END IF;
END;%%
DELIMITER ;

# #############################################################################
# net_detector_unregister #####################################################
# #############################################################################
DROP PROCEDURE IF EXISTS net_detector_unregister;

DELIMITER %%
CREATE PROCEDURE net_detector_unregister(
    IN __url VARCHAR(256))
BEGIN
    IF (NOT ISNULL(__url) AND EXISTS(SELECT _id FROM net_detectors WHERE (url = __url))) THEN
        SET SQL_SAFE_UPDATES = 0;
        DELETE FROM net_detectors
        WHERE (url = __url);
        SET SQL_SAFE_UPDATES = 1;
    END IF;
END;%%
DELIMITER ;

# #############################################################################
# net_detector_update #########################################################
# #############################################################################
DROP PROCEDURE IF EXISTS net_detector_update;

DELIMITER %%
CREATE PROCEDURE net_detector_update(
    IN __url VARCHAR(256))
BEGIN
    IF (NOT ISNULL(__url) AND EXISTS(SELECT _id FROM net_detectors WHERE (url = __url))) THEN
        SET SQL_SAFE_UPDATES = 0;
        UPDATE net_detectors
        SET _time = CURRENT_TIMESTAMP()
        WHERE (url = __url);
        SET SQL_SAFE_UPDATES = 1;
    END IF;
END;%%
DELIMITER ;

# #############################################################################
# net_filter_register #########################################################
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
# net_filter_unregister #######################################################
# #############################################################################
DROP PROCEDURE IF EXISTS net_filter_unregister;

DELIMITER %%
CREATE PROCEDURE net_filter_unregister(
    IN __type ENUM("IP", "URL"),
    IN __value VARCHAR(256))
BEGIN
    SET __type = UPPER(__type);
    SET __value = LOWER(__value);
    SET __value = TRIM(__value);
    
    IF (NOT ISNULL(__type) AND NOT ISNULL(__value) AND EXISTS(SELECT _id FROM net_filters WHERE (type = __type) AND (value = __value))) THEN
        SET SQL_SAFE_UPDATES = 0;
        DELETE FROM net_filters
        WHERE (type = __type) AND (value = __value);
        SET SQL_SAFE_UPDATES = 1;
    END IF;
END;%%
DELIMITER ;

# #############################################################################
# net_realtime_register #######################################################
# #############################################################################
DROP PROCEDURE IF EXISTS net_realtime_register;

DELIMITER %%
CREATE PROCEDURE net_realtime_register(
    IN __netId VARCHAR(16),
    IN __channel VARCHAR(64),
    IN __source VARCHAR(128),
    IN __project VARCHAR(128),
    IN __action VARCHAR(64),
    IN __url VARCHAR(256),
    IN __message TEXT,
    IN __events INTEGER)
BEGIN
    SET SQL_SAFE_UPDATES = 0;

    DELETE FROM net_realtime WHERE _time < DATE_SUB(NOW(), INTERVAL 1 DAY);

    INSERT INTO net_realtime(netId, channel, action, project, source, url, message, events)
    VALUE (__netId, __channel, __action, __project, __source, __url, __message, __events);

    SET SQL_SAFE_UPDATES = 1;
END;%%
DELIMITER ;

# #############################################################################
# net_session_register ########################################################
# #############################################################################
DROP PROCEDURE IF EXISTS net_session_register;

DELIMITER %%
CREATE PROCEDURE net_session_register(
    IN __netId VARCHAR(16),
    IN __country VARCHAR(64),
    IN __city VARCHAR(64),
    IN __organization VARCHAR(128),
    IN __browser VARCHAR(64),
    IN __os VARCHAR(64),
    IN __resolution VARCHAR(64),
    IN __language VARCHAR(8),
    IN __ref VARCHAR(256),
    IN __campaignGroup VARCHAR(128),
    IN __campaignTerm VARCHAR(128),
    IN __campaignContent VARCHAR(128))
BEGIN
    IF (NOT ISNULL(__netId)) THEN
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

        IF (NOT ISNULL(__campaignGroup) AND (__campaignGroup = "")) THEN
            SET __campaignGroup = null;
        END IF;

        IF (NOT ISNULL(__campaignTerm) AND (__campaignTerm = "")) THEN
            SET __campaignTerm = null;
        END IF;

        IF (NOT ISNULL(__campaignContent) AND (__campaignContent = "")) THEN
            SET __campaignContent = null;
        END IF;

        IF (NOT EXISTS(SELECT _id FROM net_sessions WHERE netId = __netId LIMIT 1)) THEN
            IF (ISNULL(__campaignGroup) AND NOT ISNULL(__ref)) THEN
                SET @__context = LOWER(__ref);
                SELECT campaignGroup FROM net_campaigns WHERE @__context LIKE pattern LIMIT 1 INTO __campaignGroup;
            END IF;

            INSERT INTO net_sessions (netId, country, city, organization, browser, os, resolution, language, ref, campaignGroup, campaignTerm, campaignContent)
            VALUE (__netId, __country, __city, __organization, __browser, __os, __resolution, __language, __ref, UPPER(__campaignGroup), LOWER(__campaignTerm), LOWER(__campaignContent));
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

            IF (NOT ISNULL(__browser)) THEN
                UPDATE net_sessions
                SET browser = __browser
                WHERE netId = __netId;
            END IF;

            SET SQL_SAFE_UPDATES = 1;
        END IF;
    END IF;
END;%%
DELIMITER ;

# #############################################################################
# trace_session_register ######################################################
# #############################################################################
DROP PROCEDURE IF EXISTS trace_session_register;

DELIMITER %%
CREATE PROCEDURE trace_session_register(
    IN __time VARCHAR(32),
    IN __netId VARCHAR(16),
    IN __source VARCHAR(128),
    IN __project VARCHAR(128),
    IN __action VARCHAR(32),
    IN __message VARCHAR(1024),
    IN __stack TEXT)
BEGIN
    IF (NOT ISNULL(__message)) THEN
        SET __action = UPPER(__action);
        SET __message = REPLACE(__message, '|||', '\n');
        SET __message = REPLACE(__message, '\r\n', '\n');
        SET __message = REPLACE(__message, '\r', '\n');
        SET __message = REPLACE(__message, '\t', ' ');
        SET __message = TRIM(__message);
        SET @__index = POSITION('\n' IN __message);

        IF ((@__index > 0) AND ISNULL(__stack)) THEN
            SET __stack = SUBSTR(__message, @__index + 1, LENGTH(__message) - @__index);
        END IF;

        IF (@__index > 0) THEN
            SET __message = SUBSTR(__message, 1, @__index);
            SET __message = TRIM(__message);
        END IF;

        IF (NOT ISNULL(__stack)) THEN
            SET __stack = REPLACE(__stack, '|||', '\n');
            SET __stack = REPLACE(__stack, '\r\n', '\n');
            SET __stack = REPLACE(__stack, '\r', '\n');
            SET __stack = REPLACE(__stack, '\t', ' ');
            SET __stack = REPLACE(__stack, '\n    ', '\n');
            SET __stack = REPLACE(__stack, '\n   ', '\n');
            SET __stack = REPLACE(__stack, '\n  ', '\n');
            SET __stack = REPLACE(__stack, '\n ', '\n');
            SET __stack = TRIM(__stack);
        END IF;

        IF (ISNULL(__time)) THEN
            IF (EXISTS(SELECT _id FROM trace_sessions WHERE (netId = __netId) AND (DATE(_time) = CURRENT_DATE) AND (source = __source) AND (project = __project) AND (action = __action) AND (message = __message) AND (stack = __stack) LIMIT 1)) THEN
                SET SQL_SAFE_UPDATES = 0;
                UPDATE trace_sessions
                SET _time = CURRENT_TIMESTAMP(), eventCount = eventCount + 1
                WHERE (netId = __netId) AND (DATE(_time) = CURRENT_DATE) AND (source = __source) AND (project = __project) AND (action = __action) AND (message = __message) AND (stack = __stack);
                SET SQL_SAFE_UPDATES = 1;
            ELSE
                INSERT INTO trace_sessions (netId, source, project, action, message, stack)
                VALUE (__netId, __source, __project, __action, __message, __stack);
            END IF;

            CALL net_realtime_register(__netId, "TRACE", __source, __project, __action, null, __message, null);
        ELSE
            INSERT INTO trace_sessions (_time, netId, source, project, action, message, stack)
            VALUE (STR_TO_DATE(__time, "%Y-%m-%dT%TZ"), __netId, __source, __project, __action, __message, __stack);
        END IF;
    END IF;
END;%%
DELIMITER ;

# #############################################################################
# app_session_register ########################################################
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
    IN __events INTEGER)
BEGIN
    IF (NOT ISNULL(__userId)) THEN
        SET @_context = 0;
        SET @_isFound = false;
        SET __action = UPPER(__action);

        IF (ISNULL(__events) OR (__events = 0)) THEN
            SET __events = 1;
        END IF;

        SELECT MAX(eventCount) FROM app_sessions WHERE (userId = __userId) INTO @_context;
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

                IF (NOT ISNULL(@_context) AND NOT ISNULL(__events) AND (__events < @_context)) THEN
                    SET __events = @_context + 1;
                END IF;

                SET @_isFound = true;

                CALL net_realtime_register(__netId, "APPLICATION", __source, __project, __action, null, null, __events);
            END IF;
        ELSE
            IF (NOT EXISTS(SELECT _id FROM app_sessions WHERE (userId = __userId) AND (DATE(_time) = DATE(__time)) LIMIT 1)) THEN
                IF (__action = "START") THEN
                    IF (NOT EXISTS(SELECT _id FROM app_sessions WHERE (userId = __userId) AND (DATE(_time) < DATE(__time)) LIMIT 1)) THEN
                        SET SQL_SAFE_UPDATES = 0;
                        SET __action = "INSTALL";
                        UPDATE app_sessions
                        SET action = "START"
                        WHERE (userId = __userId) AND (action = "INSTALL");
                        SET SQL_SAFE_UPDATES = 1;
                    END IF;

                    IF (EXISTS(SELECT _id FROM (SELECT _id, project FROM app_sessions WHERE (userId = __userId) AND (DATE(_time) < DATE(__time)) ORDER BY _time DESC LIMIT 1) AS context WHERE (context.project != __project))) THEN
                        SET SQL_SAFE_UPDATES = 0;
                        SET __action = "UPDATE";
                        UPDATE app_sessions
                        SET action = "START"
                        WHERE (userId = __userId) AND (project = __project);
                        SET SQL_SAFE_UPDATES = 1;
                    END IF;
                END IF;

                INSERT INTO app_sessions (_time, netId, userId, action, source, project)
                VALUE (STR_TO_DATE(__time, "%Y-%m-%dT%TZ"), __netId, __userId, __action, __source, __project);

                IF (NOT ISNULL(@_context) AND NOT ISNULL(__events) AND (__events < @_context)) THEN
                    SET __events = @_context;
                END IF;

                SET @_isFound = true;
            END IF;
        END IF;

        IF (@_isFound = true) THEN
            SET SQL_SAFE_UPDATES = 0;
            UPDATE app_sessions
            SET eventCount = __events
            WHERE (userId = __userId);
            SET SQL_SAFE_UPDATES = 1;
        END IF;
    END IF;
END;%%
DELIMITER ;

# #############################################################################
# campaign_session_register ###################################################
# #############################################################################
DROP PROCEDURE IF EXISTS campaign_session_register;

DELIMITER %%
CREATE PROCEDURE campaign_session_register(
    IN __time VARCHAR(32),
    IN __campaignGroup VARCHAR(128),
    IN __name VARCHAR(128),
    IN __source VARCHAR(128),
    IN __medium VARCHAR(128),
    IN __description VARCHAR(256),
    IN __pattern VARCHAR(256),
    IN __logo TEXT)
BEGIN
    IF (NOT ISNULL(__name) AND NOT ISNULL(__source) AND NOT ISNULL(__medium)) THEN
        SET __name = LOWER(__name);
        SET __name = REPLACE(__name, ' ', '-');
        SET __name = REPLACE(__name, '\t', '-');
        SET __source = LOWER(__source);
        SET __source = REPLACE(__source, ' ', '-');
        SET __source = REPLACE(__source, '\t', '-');
        SET __medium = LOWER(__medium);
        SET __medium = REPLACE(__medium, ' ', '-');
        SET __medium = REPLACE(__medium, '\t', '-');

        IF (ISNULL(__time) OR (__time = "")) THEN
            SET __time = CURRENT_TIMESTAMP();
        END IF;

        IF (ISNULL(__campaignGroup) OR (NOT ISNULL(__campaignGroup) AND NOT EXISTS(SELECT _id FROM net_campaigns WHERE (name = __name) AND (source = __source) AND (medium = __medium) LIMIT 1))) THEN
            IF (ISNULL(__campaignGroup)) THEN
                SET @__context = 0;
                SELECT COUNT(_id) + 1 FROM net_campaigns WHERE source = __source INTO @__context;
                SET __campaignGroup = CONCAT(__source, "-", @__context);
                SET __campaignGroup = REPLACE(__campaignGroup, '.', '-');
                SET __campaignGroup = UPPER(__campaignGroup);
            END IF;

            IF (NOT EXISTS(SELECT _id FROM net_campaigns WHERE (name = __name) AND (source = __source) AND (medium = __medium))) THEN
                INSERT INTO net_campaigns (_time, campaignGroup, name, source, medium, description, pattern, logo)
                VALUE (__time, __campaignGroup, __name, __source, __medium, __description, __pattern, __logo);
            END IF;
        ELSE
            SET SQL_SAFE_UPDATES = 0;
            SET __campaignGroup = UPPER(__campaignGroup);

            UPDATE net_campaigns
            SET
                _time = __time,
                name = __name,
                source = __source,
                medium = __medium,
                description = __description,
                pattern = __pattern,
                logo = __logo
            WHERE (campaignGroup = __campaignGroup);

            SET SQL_SAFE_UPDATES = 1;
        END IF;
    END IF;
END;%%
DELIMITER ;

# #############################################################################
# review_session_register #####################################################
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

        DELETE FROM review_sessions
        WHERE (user = __user) AND (source = __source) AND (project = __project) AND (action = __action) AND (message = __message) AND (url = __url);

        SET SQL_SAFE_UPDATES = 1;

        IF (ISNULL(__time)) THEN
            INSERT INTO review_sessions (netId, source, project, action, user, avatar, email, url, rating, message)
            VALUE (__netId, __source, __project, __action, __user, __avatar, __email, __url, __rating, __message);

            CALL net_realtime_register(__netId, "REVIEW", __source, __project, __action, __url, __message, null);
        ELSE
            INSERT INTO review_sessions (_time, netId, source, project, action, user, avatar, email, url, rating, message)
            VALUE (STR_TO_DATE(__time, "%Y-%m-%dT%TZ"), __netId, __source, __project, __action, __user, __avatar, __email, __url, __rating, __message);
        END IF;
    END IF;
END;%%
DELIMITER ;

# #############################################################################
# dev_session_register ########################################################
# #############################################################################
DROP PROCEDURE IF EXISTS dev_session_register;

DELIMITER %%
CREATE PROCEDURE dev_session_register(
    IN __time VARCHAR(32),
    IN __netId VARCHAR(16),
    IN __source VARCHAR(128),
    IN __project VARCHAR(128),
    IN __action VARCHAR(64),
    IN __branch VARCHAR(128),
    IN __user VARCHAR(128),
    IN __avatar VARCHAR(256),
    IN __url VARCHAR(256),
    IN __message VARCHAR(1024))
BEGIN
    SET __action = UPPER(__action);

    IF (INSTR(__action, "DELETED") > 0) THEN
        SET __action = REPLACE(__action, "DELETED", "CREATED");
        SET SQL_SAFE_UPDATES = 0;

        DELETE FROM dev_sessions
        WHERE (netId = __netId) AND (action = __action) AND (user = __user) AND (source = __source) AND (project = __project);

        SET SQL_SAFE_UPDATES = 1;
    ELSE
        IF (NOT ((INSTR(__action, "CREATED") > 0) AND EXISTS(SELECT * FROM dev_sessions WHERE (netId = __netId) AND (action = __action) AND (source = __source) AND (project = __project)))) THEN
            IF (ISNULL(__time)) THEN
                INSERT INTO dev_sessions (netId, action, source, project, branch, user, avatar, url, message)
                VALUE (__netId, __action, __source, __project, __branch, __user, __avatar, __url, __message);

                CALL net_realtime_register(__netId, "DEVELOPMENT", __source, __project, __action, __url, __message, null);
            ELSE
                INSERT INTO dev_sessions (_time, netId, action, source, project, branch, user, avatar, url, message)
                VALUE (STR_TO_DATE(__time, "%Y-%m-%dT%TZ"), __netId, __action, __source, __project, __branch, __user, __avatar, __url, __message);
            END IF;
        END IF;
    END IF;
END;%%
DELIMITER ;

# #############################################################################
# watch_session_register ######################################################
# #############################################################################
DROP PROCEDURE IF EXISTS watch_session_register;

DELIMITER %%
CREATE PROCEDURE watch_session_register(
    IN __time VARCHAR(32),
    IN __netId VARCHAR(16),
    IN __source VARCHAR(128),
    IN __project VARCHAR(128),
    IN __action VARCHAR(64),
    IN __url VARCHAR(256),
    IN __events INTEGER)
BEGIN
    IF (NOT EXISTS(SELECT _id FROM net_filters WHERE (type = "URL") AND (__url LIKE value) LIMIT 1)) THEN
        SET @__isFound = null;

        IF (ISNULL(__events) OR (__events < 1)) THEN
            SET __events = 1;
        END IF;

        IF (ISNULL(__project)) THEN
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

        IF (ISNULL(__source)) THEN
            SET __source = "WEB-SITE";
        END IF;
        IF (ISNULL(__action)) THEN
            SET __action = "VIEW";
        END IF;

        SET __source = UPPER(__source);
        SET __action = UPPER(__action);

        IF (ISNULL(__time)) THEN
            IF (ISNULL(__url)) THEN
                SET @__isFound = EXISTS(SELECT _id FROM watch_sessions WHERE (netId = __netId) AND (action = __action) AND (project = __project) AND (source = __source) AND ISNULL(url) AND (_time > DATE_SUB(NOW(), INTERVAL 1 DAY)) LIMIT 1);
            ELSE
                SET @__isFound = EXISTS(SELECT _id FROM watch_sessions WHERE (netId = __netId) AND (action = __action) AND (project = __project) AND (source = __source) AND (url = __url) AND (_time > DATE_SUB(NOW(), INTERVAL 1 DAY)) LIMIT 1);
            END IF;
        ELSE
            IF (ISNULL(__url)) THEN
                SET @__isFound = EXISTS(SELECT _id FROM watch_sessions WHERE (netId = __netId) AND (action = __action) AND (project = __project) AND (source = __source) AND ISNULL(url) AND (DATE(_time) = DATE(__time)) LIMIT 1);
            ELSE
                SET @__isFound = EXISTS(SELECT _id FROM watch_sessions WHERE (netId = __netId) AND (action = __action) AND (project = __project) AND (source = __source) AND (url = __url) AND (DATE(_time) = DATE(__time)) LIMIT 1);
            END IF;

        END IF;

        IF (@__isFound) THEN
            SET SQL_SAFE_UPDATES = 0;
            
            IF (ISNULL(__time)) THEN
                IF (ISNULL(__url)) THEN
                    UPDATE watch_sessions
                    SET
                        _time = CURRENT_TIMESTAMP(),
                        eventCount = eventCount + __events
                    WHERE (netId = __netId) AND (action = __action) AND (project = __project) AND (source = __source) AND ISNULL(url) AND (_time > DATE_SUB(NOW(), INTERVAL 1 DAY));
                ELSE
                    UPDATE watch_sessions
                    SET
                        _time = CURRENT_TIMESTAMP(),
                        eventCount = eventCount + __events
                    WHERE (netId = __netId) AND (action = __action) AND (project = __project) AND (source = __source) AND (url = __url) AND (_time > DATE_SUB(NOW(), INTERVAL 1 DAY));
                END IF;
            ELSE
                IF (ISNULL(__url)) THEN
                    UPDATE watch_sessions
                    SET
                        _time = __time,
                        eventCount = eventCount + __events
                    WHERE (netId = __netId) AND (action = __action) AND (project = __project) AND (source = __source) AND ISNULL(url) AND (DATE(_time) = DATE(__time));
                ELSE
                    UPDATE watch_sessions
                    SET
                        _time = __time,
                        eventCount = eventCount + __events
                    WHERE (netId = __netId) AND (action = __action) AND (project = __project) AND (source = __source) AND (url = __url) AND (DATE(_time) = DATE(__time));
                END IF;
            END IF;

            SET SQL_SAFE_UPDATES = 1;
        ELSE
            IF (ISNULL(__time)) THEN
                INSERT INTO watch_sessions (netId, source, project, action, url, eventCount)
                VALUE (__netId, __source, __project, __action, __url, __events);

                CALL net_realtime_register(__netId, "WATCH", __source, __project, __action, __url, null, __events);
            ELSE
                INSERT INTO watch_sessions (_time, netId, source, project, action, url, eventCount)
                VALUE (STR_TO_DATE(__time, "%Y-%m-%dT%TZ"), __netId, __source, __project, __action, __url, __events);
            END IF;
        END IF;
    END IF;
END;%%
DELIMITER ;

# #############################################################################
# service_cleanup_debug #######################################################
# #############################################################################
DROP PROCEDURE IF EXISTS service_cleanup_debug;

DELIMITER %%
CREATE PROCEDURE service_cleanup_debug(
    IN __daysIgnore INTEGER)
BEGIN
    SET SQL_SAFE_UPDATES = 0;

    IF ISNULL(__daysIgnore) THEN
        DELETE FROM net_sessions WHERE (netId LIKE "%TEST-%");
        DELETE FROM app_sessions WHERE (netId LIKE "%TEST-%") OR (userId LIKE "TEST-%");
        DELETE FROM dev_sessions WHERE (netId LIKE "%TEST-%");
        DELETE FROM review_sessions WHERE (netId LIKE "%TEST-%");
        DELETE FROM trace_sessions WHERE (netId LIKE "%TEST-%");
        DELETE FROM watch_sessions WHERE (netId LIKE "%TEST-%");
    ELSE
        DELETE FROM net_sessions WHERE ((netId LIKE "%TEST-%")) AND (_time < DATE_SUB(NOW(), INTERVAL __daysIgnore DAY));
        DELETE FROM app_sessions WHERE ((netId LIKE "%TEST-%") OR (userId LIKE "TEST-%")) AND (_time < DATE_SUB(NOW(), INTERVAL __daysIgnore DAY));
        DELETE FROM dev_sessions WHERE ((netId LIKE "%TEST-%")) AND (_time < DATE_SUB(NOW(), INTERVAL __daysIgnore DAY));
        DELETE FROM review_sessions WHERE ((netId LIKE "%TEST-%")) AND (_time < DATE_SUB(NOW(), INTERVAL __daysIgnore DAY));
        DELETE FROM trace_sessions WHERE ((netId LIKE "%TEST-%")) AND (_time < DATE_SUB(NOW(), INTERVAL __daysIgnore DAY));
        DELETE FROM watch_sessions WHERE ((netId LIKE "%TEST-%")) AND (_time < DATE_SUB(NOW(), INTERVAL __daysIgnore DAY));
    END IF;

    SET SQL_SAFE_UPDATES = 1;
END;%%
DELIMITER ;

# #############################################################################
# service_update_session_count ################################################
# #############################################################################
DROP PROCEDURE IF EXISTS service_update_session_count;

DELIMITER %%
CREATE PROCEDURE service_update_session_count(
    IN __userId varchar(64))
BEGIN
    SET SQL_SAFE_UPDATES = 0;
    SET @__count = null;
    SELECT COUNT(*) FROM app_sessions WHERE (userId = __userId) INTO @__count;
    if (NOT ISNULL(@__count)) THEN
        UPDATE app_sessions SET eventCount = @__count WHERE (userId = __userId);
        #SELECT * FROM app_sessions WHERE (userId = __userId) ORDER BY _time ASC;
    END IF;
    SET SQL_SAFE_UPDATES = 1;
END;%%
DELIMITER ;

# #############################################################################
# service_find_repeated_messages ##############################################
# #############################################################################
DROP PROCEDURE IF EXISTS service_find_repeated_messages;

DELIMITER %%
CREATE PROCEDURE service_find_repeated_messages()
BEGIN
    SELECT *
    FROM app_sessions
    GROUP BY netId, userId, DATE(_time), source, project
    HAVING COUNT(userId) > 1
    ORDER BY _time, userId;
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

CALL campaign_session_register(null, "INSTALL-MANUALLY", "install-manually", "unknown", "organic", "Install application from manually by user from unknown source.", null, "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAQAAAAEABAMAAACuXLVVAAAABGdBTUEAALGPC/xhBQAAAAFzUkdCAK7OHOkAAAAPUExURUdwTHWc2V6M0vL2+1CBzI+rpH4AAAAEdFJOUwCL0xNwWEX5AAADOklEQVR42u3aa3LbIBSGYYG7ANphAeqMFmApXkCw2P+a2jRpY3ERtwMnU3/nV34Q58lrx5HA04TBYDAYDAaDwWAwX2vWH7ZsXsOP8+1hScGPv2hrOQGXxfICyn9/WsBmeQEXywy4MQPqAhACbsyAygB0AMENuDEDat4EaQGWGSC5ATdugOYGLNwACwAAACQfsmwAAAAAAAAAAAAAAAAAAAAAAGA84Hsu4NIHIKzKBGjVBaCtyQMIZyER4G2vXWUBtLOQCPC2z2lyAMJdSAN4P2xQGQDtLqQBvG/0mjRAeAtJAOvHd6okQHsLSQB/d7pNCiD8hRSAz+MmlQBofyEF4HOr35wDRGAhAeDxvE2dAnRgIQHg8azDnAFEaGE74HjgqE4AOrSwHXA87DFxgAgubAaszua1igJ0cGEzwD1uMzGAeza8EwG8E08VAWjbp0AkgQcQ4VIEgHACD5AI0PI+EEzgAlIBWgDBBC4gFaDpf0EogQNIBmgChBI4gGSAtuuBQIIjIB2gDRBIcASkAzReE/oJDoCMAI0AP8EBkBGg9b7AS/AIWDMCtAK8BEvk61iA5nvDgo8Cdrk3LPkYUJ+74/wEptMGRfZHsVSvLZqtKQABIDOB6rdJtbUEoABkJVA9t+m2hgAkgIwEqu9G5VYfgAaQTKB6b9Vu1QGIAIkEqv9mtawNQAU4TaBGbNfLygBkgJMEasyBhawLQHhislQFIATIqgCUZ0ZLTQBKgKwJQHpqtlQEIAXIigC054Z+gnksQJYHID45XYoDEAOcBPdpNMBJMI8HyNIA5KfnS2EAcoAsDEAOeEgw8wBkWQB6wL8EMxdAFgXoAPhIMPMBZEmAHoA/CWZOgCwI0AXwO8HMC5D5AfoAJsUN8Cb++SYAAAAAAAAAAAAAAAAAAAAAAAAAgK8EGDVPD7g/PcD4+7qsAD0csHMDXuPvEGPG2cYVwwHXI+DC/Fc4/kWwB443OF8C0/TC/AyMfg52HyA4/waGJ9hDVyuCOcDIBHv4gm3Ym5G5RgCDnoT7NXrRug75+WeniWv/18HPK8ElffF/e+p7CgAAAAAAAAAAAAAAAHhOAAaDwWAwGAwGg/lv5xeRId86xeaS1wAAAABJRU5ErkJggg==");
CALL campaign_session_register(null, "BING", "search-request", "bing.com", "organic", "Search request by Bing search engine.", "%bing.com%", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAQAAAAEABAMAAACuXLVVAAAAGFBMVEVHcEwQjoEAiHoAiXsAinsAiXsAiXsAiHph873pAAAAB3RSTlMAbB/sx5pDpNAp1QAABHRJREFUeNrtmkFvGjEQhQcEnFGIwnUrgnqmKuw5SGWvlEjhSmnSnClQ//2SkEJgzXo89niqdt4tAmU+Fr/nsQcAlUqlUqlUKpXqL9UPaYDucCkMYNZfM1kAYz5fCQOY9d1CFsCYzYMwgDFflsIAZv2QyQIYM7wSBtgtxkwWYOfIG2GA3WJcCAOkdmQZIPFitAEk3R6sACm3hwsAZqUACqAACqAACqAACqAACqAACqAACqAACqAACqAACvD2en8pDNDgvrZ1AdS4r22da6DY/cE51XMCdPczhEwMoMc8Q3AC1JgHWk6Aes47y3EH0fzdLGcpAdDjneW4AZq8sxw3QOvslcihgNiMitJgMUsL8Mw6WEQANCyDxXihgACo2V7f3KQDKC2CqD+5wABceE+cUMAA9C68J0ooYACa5qLCf22AATjuR5bFGBoKqK54bioUGAoogI9VAIGhgAJommqFhAIKoGVcoocC7mRUOAnIoYADeDZuEUMBB9BAABB/FIgDqBmUKKGAPB3nOAJCKCABukgA/1BAAvQMWp6hgARoGg957VBIgHruQ/CJ4YpmLg3wLA3QkAZoSQMg9iNmgK40QEMaoCYN4BNFLAA+i4AHoCcN0JQGqBfCANC6FwaA+r0wANQ7wgAA19IA8CgNAE/SAPCUCwNAPxcGgFohDOAkYAeAViEM4IjlBADVsZwCAOrXwgBVTWISgConpACo9EEKFxT/dw605rJJ6GzNmAHcrSEvAKIxZAXANKasAB3hlgzVFjMCoJpiRgBcfT6AJyMLgK1vfvIAuNtx3ieAr8/zBDzqR3kC0/MGyOe+PsITWPkehk40CgZYt0PqRwAYeTVAJf0KBdgsguqHP4FxWP1tFgiwOfkH9bln/Y3XBLfrsiD6bu7SAvYH2AbVN7PgyWmbcDN41CR4djwIqj8IHl6vF973klQD2AFGIfX9DGAFeG/BR8NrACvAOKC+rwFsAFtCA0Y2gA3gmEF9w24AC8CK1ABRDVAGOC4i//oEA5QBDhb8kKcwQAng8CH865MMUAIY0xowsgHOAf5kEKH+AGIATIkNkDHDLAbAllyfaoAzgDbqBi6mAU4BBrQGcFd/BjEA9m2AfwMWYoATgBG1/h1EAXi1oH8DFmaA9wBj7A1c5RGCDvC6k10T6rchDsCUVj/QAEeAFakBC9iBzgBekoRSfwKRAEaUBnAXXVkkgF0G9Qn1t1HqvwCMCQ1Y4A50ArDJKPXXbYgFMCU0YHEMsAfYkupPIBrA14JiAIgHUMgZ4FW3Rs4Ae83lDPDWhOZiBiAegycQWx0pAxyuwgohAxzUlDKA/21QZAP430fPgEnIidAE2HQrZAAvLw4zTgD3qZzJAOhA5DIA+kuYcdd3BOIE+FXlxQGk0KOQAdzNCbcBXM3Jpg2p1Oc6hAd5cZKwvi0Q7yCpmlIGOOi7kAEuNCcJDWANxKQGsDUnYxBRR8SAFi8OMiGAt0DcitXffwnpDXjqxXUbJFXLZyCrb6BSqVQqlUqlUv1r+g3c9qr2RVGhSAAAAABJRU5ErkJggg==");
CALL campaign_session_register(null, "GOOGLE", "search-request", "google.com", "organic", "Search request by Google search engine.", "%google.com%", "data:image/png;base64,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");
CALL campaign_session_register(null, "GOOGLE-ADS", "search-request", "google-ads", "cpc", "Payed search request by Google Ads.", "%googleads.g.doubleclick.net%", "data:image/png;base64,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");
CALL campaign_session_register(null, "DUCKDUCKGO", "search-request", "duckduckgo.com", "organic", "Search request by DuckDuckGo search engine.", "%duckduckgo.com%", "data:image/png;base64,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");
CALL campaign_session_register(null, "YAHOO", "search-request", "yahoo.com", "organic", "Search request by Yahoo search engine.", "%yahoo.com%", "data:image/png;base64,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");
CALL campaign_session_register(null, "YANDEX", "search-request", "yandex.ru", "organic", "Search request by Yandex search engine.", "%yandex.ru%", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAQAAAAEABAMAAACuXLVVAAAABGdBTUEAALGPC/xhBQAAAAFzUkdCAK7OHOkAAAASUExURUdwTPw/Hf/////Z0v1sUv6ml0mlb8kAAAABdFJOUwBA5thmAAAC5klEQVR42u3a0XHiQBCEYV8GxwoFYHwXAMrAZGDlH4wfRYnVbu9Mc3ad/3lW4Q8z6hZCLy8MwzAMwzAMwzAM873m1+np8xsAAAAAAAAAAAAAAAAAAAAAAAAAAAAAQoDpsk3r1ct22Kv3P3AH+GgA1u2wqxew9N/azmnegdv2yn+O//55O+rNDNCWYBKYQcDde7u8n4T/09V9Gi7Ca98f9OEGSEugfE5RQBH2a96O+WsHzMK7K8q5Go5iIYpWZU/CgLX/9hblTAkDSvcDVmIoAehH0SSlZbyOu1F0k/oiDuj20SI1ZhzQjSLtmiEOmDo7JsVQBtDro6JdMiSuCS/tnFGqMAfobLlU2ClAu4+0GEoB2n2kxVDue0Gzj8QdTAGafaTFUA7Q7CPxq0sK0OojMYaS3w0bZ5q6AjlA49JYjKEkoNFHixZDScBxH6kxlAQc95EaQ9kbFId9JO9gEnDYR6sYQ1nAYRSpMZQFHPXRLO9g9ibVQR9N8gpkAQd9JMdQGlDqp5scQ2lAvY/O+g5mAfUo0mMof6e02kd6DOUB1T7SYygPqPbRwAqkAbV906vQcbe80kdlYAfzgEoUDcSQAVDpo4EYMgAqfTSyg4ZfTB76aFKvyE2AhyUYiSEH4CGKRmLIAXiIoqEVMAD2fTQUQ5af7XZ9NFKFHsBuCYZiyALYLcFQDFkAuz4a20HLT7eXofPuCYB1KHmeAChD2fsEwDz4sdsB6k3R5wGWxBJYAGUs/PyAaSz+/YBzYgk8z5AsY/nvB9ziW+gBJJbAA0hEkek5ongfmQDxPjIB4lFkAsSXwPUsWTiKXIBwFLkA4ShyAaboVZELcI5uoe2BxiW4hTbALZiFNkAJbqENMH814BQ8DXyANXZJ4AOU2HnoA0xfDZhjQWB8sjoWBP8n4PrjAa8AAAAAAAAAAAAAAAAAAADADwXEBgAAAAAAAAAAAAAAAAAAAAAA4JsDGIZhGIZhGIZhGObfzydnxauloG5qlgAAAABJRU5ErkJggg==");
CALL campaign_session_register(null, "HABR", "read-article", "habr.com", "referral", "Read article from Habr IT resource.", "%habr.com%", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAQAAAAEABAMAAACuXLVVAAAAD1BMVEVHcEx6oLJ5oLF6oLH///9pDujsAAAAA3RSTlMAlUJukpo9AAABGUlEQVR42u3duxGCQBiFUR8NONIAagPi2oH2X5Opka4z/F4cz5cacIaVgOSyWkmSJEmSpGV2HNrMTcdPrn9oBe37r79uJe16r79pRY2dgKEKMEUPoP8QhjrAFL4BfbfgVAm4dABaaeET6DmDUy3gknwGup6DTStuXDpgXQ149y/cVgPOAAAAAAAAAAAAAAAAAAAAPwy43p+6ffYrAAAAAAAAAAAAAAAAAAAAAAAAwPyA1wEAAAAAAAAAAAD8A8B7AQAAAAAAAAAAAAAAAAAAAABAAjBPAAAAAAAAAAAAAAAAAAAAiwfEJyKtdMaHUvNTsfGx3PhccH4wOT4ZHR/Nzs+Gx4fT89Px8fH8/OcD8h9QkCRJkiRJX+wBbr1GnhjByRkAAAAASUVORK5CYII=");
CALL campaign_session_register(null, "GITHUB", "view-github", "github.com", "referral", "View project related with MetaOutput on GitHub web site.", "%github.com%", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAQAAAAEABAMAAACuXLVVAAAABGdBTUEAALGPC/xhBQAAAAFzUkdCAK7OHOkAAAAnUExURUdwTAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH6NKgYAAAAMdFJOUwAN8uEhazhQzLSDnHZ9v+QAAAjeSURBVHja7VxLU1RHFJ5bNTNWcMNU8YjMbih0gFkxURFmgWXkIRs0Jhh0gUoQyw3iM5hNhKAoG3wSYSFEakziQiUatFjdKUtg+kcFGXHu49zuPqf7DpWq+y2pmtsfp0+fx9ePUChAgAABAgQIECBAgAAB/q8wYh19v48lGEs0zy5ejZWXePSKjpMzt9OJjfGZmahN3558c/Vg6TjE2kdnmlLMBrN2MjtQIgrto/cYiPrsQAmGrxi9zzxxIHvQ78k/vJxhHOTuXvZ1HsI3xpgAzdk2/8aP/plhQuSe9Ps1fvUSk4HZetGf6a+8ySRRf9QX95Men7Hkcf2ueHiKMQwD7ePPMRTWNDOovseQqNfqidElhkarxtUY/oMRcEdfRPo5RSFgPtY1/hHS+BsMnmlywClGxJoWRwwvMDLqdLjBeaaAt+rj75hSIbA2rJwCvmNK2KuaFLpTagTMfxRD4BxTxJpaQLzOlDGhFAIy6gRyCsHAOMY0YD/dDytTOgjkjm6vARSWoh4DbCzFo9trALIJdBlgwwt6ttcAjO0hZaGUPgImJSddYhqxj5AFpnQSWMVnhC6d4zPzAdoFV7QSYI3YlRhJ6SVg9mynC26mpO10QYIbdtt/nU6nE0iTb/zE/pdXKBd84WBvtJ+cQXiFOflmoLzKbsUPqChor4TWP7lw1Y9NsuPXPjzt/i9ymDnYBYVyY1RSpElmC2vOkUymEQTs3Nn4lkxyX0qa2BJHOu1/byDPQNF/Ou4hxg/FGXUOujyDSLWwT7B0xM5gJh+Oj3lTF4llq8e9DbmXGoXWrE32kc9fTaSbZxd7rw0OnrvS925sK0zYNInwFDEWxZ1WtSYSY1OvaZ5cHChu08Ri7X0zTS5VxnDO1zwxDzSU2xWrxIH3V13JzTj391iixSZIGAu0fBB2Eq9zrJHFy/APO/qGub7E8nI52VUMkkrKTxhxVsfDtFpoP5WAK6dLBUNjRENFWcBZUnnucgGNBNZknCDC/CPAZJzgaz8JTBNcVysBCScw5ph/q0DGCaIZPwlIpOSdgOJLJQD01y+FPxpy/6iBKLEYgMw9TmG9RiUwR7Am9KNVougeBoqXetE/swOQJiVziNy3RF5YBrQf5lMaAdK3OqFCb5pGAJQYHqCXLkVd4BAQBZUXzF8fYOvYXIwpp52AdlsEaxoibc5TCdSk0OaMQJzJe2+gPXtQLYFSNobysUioGNIXBTbnAL2F8wsQiBU23qBg/BEhzah1BR6pbR3rNdMqBHa5v8dtj4ByyBxWIQDonTneotqhcxF6mNTk5cNKN4EPKuOHjFO4QBDXvPEZMoZwgaATGzfQYofAqw+pq9xiL/wG1RURtjpEqvc+VNxQWwTgMqhDlSP5cjUCwM4LTzGd09cVeRs1X5rGlNOgcghM6SwGvEoCTnoFsue4KoFOTKPlzkXUipxXm3NWNlCSvlIl0I0pS90ETGUCcQwBd9z0gwAnugME5ktKoMwHAjWYMruMlcICDEXgVUCgpAR2slJEQo5WWIZXVCgEMFPgRzLCEZhQJTCEIpAqRT2AI+BDRYTKBX7UhDgCVKX8CxYwZ+uAgsSHshxVkPjRmHAIAPqED60Z55NAVUyVaTlG5VTFQF/AnqoRKMPJbnOl0Ac4nVFopRQKSR4n1n9UswCgETXgdEW1QBBewSmfZ/RtmXmuQm5+O4SW1wUAdD9uidGpb8fKU6rlfhDaLtitQgCYU+5pIshieRUC2C2TKCPsdfK+B21d9iOdVmLH3RNfMeSygpatSlU2wpCBBRK3de+afUBT1rtvKNgC6mQ65wA8nj2OzZ70OQBnQJDf4TPtxJqgm3DKPQpteBNrc2OBcMbcmNN3UQh0QeGJGPiCaV25LgMIjzefhQ+rz+sygLDb3eVxQwO9EMIed0RE2d3rascj5CQY54lXPeBlgL+zV5khXrTwvF3TiMrK0dfk2zaeN8xaEG4Q9byuLz4MYM0G9nsld6RfWal47nn4Xay6FZu53Oxfy9ZbHead03LjVz33vI4icR6k6IW3YrHYT9YbDWbrZRn/71jyvg4jU9+t2Eox++MTSfFjNxUneTdRZCrcM/bEXWkrE827Pxzk+HGsYpR/G0hG9ftSEtQX3P58ynGFKDsAczC+Hey7L7iMJJPYvxyuNx95lBXJJ72AO1b3vRNeRDJlgkkxFK1e9Kwr5iXLD1KrXSxMW9s80kq+TbYAo7R5cac80iUnmwyJCcjVdhZha3UYVLrgs0XiO5KSXZ41H02Ayg08lYZwDtYlc/qQM3t2yTUKwluasoKXRbUv7Bk55+ClfCtKOpFj9edCRf5C6niZyAnkG5xLTqm2S0rqDGf4BORbvLgzgdtF5DxGDyHtQVoLwzr3Gt+DUCWJwvspp6Bhe49kN0aSou3+xF2a0oWURIN9SEMYdGtFvxaizAmJNol7YR4nuY641Orw50LPbH5bjlIXaIdjLY3dVjsbvjGTTqdvP+E8rFLDWwO4zsYSi4pFRPuV73u5bzDWaIlCznxgyuuEEQ15AMjJEzoIoDe/LPKC/JYFh0ALWuKIy2y1ShMgHAWxlBcT6gTq0QawdqnSIcSbAOUghiUaPlAlQNt4KlYFsg9bRXStQddKlFSIKnWtQZcJcs+ULEBVuy0mkHvwMaLXALba8MBx+hTQt1ys5Xjy3y1Prm7DWWCVbAB7KWgm3/cODl7rm2nqwVlAZf89CsotOAJqp1C6UqoEFM/jhV+rEmhUMgCs+WII5FQf7jWuqxG4FVIF8EQigkC+X5kA8EyqPAH1U8HgJDyVropvhXQgvCRrAeeppdY2LQRCzseqZS2Q1PZ09YWMHAG7BXJvdY3/+f0ZpAXMx+XaCITCJ/AEfmsLaYRtE0iKQEt/SCuqXuMINJ4OaUbVEoZAq/bxrQzEBPwYf8MPllOCQBTZ2l7rD/mCaOFtNm+5rSDv1T70afxPKs1N7mGCzYc9i9WrDzAOL6cnOQG2ciZ914eH+20M3mU5Axg3Zv0dP0CAAAECBAgQIECAAAECBPAB/wHZfPILYu7GFAAAAABJRU5ErkJggg==");
CALL campaign_session_register(null, "VISUAL-STUDIO-MARKETPLACE", "view-extension", "marketplace.visualstudio.com", "referral", "View information about extension in Visual Studio Marketplace.", "%marketplace.visualstudio.com%", "data:image/png;base64,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");
CALL campaign_session_register(null, "YOUTUBE", "view-video", "youtube.com", "organic", "View video on YouTube.", "%youtube.com%", "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAQAAAAEABAMAAACuXLVVAAAABGdBTUEAALGPC/xhBQAAAAFzUkdCAK7OHOkAAAAqUExURUdwTM0gH84iIc0gH84hIM0gH80gHtleXe7OzeWfn80gH////+ng4Pns7PpP7nkAAAAKdFJOUwCcwnfhTijM7Nz0C+NIAAAD90lEQVR42u2cMW/aQBSASSkMnTBRl0zBYmIyRV0yRQh18FQpIkMmVBWGzJkyZmGP8gMCOBnuFyRymJNK3jMk/S+1DUMX2/fu3rtHpPdNSCC9T/fOd+fj3tVqgiAIgiAIgiAIgiAIgiAIgiAIgvBRmM1m4/F4MBh4GZ2On9PtDoebT+12/kX6g/Rn6Y+Rok7Hg77nd0fKgGjoe/uD8amhy7Tf7iokhp39U2D4k55CJvoKCN88UAQsfurGb/QUCUtNgyZR/DQNegYHioyFTvxfipAfGgkIKQVUdRLOSOOru8oGUMRUNcFvaoGqJgipBaLy+HVFTlAqcE4vcFwq0KMXKB2MGsoBkxKBPRcCAW8XKO8ERy4E7jhHgXxZwDgOV/XCuhuB4l74yY1Aq1DgixuBW661QPVjcORGYMWxHNV7DkM3AqpQwFH8woGg6UrgJ+dkXDYQ1F0JHHKuBsomZGcCRUPhZ1cC99wCd7xzUbHAuSuBFe9kWPxqwC6gPxtbzlpL69l4bmcQWQu8PZMI6L+ZvsVzigUBRGA9ZxaIn67wBUKIQPxuYTDBEIiTa2wBBRNYJzfIazKgQPxkbIAkEL+bGgS2i+KtQJwkF7wC6yS5xBNowAXSbmBkgCeQdoOXS1aBtBsYGAS27yX/CaTd4KXHKZAmAW6AKpAZ/Ak5BdIkQA1wBQwMWrgCWRJgBsgtsDF4tm6BPXOBLAkQA+wUbA3mfC2wSYK+AYEAzIBCIE9CcsUnsDW44RPYJEHPgEYAYEAkkCdBa3VAJJAt0PRWaFQC2uv0QyqB+IbxMQTEJxO4VrwCV5aTUd1SALBfQNICkD0bihYA7RkRCMD2rPAFgPuG6ALQfUtsgVfWd0OD+AUt0DAUgMfHbYHXEEvArAUeTXbuEQWM4iMKmMXH26YzjI8m8NhTrAIPpvGLThIBBczj4wg8XCpWAZv4Rdv1IUDgySY+gsDaKr79f0Z/7eIXCej36gu7+Pb/G6oPLmD/57Uly10VOHIlsNhVgTNXAivuYzw7e5DJmQD7WbJb3oPVO3CekP1EJfuZ0hb3qdqA+1zxhPtkNWeZU9ls7GxBsOAucFhxl3jccxe5HHOX+bR2t9DJzXMYcRe7LbjL/e65Cx4POcueS3YnnPXCiLvst7z0eo+3Czgp/Z7UeHNQVfxOvi4Mqi4gIB4MV9V3gDAOAg6uQNC4BIM0CcvJh7gIhegqmjR+UNOk+Y2k/bUvw8mehTb2kBjtT2owpv0ujsTI9wbfT6Hht7mYnvQ93x+ZmIyGeWCky6lqzdl0cydW3/Pavu8PRznhRi1KP+a3Y3U6XnYrFtadWIIgCIIgCIIgCIIgCIIgCIIgCILggn/JJFu5AinihQAAAABJRU5ErkJggg==");
CALL campaign_session_register(null, "METAOUTPUT", "view-site", "metaoutput.net", "organic", "View MetaOutput web site.", "%metaoutput.net%", "data:image/png;base64,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");

CALL net_detector_register("MetaOutput", "https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.MetaOutput-2019");
CALL net_detector_register("MetaOutput", "https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.MetaOutput-2022");
CALL net_detector_register("MetaProject", "https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.MetaProject");
CALL net_detector_register("MetaProject", "https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.MetaProject-2022");
CALL net_detector_register("Preview-AUDIO", "https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-AUDIO");
CALL net_detector_register("Preview-CS", "https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-CS");
CALL net_detector_register("Preview-CSV", "https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-CSV");
CALL net_detector_register("Preview-DLL", "https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-DLL");
CALL net_detector_register("Preview-HTML", "https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-HTML");
CALL net_detector_register("Preview-INI", "https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-INI");
CALL net_detector_register("Preview-JS", "https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-JS");
CALL net_detector_register("Preview-JSON", "https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-JSON");
CALL net_detector_register("Preview-MD", "https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-MD");
CALL net_detector_register("Preview-PDF", "https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-PDF");
CALL net_detector_register("Preview-PICTURE", "https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-PICTURE");
CALL net_detector_register("Preview-SQL", "https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-SQL");
CALL net_detector_register("Preview-TOML", "https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-TOML");
CALL net_detector_register("Preview-VB", "https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-VB");
CALL net_detector_register("Preview-VIDEO", "https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-VIDEO");
CALL net_detector_register("Preview-XML", "https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-XML");
CALL net_detector_register("Preview-YAML", "https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-YAML");
CALL net_detector_register("Preview-ZIP", "https://marketplace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-ZIP");
CALL net_detector_register("Preview-CPP", "https://marketplace.visualstudio.com/items?itemName=NesviatypaskhaOleksii.Preview-cpp");
CALL net_detector_register("MetaOutput.Client", "https://www.nuget.org/packages/MetaOutput.Client");
CALL net_detector_register("MetaOutput.Media", "https://www.nuget.org/packages/MetaOutput.Media");
CALL net_detector_register("MetaPlatform", "https://www.nuget.org/packages/MetaPlatform");
# #############################################################################
# #############################################################################




# #############################################################################
# VIEW TABLES #################################################################
SET PROFILING_HISTORY_SIZE = 100;
SET PROFILING = 1;

#SELECT * FROM net_filters LIMIT 50000;
#SELECT * FROM trace_sessions LIMIT 50000;
#SELECT * FROM trace_sessions_view LIMIT 50000;
#SELECT * FROM net_realtime LIMIT 50000;
#SELECT * FROM net_realtime_view LIMIT 50000;
#SELECT * FROM net_sessions LIMIT 50000;
#SELECT * FROM app_sessions LIMIT 50000;
#SELECT * FROM app_sessions_view LIMIT 50000;
#SELECT * FROM watch_sessions LIMIT 50000;
#SELECT * FROM watch_sessions_view LIMIT 50000;
#SELECT * FROM dev_sessions LIMIT 50000;
#SELECT * FROM dev_projects LIMIT 50000;

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
