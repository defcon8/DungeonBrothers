#include <winsock2.h>
#include <string>
#include "config.h"
#ifndef DEBUG_H_
#define DEBUG_H_

using namespace std;

class cDebug {

private:
    cDebug();
    static cDebug* instance;
    SOCKET debugsocket;
    int connectToServer();

public:
    static cDebug* getInstance();
    ~cDebug();
    void sendTraceItems();
    void prepareTrace(string trace, string text);
    byte command[5];
};

//! Debug message creation macro
#define TRACE(traceitem, ...)                                           \
    do {                                                                \
        char __message[512];                                            \
        snprintf(__message, 512, __VA_ARGS__);                          \
        string output(__message);                                       \
        cDebug::getInstance()->prepareTrace(traceitem, output);   \
    } while(0)



#endif /* DEBUG_H_ */
