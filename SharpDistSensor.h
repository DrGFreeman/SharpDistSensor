/*
SharpDistSensor.h
Source: https://github.com/DrGFreeman/SharpDistSensor

MIT License

Copyright (c) 2018 Julien de la Bruere-Terreault <drgfreeman@tuta.io>

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

The analog value from the sensor is converted to distance using either a fifth
order polynomial fit function or a power fit function.

By default, this library is set to use polynomial coefficients calibrated for
the Sharp GP2Y0A60SZLF Analog Distance Sensor 10-150cm 5V, over a range of
50-1500 mm (analog values 30-875). The returned distance is in millimeters (mm)
units.  For different accuracy, range, sensor model or units, different
coefficients may be required.

Use the setModel method to change the sensor model calibration. The following
models are currently supported:
-GP2Y0A60SZLF_5V (GP2Y0A60SZLF Analog Distance Sensor 10-150cm, 5V)
-GP2Y0A710K0F_5V_DS (GP2Y0A710K0F Analog Distance Sensor 100-500cm, 5V)

Use the setPolyFitCoeffs method to define custom polynomial coefficients.

Use the setPowerFitCoeffs method to define custom power coefficients.

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
  // List of pre-defined sensor models
  enum models
  {
    // Constant for GP2Y0A60SZLF 5V model
    GP2Y0A60SZLF_5V,
    // Constant for GP2Y0A710K0F 5V model
    GP2Y0A710K0F_5V_DS,
    // Constant for GP2Y0A51SK0F 5V model
    GP2Y0A51SK0F_5V_DS,
    // Constant for GP2Y0A41SK0F 5V model
    GP2Y0A41SK0F_5V_DS
  };

  /** Constructor
    pin:    Arduino analog pin the sensor is connected to
    size: Window size of the median filter (1 = no filtering)
  **/
  SharpDistSensor(const byte pin, const byte size = 1);

  // Return the measured distance
  uint16_t getDist();

  // Set the sensor model
  void setModel(const models model);

  /* Set the polynomial fit function coefficients and range
    nbCoeffs: Number of coefficients (1 min, 6 max)
    coeffs:   Coefficients (x^0 to x^5)
    valMin: Minimal analog value for which to return a distance
    valMax: Maximal analog value for which to return a distance
  */
  void setPolyFitCoeffs(const byte nbCoeffs, const float* coeffs,
    const uint16_t valMin, const uint16_t valMax);

  /* Set the power fit function coefficients and range
    C and P: Coefficients in Distance = C*x^P relation
    valMin: Minimal analog value for which to return a distance
    valMax: Maximal analog value for which to return a distance
  */
  void setPowerFitCoeffs(const float C, const float P,
    const uint16_t valMin, const uint16_t valMax);

  // Set the analog value range for which to return a distance
  void setValMinMax(const uint16_t valMin, const uint16_t valMax);

private:
  // Arduino analog pin the sensor is connected to
  byte _pin;

  // Window size of the median filter (1 = no filtering)
  byte _mfSize;

  // Minimal analog value for which to return a distance
  uint16_t _valMin;

  // Maximal analog value for which to return a distance
  uint16_t _valMax;

  // Polynomial function coefficients to convert analog signal to distance
  float _polyCoeffs[6];

  // Power function coefficients to convert analog signal to distance
  float _powerCoeffC;
  float _powerCoeffP;

  // Possible types of fit functions
  enum fitTypes
  {
    FIT_POLY,
    FIT_POWER
  };

  // Fit function type used
  fitTypes _fitType;

  // Median filter object instance
  MedianFilter medFilt;
};

#endif
