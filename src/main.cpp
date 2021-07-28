#include <Arduino.h>
#include <Servo.h> //Add the servo library and the pins for the turret.
//Define the pins for the motor driver (L298N).
int ENA= 10;
int IN1= 7;
int IN2= 8;

int IN3= 12;
int IN4= 13;
int ENB= 11;

// Define the drive functions.
int forward;
int backward;
int left;
int right;

//Define the channels of the analog inputs of the reciever.
int ch1 = 9; 
int ch2 = 6;
int ch3 = 5;
int ch4 = 3; 
int ch5 = A1;
int ch6 = A0;

//Define the pulsein functions.
int PWM_CH1=0;
int PWM_CH2=0;
int PWM_CH3=0;
int PWM_CH4=0;
int PWM_CH5=0;
int PWM_CH6=0;

//Define the values for mapping the inputs for the tank.
int CH1_VAL=0;
int CH2_VAL=0;
int CH3_VAL=0;
int CH4_VAL=0;
int CH5_VAL=0;
int CH6_VAL=0;
void setup() {
//Define the inputs and engage the serial monitor in the setup.
pinMode(ch1,INPUT);
pinMode(ch2,INPUT);
pinMode(ch3,INPUT);
pinMode(ch4,INPUT);
pinMode(ch5,INPUT);
pinMode(ch6,INPUT);

pinMode(ENA,OUTPUT);
pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);

pinMode(ENB,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);

Serial.begin(115200);
}

void loop() {
//Read the PWM pulse.
PWM_CH1 = pulseIn (ch1,HIGH);
PWM_CH2 = pulseIn (ch2,HIGH);
PWM_CH3 = pulseIn (ch3,HIGH);
PWM_CH4 = pulseIn (ch4,HIGH);
PWM_CH5 = pulseIn (ch5,HIGH);
PWM_CH6 = pulseIn (ch6,HIGH);

//map the values.
CH1_VAL = map(PWM_CH1, 1000, 1990, 0, 255);
CH2_VAL = map(PWM_CH2, 1000, 1990, 0, 255);
CH3_VAL = map(PWM_CH3, 1000, 1990, 0, 255);
CH4_VAL = map(PWM_CH4, 1000, 1990, 0, 255);
//fix for channel 4 hitting -1
if(CH4_VAL<0){
  CH4_VAL=0;
}

//format the digital switched inputs.
if(PWM_CH5>1300){
  CH5_VAL=0;
}
else{
  CH5_VAL=1000;
}

if(PWM_CH6<1100){
  CH6_VAL=1000;
}
if(PWM_CH6>1300){
  CH6_VAL=500;
}
if(PWM_CH6>1600){
  CH6_VAL=0;
}


//Read the pulses on the serial monitor, with a bit of formating.
Serial.print("  Channel 1 = ");
Serial.print(CH1_VAL);

Serial.print("  Channel 2 = ");
Serial.print(CH2_VAL);

Serial.print("  Channel 3 = ");
Serial.print(CH3_VAL);

Serial.print("  Channel 4 = ");
Serial.print(CH4_VAL);

Serial.print("  Channel 5 = ");
Serial.print(CH5_VAL);

Serial.print("  Channel 6 = ");
Serial.println(CH6_VAL);

//Map the PWM_CH functions to the motors for a forward motion.
if(CH5_VAL==1000){
  forward = map (CH2_VAL, 0, 255, 0, 255);
digitalWrite(IN1,LOW);
digitalWrite(IN2,HIGH);
analogWrite(ENA,forward);

digitalWrite(IN3,LOW);
digitalWrite(IN4,HIGH);
analogWrite(ENB,forward);
}

//Map the PWM_CH functions to the motors for a backward motion.
if(CH5_VAL==0){
  backward = map (CH2_VAL, 0, 253, 0, 255);
digitalWrite(IN1,HIGH);
digitalWrite(IN2,LOW);
analogWrite(ENA,backward);

digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
analogWrite(ENB,backward);
}

//Map the PWM_CH functions to the motors for a left motion.
if(CH6_VAL==500){
  if(CH4_VAL<120){
  left = map (CH4_VAL, 126, 0, 0, 255);
digitalWrite(IN1,HIGH);
digitalWrite(IN2,LOW);
analogWrite(ENA,left);

digitalWrite(IN3,LOW);
digitalWrite(IN4,HIGH);
analogWrite(ENB,left);
  }
}

//Map the PWM_CH functions to the motors for a right motion.
if(CH6_VAL==0){
  if(CH4_VAL>135){
  right = map (CH4_VAL, 126, 253, 0, 255);
digitalWrite(IN1,LOW);
digitalWrite(IN2,HIGH);
analogWrite(ENA,right);

digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
analogWrite(ENB,right);
   }
  }
}