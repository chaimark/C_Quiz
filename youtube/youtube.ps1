# ����Ƿ��Թ���Ա�������
# if (-NOT ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] "Administrator")) {
#     # ���������ű�Ϊ����Աģʽ
#     Start-Process powershell -Verb runAs -ArgumentList "-File `"$PSCommandPath`""
#     exit
# }

# ���ù���Ŀ¼Ϊ�ű�����Ŀ¼
$scriptDir = Split-Path $MyInvocation.MyCommand.Definition
Set-Location $scriptDir

# ��ʾ��ǰ����Ŀ¼
Write-Host "��ǰ����·���ǣ�$scriptDir"
Write-Host "�ѻ�ȡ����ԱȨ��"

$host.UI.RawUI.WindowSize = New-Object System.Management.Automation.Host.Size(80, 25)
$host.UI.RawUI.BufferSize = New-Object System.Management.Automation.Host.Size(132, 30)

function ShowProcess {
    param (
        [int]$NextLen,
        [int]$MaxLen,
        [int]$NowLen = 0 # Ĭ��NowLenΪ0�����֮ǰ�Ѿ����������Ӧ�ô��뵱ǰ����
    )
    $NeedLen = if ($NextLen -le $MaxLen) {
        # ������Ҫ�ĳ���
        $NextLen - $NowLen
    }
    else {
        $MaxLen - $NowLen
    }
    for ($i = 1; $i -le $NeedLen; $i++) {
        # ʹ��ѭ������ʾ������
        Write-Host "��" -NoNewline
        Start-Sleep -Milliseconds 50 # ������ping /n 1 127.0.0.1>nul����ʱЧ��
    }
    $NowLen += $NeedLen  # ���µ�ǰ����
    if ($NowLen -eq $MaxLen) {
        # ����ﵽ��󳤶ȣ������õ�ǰ����
        Write-Host "" # ���һ�����з�
        $NowLen = 0
    }
    $NowLen  # ���ظ��º�ĵ�ǰ���ȣ������Ҫ�Ļ���
}

$ClashRunning = $true
# ��� Clash for Windows �Ƿ���������
$clashProcess = Get-Process | Where-Object { $_.ProcessName -eq "Clash for Windows" }
if (-not $clashProcess) {
    $ClashRunning = $false
}

# ���߼�
if ($ClashRunning) {
    Write-Host "���ڹر�Clash for Windows.exe"
    Stop-Process -Name "Clash for Windows" -Force

    # ��� Git ��������
    git config --global --unset http.proxy
    git config --global --unset https.proxy

    Set-ItemProperty -Path 'HKCU:\Software\Microsoft\Windows\CurrentVersion\Internet Settings' -Name ProxyEnable -Value 0
    # �������������
    $MaxLen = 20
    $NowLen = 0
    for ($i = 0; $i -lt 2; $i++) {
        $NextLen += 10;
        $NowLen = ShowProcess -NextLen $NextLen -MaxLen $MaxLen -NowLen $NowLen
        if ($NextLen -ge $MaxLen) {
            $NextLen = 0
        }
    }
    # Start-Process ms-settings:network-proxy 
}
else {
    Write-Host "Clash for Windows δ���С�"
    # ���� Git ����
    git config --global http.proxy http://127.0.0.1:7890
    git config --global https.proxy https://127.0.0.1:7890
    
    # �� youtube
    Start-Process "https://www.youtube.com"
    # ���� Clash for Windows
    Start-Process -Filepath "D:\Program Files\Clash for Windows\Clash for Windows.exe"
}
exit