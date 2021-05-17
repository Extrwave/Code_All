/*****客户端代码*****/
#include "winsock2.h"
#include "windows.h"
#include "stdio.h"
#include "string.h"
#include "time.h"
#define BUFFSIZE 1024
#define IP "192.168.1.105"

void findIP(char *ip, int size);

char recvData[BUFFSIZE];

int main()
{

    //请求协议版本
    WSADATA WSversion;
    WSAStartup(MAKEWORD(2, 2), &WSversion);
    if (HIBYTE(WSversion.wVersion) != 2 || LOBYTE(WSversion.wVersion) != 2)
    {
        printf("请求协议版本失败！\n");
        return ERROR;
    }
    //创建socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (SOCKET_ERROR == clientSocket)
    {
        printf("创建socket失败！\n");
        WSACleanup(); //清除协议！
        return ERROR;
    }
    printf("socke创建成功！\n");

    //创建协议地址族
    SOCKADDR_IN addr = {0};
    addr.sin_family = AF_INET;                 //协议版本
    addr.sin_addr.S_un.S_addr = inet_addr(IP); //这里填写自己的ip地址
    addr.sin_port = htons(10086);              //0-65535个端口可供选择，建议选择一万左右的，OS内核还有其他会被其他程序占用

    //链接服务器
    printf("等待连接服务器！\n");

    if ((connect(clientSocket, (sockaddr *)&addr, sizeof(addr))) == INVALID_SOCKET)
    {
        printf("连接服务器失败！\n");
        closesocket(clientSocket);
        return ERROR;
    }
    else
        printf("连接服务器成功！\n");
    //通信
    char sendData[BUFFSIZE];

    //发送与接收存在问题~！！！

    //
    //
    //
    if (recv(clientSocket, recvData, BUFFSIZE, 0))
        printf("服务器：%s\n", recvData);

    // scanf("%s", sendData);
    // if (strcmp(sendData, "quit") == 0)
    //     exit(0);
    // if (send(clientSocket, recvData, 1024, 0) == SOCKET_ERROR)
    // {
    //     printf("消息发送失败!\n");
    // }

    //if (send(clientSocket, sendData, strlen(sendData), NULL))
    // printf("发送成功！\n");
    system("pasue");
    return 0;
}

void findIP(char *ip, int size)
{
    WORD v = MAKEWORD(1, 1);
    WSADATA wsaData;
    WSAStartup(v, &wsaData); // 加载套接字库

    struct hostent *phostinfo = gethostbyname("");
    char *p = inet_ntoa(*((struct in_addr *)(*phostinfo->h_addr_list)));
    strncpy(ip, p, size - 1);
    ip[size - 1] = '\0';
    WSACleanup();
}