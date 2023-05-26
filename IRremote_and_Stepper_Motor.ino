#include <IRremote.h>  //it requires IRremote to be installed and included in the code
#include <Stepper.h>  //Install and include the Stepper library to control the Stepper motor

const int IRpin = 2; // Pin for IR receiver
//const int stopButtonPin = 7; // Pin for stop button
const int stepsPerRevolution = 200; // Change this value to match your stepper motor

IRrecv irrecv(IRpin);
decode_results results;
Stepper myStepper(stepsPerRevolution,8,9,10,11); //define pins for the stepper motor (In actual there is LN298 driver to control the motor)

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  //pinMode(stopButtonPin, INPUT_PULLUP);
}
// voidloop below implements the switch cases for the different conditions, and contains the IR remote button instructions to rotate the motor in 4 different modes. 
void loop() {
  if (irrecv.decode(&results)) { //decodes the IR remote instruction (i.e. button press) 
    switch (results.value) {
      case 0xFFA25D: // Button "UP"
        myStepper.setSpeed(60); //sets the speed to 60 rpm
        myStepper.step(1200); //rotates the motor for 1200 steps
        break;
      case 0xFFE01F: // Button "UP"
        myStepper.setSpeed(60);
        myStepper.step(150);
        break;
      case 0xFFE21D: // Button "DOWN"
        myStepper.setSpeed(60);
        myStepper.step(-1200);
        break;
      case 0xFFA857: // Button "DOWN"
        myStepper.setSpeed(60);
        myStepper.step(-150);
        break;
    }
    irrecv.resume(); //resume to look for the IR instructions after implementing the previous instruction.
  }

}
