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

#include "QwiicRF.h"

void QwiicRF::begin(uint8_t deviceAddress, TwoWire &wirePort)
{
  _deviceAddress = deviceAddress;
  _i2cPort = &wirePort;
  _i2cPort->begin();
}

/********************************************************
 * Status Checking Functions 
 *******************************************************/

// Get a 4 bit status report from the QwiicRF
// Bit 0 - Ready to Send
// Bit 1 - Packet Available to Read
// Bit 2 - Waiting on Reliable Send Ack
// Bit 3 - Previous Reliable Send Timed Out
byte QwiicRF::getStatus()
{
  byte qrfStatus = 0x00;
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_GET_STATUS);
  _i2cPort->endTransmission(false);
  _i2cPort->requestFrom(_deviceAddress, 1);
  while ( _i2cPort->available() ) 
  {
    qrfStatus = _i2cPort->read();
  }

  return qrfStatus;
} 
 
// Returns True if the QwiicRF has a payload available to read 
boolean QwiicRF::hasPayload()
{
  byte qrfStatus = 0x00;
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_GET_STATUS); 
  _i2cPort->endTransmission(false);
  _i2cPort->requestFrom(_deviceAddress, 1);
  while ( _i2cPort->available() ) 
  {
    qrfStatus = _i2cPort->read();
  }

  return CHECK_BIT(qrfStatus, 1);
  
}

// Returns True if the QwiicRF is ready to send messages
boolean QwiicRF::isReady()
{
  byte qrfStatus = 0x00;
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_GET_STATUS); 
  _i2cPort->endTransmission(false);
  _i2cPort->requestFrom(_deviceAddress, 1);
  while ( _i2cPort->available() ) 
  {
    qrfStatus = _i2cPort->read();
  }

  return CHECK_BIT(qrfStatus, 0);
  
}

// Set the time in seconds before a reliable send operation fails
void QwiicRF::setReliableSendTimeout(byte seconds)
{
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_SET_RELIABLE_TIMEOUT);
  _i2cPort->write(seconds); 
  _i2cPort->endTransmission(); 
}

// Returns True if the QwiicRF is waiting for an Ack for 
// the previous reliable send operation
boolean QwiicRF::waitingForAck()
{
  byte qrfStatus = 0x00;
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_GET_STATUS); 
  _i2cPort->endTransmission(false);
  _i2cPort->requestFrom(_deviceAddress, 1);
  while ( _i2cPort->available() ) 
  {
    qrfStatus = _i2cPort->read();
  }

  return CHECK_BIT(qrfStatus, 2); 
}

// Returns True if the previous reliable send operation timed out
// before receiving a valid Ack
boolean QwiicRF::reliableFailed()
{
  byte qrfStatus = 0x00;
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_GET_STATUS); 
  _i2cPort->endTransmission(false);
  _i2cPort->requestFrom(_deviceAddress, 1);
  while ( _i2cPort->available() ) 
  {
    qrfStatus = _i2cPort->read();
  }

  return CHECK_BIT(qrfStatus, 3); 
} 
 
/********************************************************
 * Send and Receive Functions 
 *******************************************************/ 

// Send a string to a particular RF address
boolean QwiicRF::send(byte rf_addr, String payload)
{
  byte qrfStatus = 0x00;
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_GET_STATUS); 
  _i2cPort->endTransmission(false);
  _i2cPort->requestFrom(_deviceAddress, 1);
  while ( _i2cPort->available() ) 
  {
    qrfStatus = _i2cPort->read();
  }
  if ( qrfStatus = 0 ) 
  {
	return 0;
  }
		
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_SEND); 
  _i2cPort->write(rf_addr); 
  for ( byte len = 0 ; len < payload.length() ; len++ ) 
  {
  _i2cPort->write(payload.charAt(len));
  }
  _i2cPort->endTransmission();
  
  return 1;
}

