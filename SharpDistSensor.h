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

This is a library for the Arduino IDE that helps interface with Sharp IR analog
distance sensors.

The analog value from the sensor is converted to distance using a fifth order
polynomial fit curve.

The default polynomial coefficients in this lilbrary are calibrated for the
Sharp GP2Y0A60SZLF Analog Distance Sensor 10-150cm, 5V over a range of 50-1500
mm (analog values 30-875). Distance units are millimeters (mm). For different
accuracy, range, sensor model or units, different coefficients may be required.

Use the setPolyFitCoeffs method to define custom coefficients.

Use the setValMinMax method to define different analog values range.

The distance output is filtered using median filtering. MedianFilter class from
the following library is used: https://github.com/daPhoosa/MedianFilter.
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
    size: Window size of the median filter (1 = no filtering)
  **/
  SharpDistSensor(const byte pin, const byte size = 1);

  // Return the measured distance
  uint16_t getDist();

  /* Set the polynomial fit curve coefficients and range
    nbCoeffs: Number of coefficients (1 min, 6 max)
    coeffs:   Coefficients (x^0 to x^5)
    valMin: Minimal analog value for which to return a distance
    valMax: Maximal analog value for which to return a distance
  */
  void setPolyFitCoeffs(const byte nbCoeffs, const float* coeffs,
    const uint16_t valMin, const uint16_t valMax);

  // Set the analog value range for which to return a distance
  void setValMinMax(uint16_t valMin, uint16_t valMax);

private:
  // Arduino analog pin the sensor is connected to
  byte _pin;

  // Window size of the median filter (1 = no filtering)
  byte _mfSize;

  // Minimal analog value for which to return a distance
  uint16_t _valMin;

  // Maximal analog value for which to return a distance
  uint16_t _valMax;

  // Polynomial curve coefficients to convert analog signal to distance
  float _coeffs[6];

  // Median filter object instance
  MedianFilter medFilt;
};

#endif
