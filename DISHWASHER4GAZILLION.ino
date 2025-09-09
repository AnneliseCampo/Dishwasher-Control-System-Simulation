#include <Servo.h>
#include "Arduino_SensorKit.h"

int binaryPins [] = {7,8,9};
int RED = 6;
int BLUE = 5;  
int GREEN = 3;
int hue = 0;

const int piezopin = 11;

Servo myServo;
int ServClosed = 20;
int ServCold = 60;
int ServHot = 120;
int ServDrain = 160;

int yell = 0;

int ss1 = LOW;
int oss1 = LOW;
int ss2 = LOW;
int oss2 = LOW;
int ss3 = LOW;
int oss3 = LOW;

int toggle = LOW;

int executeVAL = 1024;

int BUTTON1 = 2;
int BUTTON2 = 4;
int clearPin = 10;

int executePin = A0;
int potpin = A1;

int potval = 0;
int scale = 0;
float delayscale = 0;

int blinkit [] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,255};
int blink1 =0;
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
void D1(void){
  Oled.setCursor(0, 2);
  Oled.print("Diagnostic 1");
  Serial.println("Diagnostic 1");
  
  //LED/binary
  Serial.println("Test Binary LEDs");
  digitalWrite(binaryPins[0],1);
  digitalWrite(binaryPins[1],0);
  digitalWrite(binaryPins[2],1);
  delay(500);
  digitalWrite(binaryPins[0],0);
  digitalWrite(binaryPins[1],0);
  digitalWrite(binaryPins[2],0);  
  delay(500);
  
  // FLASH the green LED
  Serial.println("Test Pulsing Light");
  analogWrite(GREEN, 255);
  delay(2000);
  analogWrite(GREEN, 25);
  delay(1000);
  
  // BEEP piezo
  Serial.println("Test Peizo");
  tone(piezopin,1000,500);
  tone(piezopin,1500,800);
}

void D2Serv(void){
  serv(ServCold);
    delay(800);
  serv(ServDrain);
    delay(800);
  serv(ServHot);
    delay(800);
  serv(ServDrain);
    delay(800);
  serv(ServClosed);
    delay(800);
}

void serv(int valve){
  myServo.write(valve);
}

void oled(void){
  Oled.setFont(u8x8_font_chroma48medium8_r); 
  Oled.setCursor(0, 0);
  Oled.print("Wash Cycle:");

  Oled.setCursor(0, 5);
  Oled.print("Timing Factor: ");
}

void blink(int t, int color, int yell){
  if (yell == 1){
    for(int i=0; i<t; i++){
      for(int i=0; i<25; i++){
      analogWrite(RED,blinkit[i]);
      analogWrite(GREEN,blinkit[i]);
      pottiming(20);
      //delay(20);
      }
      for(int i=25; i>0; i--){
      analogWrite(RED,blinkit[i]);
      analogWrite(GREEN,blinkit[i]);
      pottiming(20);
      //delay(20);
      }
    }
  }
  else{
    for(int i=0; i<t; i++){
      for(int i=0; i<25; i++){
        analogWrite(color,blinkit[i]);
        pottiming(20);
        //delay(20);
      }
      for(int i=25; i>0; i--){
        analogWrite(color,blinkit[i]);
        pottiming(20);
        //delay(20);
      }
    }
  }
  analogWrite(RED,0);
  analogWrite(GREEN,0);
  analogWrite(BLUE,0);
}

void BinaryOut(int binary){
  switch(binary){
    case 0:
    digitalWrite(binaryPins[0],0);
    digitalWrite(binaryPins[1],0);
    digitalWrite(binaryPins[2],0);
    serv(ServClosed);
    delay(400);
    break;
    
    case 1:
    digitalWrite(binaryPins[0],0);
    digitalWrite(binaryPins[1],0);
    digitalWrite(binaryPins[2],1);
    serv(ServCold);
    delay(400);
    break;
    
    case 2:
    digitalWrite(binaryPins[0],0);
    digitalWrite(binaryPins[1],1);
    digitalWrite(binaryPins[2],0);
    serv(ServHot);
    delay(400);
    break;
    
    case 3:
    digitalWrite(binaryPins[0],0);
    digitalWrite(binaryPins[1],1);
    digitalWrite(binaryPins[2],1);
    serv(ServClosed);
    delay(400);
    break;
    
    case 4:
    digitalWrite(binaryPins[0],1);
    digitalWrite(binaryPins[1],0);
    digitalWrite(binaryPins[2],0);
    serv(ServClosed);
    delay(400);
    break;
    
    case 5:
    digitalWrite(binaryPins[0],1);
    digitalWrite(binaryPins[1],0);
    digitalWrite(binaryPins[2],1);
    serv(ServClosed);
    delay(400);
    break;
    
    case 6:
    digitalWrite(binaryPins[0],1);
    digitalWrite(binaryPins[1],1);
    digitalWrite(binaryPins[2],0);
    serv(ServDrain);
    delay(400);
    break;
    
    case 7:
    digitalWrite(binaryPins[0],1);
    digitalWrite(binaryPins[1],1);
    digitalWrite(binaryPins[2],1);
    serv(ServDrain);
    delay(400);
    break;
  }
}

void pottiming(int duration){
  Serial.println(round(delayscale*duration));
  delay(round(delayscale*duration));
  //Serial.println(delayscale);
}

