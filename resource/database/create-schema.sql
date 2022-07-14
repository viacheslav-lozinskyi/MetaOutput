# #############################################################################
# CREATING DATABASE ###########################################################
# #############################################################################
#CREATE DATABASE IF NOT EXISTS metaoutput_dev;
CREATE DATABASE IF NOT EXISTS metaoutput;

# #############################################################################
# SET DEFAULT DATABASE ########################################################
# #############################################################################
#USE metaoutput_dev;
USE metaoutput;
SET time_zone = "Europe/Kiev";
SET character_set_client = "UTF8MB4";
SET character_set_results = "UTF8MB4";

# #############################################################################
# DROPPING TABLES #############################################################
# #############################################################################
#DROP TABLE IF EXISTS net_crawlers;
#DROP TABLE IF EXISTS net_filters;
#DROP TABLE IF EXISTS net_sessions;
#DROP TABLE IF EXISTS review_sessions;
#DROP TABLE IF EXISTS net_traces;
#DROP TABLE IF EXISTS net_realtime;
#DROP TABLE IF EXISTS app_sessions;
#DROP TABLE IF EXISTS dev_sessions;
#DROP TABLE IF EXISTS watch_sessions;

# #############################################################################
# CREATING TABLES #############################################################
# #############################################################################
# net_detectors ###############################################################
# #############################################################################
CREATE TABLE net_detectors(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    _time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    project VARCHAR(128) NOT NULL,
    url VARCHAR(256) NOT NULL UNIQUE
);

CREATE INDEX metaoutput_net_detectors ON net_detectors(url);

# #############################################################################
# net_filters #################################################################
# #############################################################################
CREATE TABLE net_filters(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    type ENUM("IP", "URL") NOT NULL,
    value VARCHAR(256) NOT NULL UNIQUE
);

CREATE INDEX metaoutput_net_filters ON net_filters(type, value);

# #############################################################################
# net_sessions ################################################################
# #############################################################################
CREATE TABLE IF NOT EXISTS net_sessions(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    netId VARCHAR(16) NOT NULL,
    country VARCHAR(64),
    city VARCHAR(64),
    organization VARCHAR(128),
    browser VARCHAR(64),
    os VARCHAR(64),
    resolution VARCHAR(64),
    language VARCHAR(8),
    ref VARCHAR(256),
    campaignGroup VARCHAR(128),
    campaignId VARCHAR(128),
    campaignTerm VARCHAR(128),
    campaignContent VARCHAR(128)
);

CREATE INDEX metaoutput_net_sessions ON net_sessions(netId, campaignId);

# #############################################################################
# review_sessions #############################################################
# #############################################################################
CREATE TABLE IF NOT EXISTS review_sessions(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    _time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    netId VARCHAR(16) NOT NULL,
    action VARCHAR(32) NOT NULL,
    source VARCHAR(128) NOT NULL,
    project VARCHAR(128) NOT NULL,
    user VARCHAR(256),
    avatar VARCHAR(256),
    email VARCHAR(256),
    url VARCHAR(256),
    rating INTEGER,
    title VARCHAR(256),
    message VARCHAR(1024)
);

CREATE INDEX metaoutput_review_sessions ON review_sessions(netId);

DROP VIEW IF EXISTS review_sessions_view;

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
    review_sessions.title,
    review_sessions.message,
    net_sessions.country,
    net_sessions.city,
    net_sessions.organization
FROM review_sessions
LEFT JOIN net_sessions ON net_sessions.netId = review_sessions.netId;

# #############################################################################
# trace_sessions ##############################################################
# #############################################################################
CREATE TABLE IF NOT EXISTS trace_sessions(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    _time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    netId VARCHAR(16),
    action VARCHAR(32) NOT NULL,
    source VARCHAR(128) NOT NULL,
    project VARCHAR(128) NOT NULL,
    message VARCHAR(1024),
    stack TEXT,
    eventCount INTEGER DEFAULT 1
);

CREATE INDEX metaoutput_trace_sessions ON trace_sessions(netId, _time);

DROP VIEW IF EXISTS trace_sessions_view;

