/*!
   ufire.co for links to documentation, examples, and libraries
   github.com/u-fire for feature requests, bug reports, and  questions
   questions@ufire.co to get in touch with someone

   For hardware version 2, firmware 2
 */

 #include <uFire_ISE.h>

uFire_ISE mv;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // https://ufire.co/docs/uFire_ISE/api.html#begin
  mv.begin();

  // reset the calibration data
  //https://ufire.co/docs/uFire_ISE/api.html#reset
  mv.reset();
  
  // mV value of the calibration solution.
  // https://ufire.co/docs/uFire_ISE/api.html#calibratesingle
  mv.calibrateSingle(200.0);
}

void loop() {
  // https://ufire.co/docs/uFire_ISE/api.html#measuremv
  mv.measuremV();
  
  Serial.println((String) "mV: " + mv.mV);
  delay(1000);
}