/*----------------------------------------------------
*客户程序代码

*程序： client.c
* 目的： 创建一个套接字，通过网络连接一个服务器，并打印来自服务器的信息
* 语法： client [ host [ port ] ]
*             host - 运行服务器的计算机的名字
*             port - 服务器监听套接字所用协议端口号
* 注意：两个参数都是可选的。如果未指定主机名，客户使用localhost；如果未指定端口号，
* 客户将使用PROTOPORT中给定的缺省协议端口号
*----------------------------------------------------
*/
#include <winsock2.h>
//#pragma comment(lib, "ws2_32")
#include <windows.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#define BUFFSIZE 1024
#define IP "192.168.1.105"

int Ret;
WSADATA wsaData;
SOCKET s;
SOCKADDR_IN ServerAddr;
unsigned short Port = 1234;
char sendData[BUFFSIZE];
char recvData[BUFFSIZE];
HANDLE HOne;


void Recieve()
{
    while(1)
    {

       //printf("等待服务器发来的消息......\n");
        Ret = recv(s, recvData, BUFFSIZE, 0);
        if((strcmp(recvData,"quit"))==0)
        {
            printf("对方退出聊天,程序关闭 !\n");
            break;
        }
        printf("服务器: %s\n", recvData);
    }
}

int main()
{
    printf("this is Client\n waitting for connection...\n");
    if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
    {
        printf("WSASTARTUP_ERROR: %d\n", Ret);
        return 0;
    }

    if ((s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
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



    //直接调用connect,差不多为固定格式
    if ((connect(s, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr))) == SOCKET_ERROR)
    {
        printf("CONNECT_ERROR: %d\n", SOCKET_ERROR);
        closesocket(s);
        return 0;
    }
    /*******************************************************************
    后面我再次打开程序,想到,client需不需要绑定套接字呢,查到了相关信息:
    有连接的socket客户端通过调用Connect函数在socket数据结构中保存本地和远端信息，
    无须调用bind()，因为这种情况下只需知道目的机器的IP地址，
    而客户通过哪个端口与服务器建立连接并不需要关心，
    socket执行会为你的程序自动选择一个未被占用的端口，
    并通知你的程序数据什么时候打开端口。
    一般情况下客户端是不用调用bind函数的，一切都交给内核搞定
    *******************************************************************/


    //绑定成功后接收来自server端的返回信息存到recvData
    //Ret = recv(s, recvData, BUFFSIZE, 0);

    // printf("%s\n", recvData);


    /******这儿可以继续,调用多线程或者直接单向通信******/
    //多线程
    HOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Recieve, NULL, 0, NULL);
    while(1)
    {
        //printf("客户端: ");
        fflush(stdin);
        scanf("%s",sendData);
        if (send(s, sendData, BUFFSIZE, 0) == SOCKET_ERROR)
        {
            printf("消息发送失败!\n");
        }
        if((strcmp(sendData,"quit"))==0)
        {
            printf("您已退出聊天,程序关闭 !\n");
            fflush(stdin);
            getchar();
            exit(0);
        }
    }
    CloseHandle(HOne);
    //关闭线程
    /******************************************************/

    shutdown(s, SD_BOTH);
    closesocket(s);
    if (WSACleanup() == SOCKET_ERROR)
    {
        printf("WSACLEANUP_ERROR: %d\n", WSAGetLastError());
        return 0;
    }
    system("pause");
    return 0;
}
