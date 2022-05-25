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
#DROP TABLE IF EXISTS net_filters;
#DROP TABLE IF EXISTS net_sessions;
#DROP TABLE IF EXISTS review_sessions;
#DROP TABLE IF EXISTS net_traces;
#DROP TABLE IF EXISTS net_realtime;
#DROP TABLE IF EXISTS app_sessions;
#DROP TABLE IF EXISTS github_sessions;
#DROP TABLE IF EXISTS github_projects;
#DROP TABLE IF EXISTS watch_sessions;

#DROP VIEW IF EXISTS net_traces_view;
#DROP VIEW IF EXISTS net_realtime_view;
#DROP VIEW IF EXISTS app_sessions_view;
#DROP VIEW IF EXISTS watch_sessions_view;
# #############################################################################
# #############################################################################




# #############################################################################
# CREATING TABLES #############################################################

CREATE TABLE net_filters(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    type ENUM("IP", "URL") NOT NULL,
    value VARCHAR(256) NOT NULL UNIQUE
);

CREATE INDEX metaoutput_net_filters ON net_filters(type, value);

CREATE TABLE net_sessions(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    _time TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    netAddress VARCHAR(16) NOT NULL,
    userId VARCHAR(64),
    country VARCHAR(64),
    city VARCHAR(64),
    coordinates VARCHAR(32),
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

CREATE INDEX metaoutput_net_sessions ON net_sessions(netAddress, userId);

CREATE TABLE review_sessions(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    _time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    netId VARCHAR(16) NOT NULL,
    source VARCHAR(128),
    project VARCHAR(128),
    action VARCHAR(32),
    user VARCHAR(256),
    avatar VARCHAR(256),
    email VARCHAR(256),
    url VARCHAR(256),
    rating FLOAT,
    message VARCHAR(1024)
);

CREATE INDEX metaoutput_review_sessions ON review_sessions(netId);

CREATE VIEW review_sessions_view AS
SELECT
    review_sessions._id,
    review_sessions._time,
    review_sessions.netId,
    review_sessions.source,
    review_sessions.project,
    review_sessions.action,
    review_sessions.user,
    review_sessions.avatar,
    review_sessions.email,
    review_sessions.url,
    review_sessions.rating,
    review_sessions.message,    
    net_sessions.country,
    net_sessions.city,
    net_sessions.coordinates,
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
LEFT JOIN net_sessions ON net_sessions.netAddress=review_sessions.netId;


CREATE TABLE net_traces(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    _time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    netAddress VARCHAR(16) NOT NULL,
    source VARCHAR(128),
    project VARCHAR(128),
    action VARCHAR(32),
    message VARCHAR(1024)
);

CREATE VIEW net_traces_view AS
SELECT
    net_traces._id,
    net_traces._time,
    net_traces.netAddress,
    net_traces.source,
    net_traces.project,
    net_traces.action,
    net_traces.message,
    net_sessions.userId,
    net_sessions.country,
    net_sessions.city,
    net_sessions.coordinates,
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
    net_sessions.sessionCount
FROM net_traces
LEFT JOIN net_sessions ON net_sessions.netAddress=net_traces.netAddress;

CREATE TABLE net_realtime(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    _time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    netAddress VARCHAR(16),
    source VARCHAR(64) NOT NULL,
    value1 VARCHAR(256),
    value2 VARCHAR(256),
    value3 VARCHAR(256)
);

CREATE INDEX metaoutput_net_realtime ON net_realtime(_time);

CREATE VIEW net_realtime_view AS
SELECT
    net_realtime._id,
    net_realtime._time,
    net_realtime.netAddress,
    net_realtime.source,
    net_realtime.value1,
    net_realtime.value2,
    net_realtime.value3,
    net_sessions.country,
    net_sessions.city,
    net_sessions.coordinates,
    net_sessions.organization,
    net_sessions.os,
    net_sessions.resolution,
    net_sessions.language
FROM net_realtime
LEFT JOIN net_sessions ON net_sessions.netAddress=net_realtime.netAddress;

CREATE TABLE app_sessions(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    _time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    netAddress VARCHAR(16) NOT NULL,
    userId VARCHAR(64) NOT NULL,
    action VARCHAR(64) NOT NULL,
    source VARCHAR(128) NOT NULL,
    project VARCHAR(128) NOT NULL
);

CREATE INDEX metaoutput_app_sessions ON app_sessions(netAddress, userId);

CREATE VIEW app_sessions_view AS
SELECT
    app_sessions._id,
    app_sessions._time,
    app_sessions.netAddress,
    app_sessions.userId,
    app_sessions.action,
    app_sessions.source,
    app_sessions.project,
    net_sessions.country,
    net_sessions.city,
    net_sessions.coordinates,
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
LEFT JOIN net_sessions ON net_sessions.netAddress=app_sessions.netAddress;

CREATE TABLE github_sessions(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    _time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    country VARCHAR(64),
    city VARCHAR(64),
    event VARCHAR(64) NOT NULL,
    action VARCHAR(64),
    project VARCHAR(128) NOT NULL,
    branch VARCHAR(128),
    user VARCHAR(128) NOT NULL,
    avatar VARCHAR(256),
    url VARCHAR(256),
    message VARCHAR(1024)
);

CREATE INDEX metaoutput_github_sessions ON github_sessions(project);

CREATE TABLE github_projects(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    project VARCHAR(128) NOT NULL UNIQUE,
    owner VARCHAR(128),
    url VARCHAR(256),
    starCount INTEGER,
    watchCount INTEGER,
    forkCount INTEGER,
    issueCount INTEGER
);

CREATE INDEX metaoutput_github_projects ON github_projects(project);

CREATE TABLE watch_sessions(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    _time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    netAddress VARCHAR(16) NOT NULL,
    source VARCHAR(128),
    action VARCHAR(64),
    project VARCHAR(128),
    user VARCHAR(128),
    url VARCHAR(256),
    message VARCHAR(256)
);

CREATE INDEX metaoutput_watch_sessions ON watch_sessions(netAddress, source);

CREATE VIEW watch_sessions_view AS
SELECT
    watch_sessions._id,
    watch_sessions._time,
    watch_sessions.netAddress,
    watch_sessions.source,
    watch_sessions.action,
    watch_sessions.project,
    watch_sessions.user,
    watch_sessions.url,
    watch_sessions.message,
    net_sessions.userId,
    net_sessions.country,
    net_sessions.city,
    net_sessions.coordinates,
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
LEFT JOIN net_sessions ON net_sessions.netAddress=watch_sessions.netAddress;
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
