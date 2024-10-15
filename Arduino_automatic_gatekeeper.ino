// Arduino Nano with IR Sensor & Servo for Gatekeeper Project
// In this project, we’ll demonstrate how to build an automatic gate system 
// using an Arduino Nano, an infrared (IR) sensor, and a servo motor. 
// When the IR sensor detects an object, the gate (servo) will open for 0.5 second. 
// After 0.5 second, the system will recheck if the object is still detected.
// If the object is gone, the gate will close after 0.5 second; otherwise, it remains open.
// 
// Components Used:
// - Arduino Nano
// - IR Sensor Module
// - Servo Motor
// - Jumper Wires
//
// Visit http://kitkraft.in for all the components you need for this project.

#include <Servo.h>  // Include the Servo library to control the servo motor

// Declare variables
int servoPin = 3;  // Pin for controlling the servo motor
const int IR_Pin = 2;  // Pin connected to the IR sensor
int ir;  // Variable to store the IR sensor reading

Servo Servo1;  // Create a servo object to control the gate

void setup() {  
   Serial.begin(9600);  // Start the serial communication for debugging
   Servo1.attach(servoPin);  // Attach the servo motor to the specified pin
   pinMode(IR_Pin, INPUT);  // Set the IR sensor pin as input
   Servo1.write(0);  // Initialize the servo at 0 degrees (gate closed)
}

void loop(){ 
  // Read the IR sensor status
  ir = digitalRead(IR_Pin);  
  Serial.print("IR status: "); 
  Serial.println(ir);  // Print the sensor reading to the Serial Monitor
  
  // If the IR sensor detects an object (ir = 0)
  if (!ir) {  
    Servo1.write(90);  // Open the gate (move servo to 90 degrees)
    delay(500);  // Hold the gate open for 0.5 second
    
    // After 1 second, check if the object is still present
    ir = digitalRead(IR_Pin);  

    // If the object is still present (ir = 0), keep the gate open
    if (!ir) {  
      Servo1.write(90);  // Keep the servo at 90 degrees (gate remains open)
    } else {  
      // If the object has passed (ir = 1), close the gate
      delay(500);  // Wait for 0.5 second before closing the gate
      Servo1.write(0);  // Move servo to 0 degrees (close the gate)
    }
  } else {
    // If no object is detected, ensure the gate remains closed
    Servo1.write(0);  // Keep the servo at 0 degrees (gate closed)
  }
}
