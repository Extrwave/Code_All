/*****服务器代码*****/
#include "winsock2.h"
#include "windows.h"
#include "stdio.h"
#include "string.h"
#include "time.h"
#define IP "192.168.1.105"

SOCKET clientSocket;
SOCKET listenSocket;
SOCKADDR_IN cAddr;
SOCKADDR_IN addr;


int count = 0;
char sendData[1024];
char recvData[1024];
int len = sizeof cAddr;

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
    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (SOCKET_ERROR == listenSocket)
    {
        printf("创建socket失败！\n");
        WSACleanup(); //清除协议！
        return ERROR;
    }
    printf("socke创建成功！\n");

    //创建协议地址族

    addr.sin_family = AF_INET;                   //协议版本
    addr.sin_addr.S_un.S_addr = inet_addr(IP); //这里填写自己的ip地址
    addr.sin_port = htons(10086);                //0-65535个端口可供选择，建议选择一万左右的，OS内核还有其他会被其他程序占用

    //绑定套接字
    int r = bind(listenSocket, (sockaddr *)&addr, sizeof addr);
    if (r == -1)
    {
        printf("绑定失败！\n");
        closesocket(listenSocket);
        WSACleanup();
        return ERROR;
    }
    else
        printf("绑定成功！\n");
    //启动监听！
    if (listen(listenSocket, 5) == SOCKET_ERROR)
    {
        printf("LISTEN_ERROR: %d\n", SOCKET_ERROR);
        return 0;
    }

    //等待客户端链接  阻塞方式，一直等到有客户端来连接！
    printf("waitting for connect from client......\n");

    clientSocket = accept(listenSocket, (struct sockaddr *)&cAddr, &len);
    if (SOCKET_ERROR == clientSocket)
    {
        printf("服务器无响应！");
        closesocket(listenSocket);
        WSACleanup();
        return -1;
    }
    else
    {
        printf("检测到一个连接: %s 端口:%d\n", inet_ntoa(cAddr.sin_addr), ntohs(cAddr.sin_port));
        printf("客户端连接到服务器成功！\n");
        count++;
    }

    /*
    if (SOCKET_ERROR == clientSocket)
    {
        printf("连接失败！\n");
        closesocket(listenSocket);
        WSACleanup();
        return ERROR;
    }
    */

    sprintf(sendData, "你是第%d个链接的！", count);
    if (send(clientSocket, sendData, 1024, 0) == SOCKET_ERROR)
    {
        printf("消息发送失败!\n");
    }

    char buff[1024];

    r = recv(clientSocket, buff, 1024, 0);
    if (r > 0)
        printf("客户端：%s\n", buff);

    // scanf("%s", buff);
    // if (strcmp(sendData, "quit") == 0)
    //     exit(0);
    // if (send(clientSocket, buff, 1024, 0) == SOCKET_ERROR)
    // {
    //     printf("消息发送失败!\n");
    // }
    //发送信息
    //关闭scoket

    shutdown(clientSocket, SD_BOTH);
    //完成新接受的连接后，用closesocket API关闭这些套接字
    closesocket(clientSocket);
    closesocket(listenSocket);
    WSACleanup();
    system("pause");
}

