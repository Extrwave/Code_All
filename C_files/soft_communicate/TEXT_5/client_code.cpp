/*----------------------------------------------------
*�ͻ��������

*���� client.c
* Ŀ�ģ� ����һ���׽��֣�ͨ����������һ��������������ӡ���Է���������Ϣ
* �﷨�� client [ host [ port ] ]
*             host - ���з������ļ����������
*             port - �����������׽�������Э��˿ں�
* ע�⣺�����������ǿ�ѡ�ġ����δָ�����������ͻ�ʹ��localhost�����δָ���˿ںţ�
* �ͻ���ʹ��PROTOPORT�и�����ȱʡЭ��˿ں�
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

       //printf("�ȴ���������������Ϣ......\n");
        Ret = recv(s, recvData, BUFFSIZE, 0);
        if((strcmp(recvData,"quit"))==0)
        {
            printf("�Է��˳�����,����ر� !\n");
            break;
        }
        printf("������: %s\n", recvData);
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


    //���SOCKADDR_IN�ṹ������ṹ����֪bind������Ҫ�ڶ˿ڼ������нӿ��ϵ�����
    ServerAddr.sin_family = AF_INET;
    //���˿ڱ����������ֽ�˳��ת��λ�����ֽ�˳��
    ServerAddr.sin_port = htons(Port);
    //�����IP��Ϊÿ�ο�����ı�,���Է�����������޸�,���ú궨��
    ServerAddr.sin_addr.s_addr = inet_addr(IP);



    //ֱ�ӵ���connect,���Ϊ�̶���ʽ
    if ((connect(s, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr))) == SOCKET_ERROR)
    {
        printf("CONNECT_ERROR: %d\n", SOCKET_ERROR);
        closesocket(s);
        return 0;
    }
    /*******************************************************************
    �������ٴδ򿪳���,�뵽,client�費��Ҫ���׽�����,�鵽�������Ϣ:
    �����ӵ�socket�ͻ���ͨ������Connect������socket���ݽṹ�б��汾�غ�Զ����Ϣ��
    �������bind()����Ϊ���������ֻ��֪��Ŀ�Ļ�����IP��ַ��
    ���ͻ�ͨ���ĸ��˿���������������Ӳ�����Ҫ���ģ�
    socketִ�л�Ϊ��ĳ����Զ�ѡ��һ��δ��ռ�õĶ˿ڣ�
    ��֪ͨ��ĳ�������ʲôʱ��򿪶˿ڡ�
    һ������¿ͻ����ǲ��õ���bind�����ģ�һ�ж������ں˸㶨
    *******************************************************************/


    //�󶨳ɹ����������server�˵ķ�����Ϣ�浽recvData
    //Ret = recv(s, recvData, BUFFSIZE, 0);

    // printf("%s\n", recvData);


    /******������Լ���,���ö��̻߳���ֱ�ӵ���ͨ��******/
    //���߳�
    HOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Recieve, NULL, 0, NULL);
    while(1)
    {
        //printf("�ͻ���: ");
        fflush(stdin);
        scanf("%s",sendData);
        if (send(s, sendData, BUFFSIZE, 0) == SOCKET_ERROR)
        {
            printf("��Ϣ����ʧ��!\n");
        }
        if((strcmp(sendData,"quit"))==0)
        {
            printf("�����˳�����,����ر� !\n");
            fflush(stdin);
            getchar();
            exit(0);
        }
    }
    CloseHandle(HOne);
    //�ر��߳�
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
