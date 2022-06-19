# #############################################################################
# CREATING DATABASE ###########################################################
#CREATE DATABASE IF NOT EXISTS metaoutput_dev;
CREATE DATABASE IF NOT EXISTS metaoutput;
# #############################################################################
# #############################################################################




# #############################################################################
# SET DEFAULT DATABASE ########################################################
#USE metaoutput_dev;
USE metaoutput;
SET time_zone = "Europe/Kiev";
SET character_set_client = "UTF8MB4";
SET character_set_results = "UTF8MB4";
# #############################################################################
# #############################################################################




# #############################################################################
# DROPPING TABLES #############################################################
#DROP TABLE IF EXISTS net_crawlers;
#DROP TABLE IF EXISTS net_filters;
#DROP TABLE IF EXISTS net_sessions;
#DROP TABLE IF EXISTS review_sessions;
#DROP TABLE IF EXISTS net_traces;
#DROP TABLE IF EXISTS net_realtime;
#DROP TABLE IF EXISTS app_sessions;
#DROP TABLE IF EXISTS dev_sessions;
#DROP TABLE IF EXISTS watch_sessions;

DROP VIEW IF EXISTS net_traces_view;
DROP VIEW IF EXISTS net_realtime_view;
DROP VIEW IF EXISTS review_sessions_view;
DROP VIEW IF EXISTS app_sessions_view;
DROP VIEW IF EXISTS watch_sessions_view;
DROP VIEW IF EXISTS dev_sessions_view;
# #############################################################################
# #############################################################################




# #############################################################################
# CREATING TABLES #############################################################

CREATE TABLE net_crawlers(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    _time TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    url VARCHAR(256) NOT NULL UNIQUE,
    downloads INTEGER,
    reviews INTEGER
);

CREATE TABLE net_filters(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    type ENUM("IP", "URL") NOT NULL,
    value VARCHAR(256) NOT NULL UNIQUE
);

CREATE INDEX metaoutput_net_filters ON net_filters(type, value);

CREATE TABLE net_sessions(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    _time TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    netId VARCHAR(16) NOT NULL,
    userId VARCHAR(64),
    country VARCHAR(64),
    city VARCHAR(64),
    organization VARCHAR(128),
    browser VARCHAR(64),
    os VARCHAR(64),
    resolution VARCHAR(64),
    language VARCHAR(8),
    ref VARCHAR(256),
    campaignName VARCHAR(64),
    campaignSource VARCHAR(64),
    campaignMedium VARCHAR(64),
    campaignTerm VARCHAR(128),
    campaignContent VARCHAR(128),
    sessionCount INTEGER
);

CREATE INDEX metaoutput_net_sessions ON net_sessions(netId, userId);

CREATE TABLE review_sessions(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    _time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    netId VARCHAR(16) NOT NULL,
    action VARCHAR(32),
    source VARCHAR(128),
    project VARCHAR(128),
    user VARCHAR(256),
    avatar VARCHAR(256),
    email VARCHAR(256),
    url VARCHAR(256),
    rating INTEGER,
    message VARCHAR(1024)
);

CREATE INDEX metaoutput_review_sessions ON review_sessions(netId);

CREATE VIEW review_sessions_view AS
SELECT
    review_sessions._id,
    review_sessions._time,
    review_sessions.netId,
    review_sessions.action,
    review_sessions.source,
    review_sessions.project,
    review_sessions.user,
    review_sessions.avatar,
    review_sessions.email,
    review_sessions.url,
    review_sessions.rating,
    review_sessions.message,
    net_sessions.country,
    net_sessions.city,
    net_sessions.organization,
    net_sessions.os,
    net_sessions.resolution,
    net_sessions.language,
    net_sessions.campaignName,
    net_sessions.campaignSource,
    net_sessions.campaignMedium,
    net_sessions.campaignTerm,
    net_sessions.campaignContent,
    net_sessions.sessionCount
FROM review_sessions
LEFT JOIN net_sessions ON net_sessions.netId=review_sessions.netId;


CREATE TABLE net_traces(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    _time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    netId VARCHAR(16),
    action VARCHAR(32),
    source VARCHAR(128),
    project VARCHAR(128),
    message VARCHAR(1024),
    eventCount INTEGER DEFAULT 1
);

CREATE INDEX metaoutput_net_traces ON net_traces(netId, _time);

CREATE VIEW net_traces_view AS
SELECT
    net_traces._id,
    net_traces._time,
    net_traces.netId,
    net_traces.action,
    net_traces.source,
    net_traces.project,
    net_traces.message,
    net_sessions.userId,
    net_sessions.country,
    net_sessions.city,
    net_sessions.organization,
    net_sessions.browser,
    net_sessions.os,
    net_sessions.resolution,
    net_sessions.language,
    net_sessions.ref,
    net_sessions.campaignName,
    net_sessions.campaignSource,
    net_sessions.campaignMedium,
    net_sessions.campaignTerm,
    net_sessions.campaignContent,
    net_traces.eventCount