// Send a string to the last paired RF address
boolean QwiicRF::send(String payload)
{
  byte qrfStatus = 0x00;
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_GET_STATUS); 
  _i2cPort->endTransmission(false);
  _i2cPort->requestFrom(_deviceAddress, 1);
  while ( _i2cPort->available() ) 
  {
    qrfStatus = _i2cPort->read();
  }
  if ( qrfStatus = 0 ) 
  {
	return 0;
  }
		
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_SEND_PAIRED); 
  for ( byte len = 0 ; len < payload.length() ; len++ ) 
  {
  _i2cPort->write(payload.charAt(len));
  }
  _i2cPort->endTransmission();
  
  return 1;
}

// Send a string using the reliable send operation
// to a particular RF address
boolean QwiicRF::sendReliable(byte rf_addr, String payload)
{
  byte qrfStatus = 0x00;
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_GET_STATUS); 
  _i2cPort->endTransmission(false);
  _i2cPort->requestFrom(_deviceAddress, 1);
  while ( _i2cPort->available() ) 
  {
    qrfStatus = _i2cPort->read();
  }
  if ( qrfStatus = 0 ) 
  {
	return 0;
  }	
	
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_SEND_RELIABLE); 
  _i2cPort->write(rf_addr); 
  for ( byte len = 0 ; len < payload.length() ; len++ ) 
  {
    _i2cPort->write(payload.charAt(len));
  }
  _i2cPort->endTransmission();

  return 1;
}

// Send a string using the reliable send operation
// to the last paired RF address
boolean QwiicRF::sendReliable(String payload)
{
  byte qrfStatus = 0x00;
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_GET_STATUS); 
  _i2cPort->endTransmission(false);
  _i2cPort->requestFrom(_deviceAddress, 1);
  while ( _i2cPort->available() ) 
  {
    qrfStatus = _i2cPort->read();
  }
  if ( qrfStatus = 0 ) 
  {
	return 0;
  }	
	
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_SEND_RELIABLE_PAIRED); 
  for ( byte len = 0 ; len < payload.length() ; len++ ) 
  {
    _i2cPort->write(payload.charAt(len));
  }
  _i2cPort->endTransmission();

  return 1;
}

// Read the payload currently in the QwiicRF's cache
String QwiicRF::read()
{
  byte payloadSize;
  String payload = "";
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_GET_PAYLOAD_SIZE); 
  _i2cPort->endTransmission(false);
  _i2cPort->requestFrom(_deviceAddress, 1);
  while ( _i2cPort->available() ) 
  {
    payloadSize = _i2cPort->read();
  }
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_GET_PAYLOAD); 
  _i2cPort->endTransmission(false);
  _i2cPort->requestFrom(_deviceAddress, payloadSize);
  while ( _i2cPort->available() ) 
  {
    payload += (char)_i2cPort->read();
  }
  return payload;
}

// Get the size in bytes of the payload currently in the
// QwiicRF's cache 
byte QwiicRF::getPayloadSize(){
  byte sizePayload = 0x00;
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_GET_PAYLOAD_SIZE);
  _i2cPort->endTransmission(false);
  _i2cPort->requestFrom(_deviceAddress, 1);
  while ( _i2cPort->available() ) 
  {
    sizePayload = _i2cPort->read();
  }

  return sizePayload;
}

/********************************************************
 * Settings Manipulation Functions 
 *******************************************************/

 // Returns the sync word (network ID) currently in use by the QwiicRF
byte QwiicRF::getSyncWord(){
  byte qrfSync = 0x00;
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_GET_SYNC_WORD);
  _i2cPort->endTransmission(false);
  _i2cPort->requestFrom(_deviceAddress, 1);
  while ( _i2cPort->available() ) 
  {
    qrfSync = _i2cPort->read();
  }

  return qrfSync;
}

// Sets the sync word (network ID) 
void QwiicRF::setSyncWord(byte syncword)
{
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_SET_SYNC_WORD); 
  _i2cPort->write(syncword); 
  _i2cPort->endTransmission(); 
}

