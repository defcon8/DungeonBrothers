#include "debug.h"
#include <stdio.h>
#include <iostream>

cDebug* cDebug::s_pInstance = NULL;

cDebug::cDebug() {
    bCommand[0] = 0;
    bCommand[1] = 1;
    bCommand[2] = 2;
    bCommand[3] = 3;
    bCommand[4] = 4;
    connectToServer();
}

cDebug::~cDebug()
{}

cDebug* cDebug::getInstance() {
    if(!s_pInstance) {
        s_pInstance = new cDebug();
    }
    return s_pInstance;
}

int cDebug::connectToServer() {
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

    if (iResult != NO_ERROR) {
        printf("Client: Error at WSAStartup().\n");
    } else {
        printf("Client: WSAStartup() is OK.\n");
    }

    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (m_socket == INVALID_SOCKET) {
        printf("Client: socket() - Error at socket(): %ld\n", WSAGetLastError());
        WSACleanup();
        return 0;
    } else {
        printf("Client: socket() is OK.\n");
    }

    sockaddr_in clientService;

    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientService.sin_port = htons(55555);

    if (connect(m_socket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
        printf("Client: connect() - Failed to connect.\n");
        WSACleanup();
        return 0;
    }

    sendTraceItems();
    prepareTrace("INFO","Hi! I am connected.\n");

    return 0;
}


void cDebug::sendTraceItems()
{
    char* chTraceItems = "Init,Mode,Slopes,Jump,Gravity,getHorScanPos,fCheckDirectionCollision,fPixelIsTransparant,Bullit";
    send(m_socket,(char*)&bCommand[3],1, 0);
    send(m_socket,chTraceItems,(int)strlen(chTraceItems), 0);
    send(m_socket,(char*)&bCommand[4],1, 0);
}
void cDebug::prepareTrace(string trace, string text) {
    //if(text != lastTraceOutput){
        send(m_socket,(char*)&bCommand[0],1, 0);
        send(m_socket,trace.c_str(),trace.length(), 0);
        send(m_socket,(char*)&bCommand[1],1, 0);
        send(m_socket,text.c_str(),text.length(), 0);
        send(m_socket,(char*)&bCommand[2],1, 0);

        lastTraceOutput = text;
    //}
}
