#include "USB2SPIDriver.h"
#include <stdexcept>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <cstring>

#include "SingletonCollector.h"
#include "customLibs/helper.h"

extern "C"{
#include <ftdi.h>
#include "myMpsse.h"
}

USB2SPIDriver* USB2SPIDriver::_instance = 0;

// SPI Mode 0
//static const unsigned char SPI_READ = 0x20;
//static const unsigned char SPI_WRITE = 0x11;

// SPI Mode 2
static const unsigned char SPI_READ = 0x24;
static const unsigned char SPI_WRITE = 0x10;

USB2SPIDriver* USB2SPIDriver::getInstance() {
    if (_instance == 0) {
        _instance = new USB2SPIDriver();
        if (SingletonCollector::available()) {
            SingletonCollector::getInstance()->addSingleton(_instance);
        }
    }
    return _instance;
}

USB2SPIDriver::USB2SPIDriver()
:_ftdi(0)
{
	initDriver();
}

USB2SPIDriver::~USB2SPIDriver()
{
	closeDriver();
}

void USB2SPIDriver::enableSPIMode()
{
	int ftStatus = 0;

	ftStatus = ftdi_usb_reset(_ftdi);
	ftStatus |= ftdi_usb_purge_buffers(_ftdi);
	ftStatus |= ftdi_read_data_set_chunksize(_ftdi, 65536);
	ftStatus |= ftdi_write_data_set_chunksize(_ftdi, 65535);
	ftStatus |= ftdi_set_event_char(_ftdi, 0, 0);
	ftStatus |= ftdi_set_error_char(_ftdi, 0, 0);
	_ftdi->usb_read_timeout = 0;
	_ftdi->usb_write_timeout = 5000;
	ftStatus |= ftdi_set_latency_timer(_ftdi, 16);
	//Reset controller
	ftStatus |= ftdi_set_bitmode(_ftdi, 0x00, 0x00);
	//Enable MPSSE mode
	ftStatus |= ftdi_set_bitmode(_ftdi, 0x00, 0x02);
	if (ftStatus != 0)			{
		throw std::runtime_error("fail on initialize ftdi device.");
	}
	// Wait for all the USB stuff to complete and work
	SLEEP_ms(50);

	// Synchronize the MPSSE interface by sending bad command 0xAA
	_outputBuffer.push_back(0xAA);
	ftStatus = ftdi_write_data(_ftdi, _outputBuffer.data(), _outputBuffer.size());
	_outputBuffer.clear();
	do{
		ftStatus = ftdi_read_data(_ftdi, _inputBuffer, _bufSize);
	}while (ftStatus == 0);

	if (!(ftStatus > 1 && _inputBuffer[0] == 0xFA && _inputBuffer[1] == 0xAA)){
		throw std::runtime_error("fail to synchronize MPSSE with command 0xAA");
	}

	// Synchronize the MPSSE interface by sending bad command 0xAB
	_outputBuffer.push_back(0xAB);
	ftStatus = ftdi_write_data(_ftdi, _outputBuffer.data(), _outputBuffer.size());
	_outputBuffer.clear();
	do{
		ftStatus = ftdi_read_data(_ftdi, _inputBuffer, _bufSize);
	}while (ftStatus == 0);

	if (!(ftStatus > 1 && _inputBuffer[0] == 0xFA && _inputBuffer[1] == 0xAB)){
		throw std::runtime_error("fail to synchronize MPSSE with command 0xAB");
	}

	_outputBuffer.clear();
	_defaultPortSettings = CS | SK; // SK and CS idle high
	_ioConfig = 0xEB; // CS=output, DI=input, DO=output, SK=output

	_outputBuffer.push_back(SET_BITS_LOW);
	_outputBuffer.push_back(_defaultPortSettings);
	_outputBuffer.push_back(_ioConfig);

    // set the clock divisor to 1MHz
	_outputBuffer.push_back(TCK_DIVISOR);
	_outputBuffer.push_back(0x05); // low byte
	_outputBuffer.push_back(0x00); // high byte
	_outputBuffer.push_back(LOOPBACK_END);
	ftdi_write_data(_ftdi, _outputBuffer.data(), _outputBuffer.size());
	_outputBuffer.clear();
}

void USB2SPIDriver::initDriver()
{
	//const int vid = 0x0403;
	//const int pid = 0x6010;
    //if ((_ftdi = ftdi_new()) == 0){
    //	throw std::runtime_error("Could not init ftdi context");
    //}
    //if(ftdi_set_interface(_ftdi, INTERFACE_A) < 0){
    //	throw std::runtime_error("Could not open ftdi interface A");
    //}
    //if (ftdi_usb_open(_ftdi, vid, pid) < 0){
    //	throw std::runtime_error("Could not open ftdi device");
    //}
    //enableSPIMode();

	_mpsse = MPSSE(SPI2, ONE_MHZ, MSB);
}



