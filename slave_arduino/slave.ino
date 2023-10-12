// ----------------------- ESCLAVO ---------------------------
#include <Servo.h>

#include <Wire.h>

#include <IRremote.h>


IRrecv ir(8);

decode_results read;


int trig = 4;
int echo = 2;
int servo = 7;
int pbT = 12; // pushButton Time
int distancia;
int tiempo;
int color;

// 1 es color verde

Servo servito;// Instancia de servo REVISION

byte CODE;

byte entra=0;

void setup()
{
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  servito.attach(servo);
  pinMode(servo, OUTPUT); 
  pinMode(pbT, INPUT);
  ir.enableIRIn();
  // esclavo
  Wire.begin(0x01);
  Wire.onReceive(entradaSolicitud);
  Wire.onRequest(peticion);
}



// --------------------- FUNCIONES -----------------------



void calcularDistancia()
{
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  (tiempo)=pulseIn(echo,HIGH);
  (distancia)=0.01715*tiempo;
  
  Serial.print("Distancia:");
  Serial.print(float(distancia));
  Serial.println("cm");
}



void tempDesc(int temp)//temporizador en descendente
{
  while(temp!=0)
  {
    temp--;
    delay(1000);
  }
}




// ---------------------  main ------------------------

void loop()
{
  int pulsacionesT=0;
  int tiempo=pulsacionesT*1000;
  
  
  while (digitalRead(pbT) == HIGH)
      {
        CODE=pulsacionesT;
        Serial.print("Tiempo: ");
        Serial.println(pulsacionesT);
        pulsacionesT+=15;
        delay(1000);
      }
  
  
  if(ir.decode(&read))
  {
    Serial.print("Codigo recibido:");
    Serial.println(read.value,HEX);
    ir.resume();
  }
  
  
  
  if(CODE>0 && read.value==0xFDA05F )
  {
    CODE=16;
    delay(1000);
    ir.resume();
    read.value=0x0;
  }
  
  
  if(CODE==16)
  {
    while(tiempo>0)// agregar OR si no detecta verde
    {
      calcularDistancia();
      detectarColor();
      tiempo--;
     }
   }  
   
  
  
  
  
  
}

// ---------------------------------------------------------



// ----------- Solicitud y peticion (maste y slave) ------------

void entradaSolicitud(int re)
{
  while(Wire.available())
  {
    entra=Wire.read();
  }
  Serial.println(entra);
}

void peticion()
{
  Wire.write(CODE);
}


// ------------------------------------------------------------