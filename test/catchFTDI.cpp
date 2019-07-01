// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

#include "catch.h"
#include "customLibs/helper.h"

#include <libMPSSE_i2c.h>

/* Application specific macro definations */
#define I2C_DEVICE_ADDRESS			0x29
#define I2C_DEVICE_BUFFER_SIZE		256
#define I2C_WRITE_COMPLETION_RETRY	10

#define CHANNEL_TO_OPEN 1

uint8 buffer[I2C_DEVICE_BUFFER_SIZE];
FT_HANDLE ftHandle;

/*!
 * \brief Reads from EEPROM
 *
 * This function reads a byte from a specified address within the i2c device
 *
 * \param[in] slaveAddress Address of the I2C slave
 * \param[in] registerAddress Address 
 * \param[in] *data Address to where the byte is to be read
 * \return Returns status code of type FT_STATUS(see D2XX Programmer's Guide)
 * \note
 * \warning
 */
FT_STATUS read_byte(uint8 slaveAddress, uint8 registerAddress, uint8* data)
{
	FT_STATUS status;
	uint32 bytesToTransfer = 0;
	uint32 bytesTransfered;
	
	bytesToTransfer = 0;
	bytesTransfered = 0;

	buffer[bytesToTransfer++] = registerAddress;
	status = I2C_DeviceWrite(ftHandle, slaveAddress, bytesToTransfer, buffer, 
								 &bytesTransfered, I2C_TRANSFER_OPTIONS_START_BIT);
	bytesToTransfer = 1;
	bytesTransfered = 0;
	status |= I2C_DeviceRead(ftHandle, slaveAddress, bytesToTransfer, buffer, 
								&bytesTransfered, I2C_TRANSFER_OPTIONS_START_BIT);
	*data = buffer[0];
	return status;
}

SCENARIO("test some i2c communications to flight sense VL6180x") {
	GIVEN("open communication, read value, close communication") {
		FT_STATUS status;
		FT_DEVICE_LIST_INFO_NODE devList;
		uint32 channels;
		ChannelConfig channelConf;


		Init_libMPSSE();

		status = I2C_GetNumChannels(&channels);
		INFO_LOG << "Number of available I2C channels = " << channels << NL;

		if (channels > 0)
		{
			for (int i = 0; i < channels; i++)
			{
				status = I2C_GetChannelInfo(i, &devList);

				INFO_LOG << "Information on channel number : " << i << NL;
				INFO_LOG << "  Flags=" << devList.Flags << NL;
				INFO_LOG << "  Type=" << devList.Type << NL;
				INFO_LOG << "  ID=" << devList.ID << NL;
				INFO_LOG << "  LocId=" << devList.LocId << NL;
				INFO_LOG << "  SerialNumber=" << devList.SerialNumber << NL;
				INFO_LOG << "  Description=" << devList.Description << NL;
				INFO_LOG << "  ftHandle="<< devList.ftHandle << NL;
			}
		}

		channelConf.ClockRate = I2C_CLOCK_FAST_MODE;/*i.e. 400000 KHz*/
		channelConf.LatencyTimer = 255;
		//channelConf.Options = I2C_DISABLE_3PHASE_CLOCKING;
		channelConf.Options = I2C_ENABLE_DRIVE_ONLY_ZERO;

		/* Open the first available channel */
		status = I2C_OpenChannel(CHANNEL_TO_OPEN, &ftHandle);
		INFO_LOG << "handle= " << ftHandle << " status=" << status << NL;
		status = I2C_InitChannel(ftHandle, &channelConf);

		uint8 address = 0x00;
		uint8 data = 0x00;

		for (int runs = 100; runs > 0; runs--) {
			status = read_byte(I2C_DEVICE_ADDRESS, address, &data);
			INFO_LOG << "status: " << status << " data: " << data << NL;
			SLEEP_ms(1000);
		}


		Cleanup_libMPSSE();
	}

	INFO_LOG << "done" << '\n';
}
