/*
SharpDistSensor.cpp
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

#include <SharpDistSensor.h>

/* Constructor
  pin:    Arduino analog pin the sensor is connected to
  size: Window size of the median filter
*/
SharpDistSensor::SharpDistSensor(const byte pin, const byte size) :
  medFilt(size, 1500)
{
  // Arduino analog pin the sensor is connected to
  _pin = pin;

  // Window size of the median filter (1 = no filtering)
  _mfSize = size;

  // Set default sensor model to GP2Y0A60SZLF 5V
  setModel(GP2Y0A60SZLF_5V);
}

// Return the measured distance
uint16_t SharpDistSensor::getDist()
{
  // Read analog value from sensor
  uint16_t sensVal = analogRead(_pin);

  // Constrain sensor values to remain within set min-max range
  sensVal = constrain(sensVal, _valMin, _valMax);

  uint16_t dist = 0;

  if (_fitType == FIT_POLY)
  {
    // Calculate distance from polynomial fit function
    dist += _polyCoeffs[5] * pow(sensVal, 5);
    dist += _polyCoeffs[4] * pow(sensVal, 4);
    dist += _polyCoeffs[3] * pow(sensVal, 3);
    dist += _polyCoeffs[2] * pow(sensVal, 2);
    dist += _polyCoeffs[1] * sensVal;
    dist += _polyCoeffs[0];
  }
  else if (_fitType == FIT_POWER)
  {
    // Calculate distance from power fit function
    dist = _powerCoeffC * pow(sensVal, _powerCoeffP);
  }

  if (_mfSize > 1)
  {
    // Get filtered distance value
    dist = medFilt.in(dist);
  }

  return dist;
}

// Set the sensor model
void SharpDistSensor::setModel(const models model)
{
  switch (model)
  {
    case GP2Y0A60SZLF_5V:
    {
      // Set coefficients and range for Sharp GP2Y0A60SZLF 5V
      float coeffs[] = {1734, -9.005, 2.023E-2, -2.251E-5, 1.167E-8, -2.037E-12};
      setPolyFitCoeffs(6, coeffs, 30, 875);
      break;
    }
    case GP2Y0A710K0F_5V_DS:
    {
      // Set coefficients and range for Sharp GP2Y0A710K0F 5V
      float coeffs[] = {178506, -1607.72, 5.5239, -8.47601E-3, 4.87819E-6};
      setPolyFitCoeffs(5, coeffs, 284, 507);
      break;
    }
    case GP2Y0A41SK0F_5V_DS:
    {
      // Set coefficients and range for Sharp GP2Y0A41SK0F 5V
      float coeffs[] = {761.913, -8.13336, 4.18857E-02, -1.11338E-04, 1.46237E-07, -7.49656E-11};
      setPolyFitCoeffs(6, coeffs, 61, 614);
      break;
    }
    case GP2Y0A51SK0F_5V_DS:
    {
      // Set coefficients and range for Sharp GP2Y0A51SK0F 5V
      setPowerFitCoeffs(4.03576E+4, -1.26093, 70, 500);
      break;
    }
  }
}

// Set the polynomial fit function coefficients and range
void SharpDistSensor::setPolyFitCoeffs(const byte nbCoeffs,
  const float* coeffs, const uint16_t valMin, const uint16_t valMax)
{
  // Set fit type to FIT_POLY
  _fitType = FIT_POLY;

  // Set coefficients
  for (byte i = 0; i < 6; i++)
  {
    if (i < nbCoeffs)
    {
      // Coefficient is provided
      _polyCoeffs[i] = coeffs[i];
    }
    else
    {
      // Coefficient is not provided, set to zero
      _polyCoeffs[i] = 0;
    }
  }

  // Set analog value range
  setValMinMax(valMin, valMax);
}

// Set the power fit function coefficients and range
void SharpDistSensor::setPowerFitCoeffs(const float C, const float P,
  const uint16_t valMin, const uint16_t valMax)
{
  // Set fit type to FIT_POWER
  _fitType = FIT_POWER;

  // Set power fit function coefficients
  _powerCoeffC = C;
  _powerCoeffP = P;

  // Set analog value range
  setValMinMax(valMin, valMax);
}

// Set the analog value range for which to return a distance
void SharpDistSensor::setValMinMax(const uint16_t valMin, const uint16_t valMax)
{
    // Minimal analog value for which to return a distance
    _valMin = valMin;

    // Maximal analog value for which to return a distance
    _valMax = valMax;
}
