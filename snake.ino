#include <Servo.h>


Servo myServos[10];  //create 10 servos

float pi = 3.14159;
int TotalNumberofServos = 10;                //change as required
float Shift = 2 * pi / TotalNumberofServos;  // Phase lag between segments
float Wavelengths, rads;
int InteriorAngle, SetpointAngle, MaxAngleDisplacement;
int mode = 0;
int ButtonPin = 3;


void setup() {
  Serial.begin(9600);
  //The following code can be cleaned up in a single for-loop if you solder the wires in a more continuous pattern than I did
  //Order of servos is such that myServos[0]=tail segment, and myServos[9]=head segment
  myServos[0].attach(A0);
  myServos[1].attach(A1);
  myServos[2].attach(A2);
  myServos[3].attach(A3);
  myServos[4].attach(6);
  myServos[5].attach(7);
  myServos[6].attach(8);
  myServos[7].attach(9);
  myServos[8].attach(10);
  
  pinMode(ButtonPin,INPUT);
  delay(1000);
}


int add = 23;
int sub = -20;

void stop_all() {
  for (int i = 4; i < 9; i += 1)
    myServos[i].write(90);
  delay(200);
}

void contract() {
  // myServos[4].write(90+sub+5);
  // delay(200);
  myServos[5].write(90 + add);
  delay(200);
  myServos[6].write(90 - 15);
  delay(200);
  myServos[7].write(90 + add + 15);
  delay(200);
  myServos[8].write(90 + sub - 5);
  delay(200);
}
void expand() {
  // myServos[4].write(90 + add-5);
  // delay(200);
  myServos[5].write(90 + sub - 5);
  delay(200);
  myServos[6].write(90 + 15);
  delay(200);
  myServos[7].write(90 + sub - 15);
  delay(200);
  myServos[8].write(90 + add - 15);
  delay(200);
}

void worm() {
  contract();
  stop_all();
  expand();
}
void unsynchro_walk() {
  myServos[0].write(180);
  myServos[2].write(0);
  delay(1000);
  myServos[1].write(180);
  myServos[3].write(0);
  delay(1000);
}

void synchro_walk() {
  myServos[0].write(0);
  myServos[2].write(180);
  myServos[1].write(0);
  myServos[3].write(180);
}
int buttonState = 0;
void loop() {
  buttonState = digitalRead(ButtonPin);

  if (buttonState == HIGH) {
    mode = mode ^ 1;
    Serial.println(mode);
  }
  if (mode == 0){
    Serial.println("A");
    worm();
  }
  else{
    Serial.println("B");
    // unsynchro_walk();
    synchro_walk();
  }

}
