#include "debug.h"
#include <stdio.h>
#include <iostream>

cDebug* cDebug::instance = NULL;

cDebug::cDebug() {
    command[0] = 0;
    command[1] = 1;
    command[2] = 2;
    command[3] = 3;
    command[4] = 4;
    connectToServer();
}

cDebug::~cDebug()
{}

cDebug* cDebug::getInstance() {
    if(!instance) {
        instance = new cDebug();
    }
    return instance;
}

int cDebug::connectToServer() {
    WSADATA data;
    int result = WSAStartup(MAKEWORD(2,2), &data);

    if (result != NO_ERROR) {
        printf("Client: Error at WSAStartup().\n");
    } else {
        printf("Client: WSAStartup() is OK.\n");
    }

    debugsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (debugsocket == INVALID_SOCKET) {
        printf("Client: socket() - Error at socket(): %ld\n", WSAGetLastError());
        WSACleanup();
        return 0;
    } else {
        printf("Client: socket() is OK.\n");
    }

    sockaddr_in clientservice;

    clientservice.sin_family = AF_INET;
    clientservice.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientservice.sin_port = htons(55555);

    if (connect(debugsocket, (SOCKADDR*)&clientservice, sizeof(clientservice)) == SOCKET_ERROR) {
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
    char* traceitems = "Init,Events,Audio,Mode,Slopes,Jump,Gravity,getHorScanPos,fCheckDirectionCollision,fPixelIsTransparant,Bullit";
    send(debugsocket,(char*)&command[3],1, 0);
    send(debugsocket,traceitems,(int)strlen(traceitems), 0);
    send(debugsocket,(char*)&command[4],1, 0);
}
void cDebug::prepareTrace(string trace, string text) {
    //if(text != lastTraceOutput){
        send(debugsocket,(char*)&command[0],1, 0);
        send(debugsocket,trace.c_str(),trace.length(), 0);
        send(debugsocket,(char*)&command[1],1, 0);
        send(debugsocket,text.c_str(),text.length(), 0);
        send(debugsocket,(char*)&command[2],1, 0);

        lasttraceoutput = text;
    //}
}