CREATE VIEW trace_sessions_view AS
SELECT
    trace_sessions._id,
    trace_sessions._time,
    trace_sessions.netId,
    trace_sessions.action,
    trace_sessions.source,
    trace_sessions.project,
    trace_sessions.message,
    trace_sessions.stack,
    net_sessions.country,
    net_sessions.city,
    net_sessions.organization,
    net_sessions.browser,
    net_sessions.os,
    net_sessions.resolution,
    net_sessions.language,
    trace_sessions.eventCount
FROM trace_sessions
LEFT JOIN net_sessions ON net_sessions.netId = trace_sessions.netId;

# #############################################################################
# net_realtime ################################################################
# #############################################################################
CREATE TABLE IF NOT EXISTS net_realtime(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    _time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    netId VARCHAR(16),
    channel VARCHAR(64) NOT NULL,
    action VARCHAR(64) NOT NULL,
    project VARCHAR(128) NOT NULL,
    source VARCHAR(128) NOT NULL,
    url VARCHAR(256),
    message TEXT,
    events INTEGER
);

CREATE INDEX metaoutput_net_realtime ON net_realtime(_time, netId);

DROP VIEW IF EXISTS net_realtime_view;

CREATE VIEW net_realtime_view AS
SELECT
    net_realtime._time,
    net_realtime.netId,
    net_realtime.channel,
    net_realtime.action,
    net_realtime.project,
    net_realtime.source,
    net_sessions.country,
    net_sessions.city,
    net_sessions.organization,
    net_realtime.url,
    net_realtime.message,
    net_realtime.events
FROM net_realtime
LEFT JOIN net_sessions ON net_sessions.netId = net_realtime.netId;

# #############################################################################
# app_sessions ################################################################
# #############################################################################
CREATE TABLE IF NOT EXISTS app_sessions(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    _time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    netId VARCHAR(16) NOT NULL,
    userId VARCHAR(64) NOT NULL,
    action VARCHAR(64) NOT NULL,
    project VARCHAR(128) NOT NULL,
    source VARCHAR(128) NOT NULL,
    eventCount INTEGER DEFAULT 1
);

CREATE INDEX metaoutput_app_sessions ON app_sessions(netId, userId, action);

DROP VIEW IF EXISTS app_sessions_view;

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
    net_sessions.ref,
    net_sessions.campaignGroup,
    net_sessions.campaignId,
    net_campaigns.name AS campaignName,
    net_campaigns.source AS campaignSource,
    net_campaigns.medium AS campaignMedium,
    net_sessions.campaignTerm,
    net_sessions.campaignContent,
    app_sessions.eventCount
FROM app_sessions
LEFT JOIN net_sessions ON net_sessions.netId = app_sessions.netId
LEFT JOIN net_campaigns ON net_sessions.campaignGroup = net_campaigns.campaignGroup;

# #############################################################################
# dev_sessions ################################################################
# #############################################################################
CREATE TABLE IF NOT EXISTS dev_sessions(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    _time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    netId VARCHAR(16),
    action VARCHAR(64) NOT NULL,
    project VARCHAR(128) NOT NULL,
    source VARCHAR(128) NOT NULL,
    branch VARCHAR(128),
    user VARCHAR(128),
    avatar VARCHAR(256),
    url VARCHAR(256),
    message VARCHAR(1024)
);

CREATE INDEX metaoutput_dev_sessions ON dev_sessions(netId, project);

DROP VIEW IF EXISTS dev_sessions_view;

CREATE VIEW dev_sessions_view AS
SELECT
    dev_sessions._id,
    dev_sessions._time,
    dev_sessions.netId,
    dev_sessions.action,
    dev_sessions.source,
    dev_sessions.project,
    dev_sessions.branch,
    dev_sessions.user,
    dev_sessions.avatar,
    dev_sessions.url,
    dev_sessions.message,
    net_sessions.country,
    net_sessions.city,
    net_sessions.organization
FROM dev_sessions
LEFT JOIN net_sessions ON net_sessions.netId = dev_sessions.netId;

