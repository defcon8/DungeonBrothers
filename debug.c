#include "debug.h"
#include <stdio.h>
#include <string>
#include <iostream>


cDebug::cDebug()
{
  fConnect();
}

int cDebug::fConnect()
{
   // Initialize Winsock.
//    WSADATA wsaData;
//    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
//
//    if (iResult != NO_ERROR)
//         printf("Client: Error at WSAStartup().\n");
//    else
//         printf("Client: WSAStartup() is OK.\n");
//
//     Create a socket.
//
//    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//
//    if (m_socket == INVALID_SOCKET)
//    {
//        printf("Client: socket() - Error at socket(): %ld\n", WSAGetLastError());
//        WSACleanup();
//        return 0;
//    }
//    else
//       printf("Client: socket() is OK.\n");
//
//     Connect to a server.
//    sockaddr_in clientService;
//
//    clientService.sin_family = AF_INET;
//    clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
//    clientService.sin_port = htons(55555);
//
//    if (connect(m_socket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR)
//    {
//        printf("Client: connect() - Failed to connect.\n");
//        WSACleanup();
//        return 0;
//    }
//
//     Send and receive data.
//    int bytesSent;
//    int bytesRecv = SOCKET_ERROR;
//
//     Be careful with the array bound, provide some checking mechanism
//    char sendbuf[200] = "Application connected...\n\r";
//    bytesSent = send(m_socket, sendbuf, strlen(sendbuf), 0);
//    printf("Client: send() - Bytes Sent: %ld\n", bytesSent);
//
//    return 0;
}

cDebug::~cDebug()
{}

//void cDebug::fSend(string buffer)
//{
//send(m_socket, chBuffer, sizeof(&chBuffer), 0);
//}
