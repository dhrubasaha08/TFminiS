/**
 * TFmini-S Sensor Reader
 * This sketch reads distance, signal strength, and temperature data from the Benewake TFmini-S sensor
 * and prints the values to the serial port. It also handles potential error states that
 * might occur during reading.
 *
 * Author: Dhruba Saha
 * Version: 0.0.1
 * License: Apache-2.0
 */

#include <TFminiS.h>

// Initialize the TFminiS object depending on the board being used.
#if defined(__AVR_ATmega2560__)
#define tfSerial Serial1
TFminiS tfmini(tfSerial);
#elif defined(ESP32)
#include <HardwareSerial.h>
HardwareSerial tfSerial(2);
TFminiS tfmini(tfSerial);
#endif

void setup() {
  // Initialize serial communication.
  Serial.begin(115200);
  tfSerial.begin(115200);
}

void loop() {
  // Read data from the TFmini-S sensor.
  tfmini.readSensor();

  int distance = tfmini.getDistance();
  int strength = tfmini.getStrength();
  int temperature = tfmini.getTemperature();

  // Check for and handle any errors.
  if (distance < 0) {
    Serial.println(TFminiS::getErrorString(distance));
  } else {
    // If no errors, print the data.
    Serial.print("Distance:");
    Serial.print(distance);
    Serial.print(", Strength:");
    Serial.print(strength);
    Serial.print(", Temperature:");
    Serial.println(temperature);
  }
}
