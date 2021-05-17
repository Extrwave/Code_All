/*------------------------------------------
*服务器实例代码
*程序：server.c
* 目的： 分配一个套接字，然后反复执行如下几步：
* （1） 等待客户的下一个连接
* （2） 发送一个短消息给客户
* （3） 关闭与客户的连接
*  (4)   转到(1)
* 命令行语法： server [ port ]
*                 port – 服务器端监听套接字使用的协议端口号
* 注意： 端口号可选。如果未指定端口号，服务器使用PROTOPORT中指定的缺省
* 端口号
*-----------------------------------------------
*/
#include <winsock2.h>
// #pragma comment(lib, "ws2_32")
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#define BUFFSIZE 1024
#define IP "192.168.1.105"

int Ret;
WSADATA wsaData;
SOCKET ListeningSocket; //监听用的套接字
SOCKET NewConnection;   //绑定后的套接字

SOCKADDR_IN ServerAddr;
SOCKADDR_IN ClientAddr;

int ClientAddrLen = sizeof(ClientAddr);

unsigned short Port = 5188;
char sendData[BUFFSIZE];
char recvData[BUFFSIZE];

HANDLE HOne; //多线程
int count = 0;

void Recieve()
{
    while (1)
    {
        //printf("等待客户端发来的消息......\n");
        Ret = recv(NewConnection, recvData, BUFFSIZE, 0);
        if ((strcmp(recvData, "quit")) == 0)
        {
            printf("对方退出聊天,程序关闭 !\n");
            break;
        }
        printf("客户端: %s\n", recvData);
    }
}

int main()
{
    printf("this is Server waitting for connection...\n");
    //请求协议版本必须为2,2,判断时上下两个字节分开判断
    if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
    {
        printf("WSASTARTUP_ERROR: %d\n", Ret);
        return 0;
        //请求失败然后报错
    }

    //创建一个套接字来监听客户机连接
    //下面一句基本为固定格式()
    if ((ListeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        printf("SOCKET_ERROR: %d\n", int(INVALID_SOCKET));
        return 0;
    }

    //填充SOCKADDR_IN结构，这个结构将告知bind我们想要在端口监听所有接口上的连接
    ServerAddr.sin_family = AF_INET;
    //将端口变量从主机字节顺序转换位网络字节顺序
    ServerAddr.sin_port = htons(Port);
    //这里的IP因为每次开机会改变,所以方便后续调试修改,采用宏定义
    ServerAddr.sin_addr.s_addr = inet_addr(IP);

    //使用bind将这个地址信息和套接字绑定起来,直接调用Bind,差不多为固定格式
    if (bind(ListeningSocket, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
    {
        printf("BIND_ERROR: %d\n", SOCKET_ERROR);
        return 0;
    }

    //监听客户机连接。这里使用5个backlog
    //listen()用来等待参数s的socket连线。参数backlog指定同时能处理的最大连接要求
    //如果连接数目达此上限则client端将收到ECONNREFUSED的错误
    // while(1)
    //{

    if (listen(ListeningSocket, 5) == SOCKET_ERROR)
    {
        printf("LISTEN_ERROR: %d\n", SOCKET_ERROR);
        return 0;
    }
    //连接到达时，接受连接
    printf("正在接受连接...\n");
    if ((NewConnection = accept(ListeningSocket, (SOCKADDR *)&ClientAddr, &ClientAddrLen)) == INVALID_SOCKET)
    {

        printf("ACCPET_ERROR: %d\n", int(INVALID_SOCKET));
        closesocket(ListeningSocket);
        return 0;
    }

    printf("检测到一个连接: %s 端口:%d\n", inet_ntoa(ClientAddr.sin_addr) /*客户端地址*/, ntohs(ClientAddr.sin_port) /*端口*/);
    count++;
    //将需要发送的信息写入sendData```````````````````````````````````````````````````````````````````````
    sprintf(sendData, "你是第%d个链接的！", count);

    if (send(NewConnection, sendData, BUFFSIZE, 0) == SOCKET_ERROR)
    {
        printf("消息发送失败!\n");
    }

    /******这儿可以继续,调用多线程或者直接单向通信******/
    HOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Recieve, NULL, 0, NULL);
    while (1)
    {
        // printf("服务器: ");
        fflush(stdin);
        scanf("%s", sendData);
        if (send(NewConnection, sendData, BUFFSIZE, 0) == SOCKET_ERROR)
        {
            printf("消息发送失败!\n");
        }
        if ((strcmp(sendData, "quit")) == 0)
        {
            printf("您已退出聊天,程序关闭 !\n");
            strcpy(sendData, "NULL");
            fflush(stdin);
            getchar();
            exit(0);
        }
    }

    CloseHandle(HOne);
    //}
    /*******************************************************/
    shutdown(NewConnection, SD_BOTH);
    //完成新接受的连接后，用closesocket API关闭这些套接字
    closesocket(NewConnection);
    closesocket(ListeningSocket);
    //应用程序完成对接的处理后，调用WSACleanup
    if (WSACleanup() == SOCKET_ERROR)
    {
        printf("WSACLEANUP_ERROR: %d\n", WSAGetLastError());
        return 0;
    }

    system("pause");
    return 0;
}
