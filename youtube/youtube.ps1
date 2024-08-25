# 检查是否以管理员身份运行
if (-NOT ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] "Administrator")) {
    # 重新启动脚本为管理员模式
    Start-Process powershell -Verb runAs -ArgumentList "-File `"$PSCommandPath`""
    exit
}

# 设置工作目录为脚本所在目录
$scriptDir = Split-Path $MyInvocation.MyCommand.Definition
Set-Location $scriptDir

# 显示当前工作目录
Write-Host "当前运行路径是：$scriptDir"
Write-Host "已获取管理员权限"

function ShowProcess {
    param (
        [int]$NextLen,
        [int]$MaxLen,
        [int]$NowLen = 0 # 默认NowLen为0，如果之前已经处理过，则应该传入当前长度
    )
    $NeedLen = if ($NextLen -le $MaxLen) {
        # 计算需要的长度
        $NextLen - $NowLen
    }
    else {
        $MaxLen - $NowLen
    }
    for ($i = 1; $i -le $NeedLen; $i++) {
        # 使用循环来显示进度条
        Write-Host "■" -NoNewline
        Start-Sleep -Milliseconds 100 # 类似于ping /n 1 127.0.0.1>nul的延时效果
    }
    $NowLen += $NeedLen  # 更新当前长度
    if ($NowLen -eq $MaxLen) {
        # 如果达到最大长度，则重置当前长度
        Write-Host "" # 输出一个换行符
        $NowLen = 0
    }
    $NowLen  # 返回更新后的当前长度（如果需要的话）
}

$ClashRunning = $true
# 检查 Clash for Windows 是否正在运行
$clashProcess = Get-Process | Where-Object { $_.ProcessName -eq "Clash for Windows" }
if (-not $clashProcess) {
    $ClashRunning = $false
}

# 主逻辑
if ($ClashRunning) {
    Write-Host "正在关闭Clash for Windows.exe"
    Stop-Process -Name "Clash for Windows" -Force

    # 清除 Git 代理设置
    git config --global --unset http.proxy
    git config --global --unset https.proxy

    Set-ItemProperty -Path 'HKCU:\Software\Microsoft\Windows\CurrentVersion\Internet Settings' -Name ProxyEnable -Value 0
    # 打开网络代理设置
    $MaxLen = 20
    $NowLen = 0
    for ($i = 0; $i -lt 2; $i++) {
        $NextLen += 10;
        $NowLen = ShowProcess -NextLen $NextLen -MaxLen $MaxLen -NowLen $NowLen
        if ($NextLen -ge $MaxLen) {
            $NextLen = 0
        }
    }
    Start-Process ms-settings:network-proxy 
}
else {
    # 设置 Git 代理
    git config --global http.proxy http://127.0.0.1:7890
    git config --global https.proxy https://127.0.0.1:7890
    Write-Host "Clash for Windows 未运行。"

    # 启动 Clash for Windows
    Start-Process "D:\Program Files\Clash for Windows\Clash for Windows.exe"

    $MaxLen = 20
    $NowLen = 0
    # 等待 Clash 启动
    for ($i = 0; $i -lt 30; $i++) {
        # 检查 Clash 是否启动
        $clashProcess = Get-Process | Where-Object { $_.ProcessName -eq "Clash for Windows" }
        if ($clashProcess) {
            # Clash 已启动 打开 YouTube
            # Start-Process "https://www.youtube.com"
            break
        }
        Start-Sleep -Seconds 2
        $NextLen += 10;
        $NowLen = ShowProcess -NextLen $NextLen -MaxLen $MaxLen -NowLen $NowLen
        if ($NextLen -ge $MaxLen) {
            $NextLen = 0
        }
    }
}
exit