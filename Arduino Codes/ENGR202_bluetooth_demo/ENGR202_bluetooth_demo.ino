// Engineering 202C
// Winter 2018
// Team 9 - Stair Climbing Robot
// University of Washington
// Code written by Aaron Su
// 
// Drives a robot based upon commands given over a bluetooth app. Uses LEDS for user feedback

// Ardunio Pins
const int rx0 = 0; // Bluetooth
const int tx1 = 1; // Bluetooth
const int lT1 = 2; // Direction, Maps to 2 on All HBridges
const int lT2 = 4; // Direction, Maps to 3 on All HBridges
const int lTP = 3; // Power, Maps to 1 on Front Two HBridges
const int rT1 = 5; // Direction, Maps to 5 on All HBridges
const int rT2 = 7; // Direction, Maps to 4 on All HBridges
const int rTP = 6; // Power, Maps to 6 on Front Two Hbridges
const int ledR = 8;
const int ledG = 9;
const int ledB = 10;
const int bLP = 11; // Power, Maps to 1 on Back Hbridge
const int bRP = 12; // Power, Maps to 6 on Back Hbridge
const int unknown = 13; // Does not yet have a purpose

// HBridge Motor Power 
const int FULL_POW = 255;
const int HIGH_POW = 240;
const int MED_POW = 150;
const int LOW_POW = 32;

// LED Constants
const int BRIGHT = 250;
const int DIM = 64;
const int OFF = 0;

int received = 0; // Global variable for BT input

void setup() 
{
    Serial.begin(9600); // Open BT connection
    //pinMode(rx0, OUTPUT); 
    //pinMode(tx1, OUTPUT);
    pinMode(lT1, OUTPUT);
    pinMode(lT2, OUTPUT);
    digitalWrite(lTP, LOW);
    pinMode(rT1, OUTPUT);
    pinMode(rT2, OUTPUT);
    digitalWrite(rTP, LOW);
    pinMode(ledR, OUTPUT);
    pinMode(ledG, OUTPUT);
    pinMode(ledB, OUTPUT);
    digitalWrite(bLP, LOW);
    digitalWrite(bRP, LOW);
    analogWrite(ledB, 255); // Turns BT on
}

void loop() 
{
  // Bluetooth Demo
  //btDemo();
  driveBack();
  
}

void btDemo() 
{
  resetColors();
  analogWrite(ledB, 255);
  if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    received = Serial.read(); // Reads the data from the serial port
    Serial.println(received);
  }
}

void driveBack() {
  resetColors();
  analogWrite(ledR, 255);
  analogWrite(bLP, FULL_POW); // Backwards, the one by MD
  analogWrite(bRP, FULL_POW); // Backwards, the one by MD
  analogWrite(lTP, FULL_POW);
  analogWrite(rTP, FULL_POW);
  digitalWrite(lT1, LOW);
  digitalWrite(lT2, HIGH);
  digitalWrite(rT1, LOW);
  digitalWrite(rT2, HIGH);
}

// Main drive program that will control the robot's movements
void drive() 
{
   if(Serial.available() > 0) // Bluetooth connected
  {
    resetColors();
    analogWrite(ledB, 255);
    received = Serial.read();
    Serial.println(received);
    if(received == 'f') {
      // Color
      resetColors();
      analogWrite(ledG, 255);
      
      // Drive
      analogWrite(lTP, FULL_POW);
      analogWrite(rTP, FULL_POW);
      analogWrite(bLP, HIGH_POW);
      analogWrite(bRP, HIGH_POW);
      digitalWrite(lT1, LOW);
      digitalWrite(lT2, HIGH);
      digitalWrite(rT1, LOW);
      digitalWrite(rT2, HIGH);
      
      // Send message
      Serial.print("Forward");
    } 
    else if (received == 'b') 
    {
      // Color
      resetColors();
      analogWrite(ledG, 255);
      analogWrite(ledR, 255);
      
      // Drive
      analogWrite(ledG, 255);
      analogWrite(ledB, 0);
      analogWrite(lTP, 255);
      analogWrite(rTP, 255);
      analogWrite(bLP, 255);
      analogWrite(bRP, 255);
      digitalWrite(lT1, HIGH);
      digitalWrite(lT2, LOW);
      digitalWrite(rT1, HIGH);
      digitalWrite(rT2, LOW);
      
      // Send message
      Serial.print("Backward");
    }
  } 
  else // Bluetooth not connected
  {
    // Color
    resetColors();
    analogWrite(ledR, 255);
  }
  
}

void resetColors() 
{
  analogWrite(ledR, 0);
  analogWrite(ledG, 0);
  analogWrite(ledB, 0);

}

// Demo to test Motors
void demoOne()
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(lT1, HIGH);
  digitalWrite(lT2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(lTP, 200);
  // now change motor directions
  digitalWrite(lT1, LOW);
  digitalWrite(lT2, HIGH);  
  delay(2000);
  // now turn off motors
  digitalWrite(lT1, LOW);
  digitalWrite(lT2, LOW);  
}

// Autonomous testing program
void demoTwo() {
  
}

// Checkpoint demo to show functionality of all parts
void checkPointDemo() {
  // Send a bluetooth message
  // Recieve a bluetooth message
  // Turn on LED to 3 different colors
  // Drive all motors forward
  // Drive all motors backwards
}




