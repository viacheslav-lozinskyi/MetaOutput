@echo ==========================================================================
@echo Creating of NuGet package...
@echo ==========================================================================
@echo Project name: MetaOutput.Proxy.Visual-Studio
@echo Output folder: %USERPROFILE%\.metaoutput\package
@echo ==========================================================================

@echo --- Package Preparation... -----------------------------------------------
@echo Before compilation of "MetaOutput.Proxy.Visual-Studio" project is necessary to remove "packages" folder. @@@EVENT WARNING

@set CONFIGURATION=Release
@if "%1" == "" goto :continue1
@set CONFIGURATION=%1
:continue1

@if exist %USERPROFILE%\.metaoutput\package\ goto :continue2
@mkdir %USERPROFILE%\.metaoutput\package
:continue2

@if not exist %USERPROFILE%\.metaoutput\package\metaoutput.proxy.visual-studio goto :continue3
@echo --- Package removing... --------------------------------------------------
@rmdir /S /Q %USERPROFILE%\.metaoutput\package\metaoutput.proxy.visual-studio
@rmdir /S /Q %HOMEDRIVE%%HOMEPATH%\.nuget\packages\metaoutput.proxy.visual-studio
:continue3

@echo --- Package copying... ---------------------------------------------------
@mkdir %USERPROFILE%\.metaoutput\package\metaoutput.proxy.visual-studio
@xcopy /S /I /Q ..\package\metaoutput.proxy.visual-studio*.nuspec %USERPROFILE%\.metaoutput\package\metaoutput.proxy.visual-studio
@xcopy /S /I /Q ..\package\metaoutput.proxy.visual-studio*.targets %USERPROFILE%\.metaoutput\package\metaoutput.proxy.visual-studio\build
@xcopy /Y /I /Q %USERPROFILE%\.metaoutput\build\%CONFIGURATION%\metaoutput.client.*dll %USERPROFILE%\.metaoutput\package\metaoutput.proxy.visual-studio\lib\net45
@xcopy /Y /I /Q %USERPROFILE%\.metaoutput\build\%CONFIGURATION%\metaoutput.proxy.visual-studio.*dll %USERPROFILE%\.metaoutput\package\metaoutput.proxy.visual-studio\lib\net45
@xcopy /Y /I /Q %USERPROFILE%\.metaoutput\build\%CONFIGURATION%\TagLibSharp.*dll %USERPROFILE%\.metaoutput\package\metaoutput.proxy.visual-studio\lib\net45

@echo --- Package generating... ------------------------------------------------
@..\..\..\metaplatform\resource\tool\nuget.exe pack %USERPROFILE%\.metaoutput\package\metaoutput.proxy.visual-studio\MetaOutput.Proxy.Visual-Studio.nuspec -OutputDirectory %USERPROFILE%\.metaoutput\package\metaoutput.proxy.visual-studio
@echo ==========================================================================
