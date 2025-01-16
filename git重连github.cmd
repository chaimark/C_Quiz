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

echo "git 网络配置清理...""
git config --global --unset http.proxy
git config --global --unset https.proxy
echo "git DNS清理..."
ipconfig /flushdns
echo "请先打开梯子, 然后按下任意键"
pause > nul
start "" "https://www.ipaddress.com/website/www.github.com"
echo 复制 github 的真实 IP 地址
set /p gitIP=""

echo # Copyright (c) 1993-2009 Microsoft Corp. >> "%SystemRoot%\TEMP\a.txt"
echo # >> "%SystemRoot%\TEMP\a.txt"
echo # This is a sample HOSTS file used by Microsoft TCP/IP for Windows. >> "%SystemRoot%\TEMP\a.txt"
echo # >> "%SystemRoot%\TEMP\a.txt"
echo # This file contains the mappings of IP addresses to host names. Each >> "%SystemRoot%\TEMP\a.txt"
echo # entry should be kept on an individual line. The IP address should >> "%SystemRoot%\TEMP\a.txt"
echo # be placed in the first column followed by the corresponding host name. >> "%SystemRoot%\TEMP\a.txt"
echo # The IP address and the host name should be separated by at least one >> "%SystemRoot%\TEMP\a.txt"
echo # space. >> "%SystemRoot%\TEMP\a.txt"
echo # >> "%SystemRoot%\TEMP\a.txt"
echo # Additionally, comments (such as these) may be inserted on individual >> "%SystemRoot%\TEMP\a.txt"
echo # lines or following the machine name denoted by a '#' symbol. >> "%SystemRoot%\TEMP\a.txt"
echo # >> "%SystemRoot%\TEMP\a.txt"
echo # For example: >> "%SystemRoot%\TEMP\a.txt"
echo # >> "%SystemRoot%\TEMP\a.txt"
echo #      102.54.94.97     rhino.acme.com          # source server >> "%SystemRoot%\TEMP\a.txt"
echo #       38.25.63.10     x.acme.com              # x client host >> "%SystemRoot%\TEMP\a.txt"
echo # >> "%SystemRoot%\TEMP\a.txt"
echo # localhost name resolution is handled within DNS itself. >> "%SystemRoot%\TEMP\a.txt"
echo #	127.0.0.1       localhost >> "%SystemRoot%\TEMP\a.txt"
echo #	::1             localhost >> "%SystemRoot%\TEMP\a.txt"
echo %gitIP% github.com >> "%SystemRoot%\TEMP\a.txt"

cd "C:\Windows\System32\drivers\etc"
del /s "C:\Windows\System32\drivers\etc\hosts"
copy "%SystemRoot%\TEMP\a.txt" "C:\Windows\System32\drivers\etc\hosts"
cd "%SystemRoot%\TEMP"
del "%SystemRoot%\TEMP\a.txt"
pause

git config --global http.proxy 127.0.0.1:7890
git config --global https.proxy 127.0.0.1:7890
