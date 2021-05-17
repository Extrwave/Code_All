/*****����������*****/
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
    //����Э��汾
    WSADATA WSversion;
    WSAStartup(MAKEWORD(2, 2), &WSversion);
    if (HIBYTE(WSversion.wVersion) != 2 || LOBYTE(WSversion.wVersion) != 2)
    {
        printf("����Э��汾ʧ�ܣ�\n");
        return ERROR;
    }
    //����socket
    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (SOCKET_ERROR == listenSocket)
    {
        printf("����socketʧ�ܣ�\n");
        WSACleanup(); //���Э�飡
        return ERROR;
    }
    printf("socke�����ɹ���\n");

    //����Э���ַ��

    addr.sin_family = AF_INET;                   //Э��汾
    addr.sin_addr.S_un.S_addr = inet_addr(IP); //������д�Լ���ip��ַ
    addr.sin_port = htons(10086);                //0-65535���˿ڿɹ�ѡ�񣬽���ѡ��һ�����ҵģ�OS�ں˻��������ᱻ��������ռ��

    //���׽���
    int r = bind(listenSocket, (sockaddr *)&addr, sizeof addr);
    if (r == -1)
    {
        printf("��ʧ�ܣ�\n");
        closesocket(listenSocket);
        WSACleanup();
        return ERROR;
    }
    else
        printf("�󶨳ɹ���\n");
    //����������
    if (listen(listenSocket, 5) == SOCKET_ERROR)
    {
        printf("LISTEN_ERROR: %d\n", SOCKET_ERROR);
        return 0;
    }

    //�ȴ��ͻ�������  ������ʽ��һֱ�ȵ��пͻ��������ӣ�
    printf("waitting for connect from client......\n");

    clientSocket = accept(listenSocket, (struct sockaddr *)&cAddr, &len);
    if (SOCKET_ERROR == clientSocket)
    {
        printf("����������Ӧ��");
        closesocket(listenSocket);
        WSACleanup();
        return -1;
    }
    else
    {
        printf("��⵽һ������: %s �˿�:%d\n", inet_ntoa(cAddr.sin_addr), ntohs(cAddr.sin_port));
        printf("�ͻ������ӵ��������ɹ���\n");
        count++;
    }

    /*
    if (SOCKET_ERROR == clientSocket)
    {
        printf("����ʧ�ܣ�\n");
        closesocket(listenSocket);
        WSACleanup();
        return ERROR;
    }
    */

    sprintf(sendData, "���ǵ�%d�����ӵģ�", count);
    if (send(clientSocket, sendData, 1024, 0) == SOCKET_ERROR)
    {
        printf("��Ϣ����ʧ��!\n");
    }

    char buff[1024];

    r = recv(clientSocket, buff, 1024, 0);
    if (r > 0)
        printf("�ͻ��ˣ�%s\n", buff);

    // scanf("%s", buff);
    // if (strcmp(sendData, "quit") == 0)
    //     exit(0);
    // if (send(clientSocket, buff, 1024, 0) == SOCKET_ERROR)
    // {
    //     printf("��Ϣ����ʧ��!\n");
    // }
    //������Ϣ
    //�ر�scoket

    shutdown(clientSocket, SD_BOTH);
    //����½��ܵ����Ӻ���closesocket API�ر���Щ�׽���
    closesocket(clientSocket);
    closesocket(listenSocket);
    WSACleanup();
    system("pause");
}

