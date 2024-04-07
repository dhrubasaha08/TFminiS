/**
 * TFminiS.cpp
 * Implementation of the TFminiS library for interfacing with the TFmini-S LiDAR sensor.
 *
 * This library allows reading distance, signal strength, and temperature data from the TFmini-S sensor.
 *
 * Author: Dhruba Saha
 * Version: 0.0.1
 * License: Apache-2.0
 */

#include "TFminiS.h"

/**
 * Constructor for the TFminiS class.
 * Initializes the communication stream with the TFminiS sensor.
 *
 * @param stream: Reference to the serial communication stream (HardwareSerial).
 */
TFminiS::TFminiS(Stream &stream)
{
  _stream = &stream;
}

/**
 * Reads sensor data from the TFmini-S sensor.
 * This method reads the incoming data from the sensor, validates it using checksum,
 * and updates the distance, strength, and temperature measurements.
 */
void TFminiS::readSensor()
{
  if (_stream->available() >= 9)
  {
    uint8_t ch1 = _stream->read();
    if (ch1 == 0x59)
    {
      uint8_t ch2 = _stream->read();
      if (ch2 == 0x59)
      {
        uint8_t distL = _stream->read();
        uint8_t distH = _stream->read();
        uint8_t strengthL = _stream->read();
        uint8_t strengthH = _stream->read();
        uint8_t tempL = _stream->read();
        uint8_t tempH = _stream->read();
        uint8_t checksum = _stream->read();

        uint8_t sum = 0x59 + 0x59 + distL + distH + strengthL + strengthH + tempL + tempH;
        if (sum == checksum)
        {
          _distance = distH << 8 | distL;
          _strength = strengthH << 8 | strengthL;
          _temperature = (tempH << 8 | tempL) / 8.0 - 256;
        }
        else
        {
          _distance = -3; // Checksum error
        }
      }
    }
  }
}

/**
 * Retrieves the last distance measurement from the sensor.
 *
 * @return The last distance measurement in centimeters if successful, or an error code if not.
 */
int TFminiS::getDistance()
{
  return _distance;
}

/**
 * Retrieves the last signal strength measurement from the sensor.
 *
 * @return The last signal strength measurement if successful, or an error code if not.
 */
int TFminiS::getStrength()
{
  return _strength;
}

/**
 * Retrieves the last temperature measurement from the sensor.
 *
 * @return The last temperature measurement in degrees Celsius if successful, or an error code if not.
 */
int TFminiS::getTemperature()
{
  return _temperature;
}

/**
 * Translates error codes into human-readable error messages.
 *
 * @param errorCode The error code to translate.
 * @return A string describing the error.
 */
String TFminiS::getErrorString(int errorCode)
{
  switch (errorCode)
  {
  case -1:
    return "Signal strength is too low.";
  case -2:
    return "Signal strength saturation.";
  case -3:
    return "Checksum error.";
  case -4:
    return "Ambient light saturation.";
  default:
    return "No error.";
  }
}
