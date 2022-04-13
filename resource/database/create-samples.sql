# #############################################################################
# SET DEFAULT DATABASE ########################################################
#USE metaoutput_dev;
USE metaoutput;
# #############################################################################
# #############################################################################




# #############################################################################
# ADDING DEFAULT DATA #########################################################
CALL net_trace_register("127.0.0.2", "APPLICATION", "MetaOutput 2.0.9.191", "WARNING", "[PERFORMANCE] Startup time is too long (execution time > 5 sec)");
CALL net_trace_register("127.0.0.3", "SITE.BACKEND", "metaoutput.net", "error", "Error: WDE0028: Request timed out.");

CALL net_session_register("127.0.0.2", "Ukraine", "Lviv", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 17);
CALL net_session_register("127.0.0.1", "United Kingdom", "London", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
CALL net_session_register("127.0.0.3", "United States", "New York", NULL, NULL, "Linux", NULL, "EN", NULL, TRUE, NULL, NULL, NULL, NULL, NULL, "!!!!", NULL);
CALL net_session_register("127.0.0.101", NULL, "Washington", NULL, NULL, "Windows", NULL, NULL, NULL, NULL, NULL, "test-campaign", "google", "cpc", "12/04/2022", "TEST", 9);
CALL net_session_register("127.0.0.101", "United States", "Washington", NULL, NULL, NULL, "1024x768", "EN-GB", NULL, FALSE, TRUE, "test-campaign", "google", "cpc", "11/01/2022", "!!!!", 20);

#CALL net_realtime_register(
#	"127.0.0.1",                                                                                # netAddress
#	"APPLICATION",                                                                              # source
#    "INSTALL",                                                                                 # value1
#    NULL);                                                                                     # value2
#CALL net_realtime_register(
#	"127.0.0.2",                                                                                # netAddress
#	"APPLICATION",                                                                              # source
#    "START",                                                                                   # value1
#    NULL);                                                                                     # value2
#CALL net_realtime_register(
#	"127.0.0.103",                                                                              # netAddress
#	"APPLICATION",                                                                              # source
#    "START",                                                                                   # value1
#    NULL);                                                                                     # value2

CALL watch_session_register(
    "127.0.0.1",                                                                               # netAddress
    "GitHub",                                                                                  # source
    "MetaOutput",                                                                              # project
    "issue",                                                                                   # action
    "Steive Jobs",                                                                             # user
    "https://trace.visualstudio.com/items?itemName=ViacheslavLozinskyi.MetaOutput-2019",       # url
    NULL);                                                                                     # message
CALL watch_session_register(
    "127.0.0.2",                                                                               # netAddress
    "GitHub",                                                                                  # source
    "MetaOutput",                                                                              # project
    "REVIEW",                                                                                  # action
    "Bill Gates",                                                                              # user
    "https://trace.visualstudio.com/items?itemName=ViacheslavLozinskyi.MetaOutput-2019",       # url
    NULL);                                                                                     # message
#CALL watch_session_register(
#    "127.0.0.3",                                                                               # netAddress
#    "Visual Studio",                                                                           # source
#    "MetaOutput",                                                                              # project
#    NULL,                                                                                      # action
#    "Elon Mask",                                                                               # user
#    "https://test.visualstudio.com/items?itemName=ViacheslavLozinskyi.MetaOutput-2019",        # url
#    NULL);                                                                                     # message
#CALL watch_session_register(
#    "127.0.0.7",                                                                               # netAddress
#    "Visual Studio",                                                                           # source
#    "Preview-AUDIO",                                                                           # project
#    "DOWNLOAD",                                                                                # action
#    "James Bond",                                                                              # user
#    "https://test.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-AUDIO",          # url
#    NULL);                                                                                     # message
#CALL watch_session_register(
#    "127.0.0.101",                                                                             # netAddress
#    "WEB-SITE",                                                                                # source
#    "Preview-CS",                                                                              # project
#    "VIEW",                                                                                    # action
#    "Johnny Depp",                                                                             # user
#    "https://trace.visualstudio.com/items?itemName=ViacheslavLozinskyi.Preview-CS",            # url
#    NULL);                                                                                     # message

CALL github_session_register(
    "push",                                                                                    # event
    "deleted",                                                                                 # action
    "Preview-CS",                                                                              # project
    "main",                                                                                    # branch
    "viacheslav-lozinskyi",                                                                    # user
    "https://avatars.githubusercontent.com/u/51988029?v=4",                                    # avatar
    "https://github.com/viacheslav-lozinskyi/Preview-CS",                                      # url
    "TEST MESSAGE!!!");                                                                        # message
CALL github_session_register(
    "star",                                                                                    # event
    "created",                                                                                 # action
    "Preview-VB",                                                                              # project
    "main",                                                                                    # branch
    "viacheslav-lozinskyi",                                                                    # user
    "https://avatars.githubusercontent.com/u/51988029?v=4",                                    # avatar
    "https://github.com/viacheslav-lozinskyi/Preview-VB",                                      # url
    "TEST MESSAGE!!!");                                                                        # message
CALL github_session_register(
    "star",                                                                                    # event
    "deleted",                                                                                 # action
    "Preview-JS",                                                                              # project
    "main",                                                                                    # branch
    "viacheslav-lozinskyi",                                                                    # user
    "https://avatars.githubusercontent.com/u/51988029?v=4",                                    # avatar
    "https://github.com/viacheslav-lozinskyi/Preview-JS",                                      # url
    "TEST MESSAGE!!!");                                                                        # message

#CALL github_project_register(
#    "Preview-CS",                                                                              # project,
#    NULL,                                                                                      # description
#    NULL,                                                                                      # version,
#    NULL,                                                                                      # owner
#    NULL);                                                                                     # url

CALL app_session_register(
	"127.0.0.101",                                                                             # netAddress
    "USER-1CAAFEAC-C113-4084-8CCE-43C2358EC991",                                               # userId
    "Visual Studio 2017",                                                                      # source
    "MetaOutput 2.0.7.172",                                                                    # project
    1);                                                                                        # sessions
# #############################################################################
# #############################################################################




# #############################################################################
# VIEW TABLES #################################################################
SELECT * FROM net_traces;
SELECT * FROM net_traces_view;
SELECT * FROM net_filters;
SELECT * FROM net_realtime;
SELECT * FROM net_realtime_view;
SELECT * FROM net_sessions;
SELECT * FROM app_sessions;
SELECT * FROM app_sessions_view;
SELECT * FROM watch_sessions;
SELECT * FROM watch_sessions_view;
SELECT * FROM github_sessions;
SELECT * FROM github_projects;
# #############################################################################
# #############################################################################