// Returns the RF address of the QwiicRF
byte QwiicRF::getRFAddress(){
  byte qrfAddr = 0x00;
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_GET_RF_ADDRESS);
  _i2cPort->endTransmission(false);
  _i2cPort->requestFrom(_deviceAddress, 1);
  while ( _i2cPort->available() ) 
  {
    qrfAddr = _i2cPort->read();
  }

  return qrfAddr;
}

// Sets the RF address of the QwiicRF
void QwiicRF::setRFAddress(byte addr)
{
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_SET_RF_ADDRESS); 
  _i2cPort->write(addr); 
  _i2cPort->endTransmission(); 
}

// Returns the last paired address of the QwiicRF
byte QwiicRF::getPairedAddress(){
  byte qrfAddr = 0x00;
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_GET_PAIRED_ADDRESS);
  _i2cPort->endTransmission(false);
  _i2cPort->requestFrom(_deviceAddress, 1);
  while ( _i2cPort->available() ) 
  {
    qrfAddr = _i2cPort->read();
  }

  return qrfAddr;
}

// Sets the paired address of the QwiicRF
void QwiicRF::setPairedAddress(byte addr)
{
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_SET_PAIRED_ADDRESS); 
  _i2cPort->write(addr); 
  _i2cPort->endTransmission(); 
}

// Sets the spread factor of the QwiicRF
void QwiicRF::setSpreadFactor(byte sf)
{
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_SET_SPREAD_FACTOR); 
  _i2cPort->write(sf); 
  _i2cPort->endTransmission(); 
}

// Set the transmit power of the QwiicRF
void QwiicRF::setTXPower(byte power)
{
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_SET_TX_POWER); 
  _i2cPort->write(power); 
  _i2cPort->endTransmission(); 
}

// Change the I2C address of the QwiicRF and start talking to
// it at that address
void QwiicRF::setI2CAddress(byte addr)
{
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_SET_I2C_ADDRESS); 
  _i2cPort->write(addr); 
  _i2cPort->endTransmission(); 
  _deviceAddress = addr;
}

/********************************************************
 * Packet Info Retrieval Functions 
 *******************************************************/
 
// Returns the RSSI of the last received packet 
byte QwiicRF::getPacketRSSI(){
  byte rssi = 0x00;
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_GET_PACKET_RSSI);
  _i2cPort->endTransmission(false);
  _i2cPort->requestFrom(_deviceAddress, 1);
  while ( _i2cPort->available() ) 
  {
    rssi = _i2cPort->read();
  }

  return rssi;
}

// Returns the SNR of the last received packet
byte QwiicRF::getPacketSNR(){
  byte snr = 0x00;
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_GET_PACKET_SNR);
  _i2cPort->endTransmission(false);
  _i2cPort->requestFrom(_deviceAddress, 1);
  while ( _i2cPort->available() ) 
  {
    snr = _i2cPort->read();
  }

  return snr;
}

// Returns the "From" address of the last received packet
byte QwiicRF::getPacketOrigin(){
  byte origin = 0x00;
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_GET_PACKET_SENDER);
  _i2cPort->endTransmission(false);
  _i2cPort->requestFrom(_deviceAddress, 1);
  while ( _i2cPort->available() ) 
  {
    origin = _i2cPort->read();
  }

  return origin;
}

// Returns the "To" address of the last received packet
byte QwiicRF::getPacketDestination(){
  byte destination = 0x00;
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_GET_PACKET_RECIPIENT);
  _i2cPort->endTransmission(false);
  _i2cPort->requestFrom(_deviceAddress, 1);
  while ( _i2cPort->available() ) 
  {
    destination = _i2cPort->read();
  }

  return destination;
}

// Returns the sequential ID of the last received packet
byte QwiicRF::getPacketID(){
  byte id = 0x00;
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(COMMAND_GET_PACKET_ID);
  _i2cPort->endTransmission(false);
  _i2cPort->requestFrom(_deviceAddress, 1);
  while ( _i2cPort->available() ) 
  {
    id = _i2cPort->read();
  }

  return id;
}