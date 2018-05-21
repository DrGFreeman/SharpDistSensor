/*
SharpDistSensorCustomPoly.ino
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
read the sensor and display the analog value and the corresponding distance
using custom polynomial fit curve and range.

The same values as the library default values for the Sharp GP2Y0A60SZLF 5V
sensor are used for example purpose, however different values may be used
for different sensors, units, calibration or range.
*/

#include <SharpDistSensor.h>

// Analog pin to which the sensor is connected
const byte sensorPin = A0;

// Window size of the median filter (odd number, 1 = no filtering)
const byte medianFilterWindowSize = 5;

// Create an object instance of the SharpDistSensor class
SharpDistSensor sensor(sensorPin, medianFilterWindowSize);

/*
 * Polynomial fit curve coefficients C0 to C5 in relation:
 * Distance = C0 + C1*A + C2*A^2 + ... + C5*A^5
 * where A is the analog value read from the sensor
 * One coefficient minimum, six maximum (5th order polynomial)
 */
const float polyCoefficients[] = {1734, -9.005, 2.023E-2, -2.251E-5, 1.167E-8, -2.037E-12};
const byte nbCoefficients = 6;  // Number of coefficients

/*
 * Minimum and maximum analog values for which to return a distance
 * These should represent a range of analog values within which the
 * polynomial fit curve is valid.
 */
const unsigned int minVal = 134; // ~800 mm
const unsigned int maxVal = 875; // ~50mm

void setup() {
  Serial.begin(9600);

  // Set custom polynomial fit curve coefficients and range
  sensor.setPolyFitCoeffs(nbCoefficients, polyCoefficients, minVal, maxVal);
}

void loop() {
  /* Print raw analog value. This step is not required to read the sensor,
     it is included here to show the relation between the raw analog value
     and the returned distance. */
  Serial.print(analogRead(sensorPin));

  Serial.print(", ");

  // Get distance from sensor
  unsigned int distance = sensor.getDist();

  // Print distance to Serial
  Serial.println(distance);

  // Wait some time
  delay(50);
}
