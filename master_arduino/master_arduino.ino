// ------------------------ MASTER ---------------------------
#include <LiquidCrystal.h>

#include <Wire.h>

LiquidCrystal pantallita(7,8,12,4,13,2);// conexiones de lcd

byte CODE;
int CODE1=0;
int CODE2;
int m1d = 6;
int m1r = 9;
int m2d = 10;
int m2r = 11;
int m3d = 3;
int m3r = 5;
int v = 50;


void setup()
{
  Serial.begin(9600);
  pantallita.begin(16,2);
  // Maestro 
  Wire.begin();
  
  pantallita.print("Set: ");
  pantallita.setCursor(5,1);
  pantallita.setCursor(0,2);
  pantallita.print("Elapsed: ");
  pinMode(m1d, OUTPUT);
  pinMode(m1r, OUTPUT);
  pinMode(m2d, OUTPUT);
  pinMode(m2r, OUTPUT);
  pinMode(m3d, OUTPUT);
  pinMode(m3r, OUTPUT);
}


void avanza()
{
  analogWrite(m1d, v);
  analogWrite(m2d, v);
  analogWrite(m3d, v);
}

void reversa()
{
  analogWrite(m1r, v);
  analogWrite(m2r, v);
}

void frenar()
{
  analogWrite(m1d, 0);
  analogWrite(m1r, 0);
  analogWrite(m2d, 0);
  analogWrite(m2r, 0);
  
}



void loop()
{
  analogWrite(m1d, HIGH);
  analogWrite(m2d, v);
  analogWrite(m3d, v);
  // Recopilacion de "CODIGO" al esclavo 1 
  Wire.requestFrom(0x01,1);
  int x=0;
  
  while(Wire.available())
  {
    CODE=Wire.read();
  }
   
  
  // toma el tiempo asignado y empieza el tiempo lapsed hasta 
  // cumplir el tiempo asignado
  
  while(CODE != CODE1)
  {
    CODE1=CODE;
    pantallita.setCursor(5,0);
    pantallita.print(CODE1);
    delay(100);
  }
  
  if(CODE == 16)
  {
    
    for(int x=0; x<=CODE;x++)
    {
     avanza();
     Serial.println(x);
     pantallita.setCursor(9,2);
     pantallita.print(x);
     delay(1000); 
    }
    
    pantallita.setCursor(9,2);
    pantallita.print("Finish!");
    exit(0);
   }

   
 }
  
  