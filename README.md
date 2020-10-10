# SharpDistSensor
A library for the Arduino IDE that helps interface with Sharp analog distance sensors.

Version 1.6.0  
[![Build Status](https://travis-ci.org/DrGFreeman/SharpDistSensor.svg?branch=master)](https://travis-ci.org/DrGFreeman/SharpDistSensor)  
By Julien de la Bruère-Terreault (drgfreeman@tuta.io) and [contributors](#contributors)

## Summary
The analog value from the sensor is converted to distance using either a
polynomial fit function up to fifth order or a power fit function.

By default, this library is set to use polynomial coefficients calibrated for the Sharp GP2Y0A60SZLF Analog Distance Sensor 10-150cm 5V, over a range of 50-1500 mm (analog values 30-875). The returned distance is in millimeters (mm) units.

The library also allows the use of pre-defined calibrations for different sensor models as well as custom defined polynomial or power fit functions. Examples are provided showing how to use pre-defined calibrations or how to define custom fit functions.

The distance output is filtered using real-time median filtering (sliding window of ajustable size). The MedianFilter class from the following library is used: https://github.com/daPhoosa/MedianFilter.

## Examples
Five example sketches are provided with the library:

* _SharpDistSensorBasic.ino_  
This example shows how to use the library with the default calibration function for the Sharp GP2Y0A60SZLF 5V sensor.

* _SharpDistSensorByModel.ino_  
This example shows how to use the library by selecting a pre-defined sensor
model calibration.

* _SharpDistSensorCustomPoly.ino_  
This example shows how to use the library with a custom, user defined polynomial calibration function.

* _SharpDistSensorCustomPower.ino_  
This example shows how to use the library with a custom, user defined power calibration function.

* _SharpDistSensorArray.ino_  
This example shows how to use the library with an array of multiple sensors.

## Library Reference
* `SharpDistSensor(const byte pin, const byte size = 1)`  
Constructor: `pin` is the analog pin to which the sensor is connected, `size` is the size of the median filter window and should be an odd positive integer (default = 1 = no filtering).

* `uint16_t getDist()`  
Returns the measured distance. Distance units are in millimeters (mm) if using the library default settings or pre-defined sensor models. If using custom calibration, units depend on the calibration used.

* `void setModel(const byte model)`  
Sets the calibration based on pre-defined sensor model fit functions. Note that the model argument must be preceded by the SharpDistSensor namespace, i.e.: `setModel(SharpDistSensor::Model_Name)`

* `void setPolyFitCoeffs(const byte nbCoeffs, const float* coeffs, const uint16_t valMin, const uint16_t valMax)`
Sets the polynomial fit function coefficients _C0_ to _C5_ in the relation:  
_Distance = C0 + C1 * A + C2 * A^2 + ... + C5 * A^5_  
where _A_ is the analog value read from the sensor. At least one coefficient must be provided and up to six maximum (5th order polynomial). `nbCoeffs` is the number of coefficients passed and `coeffs` a vector containing the coefficients (C0 to C5). `valMin` and `valMax` define the range of analog values for which the polynomial fit is valid. Analog values outside this range will be set to the respective min or max values.

* `void setPowerFitCoeffs(const float C, const float P, const uint16_t valMin, const uint16_t valMax)`  
Sets the power fit function coefficients _C_ and _P_ in the relation:  
_Distance = C * A^P_  
where _A_ is the analog value read from the sensor. `valMin` and `valMax` define the range of analog values for which the power fit is valid. Analog values outside this range will be set to the respective min or max values.

* `void setValMinMax(const uint16_t valMin, const uint16_t valMax)`  
Sets the range of analog values for which the polynomial or power fit is valid (`valMin` and `valMax`). Analog values outside this range will be set to the respective min or max values.

## Pre-defined sensor models
* `GP2Y0A60SZLF_5V`: GP2Y0A60SZLF Analog Distance Sensor 10-150cm, 5V, polynomial fit.
* `GP2Y0A41SK0F_5V_DS`: GP2Y0A41SK0F Analog Distance Sensor 4-30cm, 5V (data sheet), polynomial fit.
* `GP2Y0A51SK0F_5V_DS`: GP2Y0A51SK0F Analog Distance Sensor 2-15cm, 5V (data sheet), power fit.
* `GP2Y0A710K0F_5V_DS`: GP2Y0A710K0F Analog Distance Sensor 100-500cm, 5V (data sheet), polynomial fit.
* `GP2Y0A21F_5V_DS`:  GP2Y0A21F Analog Distance Sensor 10-80cm, 5V (data sheet), power fit
#### Polynomial / Power fit coefficients:

Model | Units | C0/C | C1/P | C2 | C3 | C4 | C5
------|-------|----|----|----|----|----|----
**GP2Y0A60SZLF_5V** | mm | 1734 | -9.005 | 2.032E-2 | -2.251E-5 | 1.167E-8 | -2.037E-12
**GP2Y0A41SK0F_5V_DS** | mm | 761.9 | -8.13336 | 4.18857E-2 | -1.11338E-4 | 1.46237E-7 | -7.49656E-11
**GP2Y0A51SK0F_5V_DS** | mm | 4.03576E+4 | -1.26093 | | | |
**GP2Y0A710K0F_5V_DS** | mm | 178506 | -1607.72 | 5.5239 | -8.47601E-3 | 4.87819E-6 |
**GP2Y0A21F_5V_DS** | mm | 116483.399834958 | -1.132373887917551 | | | |

#### Analog values range:

Model | valMin | valMax
------|--------|--------
**GP2Y0A60SZLF_5V** | 30 | 875
**GP2Y0A41SK0F_5V_DS** | 61 | 614
**GP2Y0A51SK0F_5V_DS** | 70 | 500
**GP2Y0A710K0F_5V_DS** | 284 | 507
**GP2Y0A21F_5V_DS**    | 0   | 1023

**Important Note:** The analog voltage returned by the sensor is largely dependent of the reflected object size and reflectivity. The distance returned by these pre-defined calibration functions can therefore vary significantly from the real distance depending on the object detected. Where accuracy is required by the application, it is recommended to perform calibration with the object to be detected and use custom calibration fit functions instead.

This library has been designed so that it is easy to add sensor models. Contributions are therefore welcome. Adding models to the library can be done by either submitting a pull request or providing me the proposed fit function and associated calibration data by email so I can add it myself. Thank you for contributing!

## Contributors

Thanks to all who have directly or indirectly contributed to this library:
- Phillip Schmidt [@daPhoosa](https://github.com/daPhoosa) - MedianFilter library used in this library
- Christian Gosch [@cgo](https://github.com/cgo) - [#17](https://github.com/DrGFreeman/SharpDistSensor/pull/17)

## Version history
* 1.6.0 (2020-10-10): Added GP2Y0A21F_5V_DS model, added Atmega 328 Nano board to CI testing.
* 1.5.0 (2018-10-22): Added GP2Y0A41SK0F_5V_DS model.
* 1.4.2 (2018-09-23): Improved comments in SharpDistSensorArray example.
* 1.4.1 (2018-08-07): Updated MedianFilter to latest version from [daPhoosa/MedianFilter](https://github.com/daPhoosa/MedianFilter).
* 1.4.0 (2018-05-21): Added GP2Y0A51SK0F_5V_DS model.
* 1.3.0 (2018-05-20): Added SharpDistSensorArray example.
* 1.2.0 (2017-05-10): Added GP2Y0A710K0F_5V_DS model.
* 1.1.1 (2017-05-01): Clarified comments and fixed typos in examples, improved README.
* 1.1.0 (2017-04-05): Added support of power fit functions.
* 1.0.0 (2017-03-29): Initial major release for Arduino Library Manager (no change rel. to 0.3.2)
* 0.3.2 (2017-03-29): Modified models enum and related type in setModel method arguments.
* 0.3.1 (2017-03-28): Improved README and fixed comments in SharpDistSensorByModel example.
* 0.3.0 (2017-03-24): Added method to set calibration based on pre-defined sensor models.
