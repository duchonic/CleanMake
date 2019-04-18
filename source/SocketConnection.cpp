#include "SocketConnection.h"

#include "customLibs/helper.h"

//#include <signal.h>

#include "SingletonCollector.h"

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

void SocketConnection::initialize()
{
	DEBUG_LOG << "initialize socket connection" << '\n';

    _socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    memset(&_pRemoteAddress, 0, sizeof(_pRemoteAddress));       /* Clear struct */
    _pRemoteAddress.sin_family = AF_INET;						/* Internet/IP */
    _pRemoteAddress.sin_addr.s_addr = htonl(INADDR_ANY);		/* Incoming addr */
#ifdef IS_MAC
    _pRemoteAddress.sin_port = htons(898);
#else
    _pRemoteAddress.sin_port = htons(PORT_NBR);					/* server port */
#endif
    bind(_socket, (struct sockaddr *) &_pRemoteAddress, sizeof(_pRemoteAddress));
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

#ifdef IS_WINDOWS
    INFO_LOG << "Connected to SYS at " << inet_ntoa(_pClientAddress.sin_addr) << '\n';
#elif IS_LINUX
	INFO_LOG << "Connected to SYS at " << inet_ntoa(_pClientAddress.sin_addr) << '\n';
#endif
	return true;
}

void SocketConnection::disconnect()
{
	//close(_iSocketStream);
	//close(_socket);
}

bool SocketConnection::canReceiveData()
{
	char buffer;
	ssize_t size = recv(_iSocketStream, &buffer, 1, MSG_PEEK);
    if(size < 0 && errno != EAGAIN){
    	ERROR_LOG << "Lost connection to SYS" << '\n';
        //raise(SIGUSR1); // raise sigusr1 to make a proper shutdown

        return false;
    }
	bool bufferHasData = false;
    if(_msgEnd >= 0)
    	bufferHasData = true;
	return bufferHasData || size > 0;
}

bool SocketConnection::receiveData(std::string& strData)
{
	char* endTag = 0;
	ssize_t size = 0;
    strData.clear();
	while(!endTag){
		size = recv(_iSocketStream, &(_buffer[_msgEnd + 1]), BUFF_SIZE - (_msgEnd + 1), 1);
		std::cout << '\n';
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
