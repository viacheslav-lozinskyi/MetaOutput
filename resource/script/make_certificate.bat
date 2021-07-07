@echo off
z:
cd Z:\projects\slirit\metaoutput\resource\certificate
sn -k key.private.snk
rem sn -p key.private.snk key.public.snk

rem ### UI for Certifcation Manager in Windows
rem certmgr.exe

rem makecert -sk XYZ -r -pe -n "CN=Viacheslav Lozinskyi" -b 01/01/2018 -e 01/01/2030 -sky exchange key.private.cer