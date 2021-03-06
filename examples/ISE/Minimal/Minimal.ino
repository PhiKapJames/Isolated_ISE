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
}

void loop() {
  // https://ufire.co/docs/uFire_ISE/api.html#measuremv
  mv.measuremV();
  
  Serial.println((String) "mV: " + mv.mV);
  delay(1000);
}