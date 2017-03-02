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

#include <SharpDistSensor.h>

/* Constructor
  pin:    Arduino analog pin the sensor is connected to
  mfSize: Window size of the median filter
  valMin: Minimal analog value for which to return a distance
  valMax: Maximal analog value for which to return a distance
*/
SharpDistSensor::SharpDistSensor(const byte pin, const byte size,
  const uint16_t valMin, const uint16_t valMax) : medFilt(size, 1500)
{
  // Arduino analog pin the sensor is connected to
  sensPin = pin;

  // Window size of the median filter (0 = no filtering)
  mfSize = size;

  // Minimal analog value for which to return a distance
  sensValMin = valMin;

  // Maximal analog value for which to return a distance
  sensValMax = valMax;
}

// Returns the measured distance
uint16_t SharpDistSensor::getDist()
{
  // Read analog value from sensor
  uint16_t sensVal = analogRead(sensPin);

  // Constrain sensor values to remain within set min-max range
  if (sensVal < sensValMin)
  {
    sensVal = sensValMin;
  }
  else if (sensVal > sensValMax)
  {
    sensVal = sensValMax;
  }

  // Calculate distance from polynomial curve
  uint16_t dist = C5 * pow(sensVal, 5);
  dist += C4 * pow(sensVal, 4);
  dist += C3 * pow(sensVal, 3);
  dist += C2 * pow(sensVal, 2);
  dist += C1 * sensVal + C0;

  if (mfSize > 1)
  {
    // Get filtered distance value
    dist = medFilt.in(dist);
  }

  return dist;
}