# #############################################################################
# net_campaigns ###############################################################
# #############################################################################
CREATE TABLE IF NOT EXISTS net_campaigns(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    _time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    campaignGroup VARCHAR(128) UNIQUE NOT NULL,
    name VARCHAR(128) NOT NULL,
    source VARCHAR(128) NOT NULL,
    medium VARCHAR(128) NOT NULL,
    user VARCHAR(128),
    description VARCHAR(256),
    pattern VARCHAR(256),
    logo TEXT
);

CREATE INDEX metaoutput_net_campaigns ON net_campaigns(campaignGroup, name, source, medium);

DROP VIEW campaign_sessions_view;

CREATE VIEW campaign_sessions_view AS
SELECT
    app_sessions._time,
    app_sessions.netId,
    app_sessions.action,
    app_sessions.source,
    app_sessions.project,
    net_sessions.country,
    net_sessions.city,
    net_sessions.organization,
    net_sessions.os,
    net_sessions.resolution,
    net_sessions.language,
    net_sessions.ref,
    net_sessions.campaignGroup,
    net_sessions.campaignId,
    net_campaigns.name AS campaignName,
    net_campaigns.source AS campaignSource,
    net_campaigns.medium AS campaignMedium,
    net_sessions.campaignTerm,
    net_sessions.campaignContent
FROM app_sessions
LEFT JOIN net_sessions ON net_sessions.netId = app_sessions.netId
LEFT JOIN net_campaigns ON net_sessions.campaignGroup = net_campaigns.campaignGroup
WHERE NOT ISNULL(net_sessions.campaignGroup) AND (app_sessions.action != "START")

UNION

SELECT
    watch_sessions._time,
    watch_sessions.netId,
    watch_sessions.action,
    watch_sessions.source,
    watch_sessions.project,
    net_sessions.country,
    net_sessions.city,
    net_sessions.organization,
    net_sessions.os,
    net_sessions.resolution,
    net_sessions.language,
    net_sessions.ref,
    net_sessions.campaignGroup,
    net_sessions.campaignId,
    net_campaigns.name AS campaignName,
    net_campaigns.source AS campaignSource,
    net_campaigns.medium AS campaignMedium,
    net_sessions.campaignTerm,
    net_sessions.campaignContent
FROM watch_sessions
LEFT JOIN net_sessions ON net_sessions.netId = watch_sessions.netId
LEFT JOIN net_campaigns ON net_sessions.campaignGroup = net_campaigns.campaignGroup
WHERE NOT ISNULL(net_sessions.campaignGroup);

# #############################################################################
# watch_sessions ##############################################################
# #############################################################################
CREATE TABLE IF NOT EXISTS watch_sessions(
    _id INTEGER AUTO_INCREMENT PRIMARY KEY,
    _time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    netId VARCHAR(16) NOT NULL,
    action VARCHAR(64) NOT NULL,
    project VARCHAR(128) NOT NULL,
    source VARCHAR(128) NOT NULL,
    url VARCHAR(256),
    eventCount INTEGER DEFAULT 1
);

CREATE INDEX metaoutput_watch_sessions ON watch_sessions(netId, source, project, action);

DROP VIEW IF EXISTS watch_sessions_view;

CREATE VIEW watch_sessions_view AS
SELECT
    watch_sessions._id,
    watch_sessions._time,
    watch_sessions.netId,
    watch_sessions.action,
    watch_sessions.source,
    watch_sessions.project,
    watch_sessions.url,
    app_sessions.userId,
    net_sessions.country,
    net_sessions.city,
    net_sessions.organization,
    net_sessions.browser,
    net_sessions.os,
    net_sessions.resolution,
    net_sessions.language,
    net_sessions.ref,
    net_sessions.campaignGroup,
    net_sessions.campaignId,
    net_campaigns.name AS campaignName,
    net_campaigns.source AS campaignSource,
    net_campaigns.medium AS campaignMedium,
    net_sessions.campaignTerm,
    net_sessions.campaignContent,
    watch_sessions.eventCount
FROM watch_sessions
LEFT JOIN net_sessions ON net_sessions.netId = watch_sessions.netId
LEFT JOIN app_sessions ON app_sessions.netId = watch_sessions.netId
LEFT JOIN net_campaigns ON net_sessions.campaignGroup = net_campaigns.campaignGroup;
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
