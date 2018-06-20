/*
  This is a library written for the QwiicRF LoRa Radio Module
  SparkFun sells these at its website: www.sparkfun.com
  Do you like this library? Help support SparkFun. Buy a board!
  https://www.sparkfun.com/products/14788 

  Written by Nick Poole @ SparkFun Electronics, June 20, 2018
 
  https://github.com/sparkfun/SparkFun_QwiicRF_Library
  https://github.com/sparkfunX/Qwiic_RF

  Development environment specifics:
  Arduino IDE 1.8.3

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>

//The default I2C address for the QwiicRF is 0x35. This can be changed to 0x36 with a solder jumper
//or to an arbitrary value using the setI2CAddress() function.
#define DEFAULT_ADDRESS 0x35

//Platform specific configurations

//Define the size of the I2C buffer based on the platform the user has
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)

//I2C_BUFFER_LENGTH is defined in Wire.H
#define I2C_BUFFER_LENGTH BUFFER_LENGTH

#elif defined(__SAMD21G18A__)

//SAMD21 uses RingBuffer.h
#define I2C_BUFFER_LENGTH SERIAL_BUFFER_SIZE

#elif __MK20DX256__
//Teensy

#elif ARDUINO_ARCH_ESP32
//ESP32 based platforms

#else

//The catch-all default is 32
#define I2C_BUFFER_LENGTH 32

#endif
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//Registers
#define COMMAND_GET_STATUS 0x01
#define COMMAND_SEND 0x02
#define COMMAND_SEND_RELIABLE 0x03
#define COMMAND_SET_RELIABLE_TIMEOUT 0x04
#define COMMAND_GET_PAYLOAD 0x05
#define COMMAND_SET_SPREAD_FACTOR 0x06
#define COMMAND_SET_SYNC_WORD 0x07
#define COMMAND_GET_SYNC_WORD 0x11
#define COMMAND_SET_RF_ADDRESS 0x08
#define COMMAND_GET_RF_ADDRESS 0x09
#define COMMAND_GET_PACKET_RSSI 0x0A
#define COMMAND_GET_PAYLOAD_SIZE 0x0B
#define COMMAND_GET_PACKET_SENDER 0x0C
#define COMMAND_GET_PACKET_RECIPIENT 0x0D
#define COMMAND_GET_PACKET_SNR 0x0E
#define COMMAND_GET_PACKET_ID 0x0F
#define COMMAND_SET_TX_POWER 0x10
#define COMMAND_SET_I2C_ADDRESS 0x20
#define COMMAND_SET_PAIRED_ADDRESS 0x12
#define COMMAND_GET_PAIRED_ADDRESS 0x13
#define COMMAND_GET_SKU 0x15
#define COMMAND_SEND_PAIRED 0x20
#define COMMAND_SEND_RELIABLE_PAIRED 0x30

//Bit Checking Macro
#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

class QwiicRF {
  public:

    // Return values

    //By default use the default I2C addres, and use Wire port
    void begin(uint8_t deviceAddress = DEFAULT_ADDRESS, TwoWire &wirePort = Wire);

	byte getStatus();
	boolean hasPayload();
	boolean isReady();
	void setReliableTimeout(byte seconds);
	boolean waitingForAck();
	boolean reliableFailed();
	
	boolean send(byte rf_addr, String payload);
	boolean send(String payload);
	boolean sendReliable(byte rf_addr, String payload);
	boolean sendReliable(String payload);
	String read();
	byte getPayloadSize();
	
	byte getSyncWord();
	void setSyncWord(byte syncword);
	byte getRFAddress();
	void setRFAddress(byte addr);
	byte getPairedAddress();
	void setPairedAddress(byte addr);
	void setSpreadFactor(byte sf);
	void setReliableSendTimeout(byte seconds);
	void setTXPower(byte power);
	void setI2CAddress(byte addr);
	
	byte getPacketRSSI();
	byte getPacketSNR();
	byte getPacketOrigin();
	byte getPacketDestination();
	byte getPacketID();

  private:
  
    TwoWire *_i2cPort; //The generic connection to user's chosen I2C hardware
    uint8_t _deviceAddress; //Keeps track of I2C address. setI2CAddress changes this.

};
