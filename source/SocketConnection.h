#pragma once

#ifdef IS_WINDOWS
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#include <stdio.h>
#ifdef IS_VISUAL_STUDIO
		#include <BaseTsd.h>
		typedef SSIZE_T ssize_t;
#endif
#endif

#ifdef IS_MAC
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netdb.h>
	#include <net/if_dl.h>
#endif

#ifdef IS_LINUX
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <sys/time.h>
	#include <arpa/inet.h>
	#include <net/if.h>
	#include <netinet/tcp.h>
	#include <netinet/in.h>
	#include <unistd.h>
	#include <sys/ioctl.h>
#endif

#include <errno.h>

// base class
#include "interface/IConnection.h"
#include "interface/ISingleton.h"

// End of message tooken
static const char MESSAGE_END[] = "</msg>";
#ifdef IS_LINUX
static const int PORT_NBR = 1979;
#elif IS_MAC
static const int PORT_NBR = 1981;
#elif IS_WINDOWS
static const int PORT_NBR = 1978;
#else
static const int PORT_NBR = 2019; // default prot addr
#endif

static const int MAXPENDING = 5;
static const int BUFF_SIZE = 32768;

class SocketConnection : public IConnection, ISingleton {

public:

	// Message Header
	typedef struct _MSG_HEADER {
		int messageSize;
	} MSG_HEADER;

    // Return the one and only one instance
    static SocketConnection* getInstance();

    // Destructor
    virtual ~SocketConnection();

    // initialize
    virtual void initialize();

	// connect
	virtual bool connect();

	// disconnect
	virtual void disconnect();

	// Check for data
	virtual bool canReceiveData();

	// Receive data
	virtual bool receiveData(std::string& strData);

	// send data
	virtual bool sendData(const std::string& strData);

protected:

    // Constructor
    // protected because of singleton implementation
    // Constructor
    SocketConnection();

    // The one and only one instance
    static SocketConnection* _instance;

private:
	// tcp/ip stream
	int _iSocketStream;

	int	_socket;

	sockaddr_in _pRemoteAddress;
	sockaddr_in _pClientAddress;

	// buffer for sending
	char* _buffer;
	int _msgEnd;
};
