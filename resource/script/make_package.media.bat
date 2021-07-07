@echo ==========================================================================
@echo Creating of NuGet package...
@echo ==========================================================================
@echo Project name: MetaOutput.Media
@echo Output folder: %USERPROFILE%\.metaoutput\package
@echo ==========================================================================

@echo --- Package Preparation... -----------------------------------------------
@echo Before compilation of "MetaOutput.Core" project is necessary to remove "packages" folder. @@@TYPE WARNING

@set CONFIGURATION=Release
@if "%1" == "" goto :continue1
@set CONFIGURATION=%1
:continue1

@if exist %USERPROFILE%\.metaoutput\package\ goto :continue2
@mkdir %USERPROFILE%\.metaoutput\package
:continue2

@if not exist %USERPROFILE%\.metaoutput\package\metaoutput.media goto :continue3
@echo --- Package removing... --------------------------------------------------
@rmdir /S /Q %USERPROFILE%\.metaoutput\package\metaoutput.media
@rmdir /S /Q %HOMEDRIVE%%HOMEPATH%\.nuget\packages\metaoutput.media
:continue3

@echo --- Package copying... ---------------------------------------------------
@mkdir %USERPROFILE%\.metaoutput\package\metaoutput.media
@xcopy /S /I /Q ..\package\metaoutput.media*.nuspec %USERPROFILE%\.metaoutput\package\metaoutput.media
@xcopy /S /I /Q ..\package\metaoutput.media*.targets %USERPROFILE%\.metaoutput\package\metaoutput.media\build
@xcopy /Y /I /Q %USERPROFILE%\.metaoutput\build\%CONFIGURATION%\metaoutput.client.*dll %USERPROFILE%\.metaoutput\package\metaoutput.media\lib\net45
@xcopy /Y /I /Q %USERPROFILE%\.metaoutput\build\%CONFIGURATION%\metaoutput.media.*dll %USERPROFILE%\.metaoutput\package\metaoutput.media\lib\net45
@xcopy /Y /I /Q %USERPROFILE%\.metaoutput\build\%CONFIGURATION%\TagLibSharp.*dll %USERPROFILE%\.metaoutput\package\metaoutput.media\lib\net45

@echo --- Package generating... ------------------------------------------------
@..\..\..\metaplatform\resource\tool\nuget.exe pack %USERPROFILE%\.metaoutput\package\metaoutput.media\MetaOutput.Media.nuspec -OutputDirectory %USERPROFILE%\.metaoutput\package\metaoutput.media
@echo ==========================================================================
