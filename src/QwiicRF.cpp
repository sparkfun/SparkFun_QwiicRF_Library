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

#include "QwiicRF.h"

//Attempt communication with the device
//Return true if we got a 'Polo' back from Marco
void QwiicRF::begin(uint8_t deviceAddress, TwoWire &wirePort)
{
  _deviceAddress = deviceAddress;
  _i2cPort = &wirePort;
}

//Change the address we read and write to
void QwiicRF::setI2CAddress(uint8_t addr)
{
  _deviceAddress = addr;
}

/********************************************************
 * Functions 
 ********************************************************
 * 
 *    
 ********************************************************/
void QwiicRF::Send(byte i2c_addr, byte rf_addr, String payload)
{
  Wire.beginTransmission(i2c_addr);
  Wire.write(0x02); // Command: Send
  Wire.write(rf_addr); // Recipient: i2c_addr
  for(byte len = 0; len < payload.length(); len++){
    Wire.write(payload.charAt(len));
  }
  Wire.endTransmission();
}

void QwiicRF::SendReliable(byte i2c_addr, byte rf_addr, String payload)
{
  Wire.beginTransmission(i2c_addr);
  Wire.write(0x03); // Command: Send Reliable
  Wire.write(rf_addr); // Recipient: i2c_addr
  for(byte len = 0; len < payload.length(); len++){
    Wire.write(payload.charAt(len));
  }
  Wire.endTransmission();
}

String QwiicRF::Read(byte i2c_addr)
{
  byte payloadSize;
  String payload = "";
  Wire.beginTransmission(i2c_addr);
  Wire.write(0x0B); // Command: Get Payload Size
  Wire.endTransmission(false);
  Wire.requestFrom(i2c_addr, 1);
  while (Wire.available()) {
    payloadSize = Wire.read();
  }
  Wire.beginTransmission(i2c_addr);
  Wire.write(0x05); // Command: Get Payload
  Wire.endTransmission(false);
  Wire.requestFrom(i2c_addr, payloadSize);
  while (Wire.available()) {
    payload += (char)Wire.read();
  }
  return payload;
}

boolean QwiicRF::HasPayload(byte i2c_addr)
{
  byte qrfStatus = 0x00;
  Wire.beginTransmission(i2c_addr);
  Wire.write(0x01); // Command: Get Status
  Wire.endTransmission(false);
  Wire.requestFrom(i2c_addr, 1);
  while (Wire.available()) {
    qrfStatus = Wire.read();
  }

  return bitRead(qrfStatus, 1);
  
}

boolean QwiicRF::IsReady(byte i2c_addr)
{
  byte qrfStatus = 0x00;
  Wire.beginTransmission(i2c_addr);
  Wire.write(0x01); // Command: Get Status
  Wire.endTransmission(false);
  Wire.requestFrom(i2c_addr, 1);
  while (Wire.available()) {
    qrfStatus = Wire.read();
  }

  return bitRead(qrfStatus, 0);
  
}

byte QwiicRF::GetStatus(byte i2c_addr){
    byte qrfStatus = 0x00;
  Wire.beginTransmission(i2c_addr);
  Wire.write(0x01); // Command: Get Status
  Wire.endTransmission(false);
  Wire.requestFrom(i2c_addr, 1);
  while (Wire.available()) {
    qrfStatus = Wire.read();
  }

  return qrfStatus;
}

void QwiicRF::SetReliableTimeout(byte i2c_addr, byte seconds)
{
  Wire.beginTransmission(i2c_addr);
  Wire.write(0x04); // Command: Send
  Wire.write(seconds); // Recipient: i2c_addr
  Wire.endTransmission(); 
}

boolean QwiicRF::IsWaiting(byte i2c_addr)
{
  byte qrfStatus = 0x00;
  Wire.beginTransmission(i2c_addr);
  Wire.write(0x01); // Command: Get Status
  Wire.endTransmission(false);
  Wire.requestFrom(i2c_addr, 1);
  while (Wire.available()) {
    qrfStatus = Wire.read();
  }

  return bitRead(qrfStatus, 2);  
}

boolean QwiicRF::ReliableFailed(byte i2c_addr)
{
  byte qrfStatus = 0x00;
  Wire.beginTransmission(i2c_addr);
  Wire.write(0x01); // Command: Get Status
  Wire.endTransmission(false);
  Wire.requestFrom(i2c_addr, 1);
  while (Wire.available()) {
    qrfStatus = Wire.read();
  }

  return bitRead(qrfStatus, 3);  
}

byte QwiicRF::GetSyncWord(byte i2c_addr){
    byte qrfSync = 0x00;
  Wire.beginTransmission(i2c_addr);
  Wire.write(0x11); // Command: Get Sync Word
  Wire.endTransmission(false);
  Wire.requestFrom(i2c_addr, 1);
  while (Wire.available()) {
    qrfSync = Wire.read();
  }

  return qrfSync;
}

void QwiicRF::SetSyncWord(byte i2c_addr, byte syncword)
{
  Wire.beginTransmission(i2c_addr);
  Wire.write(0x07); // Command: Set Sync Word
  Wire.write(syncword); // Recipient: i2c_addr
  Wire.endTransmission(); 
}

/********************************************************
 * Functions for setting and getting registers over I2C
 ******************************************************** 
 * 
 * setRegister() - set unsigned char value at unsigned char register
 * 
 * getRegister() - get up to INT16 value from unsigned char register
 * 
 ********************************************************/

void QwiicRF::setRegister(unsigned char reg, unsigned char val)
{

    _i2cPort->beginTransmission(_deviceAddress);
    _i2cPort->write(reg);
    _i2cPort->write(val);
    _i2cPort->endTransmission();
    
}

int16_t QwiicRF::getRegister(unsigned char reg, int8_t len)
{

  int16_t result;

    _i2cPort->beginTransmission(_deviceAddress);
    _i2cPort->write(reg);
    _i2cPort->endTransmission(false);
    _i2cPort->requestFrom((uint8_t)_deviceAddress, (uint8_t)len);

    while(_i2cPort->available())    // client may send less than requested
    {
      // Get bytes from sensor
      uint8_t lsb = _i2cPort->read(); 
      uint8_t msb = _i2cPort->read(); 
  
      // concat bytes into int
      result = (uint16_t)msb << 8 | lsb;
    }

    _i2cPort->endTransmission();

    return result;
                         
}