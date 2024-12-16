#include <Servo.h>


Servo myServos[10];  //create 10 servos

float pi = 3.14159;
int TotalNumberofServos = 10;                //change as required
float Shift = 2 * pi / TotalNumberofServos;  // Phase lag between segments
float Wavelengths, rads;
int InteriorAngle, SetpointAngle, MaxAngleDisplacement;
int mode = 0;


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
  
  pinMode(3,INPUT);
  //Initialise snake in a straight line
  //for(int i=0; i<10; i++){
  //  myServos[i].write(90);
  //  delay(15);
  //}
  delay(1000);
}

void straightline() {
  Serial.println("hola");
  for (int i = 0; i < 10; i++) {
    myServos[i].write(180);
    delay(100);
  }
}

void Cshape() {
  for (int i = 0; i < 10; i++) {
    myServos[i].write(60);
    delay(100);
  }
}

void ubend() {
  for (int i = 0; i < 10; i++) {
    if (i == 4 or i == 5) {
      myServos[i].write(0);
      delay(100);
    } else {
      myServos[i].write(90);
      delay(100);
    }
  }
}

void ring() {
  InteriorAngle = 180 - 360 / (TotalNumberofServos + 1);  //general formula for a polygon with 3 or more vertices, +1 vertice between tail and head segment
  SetpointAngle = abs(InteriorAngle - 90);                //Offset the angle from the initial position of 90 degrees.
  for (int i = 0; i < 10; i++) {
    myServos[i].write(SetpointAngle);
    delay(100);
  }
}


void slither(int offset, int Amplitude, int Speed, float Wavelengths) {
  MaxAngleDisplacement = abs(offset) + abs(Amplitude);  //amount servo can rotate from the SetpointAngle without going out of the [0,180] degree range
  while (MaxAngleDisplacement > 90) {                   //prevents a setpoint angle outside the rage of[0,180]
    Amplitude = abs(Amplitude) - 1;
    MaxAngleDisplacement = abs(offset) + Amplitude;
  }
  for (int i = 0; i < 360; i++) {
    rads = i * pi / 180.0;  //convert from degrees to radians
    for (int j = 0; j < 10; j++) {
      myServos[j].write(90 + offset);  //+Amplitude*sin(Speed*rads+j*Wavelengths*Shift));
    }
    delay(10);
  }
}

void staticWave(int offset, int Amplitude, float Wavelengths) {
  MaxAngleDisplacement = abs(offset) + abs(Amplitude);  //amount servo can rotate from the SetpointAngle without going out of the [0,180] degree range
  while (MaxAngleDisplacement > 90) {                   //prevents a setpoint angle outside the rage of[0,180]
    Amplitude = abs(Amplitude) - 1;
    MaxAngleDisplacement = abs(offset) + Amplitude;
  }

  for (int j = 0; j < 10; j++) {
    myServos[j].write(90 + offset + Amplitude * sin(j * Wavelengths * Shift));
    delay(15);
  }
}

void InchWorm() {
  for (int pos = 0; pos < 45; pos += 1) {
    myServos[0].write(90 - pos);
    myServos[1].write(90 + 2 * pos);
    myServos[2].write(90 - pos);
    delay(10);
  }

  for (int i = 0; i < 7; i += 1) {
    for (int pos = 0; pos < 45; pos += 1) {
      myServos[i].write(45 + pos);
      myServos[i + 1].write(180 - 3 * pos);
      myServos[i + 2].write(45 + 3 * pos);
      myServos[i + 3].write(90 - pos);
      delay(10);
    }
  }

  for (int pos = 0; pos < 45; pos += 1) {
    myServos[7].write(45 + pos);
    myServos[8].write(180 - 2 * pos);
    myServos[9].write(45 + pos);
    delay(10);
  }
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
  buttonState = digitalRead(3);

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

  









  //delay(100);
}
