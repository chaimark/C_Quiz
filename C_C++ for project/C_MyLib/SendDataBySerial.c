#include "SendDataBySerial.h"
#include <windows.h>
#include <stdio.h>
typedef struct _threadArgs {
    HANDLE hComObj;
    strnew recvBuff;
    DWORD bytesRead;
} threadArgs; // 线程参数

void SetComPortData(HANDLE * _hCom) {
#define hCom (*_hCom)
    DCB ComObj = {0};
    // 配置串口
    ComObj.DCBlength = sizeof(ComObj);
    if (!GetCommState(hCom, &ComObj)) {
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
            ComObj.BaudRate = CBR_2400;
            break;
        case 2:
            ComObj.BaudRate = CBR_4800;
            break;
        case 3:
            ComObj.BaudRate = CBR_9600;
            break;
        case 4:
            ComObj.BaudRate = CBR_19200;
            break;
        case 5:
            ComObj.BaudRate = CBR_38400;
            break;
        case 6:
            ComObj.BaudRate = CBR_57600;
            break;
        case 7:
            ComObj.BaudRate = CBR_115200;
            break;
    }
    ComObj.ByteSize = 8;   // 数据位 8
    ComObj.StopBits = ONESTOPBIT; // 1 个停止位
    printf("1.无校验\n");
    printf("2.奇校验\n");
    printf("3.偶校验\n");
    printf("请设置串口校验方式：");
    int parity;
    scanf("%d", &parity);
    switch (parity) {
        case 1:
            ComObj.Parity = NOPARITY;   // 无校验位
            break;
        case 2:
            ComObj.Parity = ODDPARITY;   // 奇校验位
            break;
        case 3:
            ComObj.Parity = EVENPARITY;   // 偶校验位
            break;
        default:
            printf("Error setting parity\n");
            ComObj.Parity = EVENPARITY;   // 偶校验位
    }
    ComObj.Parity = NOPARITY;   // 无校验位
    if (!SetCommState(hCom, &ComObj)) {
        printf("Error setting serial parameters\n");
        CloseHandle(hCom);
        return;
    }
}

// 串口数据写入函数
bool SendDataToComX(strnew DataStr, HANDLE hComObj) {
    DWORD bytesWritten = 0;  // 用于记录实际写入的字节数
    BOOL writeStatus;
    
    // 确保数据末尾是以 '\0' 结尾（字符串格式）
    DataStr.Name._char[strlen(DataStr.Name._char)] = '\0';

    // 调用 WriteFile 将数据发送到串口
    writeStatus = WriteFile(
        hComObj,                     // 串口句柄
        DataStr.Name._char,          // 发送的数据
        strlen(DataStr.Name._char),  // 数据长度
        &bytesWritten,               // 实际写入的字节数
        NULL                         // 重叠结构（此处不使用重叠IO）
    );
    
    // 判断写入操作是否成功
    if (!writeStatus) {
        DWORD dwError = GetLastError();
        printf("Error writing to serial port, error code: %lu\n", dwError);
        return false;
    }

    printf("Successfully sent %lu bytes of data to COM port.\n", bytesWritten);
    return true;
}
// 串口数据接收线程函数
DWORD WINAPI CopyStsToUser(LPVOID Args) {
    threadArgs ArgStrutc = *((threadArgs *)Args);  // 获取线程 ID
    while (1) {
        if (ReadFile(ArgStrutc.hComObj, Args, sizeof(ArgStrutc.recvBuff.Name._char) - 1, &ArgStrutc.bytesRead, NULL)) {
            if (ArgStrutc.bytesRead > 0) {
                ArgStrutc.recvBuff.Name._char[ArgStrutc.bytesRead] = '\0';  // 确保字符串结束
                printf("Received data: %s\n", ArgStrutc.recvBuff.Name._char);
            } else {
                printf("No data received\n");
            }
        } else {
            DWORD dwError = GetLastError();
            if (dwError != ERROR_IO_PENDING) {
                printf("ReadFile failed, error code: %lu\n", dwError);
            }
        }
        Sleep(500);
    }
    pthread_exit(NULL);
}

void SendDataTask(const char * comPort, char (*SwitchNeedSendData)(strnew data)) {
    // 打开串口
    HANDLE hComObj = CreateFile(comPort,
        GENERIC_READ | GENERIC_WRITE,
        0,          // 不共享
        NULL,       // 默认安全性
        OPEN_EXISTING,
        0,          // 默认属性
        NULL
    );
    if (hComObj == INVALID_HANDLE_VALUE) {
        printf("Error opening port\n");
        return;
    }

    // 配置串口
    SetComPortData(&hComObj);

    char recvData[2048] = {0};  // 接收缓冲区
    HANDLE threads; // 存储线程句柄
    DWORD threadId; // 存储线程 ID
    threadArgs ArgeObj;
    ArgeObj.recvBuff = NEW_NAME(recvData);
    ArgeObj.bytesRead = 0;
    ArgeObj.hComObj = hComObj;

    threads = CreateThread(
        NULL,           // 默认安全属性
        0,              // 默认堆栈大小
        CopyStsToUser, // 线程函数
        &ArgeObj,    // 传递给线程的参数
        0,              // 默认创建方式
        &threadId       // 线程 ID
    );
    if (threads == NULL) {
        printf("Failed to create thread\n");
        return;
    }
    char sendData[2048] = {0};  // 发送缓冲区
    while (1) {
        // 获取发送数据并进行处理
        if (SwitchNeedSendData(NEW_NAME(sendData)) == '#') {
            pthread_cancel(threads);
            break; // 如果返回 '#'，则不继续发送数据
        }
        SendDataToComX(NEW_NAME(sendData), hComObj);
        Sleep(1000);
    }
    // 等待线程完成
    WaitForMultipleObjects(1, threads, TRUE, INFINITE);
    // 关闭线程句柄
    CloseHandle(threads);
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

