/*
SharpDistSensor.h
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
SharpDistSensor; Sharp analog distance sensor library

This is a library for the Arduino IDE that helps interface with Sharp analog
distance sensors.

The analog value from the sensor is converted to distance using a fifth order
polynomial fit curve. The polynomial coefficients in this file are calibrated
for the Sharp GP2Y0A60SZLF Analog Distance Sensor 10-150cm, 5V over a range of
50-1500 mm (analog values 30-875). Distance units are millimeters (mm).
For different accuracy, range, sensor model or units, different coefficients
may be required.

The distance output is filtered using median filtering. The following library
is required: https://github.com/daPhoosa/MedianFilter.
*/

#ifndef SharpDistSensor_h
#define SharpDistSensor_h

#include <Arduino.h>
#include <MedianFilter.h>

class SharpDistSensor
{
public:

  /** Constructor
    pin:    Arduino analog pin the sensor is connected to
    valMin: The minimal analog value for which to return a distance
    valMax: The maximal analog value for which to return a distance
    mfSize: Window size of the median filter
  **/
  SharpDistSensor(byte pin, uint16_t valMin, uint16_t valMax, byte mfSize);

  // Returns the measured distance
  uint16_t getDist();

private:
  // Analog pin to which the sensor is connected
  byte sensPin;

  // The minimal analog value for which to return a distance
  uint16_t sensValMin;

  // The maximal analog value for which to return a distance
  uint16_t sensValMax;

  // Polynomial curve coefficients to convert analog signal to distance (in mm)
  const float C5 = -2.037E-12; // The x^5 coefficient
  const float C4 = 1.167E-8;  // The x^4 coefficient
  const float C3 = -2.251E-5; // The x^3 coefficient
  const float C2 = 2.023E-2;  // The x^2 coefficient
  const float C1 = -9.005;    // The x^1 coefficient
  const uint16_t C0 = 1734;   // The constant term

  // Median filter object instance
  MedianFilter medFilt;
};

#endif
