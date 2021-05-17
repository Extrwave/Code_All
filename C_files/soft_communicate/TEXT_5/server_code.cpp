/*------------------------------------------
*������ʵ������
*����server.c
* Ŀ�ģ� ����һ���׽��֣�Ȼ�󷴸�ִ�����¼�����
* ��1�� �ȴ��ͻ�����һ������
* ��2�� ����һ������Ϣ���ͻ�
* ��3�� �ر���ͻ�������
*  (4)   ת��(1)
* �������﷨�� server [ port ]
*                 port �C �������˼����׽���ʹ�õ�Э��˿ں�
* ע�⣺ �˿ںſ�ѡ�����δָ���˿ںţ�������ʹ��PROTOPORT��ָ����ȱʡ
* �˿ں�
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
SOCKET ListeningSocket; //�����õ��׽���
SOCKET NewConnection;   //�󶨺���׽���

SOCKADDR_IN ServerAddr;
SOCKADDR_IN ClientAddr;

int ClientAddrLen = sizeof(ClientAddr);

unsigned short Port = 5188;
char sendData[BUFFSIZE];
char recvData[BUFFSIZE];

HANDLE HOne; //���߳�
int count = 0;

void Recieve()
{
    while (1)
    {
        //printf("�ȴ��ͻ��˷�������Ϣ......\n");
        Ret = recv(NewConnection, recvData, BUFFSIZE, 0);
        if ((strcmp(recvData, "quit")) == 0)
        {
            printf("�Է��˳�����,����ر� !\n");
            break;
        }
        printf("�ͻ���: %s\n", recvData);
    }
}

int main()
{
    printf("this is Server waitting for connection...\n");
    //����Э��汾����Ϊ2,2,�ж�ʱ���������ֽڷֿ��ж�
    if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
    {
        printf("WSASTARTUP_ERROR: %d\n", Ret);
        return 0;
        //����ʧ��Ȼ�󱨴�
    }

    //����һ���׽����������ͻ�������
    //����һ�����Ϊ�̶���ʽ()
    if ((ListeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        printf("SOCKET_ERROR: %d\n", int(INVALID_SOCKET));
        return 0;
    }

    //���SOCKADDR_IN�ṹ������ṹ����֪bind������Ҫ�ڶ˿ڼ������нӿ��ϵ�����
    ServerAddr.sin_family = AF_INET;
    //���˿ڱ����������ֽ�˳��ת��λ�����ֽ�˳��
    ServerAddr.sin_port = htons(Port);
    //�����IP��Ϊÿ�ο�����ı�,���Է�����������޸�,���ú궨��
    ServerAddr.sin_addr.s_addr = inet_addr(IP);

    //ʹ��bind�������ַ��Ϣ���׽��ְ�����,ֱ�ӵ���Bind,���Ϊ�̶���ʽ
    if (bind(ListeningSocket, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
    {
        printf("BIND_ERROR: %d\n", SOCKET_ERROR);
        return 0;
    }

    //�����ͻ������ӡ�����ʹ��5��backlog
    //listen()�����ȴ�����s��socket���ߡ�����backlogָ��ͬʱ�ܴ�����������Ҫ��
    //���������Ŀ���������client�˽��յ�ECONNREFUSED�Ĵ���
    // while(1)
    //{

    if (listen(ListeningSocket, 5) == SOCKET_ERROR)
    {
        printf("LISTEN_ERROR: %d\n", SOCKET_ERROR);
        return 0;
    }
    //���ӵ���ʱ����������
    printf("���ڽ�������...\n");
    if ((NewConnection = accept(ListeningSocket, (SOCKADDR *)&ClientAddr, &ClientAddrLen)) == INVALID_SOCKET)
    {

        printf("ACCPET_ERROR: %d\n", int(INVALID_SOCKET));
        closesocket(ListeningSocket);
        return 0;
    }

    printf("��⵽һ������: %s �˿�:%d\n", inet_ntoa(ClientAddr.sin_addr) /*�ͻ��˵�ַ*/, ntohs(ClientAddr.sin_port) /*�˿�*/);
    count++;
    //����Ҫ���͵���Ϣд��sendData```````````````````````````````````````````````````````````````````````
    sprintf(sendData, "���ǵ�%d�����ӵģ�", count);

    if (send(NewConnection, sendData, BUFFSIZE, 0) == SOCKET_ERROR)
    {
        printf("��Ϣ����ʧ��!\n");
    }

    /******������Լ���,���ö��̻߳���ֱ�ӵ���ͨ��******/
    HOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Recieve, NULL, 0, NULL);
    while (1)
    {
        // printf("������: ");
        fflush(stdin);
        scanf("%s", sendData);
        if (send(NewConnection, sendData, BUFFSIZE, 0) == SOCKET_ERROR)
        {
            printf("��Ϣ����ʧ��!\n");
        }
        if ((strcmp(sendData, "quit")) == 0)
        {
            printf("�����˳�����,����ر� !\n");
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
    //����½��ܵ����Ӻ���closesocket API�ر���Щ�׽���
    closesocket(NewConnection);
    closesocket(ListeningSocket);
    //Ӧ�ó�����ɶԽӵĴ���󣬵���WSACleanup
    if (WSACleanup() == SOCKET_ERROR)
    {
        printf("WSACLEANUP_ERROR: %d\n", WSAGetLastError());
        return 0;
    }

    system("pause");
    return 0;
}
