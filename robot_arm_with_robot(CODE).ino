#include <AFMotor.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
AF_DCMotor m1lf(1);
AF_DCMotor m2lb(2);
AF_DCMotor m3rb(3);
AF_DCMotor m4rf(4);
Adafruit_PWMServoDriver pwmm = Adafruit_PWMServoDriver();
#define Echo A2
#define Trig A3
#define servo1 0
#define servo2 1
#define servo3 2
#define servo4 3
void setup() {
  pinMode(A5,INPUT);  
  m1lf.setSpeed(200);
  m1lf.run(RELEASE);
  m2lb.setSpeed(200);
  m2lb.run(RELEASE);
  m3rb.setSpeed(200);
  m3rb.run(RELEASE);
  m4rf.setSpeed(200);
  m4rf.run(RELEASE);
   pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pwmm.begin();
  pwmm.setPWMFreq(60);
  pwmm.setPWM(servo1, 0, 330);
  pwmm.setPWM(servo2, 0, 150);
  pwmm.setPWM(servo3, 0, 300);
  pwmm.setPWM(servo4, 0, 410);
  delay(3000);
  Serial.begin(9600);
}

void loop() {
  
  int distance = obstacle();
  Serial.println(distance);
  if (distance <= 9) {
  m1lf.run(RELEASE);
  m2lb.run(RELEASE);
  m3rb.run(RELEASE);
  m4rf.run(RELEASE);
  m1lf.run(BACKWARD);
  m2lb.run(BACKWARD);
  m3rb.run(BACKWARD);
  m4rf.run(BACKWARD);
    delay(100);
  m1lf.run(RELEASE);
  m2lb.run(RELEASE);
  m3rb.run(RELEASE);
  m4rf.run(RELEASE);
    delay(100);
    robotarm();
    delay(100);
  m1lf.run(FORWARD);
  m2lb.run(FORWARD);
  m3rb.run(FORWARD);
  m4rf.run(FORWARD);
    delay(100);
  } else {
    linefollower();
  }
}
int obstacle() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(4);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  long t = pulseIn(Echo, HIGH);
  int cm = t / 29 / 2;
  return cm;
}
void robotarm()
{
  for (int S1value = 330; S1value >= 250; S1value--) {
    pwmm.setPWM(servo1, 0, S1value);
    Serial.println(S1value);
    delay(10);
  }

  for (int S2value = 150; S2value <= 300; S2value++) {
    pwmm.setPWM(servo2, 0, S2value);
    delay(10);
  }

  for (int S3value = 320; S3value <= 400; S3value++) {
    pwmm.setPWM(servo3, 0, S3value);
    delay(10);
  }

  for (int S4value = 410; S4value <= 490; S4value++) {
    pwmm.setPWM(servo4, 0, S4value);
    Serial.println(S4value);
    delay(10);
  }
  ////////////////////////
  delay(2000);
  for (int S4value = 490; S4value > 410; S4value--) {
    pwmm.setPWM(servo4, 0, S4value);
    Serial.println(S4value);
    delay(10);
  }
//
  for (int S3value = 400; S3value > 320; S3value--) {
    pwmm.setPWM(servo3, 0, S3value);
    delay(10);
  }

  for (int S2value = 300; S2value > 150; S2value--) {
    pwmm.setPWM(servo2, 0, S2value);
    delay(10);
  }

  for (int S1value = 250; S1value < 500; S1value++) {
    pwmm.setPWM(servo1, 0, S1value);
    Serial.println(S1value);
    delay(10);
  }
  //////////////////////
  for (int S2value = 150; S2value <= 300; S2value++) {
    pwmm.setPWM(servo2, 0, S2value);
    delay(10);
  }

  for (int S3value = 320; S3value <= 400; S3value++) {
    pwmm.setPWM(servo3, 0, S3value);
    delay(10);
  }

  for (int S4value = 410; S4value <= 490; S4value++) {
    pwmm.setPWM(servo4, 0, S4value);
    Serial.println(S4value);
    delay(10);
  }

  for (int S4value = 490; S4value > 410; S4value--) {
    pwmm.setPWM(servo4, 0, S4value);
    Serial.println(S4value);
    delay(10);
  }
//  ///////////////////
  for (int S3value = 400; S3value > 320; S3value--) {
    pwmm.setPWM(servo3, 0, S3value);
    delay(10);
  }

  for (int S2value = 300; S2value > 150; S2value--) {
    pwmm.setPWM(servo2, 0, S2value);
    delay(10);
  }

  for (int S1value = 500; S1value > 330; S1value--) {
    pwmm.setPWM(servo1, 0, S1value);
    Serial.println(S1value);
    delay(10);
  } 
}
void linefollower() {
  bool vr = digitalRead(A5);
  bool vl = digitalRead(A4);
//Serial.println(vr);
//Serial.println(vl);
  if (vl == 0 && vr == 0) 
  {
  m1lf.run(FORWARD);
  m2lb.run(FORWARD);
  m3rb.run(FORWARD);
  m4rf.run(FORWARD);
  } 
  else if(vl == 1 && vr == 1) 
  {
  m1lf.run(RELEASE);
  m2lb.run(RELEASE);
  m3rb.run(RELEASE);
  m4rf.run(RELEASE);
  } 
  else if(vl == 1 && vr == 0) 
  {
  m1lf.run(BACKWARD);
  m2lb.run(BACKWARD);
  m3rb.run(FORWARD);
  m4rf.run(FORWARD);
  } 
  else if (vl == 0 && vr == 1) {
  m1lf.run(FORWARD);
  m2lb.run(FORWARD);
  m3rb.run(BACKWARD);
  m4rf.run(BACKWARD);
  }
}
