#include <IRremote.h>           //using the iRremote library by  z3t0   https://github.com/z3t0/Arduino-IRremote
int brightR=0;
int red=9; //connect your red to pin 9 
int steps=5; //dimmer steps, vary those to increase/decrease the steps between full brightness and turned off
int RECV_PIN = 11; //data out of IR receiver connects to pin 11
int green=10; //connect your green to pin 10
int blue=12;  //connect your blue to pin 9
int brightG=0;
int brightB=0;
IRrecv irrecv(RECV_PIN);

decode_results results;

void setup(){
  pinMode(red,OUTPUT);
  pinMode(blue,OUTPUT);
  pinMode(green,OUTPUT);

  irrecv.enableIRIn(); // start the receiver
 
  
}

void loop() {
 if (irrecv.decode(&results)) {
      Serial.println(results.value, HEX);

  if (results.value==0xE0E0A857){               // this is a preset from the colour white 
      digitalWrite(red,HIGH);
      digitalWrite(green,HIGH);
      digitalWrite(blue,HIGH);
      
  }  
  if (results.value==0xE0E0A45B){
      digitalWrite(red,LOW);                        //turning the led strip off
      digitalWrite(green,LOW);
      digitalWrite(blue,LOW);
      //before=0;
  }
    
  if (results.value==0xE0E0926D ){ //Code to decrease the brightnessRED
    if(brightR-255/steps<0){ 
      analogWrite(red,brightR);
    }
    else{
      brightR=brightR-255/steps;
      analogWrite(red,brightR);
    }
  }  
  if (results.value==0xE0E036C9){ //Code to increase the brightnessRED
    if(brightR+255/steps>255){
      analogWrite(red,brightR);
    }
    else{    
    brightR=brightR+255/steps;
    analogWrite(red,brightR);
    }
  }
  if (results.value==0xE0E0FC03){ //Code to decrease the brightnessGREEN
    if(brightG-255/steps<0){ 
      analogWrite(green,brightG);
    }
    else{
      brightG=brightG-255/steps;
      analogWrite(green,brightG);
    }
  }  
  if (results.value==0xE0E028D7){ //Code to increase the brightnessGREEN
    if(brightG+255/steps>255){
      analogWrite(green,brightG);
    }
    else{    
      brightG=brightG+255/steps;
      analogWrite(green,brightG);
    }
  }    



  if (results.value==0xE0E0629D){ //Code to decrease the brightnessBLUE
    if(brightB-255/steps<0){ 
      analogWrite(blue,brightB);
    }
    else{
      brightB=brightB-255/steps;
      analogWrite(blue,brightB);
    }
  } 
  if (results.value==0xE0E06897){ //Code to increase the brightnessBLUE
    if(brightB+255/steps>255){
      analogWrite(blue,brightB);
    }
    else{    
      brightB=brightB+255/steps;
      analogWrite(blue,brightB);
    }
  }
  if (results.value==0xE0E0A25D){         //code for red breathing effect
    while(results.value==0xE0E0A25D){
      for (int i=0;i<255;i++){
        analogWrite(red,i);
        delay(10);
      }
      for(int i=255;i>=0;i--){
        analogWrite(red,i);
        delay(10);
      }
     
    }
  }
  if (results.value==0xE0E0E21D){     //code for green breathing effect
    while(results.value==0xE0E0E21D){
      for (int i=0;i<255;i++){
        analogWrite(green,i);
        delay(10);
      }
      for(int i=255;i>=0;i--){
        analogWrite(green,i);
        delay(10);
      }
    }
  }
  if (results.value==0xE0E052AD){       //code for blue breathing effect
    while(results.value==0xE0E052AD){
      for (int x=0;x<255;x++){
        analogWrite(blue,x);
        delay(10);
      }
      for(int x=255;x>=0;x--){
        analogWrite(blue,x);
        delay(10);
      }
    }
  }
  if (results.value==0xE0E012ED){                 //preset for orange
    analogWrite(red,200);
    analogWrite(green,10);
  }
  irrecv.resume();
 }
} 
