/*
SharpDistSensor.cpp
Source: https://github.com/DrGFreeman/SharpDistSensor

MIT License

Copyright (c) 2017 Julien de la Bruere-Terreault <drgfreeman@tuta.io>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*
This example shows how to use the SharpDistSensor library to continuously
read the sensor and display the analog value and the corrseponding distance
(in mm).
*/

#include <SharpDistSensor.h>

// Analog pin to which the sensor is connected
const byte pin = A0;

// Minimum and maximum analog values for which to return a distance
// Calibration range is from 30 to 875 (~1500-50 mm)
uint16_t minVal = 30;
uint16_t maxVal = 875;

// Window size of the median filter
byte mfSize = 5;


// Create an object instance of the SharpDistSensor class
SharpDistSensor sensor(pin, minVal, maxVal, mfSize);

void setup() {
  Serial.begin(9600);
}

void loop() {
  /* Print raw analog value. This step is not required to read the sensor,
     it is included here to show the relation between the raw analog value
     and the returned distance. */
  Serial.print(analogRead(pin));

  Serial.print(", ");

  // Get and print distance from sensor
  Serial.println(sensor.getDist());

  // Wait some time
  delay(50);
}