void USB2SPIDriver::runDriver()
{
}

void USB2SPIDriver::resetDriver()
{
    closeDriver();
    initDriver();
}

void USB2SPIDriver::closeDriver()
{
	//ftdi_usb_close(_ftdi);
	//ftdi_free(_ftdi);
	Close(_mpsse);
}

void USB2SPIDriver::write(const unsigned char* data, int dataSize)
{
//	_outputBuffer.clear();
//	uint16_t size = dataSize - 1;
//	unsigned char lsb = (unsigned char)(size & 0xFF);
//	unsigned char msb = (unsigned char)((size >> 8) & 0xFF);
//	_outputBuffer.push_back(SPI_WRITE);
//	_outputBuffer.push_back(msb);
//	_outputBuffer.push_back(lsb);
//	for(int i = 0; i < dataSize; ++i){
//		_outputBuffer.push_back(data[i]);
//	}
//	ftdi_write_data(_ftdi, _outputBuffer.data(), _outputBuffer.size());
	Write(_mpsse, (char*)data, dataSize);
}

void USB2SPIDriver::purgeReadBuffer()
{
	//int bytesRead = 0;
	//do{
	//	bytesRead = ftdi_read_data(_ftdi, _inputBuffer, _bufSize);
	//}while(bytesRead != 0);
}

void USB2SPIDriver::read(unsigned char* data, int dataSize)
{
	char* buffer = Read(_mpsse, dataSize);
	std::memcpy(data, buffer, dataSize);
//	_outputBuffer.clear();
//	uint16_t size = dataSize - 1;
//	unsigned char lsb = (unsigned char)(size & 0xFF);
//	unsigned char msb = (unsigned char)((size >> 8) & 0xFF);
//	_outputBuffer.push_back(SPI_READ);
//	_outputBuffer.push_back(msb);
//	_outputBuffer.push_back(lsb);
//	_outputBuffer.push_back(SEND_IMMEDIATE);
//	ftdi_write_data(_ftdi, _outputBuffer.data(), _outputBuffer.size());
//	_outputBuffer.clear();
//	int bytesRead = 0;
//	do{
//    	bytesRead = ftdi_read_data(_ftdi, _inputBuffer, _bufSize);
//    }while(bytesRead == 0 && !(bytesRead < 0));
//    if(bytesRead < 0){
//    	throw std::runtime_error("Could not read from ftdi device.");
//    }
//    for(int i = 0; i < bytesRead; ++i)
//    	data[i] = _inputBuffer[i];
}

void USB2SPIDriver::beginFrame()
{
	//_outputBuffer.clear();
	//_outputBuffer.push_back(SET_BITS_LOW);
	//_outputBuffer.push_back(_defaultPortSettings &= ~CS);
	//_outputBuffer.push_back(_ioConfig);
	//ftdi_write_data(_ftdi, _outputBuffer.data(), _outputBuffer.size());
	Start(_mpsse);
}

void USB2SPIDriver::endFrame()
{
	//_outputBuffer.clear();
	//_outputBuffer.push_back(SET_BITS_LOW);
	//_outputBuffer.push_back(_defaultPortSettings |= CS);
	//_outputBuffer.push_back(_ioConfig);
	//ftdi_write_data(_ftdi, _outputBuffer.data(), _outputBuffer.size());
	Stop(_mpsse);
}

bool USB2SPIDriver::waitForConversion()
{
	_outputBuffer.clear();
    // Wait for GPIOL0 to go low this signals end of conversion
    int loopCnt = 0;
	_outputBuffer.push_back(GET_BITS_LOW);
	_outputBuffer.push_back(SEND_IMMEDIATE);
	int bytesRead = 0;
    do{
    	ftdi_write_data(_ftdi, _outputBuffer.data(), _outputBuffer.size());
    	do{
    		bytesRead = ftdi_read_data(_ftdi, _inputBuffer, _bufSize);
    	}while(bytesRead == 0 && !bytesRead < 0);
    	if(bytesRead < 0){
    		throw std::runtime_error("Could not read from ftdi device.");
    	}
    	//DEBUG_LOG << "read ftdi low bits: " << (int)(_inputBuffer[0]) << '\n';
    	// check GPIOL0 for 0 bit
    }while(((_inputBuffer[0] & GPIO0) > 0) && (loopCnt++ < 100));
    if((_inputBuffer[0] & GPIO0) > 0){
    	return false;
    	//throw std::runtime_error("Did not get conversion finished signal from A/D chip.");
    }
    return true;
}

