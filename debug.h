#include <winsock2.h>


class cDebug {             

  private:
    SOCKET m_socket;      
    int fConnect();

  public:

    cDebug();
    ~cDebug();
    //void fSend(string buffer);
    
};
