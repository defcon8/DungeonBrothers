#include <winsock2.h>
#include <string>
#ifndef DEBUG_H_
#define DEBUG_H_

using namespace std;

class cDebug {

private:
    //! Initializes a instance of the cDebug class
    cDebug();

    static cDebug* instance;  //!< Private pointer to the singleton object

    SOCKET debugsocket;
    int connectToServer();
    string lasttraceoutput;

public:
    static cDebug* getInstance(); //!< Function to get the singleton instance
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
