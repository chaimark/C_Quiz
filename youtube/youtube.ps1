# ����Ƿ��Թ���Ա�������  
if (-NOT ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] "Administrator"))  
{  
    # ���������ű�Ϊ����Աģʽ  
    Start-Process powershell -Verb runAs -ArgumentList "-File `"$PSCommandPath`""  
    exit  
}  
  
# ���ù���Ŀ¼Ϊ�ű�����Ŀ¼  
$scriptDir = Split-Path $MyInvocation.MyCommand.Definition  
cd $scriptDir  
  
# ��ʾ��ǰ����Ŀ¼  
Write-Host "��ǰ����·���ǣ�$scriptDir"  
Write-Host "�ѻ�ȡ����ԱȨ��"  
  
# �趨����  
$MaxLen = 20  
$NowLen = 0  
$NextLen = 0  
$ClashRunning = $true  
  
# ��� Clash for Windows �Ƿ���������  
$clashProcess = Get-Process | Where-Object { $_.ProcessName -eq "Clash for Windows" }  
if (-not $clashProcess)  
{  
    $ClashRunning = $false  
}  
  
# ���߼�  
if ($ClashRunning)  
{  
    Write-Host "���ڹر�Clash for Windows.exe"  
    Stop-Process -Name "Clash for Windows" -Force  
  
    # ��� Git ��������  
    git config --global --unset http.proxy  
    git config --global --unset https.proxy  
  
    # �������������  
    Start-Process ms-settings:network-proxy  
}  
else  
{  
    # ���� Git ����  
    git config --global http.proxy http://127.0.0.1:7890  
    git config --global https.proxy https://127.0.0.1:7890  
    Write-Host "Clash for Windows δ���С�"  
  
    # ���� Clash for Windows  
    Start-Process "D:\Program Files\Clash for Windows\Clash for Windows.exe"  
  
    # �ȴ� Clash ����  
    for ($i = 0; $i -lt 30; $i++)  
    {  
        # ��� Clash �Ƿ�����  
        $clashProcess = Get-Process | Where-Object { $_.ProcessName -eq "Clash for Windows" }  
        if ($clashProcess)  
        {  
            # ������������ʵ�֣�  
            $NeedLen = $MaxLen - $NowLen  
            if ($NeedLen > 0)  
            {  
                for ($j = 0; $j -lt $NeedLen; $j++)  
                {  
                    Write-Host -NoNewline "��"  
                    Start-Sleep -Milliseconds 100  
                }  
                Write-Host ""  
                $NowLen = 0  
            }  
  
            # �� YouTube  
            Start-Process "https://www.youtube.com"  
            break  
        }  
        Start-Sleep -Seconds 1  
    }  
}