/*****�ͻ��˴���*****/
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

    //����Э��汾
    WSADATA WSversion;
    WSAStartup(MAKEWORD(2, 2), &WSversion);
    if (HIBYTE(WSversion.wVersion) != 2 || LOBYTE(WSversion.wVersion) != 2)
    {
        printf("����Э��汾ʧ�ܣ�\n");
        return ERROR;
    }
    //����socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (SOCKET_ERROR == clientSocket)
    {
        printf("����socketʧ�ܣ�\n");
        WSACleanup(); //���Э�飡
        return ERROR;
    }
    printf("socke�����ɹ���\n");

    //����Э���ַ��
    SOCKADDR_IN addr = {0};
    addr.sin_family = AF_INET;                 //Э��汾
    addr.sin_addr.S_un.S_addr = inet_addr(IP); //������д�Լ���ip��ַ
    addr.sin_port = htons(10086);              //0-65535���˿ڿɹ�ѡ�񣬽���ѡ��һ�����ҵģ�OS�ں˻��������ᱻ��������ռ��

    //���ӷ�����
    printf("�ȴ����ӷ�������\n");

    if ((connect(clientSocket, (sockaddr *)&addr, sizeof(addr))) == INVALID_SOCKET)
    {
        printf("���ӷ�����ʧ�ܣ�\n");
        closesocket(clientSocket);
        return ERROR;
    }
    else
        printf("���ӷ������ɹ���\n");
    //ͨ��
    char sendData[BUFFSIZE];

    //��������մ�������~������

    //
    //
    //
    if (recv(clientSocket, recvData, BUFFSIZE, 0))
        printf("��������%s\n", recvData);

    // scanf("%s", sendData);
    // if (strcmp(sendData, "quit") == 0)
    //     exit(0);
    // if (send(clientSocket, recvData, 1024, 0) == SOCKET_ERROR)
    // {
    //     printf("��Ϣ����ʧ��!\n");
    // }

    //if (send(clientSocket, sendData, strlen(sendData), NULL))
    // printf("���ͳɹ���\n");
    system("pasue");
    return 0;
}

void findIP(char *ip, int size)
{
    WORD v = MAKEWORD(1, 1);
    WSADATA wsaData;
    WSAStartup(v, &wsaData); // �����׽��ֿ�

    struct hostent *phostinfo = gethostbyname("");
    char *p = inet_ntoa(*((struct in_addr *)(*phostinfo->h_addr_list)));
    strncpy(ip, p, size - 1);
    ip[size - 1] = '\0';
    WSACleanup();
}