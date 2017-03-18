# SharpDistSensor
A library for the Arduino IDE that helps interface with Sharp analog distance sensors.  

Version 0.2.3  
[![Build Status](https://travis-ci.org/DrGFreeman/SharpDistSensor.svg?branch=master)](https://travis-ci.org/DrGFreeman/SharpDistSensor)  
By Julien de la Bruère-Terreault (drgfreeman@tuta.io)

## Summary
The analog value from the sensor is converted to distance using a polynomial fit curve up to fifth order.
The default polynomial coefficients in this library are calibrated for the Sharp GP2Y0A60SZLF Analog Distance Sensor 10-150cm 5V, over a range of 50-1500 mm (analog values 30-875). The returned distance is in millimeters (mm) units.  
For different accuracy, range, sensor model or units, different coefficients may be required.  
The distance output is filtered using real-time median filtering (moving window of ajustable size). The MedianFilter class from the following library is used: https://github.com/daPhoosa/MedianFilter.

## Examples
Two example sketches are provided with the library:
* _SharpDistSensorBasic.ino_  
This example shows how to use the library with the default calibration curve for the Sharp GP2Y0A60SZLF 5V sensor.

* _SharpDistSensorCustom.ino_  
This example shows how to use the library with a custom, user defined calibration curve.

## Library Reference
* `SharpDistSensor(const byte pin, const byte size = 1)`  
Constructor: `pin` is the analog pin to which the sensor is connected, `size` is the size of the median filter window and should be an odd positive integer (default = 1 = no filtering).  

* `uint16_t getDist()`  
Returns the measured distance. Distance units are in millimeters (mm) if using the library default settings. If using custom calibration, units depend on the calibration used.  

* `void setPolyFitCoeffs(const byte nbCoeffs, const float* coeffs, const uint16_t valMin, const uint16_t valMax)`  
Sets the polynomial fit curve coefficients _C0_ to _C5_ in the relation:  
_Distance = C0 + C1 * A + C2 * A^2 + ... + C5 * A^5_  
where _A_ is the analog value read from the sensor. At least one coefficient must be provided and up to six maximum (5th order polynomial). `nbCoeffs` is the number of coefficients passed and `coeffs` a vector containing the coefficients (C0 to C5). `valMin` and `valMax` define the range of analog values for which the polynomial fit is valid. Analog values outside this range will be set to the respective min or max values.  

* `void setValMinMax(const uint16_t valMin, const uint16_t valMax)`  
Sets the range of analog values for which the polynomial fit is valid (`valMin` and `valMax`). Analog values outside this range will be set to the respective min or max values.
