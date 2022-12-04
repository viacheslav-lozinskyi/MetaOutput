@echo ==========================================================================
@echo Creating of NuGet package...
@echo ==========================================================================
@echo Project name: MetaOutput.Client
@echo Output folder: %USERPROFILE%\.metaoutput\package
@echo ==========================================================================

@echo --- Package Preparation... -----------------------------------------------
@echo Before compilation of "MetaOutput.Core" project is necessary to remove "packages" folder. @@@EVENT WARNING

@set CONFIGURATION=Release
@if "%1" == "" goto :continue1
@set CONFIGURATION=%1
:continue1

@if exist %USERPROFILE%\.metaoutput\package\ goto :continue2
@mkdir %USERPROFILE%\.metaoutput\package
:continue2

@if not exist %USERPROFILE%\.metaoutput\package\metaoutput.client goto :continue3
@echo --- Package removing... --------------------------------------------------
@rmdir /S /Q %USERPROFILE%\.metaoutput\package\metaoutput.client
@rmdir /S /Q %HOMEDRIVE%%HOMEPATH%\.nuget\packages\metaoutput.client
:continue3

@echo --- Package copying... ---------------------------------------------------
@mkdir %USERPROFILE%\.metaoutput\package\metaoutput.client
@xcopy /S /I /Q ..\package\metaoutput.client*.nuspec %USERPROFILE%\.metaoutput\package\metaoutput.client
@xcopy /S /I /Q ..\package\metaoutput.client*.targets %USERPROFILE%\.metaoutput\package\metaoutput.client\build
@xcopy /S /I /Q ..\..\library\metaoutput.client\*.hpp %USERPROFILE%\.metaoutput\package\metaoutput.client\include\metaoutput.client
@xcopy /Y /I /Q %USERPROFILE%\.metaoutput\build\%CONFIGURATION%\metaoutput.client.*dll %USERPROFILE%\.metaoutput\package\metaoutput.client\lib\net45

@echo --- Package generating... ------------------------------------------------
@..\..\..\metaplatform\resource\tool\nuget.exe pack %USERPROFILE%\.metaoutput\package\metaoutput.client\MetaOutput.Client.nuspec -OutputDirectory %USERPROFILE%\.metaoutput\package\metaoutput.client
@echo ==========================================================================
