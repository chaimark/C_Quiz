@echo off
title �Դ�BGM���ڸ�
color 0e
:nulc
cls
echo.	ѡ������ϵͳ�������߽������н��̣�����cmd��ֱ�ӽ���������ʾ������
echo.
echo.	��0����ColorDisplay_App
echo.
echo.	��1����MQTT_DataUpdataDev_Lanzhou_Code_2024
echo.
echo.	��2����WIFI_Project
echo.
echo.	��3����PLCҵ������
echo.
echo.	��4����MQTT_DataUpdataDev_Usually_Code_24
echo.
echo.	��5����ReadT_NB_SLM130_Usually_CTWing
echo.
echo.	��6����MQTT_DataUpdataDev_WT_Code_2024
echo.
echo.	��7����ReadT_NB_SLM332_WTMQTT
echo.
echo.	��8����ReadT_4G_ML307_Usually_HYMQTT
echo.
echo.

set /p num="������ѡ��"
if "%num%" equ "������ѡ��" exit
set MyCode="C:\Users\choulei\AppData\Local\Programs\Microsoft VS Code\Code.exe"
setlocal enabledelayedexpansion
:process
if not "!num!"=="" (
    set char=!num:~0,1!
    set num=!num:~1!
    if "!char!"=="0" (
        start "" %MyCode% "E:\work\git_room\QiuLei_WorkSpace\ColorDisplay_24\ColorDisplay_App"
    )
    if "!char!"=="1" (
        start "" %MyCode% "E:\work\git_room\QiuLei_WorkSpace\MQTT_DataUpdataDev_Lanzhou_Code_2024\4G_MBUS_NET_MQTT_Application"
    )
    if "!char!"=="2" (
        start "" %MyCode% "E:\work\git_room\QiuLei_WorkSpace\MUBS_WIFI (����josnCmd����)\MUBS_WIFI_Application"
    )
    if "!char!"=="3" (
        start "" %MyCode% "E:\work\git_room\QiuLei_WorkSpace\PLCҵ������"
    )
    if "!char!"=="4" (
        start "" %MyCode% "E:\work\git_room\QiuLei_WorkSpace\MQTT_DataUpdataDev_Usually_Code_24\4G_MBUS_NET_MQTT_Application"
    )
    if "!char!"=="5" (
        start "" %MyCode% "E:\work\git_room\QiuLei_WorkSpace\ReadT_NB_SLM130_Usually_CTWing\Temperature_Measurement_24\Temperature_Code_Project"
    )
    if "!char!"=="6" (
        start "" %MyCode% "E:\work\git_room\QiuLei_WorkSpace\MQTT_DataUpdataDev_WT_Code_2024\4G_MBUS_NET_MQTT_Application"
    )
    if "!char!"=="7" (
        start "" %MyCode% "E:\work\git_room\QiuLei_WorkSpace\ReadT_NB_SLM332_WTMQTT\Temperature_Measurement_24\Temperature_Code_Project"
    )
    if "!char!"=="8" (
        start "" %MyCode% "E:\work\git_room\QiuLei_WorkSpace\ReadT_4G_ML307_Usually_HYMQTT\Temperature_Measurement_24\Temperature_Code_Project"
    )
    goto process
)
endlocal

exit



