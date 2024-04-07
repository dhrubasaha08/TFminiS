/**
 * TFminiS.h
 * Header file for the TFminiS library, providing functionalities to interface with
 * the TFmini-S LiDAR sensor.
 *
 * This library facilitates reading distance, signal strength, and ambient temperature
 * measurements from the TFmini-S sensor.
 *
 * Author: Dhruba Saha
 * Version: 0.0.1
 * License: Apache-2.0
 */

#ifndef TFminiS_h
#define TFminiS_h

#include "Arduino.h"

/**
 * TFminiS Class
 * Provides methods to read distance, signal strength, and temperature data from the TFmini-S sensor.
 */
class TFminiS
{
public:
  TFminiS(Stream &stream);
  void readSensor();
  int getDistance();
  int getStrength();
  int getTemperature();
  static String getErrorString(int errorCode);

private:
  Stream *_stream;
  int _distance;
  int _strength;
  int _temperature;
};

#endif
