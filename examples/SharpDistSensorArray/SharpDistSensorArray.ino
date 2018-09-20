/*
SharpDistSensorArray.ino

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
This example shows how to use the SharpDistSensor library with an array of
multiple sensors.

See the library README for how to use pre-defined sensor models or  custom fit
functions.
*/

#include <SharpDistSensor.h>

// Define the number of sensors in the array as a constant
const byte nbSensors = 2;

// Window size of the median filter (odd number, 1 = no filtering)
const byte medianFilterWindowSize = 5;

// Define the array of SharpDistSensor objects
SharpDistSensor sensorArray[] = {
  SharpDistSensor(A1, medianFilterWindowSize), // First sensor using pin A1
  SharpDistSensor(A2, medianFilterWindowSize), // Second sensor using pin A2
  // Add as many sensors as required
};

// Alternatively, the array can be defined this way
// SharpDistSensor sensorArray[nbSensors] = {{A1, medianFilterWindowSize},
//                                           {A2, medianFilterWindowSize}};

// Define an array of integers that will store the measured distances
uint16_t distArray[nbSensors];

void setup() {
  // Set some parameters for each sensor in array
  for (byte i = 0; i < nbSensors; i++) {
    sensorArray[i].setModel(SharpDistSensor::GP2Y0A710K0F_5V_DS);  // Set sensor model
    // Set other parameters as required
  }
}

void loop() {
  // Read distance for each sensor in array into an array of distances
  for (byte i = 0; i < nbSensors; i++) {
    distArray[i] = sensorArray[i].getDist();
  }

  // The measured distances can now be accessed through the different indices of the
  // distArray array, i.e. distArray[0] for the first sensor, distArray[1] for the
  // sencond sensor ...
}
