#include "SocketConnection.h"

#include "customLibs/helper.h"

#include <cassert>
#include "SingletonCollector.h"

#include <Windows.h>

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512


SocketConnection* SocketConnection::_instance = 0;

SocketConnection* SocketConnection::getInstance()
{
    if (_instance == 0) {
        _instance = new SocketConnection();
        if (SingletonCollector::available()) {
            SingletonCollector::getInstance()->addSingleton(_instance);
        }
    }
    return _instance;
}

SocketConnection::SocketConnection()
:_iSocketStream(0),_socket(0), _buffer(0), _msgEnd(-1)
{
	_buffer = new char[BUFF_SIZE + 1];
}

SocketConnection::~SocketConnection()
{
	delete[] _buffer;
}

void SocketConnection::initialize(){
	DEBUG_LOG << "initialize socket connection" << '\n';
    
#ifdef IS_WINDOWS	
	struct addrinfo* result = NULL;
	struct addrinfo hints;

	// Declare and initialize variables
	WSADATA wsaData;

	// Initialize Winsock
	assert(WSAStartup(MAKEWORD(2, 2), &wsaData) == 0);

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the local address and port to be used by the server
	assert(getaddrinfo(NULL, DEFAULT_PORT, &hints, &result) == 0);

	_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	assert(_socket != INVALID_SOCKET);

#else
	_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
#endif

    memset(&_pRemoteAddress, 0, sizeof(_pRemoteAddress));       /* Clear struct */
    _pRemoteAddress.sin_family = AF_INET;						/* Internet/IP */
    _pRemoteAddress.sin_addr.s_addr = htonl(INADDR_ANY);		/* Incoming addr */
    _pRemoteAddress.sin_port = htons(PORT_NBR);					/* server port */
    bind(_socket, (struct sockaddr *) &_pRemoteAddress, sizeof(_pRemoteAddress));
	DEBUG_LOG << "sin_family: " << _pRemoteAddress.sin_family << " sin_addr: " << _pRemoteAddress.sin_addr.s_addr << " sin_port: " << _pRemoteAddress.sin_port << '\n';
}

bool SocketConnection::connect()
{

	if (listen(_socket, MAXPENDING) < 0) {
		DEBUG_LOG << "socket error: " << listen(_socket, MAXPENDING) << '\n';
		//return false;
	}

#ifdef IS_WINDOWS
	int clientlen = sizeof(_pClientAddress);
#else
	unsigned int clientlen = sizeof(_pClientAddress);
#endif

    DEBUG_LOG << "Waiting for SYS connection..." << '\n';

	/* Wait for client connection */
    if ((_iSocketStream = accept(_socket, (struct sockaddr *) &_pClientAddress, &clientlen)) < 0) {
    	return false;
    }

    INFO_LOG << "Connected to SYS at " << inet_ntoa(_pClientAddress.sin_addr) << '\n';
	return true;
}

void SocketConnection::disconnect()
{
	//close(_iSocketStream);
	//close(_socket);
}

bool SocketConnection::canReceiveData()
{

#ifdef asdf
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	int iResult;

	// Receive until the peer closes the connection
	do {
		iResult = recv(_iSocketStream, recvbuf, recvbuflen, 0);
		if (iResult > 0)
			printf("Bytes received: %d\n", iResult);
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed: %d\n", WSAGetLastError());
	} while (iResult > 0);
	
	DEBUG_LOG << "nothing received" << '\n';

	return 0;
#else
	char buffer;
	ssize_t size = recv(_iSocketStream, &buffer, 1, MSG_PEEK);
	DEBUG_LOG << "msg size: " << size << '\n';

    if(size < 0 && errno != EAGAIN){
    	ERROR_LOG << "Lost connection to SYS" << '\n';
        //raise(SIGUSR1); // raise sigusr1 to make a proper shutdown
        return false;
    }
	bool bufferHasData = false;
    if(_msgEnd >= 0)
    	bufferHasData = true;
	return bufferHasData || size > 0;
#endif

}

bool SocketConnection::receiveData(std::string& strData)
{
	char* endTag = 0;
	ssize_t size = 0;
    strData.clear();
	while(!endTag){

		DEBUG_LOG << "dada received recv started" << '\n';
		size = recv(_iSocketStream, &(_buffer[_msgEnd + 1]), BUFF_SIZE - (_msgEnd + 1), 1);
		DEBUG_LOG << "dada received recv ended size:" << size << '\n';

        //if(size < 0 && errno != EAGAIN && errno != EWOULDBLOCK && errno != ENOENT){
        //	ERROR_LOG << "Lost connection to SYS" << '\n';
        //	//raise(SIGUSR1); // raise sigusr1 to make a proper shutdown

        //    return false;
        //}
        if(size < 0)
        	size = 0;
		_buffer[_msgEnd + size + 1] = '\0';
        endTag = strstr(_buffer, MESSAGE_END);
		if(endTag){
			// whole message received
			strData.append(_buffer, endTag + strlen(MESSAGE_END));
			// if we read too much copy it to the front of the buffer
			int i = 0;
            char* p = endTag + strlen(MESSAGE_END);
			while(p != &(_buffer[_msgEnd + 1]) + size){
				_buffer[i] = *p;
				++p;
				++i;
			}
			_msgEnd = i - 1;
		}else{
			_msgEnd += size;
		}

	}
	return true;
}

bool SocketConnection::sendData(const std::string& strData)
{
	ssize_t rc = 0; // write(_iSocketStream, strData.c_str(), strData.size() + 1);
	return rc >= 0;
}