void quickwash(){
  Oled.setCursor(0, 2);
  Oled.print("Quickwash v1");
  Serial.println("Quickwash Initiated");
  
  BinaryOut(1);
  blink(4,GREEN,0);
  BinaryOut(3);
  blink(6,GREEN,0);
  BinaryOut(1);
  blink(2,GREEN,0);
  BinaryOut(7);
  blink(1,GREEN,0);
  BinaryOut(0);

  tone(piezopin,1000,500);
  shutdown();
  Serial.println("Quickwash Finished");
}

void test1(){
  Oled.setCursor(0, 2);
  Oled.print("Test 1");
  Serial.println("Test Program 1: Initiated");
  
  for(int i=0; i<8; i++)
  {
    BinaryOut(i);
    delay(600);
  }
  for(int i=7; i>-1; i--)
  {
    BinaryOut(i);
    delay(600);
  }

  shutdown();
  Serial.println("Test Program 1: Finished");
}

void test2(){
  Oled.setCursor(0, 2);
  Oled.print("Test 2");
  Serial.println("Test Program 2: Initiated");

  BinaryOut(2);
  delay(1000);
  BinaryOut(3);
  delay(1000);
  BinaryOut(0);

  shutdown();
  Serial.println("Test Program 2: Finished");
}

void test3(){
  Oled.setCursor(0, 2);
  Oled.print("Test 3");
  Serial.println("Test Program 3: Initiated");

  blink(1,RED,0);
  blink(1,GREEN,0);
  blink(1,BLUE,0);
  blink(1,RED,1);

  tone(piezopin,1000,500);
  delay(1000);
  tone(piezopin,1000,500);
  delay(1000);
  tone(piezopin,1000,500);
  delay(1000);
  shutdown();
  Serial.println("Test Program 3: Finished");
}

void Quickcycle(){
  Oled.setCursor(0, 2);
  Oled.print("Quickwash    ");

  BinaryOut(1);
  blink(3,GREEN,0);
  BinaryOut(3);
  blink(3,GREEN,0);
  BinaryOut(1);
  blink(3,GREEN,0);
  BinaryOut(7);
  blink(3,GREEN,0);
  BinaryOut(0);

  tone(piezopin,1500,1000*round(delayscale));
  delay(1000*round(delayscale));

  shutdown();
}

void Normalcycle(){
  Oled.setCursor(0, 2);
  Oled.print("Normal       ");

  BinaryOut(1);
  blink(3,RED,1);
  BinaryOut(4);
  blink(5,RED,1);
  BinaryOut(1);
  blink(3,RED,1);
  BinaryOut(7);
  blink(3,RED,1);
  BinaryOut(0);

  tone(piezopin,750,1500*round(delayscale));
  delay(1000*round(delayscale));

  shutdown();
}

void PotsandPanscycle(){
  Oled.setCursor(0, 2);
  Oled.print("Pots and Pans");

  BinaryOut(2);
  blink(3,RED,0);
  BinaryOut(5);
  blink(7,RED,0);
  BinaryOut(2);
  blink(5,RED,0);
  BinaryOut(6);
  blink(3,RED,0);
  BinaryOut(0);

  tone(piezopin,300,500*round(delayscale));
  delay(1000);

  shutdown();
}

void shutdown(){
  Serial.println("shutting down");
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 0);
  analogWrite(RED, 0);
  myServo.write(ServClosed);
  Oled.setCursor(0, 2);
  Oled.print("              ");
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
void setup()
{
  pinMode(piezopin, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  for(int i=0; i<3; i++)
  {
    pinMode(binaryPins[i], OUTPUT);
    digitalWrite(binaryPins[i], LOW);
  }
  
  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);

  pinMode(clearPin,OUTPUT);
  pinMode(executePin,INPUT);
  pinMode(potpin,INPUT);

  digitalWrite(clearPin,HIGH);
  
  myServo.attach(12);
  serv(ServClosed);
  
  Oled.begin();
  Oled.setFlipMode(true);

  Serial.begin(9600);
  while (!Serial){}
  Serial.println("System Active");
  
  oled();
}

////////////////////////////////////////////////////////////////
void loop()
{
  Oled.setCursor(0, 6);
  Oled.print(delayscale);
  
  ss1 = digitalRead(BUTTON1);
  delay(20);
  ss2 = digitalRead(BUTTON2);
  delay(20);
  executeVAL = analogRead(executePin);
  delay(20);
  potval = analogRead(potpin);
  delay(20);  
  
  scale = map(potval,1,1024,50,350);
  delayscale = scale*0.01;


  if (ss2 == LOW && ss1 == HIGH && executeVAL >= 312 && toggle == LOW)
  {
    digitalWrite(clearPin,LOW);
    toggle = !toggle;
    Serial.println("menu: 1");  
    Quickcycle();
    digitalWrite(clearPin,HIGH);
  }
  
  if (ss2 == HIGH && ss1 == LOW && executeVAL >= 312 && toggle == LOW)
  {
    digitalWrite(clearPin,LOW);
    toggle = !toggle;
    Serial.println("menu: 2");
    Normalcycle();
    digitalWrite(clearPin,HIGH);
  }

  if (ss2 == HIGH && ss1 == HIGH && executeVAL >= 312 && toggle == LOW)
  {
    digitalWrite(clearPin,LOW);
    toggle = !toggle;
    Serial.println("menu: 3");
    PotsandPanscycle();
    digitalWrite(clearPin,HIGH);
    
  }
  toggle = !toggle;
}

