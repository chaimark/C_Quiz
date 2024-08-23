@echo off  
if exist "%SystemRoot%\SysWOW64" path %path%;%windir%\SysNative;%SystemRoot%\SysWOW64;%~dp0
bcdedit >nul
if '%errorlevel%' NEQ '0' (goto UACPrompt) else (goto UACAdmin)
:UACPrompt
%1 start "" mshta vbscript:createobject("shell.application").shellexecute("""%~0""","::",,"runas",1)(window.close)&exit
exit /B
:UACAdmin
cd /d "%~dp0"
echo 当前运行路径是：%CD%
echo 已获取管理员权限

TITLE youtube或恢复代理设置
set MaxLen=20
set NowLen=0
set NextLen=0
set Clash=1
set delayClashFlag=1
goto Main
:delayClashStart  
REM 检查软件是否正在运行  
TASKLIST /nh|find /i "Clash for Windows.exe" >nul & if ERRORLEVEL 1 (set delayClashFlag=0)
if %delayClashFlag% neq 1 (
    set NextLen=20 & call :showProcess
)
exit /b 0
:showProcess
set NeedLen=0
if %NextLen% leq %MaxLen% (
	set /a NeedLen=%NextLen%-%NowLen%
) else (
	set /a NeedLen=%MaxLen%-%NowLen%
)
for /L %%i in (1 1 %NeedLen%) do set /p a=■<nul&ping /n 1 127.0.0.1>nul
set /a NowLen=%NowLen%+%NeedLen%
if %NowLen%==%MaxLen% (
	echo.
	set NowLen=0
)
exit /b 0
:Main
REM 检查软件是否正在运行  
TASKLIST /nh|find /i "Clash for Windows.exe" >nul & if ERRORLEVEL 1 (set Clash=0)
if %Clash%==1 (
    echo 正在关闭Clash for Windows.exe 
    taskkill /f /IM "Clash for Windows.exe"
    rem control inetcpl.cpl,,4
    git config --global --unset http.proxy
    git config --global --unset https.proxy
    start ms-settings:network-proxy
) else (  
    git config --global http.proxy 127.0.0.1:7890
    git config --global https.proxy 127.0.0.1:7890
    echo Clash for Windows 未运行。
    start "" "D:\Program Files\Clash for Windows\Clash for Windows.exe"
    for /L %%i in (1,1,30) do (
        call :delayClashStart
        if %delayClashFlag% == 1 (start "" "https://www.youtube.com" & exit)
    )
)
exit