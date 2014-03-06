#include <winsock2.h>
#include <string>
#ifndef DEBUG_H_
#define DEBUG_H_

using namespace std;

class cDebug {

private:
    //! Initializes a instance of the cDebug class
    cDebug();

    static cDebug* s_pInstance;  //!< Private pointer to the singleton object

    SOCKET m_socket;
    int connectToServer();

public:
    static cDebug* getInstance(); //!< Function to get the singleton instance
    ~cDebug();

    void prepareTrace(string trace, string text);
    byte bCommand[2];
};

//! Debug message creation macro
#define TRACE(traceitem, ...)                                           \
    do {                                                                \
        char __message[512];                                            \
        snprintf(__message, 512, __VA_ARGS__);                          \
        string output(__message);                                       \
        CDevelopTools::getInstance().prepareTrace(traceitem, output);   \
    } while(0)



#endif /* DEBUG_H_ */
