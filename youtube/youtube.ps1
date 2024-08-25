# 检查是否以管理员身份运行  
if (-NOT ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] "Administrator"))  
{  
    # 重新启动脚本为管理员模式  
    Start-Process powershell -Verb runAs -ArgumentList "-File `"$PSCommandPath`""  
    exit  
}  
  
# 设置工作目录为脚本所在目录  
$scriptDir = Split-Path $MyInvocation.MyCommand.Definition  
cd $scriptDir  
  
# 显示当前工作目录  
Write-Host "当前运行路径是：$scriptDir"  
Write-Host "已获取管理员权限"  
  
# 设定变量  
$MaxLen = 20  
$NowLen = 0  
$NextLen = 0  
$ClashRunning = $true  
  
# 检查 Clash for Windows 是否正在运行  
$clashProcess = Get-Process | Where-Object { $_.ProcessName -eq "Clash for Windows" }  
if (-not $clashProcess)  
{  
    $ClashRunning = $false  
}  
  
# 主逻辑  
if ($ClashRunning)  
{  
    Write-Host "正在关闭Clash for Windows.exe"  
    Stop-Process -Name "Clash for Windows" -Force  
  
    # 清除 Git 代理设置  
    git config --global --unset http.proxy  
    git config --global --unset https.proxy  
  
    # 打开网络代理设置  
    Start-Process ms-settings:network-proxy  
}  
else  
{  
    # 设置 Git 代理  
    git config --global http.proxy http://127.0.0.1:7890  
    git config --global https.proxy https://127.0.0.1:7890  
    Write-Host "Clash for Windows 未运行。"  
  
    # 启动 Clash for Windows  
    Start-Process "D:\Program Files\Clash for Windows\Clash for Windows.exe"  
  
    # 等待 Clash 启动  
    for ($i = 0; $i -lt 30; $i++)  
    {  
        # 检查 Clash 是否启动  
        $clashProcess = Get-Process | Where-Object { $_.ProcessName -eq "Clash for Windows" }  
        if ($clashProcess)  
        {  
            # 填充进度条（简化实现）  
            $NeedLen = $MaxLen - $NowLen  
            if ($NeedLen > 0)  
            {  
                for ($j = 0; $j -lt $NeedLen; $j++)  
                {  
                    Write-Host -NoNewline "■"  
                    Start-Sleep -Milliseconds 100  
                }  
                Write-Host ""  
                $NowLen = 0  
            }  
  
            # 打开 YouTube  
            Start-Process "https://www.youtube.com"  
            break  
        }  
        Start-Sleep -Seconds 1  
    }  
}