FROM net_traces
LEFT JOIN net_sessions ON net_sessions.netId=net_traces.netId;

CREATE TABLE net_realtime(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    _time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    netId VARCHAR(16),
    source VARCHAR(64) NOT NULL,
    value1 VARCHAR(256),
    value2 VARCHAR(256),
    value3 VARCHAR(256),
    value4 VARCHAR(256)
);

CREATE INDEX metaoutput_net_realtime ON net_realtime(_time);

CREATE VIEW net_realtime_view AS
SELECT
    net_realtime._time,
    net_realtime.netId,
    net_realtime.source,
    net_realtime.value1,
    net_realtime.value2,
    net_realtime.value3,
    net_realtime.value4,
    net_sessions.country,
    net_sessions.city,
    net_sessions.organization,
    net_sessions.os,
    net_sessions.resolution,
    net_sessions.language
FROM net_realtime
LEFT JOIN net_sessions ON net_sessions.netId=net_realtime.netId;

CREATE TABLE app_sessions(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    _time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    netId VARCHAR(16) NOT NULL,
    userId VARCHAR(64) NOT NULL,
    action VARCHAR(64) NOT NULL,
    source VARCHAR(128) NOT NULL,
    project VARCHAR(128) NOT NULL
);

CREATE INDEX metaoutput_app_sessions ON app_sessions(netId, userId, action);

CREATE VIEW app_sessions_view AS
SELECT
    app_sessions._id,
    app_sessions._time,
    app_sessions.netId,
    app_sessions.userId,
    app_sessions.action,
    app_sessions.source,
    app_sessions.project,
    net_sessions.country,
    net_sessions.city,
    net_sessions.organization,
    net_sessions.os,
    net_sessions.resolution,
    net_sessions.language,
    net_sessions.campaignName,
    net_sessions.campaignSource,
    net_sessions.campaignMedium,
    net_sessions.campaignTerm,
    net_sessions.campaignContent,
    net_sessions.sessionCount
FROM app_sessions
LEFT JOIN net_sessions ON net_sessions.netId=app_sessions.netId;

CREATE TABLE dev_sessions(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    _time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    netId VARCHAR(16),
    action VARCHAR(64) NOT NULL,
    project VARCHAR(128) NOT NULL,
    source VARCHAR(128) NOT NULL,
    branch VARCHAR(128),
    url VARCHAR(256),
    message VARCHAR(1024)
);

CREATE INDEX metaoutput_dev_sessions ON dev_sessions(netId, project);

CREATE VIEW dev_sessions_view AS
SELECT
    dev_sessions._id,
    dev_sessions._time,
    dev_sessions.netId,
    dev_sessions.action,
    dev_sessions.source,
    dev_sessions.project,
    dev_sessions.branch,
    dev_sessions.url,
    dev_sessions.message,
    net_sessions.userId,
    net_sessions.country,
    net_sessions.city,
    net_sessions.organization,
    net_sessions.ref
FROM dev_sessions
LEFT JOIN net_sessions ON net_sessions.netId=dev_sessions.netId;

CREATE TABLE watch_sessions(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    _time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    netId VARCHAR(16) NOT NULL,
    action VARCHAR(64),
    source VARCHAR(128),
    project VARCHAR(128),
    user VARCHAR(128),
    url VARCHAR(256)
);

CREATE INDEX metaoutput_watch_sessions ON watch_sessions(netId, source);

CREATE VIEW watch_sessions_view AS
SELECT
    watch_sessions._id,
    watch_sessions._time,
    watch_sessions.netId,
    watch_sessions.action,
    watch_sessions.source,
    watch_sessions.project,
    watch_sessions.user,
    watch_sessions.url,
    net_sessions.userId,
    net_sessions.country,
    net_sessions.city,
    net_sessions.organization,
    net_sessions.browser,
    net_sessions.os,
    net_sessions.resolution,
    net_sessions.language,
    net_sessions.ref,
    net_sessions.campaignName,
    net_sessions.campaignSource,
    net_sessions.campaignMedium,
    net_sessions.campaignTerm,
    net_sessions.campaignContent
FROM watch_sessions
LEFT JOIN net_sessions ON net_sessions.netId=watch_sessions.netId;
# #############################################################################
# #############################################################################




# #############################################################################
# DATABASE INFO ###############################################################
SHOW ERRORS;
SHOW WARNINGS;
SHOW STATUS;
SHOW VARIABLES;
SHOW CHARSET;
#SHOW ENGINES;
#SHOW EVENTS;
#SHOW PROCEDURE STATUS;
#SHOW OPEN TABLES;
#SHOW PLUGINS;
#SHOW GRANTS;
#SHOW TRIGGERS;
#SHOW SCHEMAS;
#SHOW BINARY LOGS;
#SHOW BINLOG EVENTS;
#SHOW MASTER STATUS;
#SHOW SLAVE HOSTS;
#SHOW DATABASES;
SHOW TABLES;
# #############################################################################
# #############################################################################
