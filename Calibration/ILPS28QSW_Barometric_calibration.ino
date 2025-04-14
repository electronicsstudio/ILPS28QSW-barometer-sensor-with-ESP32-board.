
/*
Electronics Studio
@file ILPS28QSW_Barometric_calibration.ino
@date  14-04-2025
@url https:https: https://github.com/electronicsstudio
@url YouTube: https://www.youtube.com/@ElectronicsStudio-v7o/featured
*/

#include <Wire.h>
#include "SparkFun_LPS28DFW_Arduino_Library.h"

// Create a new sensor object
LPS28DFW pressureSensor;

// I2C address selection
uint8_t i2cAddress = LPS28DFW_I2C_ADDRESS_DEFAULT; // 0x5C

// Define sea-level pressure (in hPa) as a global variable
const float seaLevelPressure = 1013.25; // Adjust based on local weather

void setup() {
  // Start serial
  Serial.begin(115200);
  //Serial.println("LPS28DFW Example 1 - Basic Readings!");

  // Initialize the I2C library
  Wire.begin();

  // Check if sensor is connected and initialize
  while (pressureSensor.begin(i2cAddress) != LPS28DFW_OK) {
    Serial.println("Error: LPS28DFW not connected, check wiring and I2C address!");
    delay(500); // Retry every 500 ms
  }

  Serial.println("LPS28DFW connected!");
}

void loop() {
  // Get sensor data
  pressureSensor.getSensorData();

  // Calculate altitude using the refined formula
  float pressure = pressureSensor.data.pressure.hpa;
  float altitude = 44330.77 * (1.0 - pow(pressure / seaLevelPressure, 0.190284));

  Serial.print("$PBAR,"); Serial.print(pressure); Serial.print(","); Serial.print(altitude); Serial.println("*00"); 
  
  delay(500); // Update every second
}








