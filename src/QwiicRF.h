/*
  This is a library written for the  
  SparkFun sells these at its website: www.sparkfun.com
  Do you like this library? Help support SparkFun. Buy a board!
  https://www.sparkfun.com/products/ 

  Written by Nick Poole @ SparkFun Electronics,  

 

  https://github.com/sparkfun/ 

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

//The default I2C address for the THING on the SparkX breakout is 0x69. 0x68 is also possible.
#define DEFAULT_ADDRESS 0x69

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

class GridEYE {
  public:

    // Return values

    //By default use the default I2C addres, and use Wire port
    void begin(uint8_t deviceAddress = DEFAULT_ADDRESS, TwoWire &wirePort = Wire);

    void setI2CAddress(uint8_t addr); //Set the I2C address we read and write to

  private:
  
    TwoWire *_i2cPort; //The generic connection to user's chosen I2C hardware
    uint8_t _deviceAddress; //Keeps track of I2C address. setI2CAddress changes this.

};
