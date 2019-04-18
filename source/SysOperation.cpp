#include "SysOperation.h"
#include "customLibs/helper.h"

#include "interface/IConnection.h"

#include "SingletonCollector.h"
#include "ConnectionFactory.h"

#include "XMLMessage.h"

// static initialization
SysOperation* SysOperation::_instance = 0;


// Constructor
// protected because of singleton implementation
SysOperation::SysOperation()
	: _bMessageArrived(false), _messageString(""), _pConnection(0) {
}

// Destructor
SysOperation::~SysOperation() {
	_instance = 0;

	// Erase all pending messages
	for (unsigned int i = 0; i < _vecMessages.size(); i++) {
		delete _vecMessages[i];
	}
	_vecMessages.erase(_vecMessages.begin(), _vecMessages.end());
}

// Returns the one and only one instance
SysOperation* SysOperation::getInstance() {
	if (_instance == 0) {
		_instance = new SysOperation();
		if (SingletonCollector::available()) {
			SingletonCollector::getInstance()->addSingleton(_instance);
		}
	}
	return _instance;
}


bool SysOperation::hasMessageArrived() const {
	static bool hasArrived = false;

	if (hasArrived){
		hasArrived = false;
		return false;
	}
	else {
		hasArrived = true;
		return true;
	}
	//return _bMessageArrived;
}

// getMessage
// <<offline>>
IMessage* SysOperation::getMessage() {

#ifdef IS_MAC
  return NULL;
#else
	static XMLMessage message;
	message.setMessageString(_messageString);
	_bMessageArrived = false;
	return &message;
#endif

}

// sendMessage
// <<offline>>
void SysOperation::sendMessage(IMessage* pMessage) {
	_vecMessages.push_back(pMessage);
}

// init the driver
// <<online>>
void SysOperation::initDriver() {
	_pConnection = ConnectionFactory::getConnection("SocketConnection");

	if (_pConnection == 0) {
		ERROR_LOG << "No valid connection" << '\n';
	}
	else {
		_pConnection->initialize();
		if (!_pConnection->connect()) {
			ERROR_LOG << "Failed to establish connection to SYS" << '\n';
		}
		else {
			DEBUG_LOG << "Connect done" << '\n';
		}
	}
}

// do the driver work
// <<online>>
void SysOperation::runDriver() {

	// First check for new message
	if (_pConnection->canReceiveData()) {
		if (_pConnection->receiveData(_messageString)) {
			DEBUG_LOG << "Data received: " << _messageString << '\n';
			_bMessageArrived = true;
		}
	}

	// And then send all available messages
	for (std::vector<IMessage*>::iterator it = _vecMessages.begin(); it != _vecMessages.end(); it++) {
		IMessage* pMessage = *it;
		const std::string str(pMessage->toString());
		if (_pConnection->sendData(str)) {
			DEBUG_LOG << "Message sent: " << str << '\n';
		}
		delete pMessage;
	}
	_vecMessages.erase(_vecMessages.begin(), _vecMessages.end());
}

// reset the drive to a defined state
// <<offline>>
void SysOperation::resetDriver() {
}

// close the driver
// <<online>>
void SysOperation::closeDriver() {
}
