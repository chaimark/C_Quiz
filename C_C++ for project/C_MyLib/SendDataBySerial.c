#include "SendDataBySerial.h"

void SetComPortData(DCB * _dcbSerialParams, HANDLE * _hCom) {
#define hCom (*_hCom)
#define dcbSerialParams (*_dcbSerialParams)
    // 配置串口
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hCom, &dcbSerialParams)) {
        printf("Error getting current serial parameters\n");
        CloseHandle(hCom);
        return;
    }
    printf("1、波特率2400\n");
    printf("2、波特率4800\n");
    printf("3、波特率9600\n");
    printf("4、波特率19200\n");
    printf("5、波特率38400\n");
    printf("6、波特率57600\n");
    printf("7、波特率115200\n");
    printf("请设置串口波特率：");
    int baudrate;
    scanf("%d", &baudrate);
    switch (baudrate) {
        case 1:
            dcbSerialParams.BaudRate = CBR_2400;
            break;
        case 2:
            dcbSerialParams.BaudRate = CBR_4800;
            break;
        case 3:
            dcbSerialParams.BaudRate = CBR_9600;
            break;
        case 4:
            dcbSerialParams.BaudRate = CBR_19200;
            break;
        case 5:
            dcbSerialParams.BaudRate = CBR_38400;
            break;
        case 6:
            dcbSerialParams.BaudRate = CBR_57600;
            break;
        case 7:
            dcbSerialParams.BaudRate = CBR_115200;
            break;
    }
    dcbSerialParams.ByteSize = 8;   // 数据位 8
    dcbSerialParams.StopBits = ONESTOPBIT; // 1 个停止位
    printf("1.无校验\n");
    printf("2.奇校验\n");
    printf("3.偶校验\n");
    printf("请设置串口校验方式：");
    int parity;
    scanf("%d", &parity);
    switch (parity) {
        case 1:
            dcbSerialParams.Parity = NOPARITY;   // 无校验位
            break;
        case 2:
            dcbSerialParams.Parity = ODDPARITY;   // 奇校验位
            break;
        case 3:
            dcbSerialParams.Parity = EVENPARITY;   // 偶校验位
            break;
        default:
            printf("Error setting parity\n");
            dcbSerialParams.Parity = EVENPARITY;   // 偶校验位
    }
    dcbSerialParams.Parity = NOPARITY;   // 无校验位
    if (!SetCommState(hCom, &dcbSerialParams)) {
        printf("Error setting serial parameters\n");
        CloseHandle(hCom);
        return;
    }
}

void SendDataTask(const char * comPort, char (*SwitchNeedSendData)(strnew data)) {
    // 打开串口
    HANDLE hComObj = CreateFile(comPort,
        GENERIC_READ | GENERIC_WRITE,
        0,          // 不共享
        NULL,       // 默认安全性
        OPEN_EXISTING,
        0,          // 默认属性
        NULL);
    if (hComObj == INVALID_HANDLE_VALUE) {
        printf("Error opening port\n");
        return;
    }
    DCB ComObj = {0};
    SetComPortData(&ComObj, &hComObj);
    // 写数据到串口
    char data[100] = {0}; // 需要发送的数据
    char recvData[128];
    DWORD bytesWritten, bytesRead;
    while (1) {
        if (SwitchNeedSendData(NEW_NAME(data)) == '#') {
            break;
        }
        if (!WriteFile(hComObj, data, strlen(data), &bytesWritten, NULL)) {
            printf("Error writing to serial port\n");
            CloseHandle(hComObj);
            return;
        }
        printf("Data sent: %s\n\n", data);
        if (ReadFile(hComObj, recvData, sizeof(recvData) - 1, &bytesRead, NULL)) {
            if (bytesRead > 0) {
                recvData[bytesRead] = '\0';  // 确保字符串结束
                printf("Received data: %s\n", recvData);
            } else {
                printf("No data received\n");
            }
        } else {
            DWORD dwError = GetLastError();
            if (dwError != ERROR_IO_PENDING) {
                printf("ReadFile failed, error code: %lu\n", dwError);
            }
        }
    }
    // 关闭串口
    CloseHandle(hComObj);
}

// 输出所有的串口列表
void list_serial_ports() {
    char szDeviceName[MAX_PATH];
    DWORD dwDeviceIndex = 0;

    // 打开COM端口的设备文件
    while (TRUE) {
        // 生成设备名称
        sprintf(szDeviceName, "\\\\.\\COM%d", dwDeviceIndex);

        // 尝试打开这个端口
        HANDLE hDevice = CreateFile(
            szDeviceName, GENERIC_READ | GENERIC_WRITE,
            0, NULL, OPEN_EXISTING, 0, NULL);

        // 如果成功打开，说明该端口存在
        if (hDevice != INVALID_HANDLE_VALUE) {
            printf("Found: \t%s\n", &szDeviceName[4]);
            CloseHandle(hDevice);
        }

        // 增加索引继续检测下一个COM端口
        dwDeviceIndex++;

        // 如果没有找到端口，假定已遍历所有可能的端口
        if (dwDeviceIndex > 255) {
            break;
        }
    }
}