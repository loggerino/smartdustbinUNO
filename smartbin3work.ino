#include <SoftwareSerial.h>  
#include <Servo.h>   
Servo servo;
SoftwareSerial SIM900A(10,11);  
long Distance1, Duration1;
int trigpin1 = 8;
int echopin1 = 9;
int servoPin = 7;
int IRsensor = 2;
int IRData;
float distanceInch;
long duration, dist, average;   
long aver[3];   
int green = 4;
int yellow = 5;
int red = 6;
int count1 = 0;
int count2 = 0;
int count3 = 0;

void setup() {
  SIM900A.begin(9600);
  Serial.begin(9600);
  servo.attach(servoPin);
  servo.write(0);
  pinMode(trigpin1, OUTPUT);
  pinMode(echopin1, INPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(IRsensor, INPUT);
  delay(1000);
}

void loop() {
    Sensor_dis();
    IR();
  }
  
void Sensor_dis(){
  digitalWrite(10,HIGH);
    Serial.println("Ultrasonic");
    digitalWrite(trigpin1, LOW);
    delayMicroseconds(2);
    digitalWrite(trigpin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigpin1, LOW);
    delayMicroseconds(10);
    Duration1 = pulseIn(echopin1, HIGH);
     distanceInch= Duration1*0.0133/2;  
    Serial.print("Distance: ");  
    Serial.println(distanceInch);  
    delay(400);  

    if ((distanceInch >= 9) && (distanceInch <= 13 && count1 == 0   ))
    {
      digitalWrite(green, HIGH);
      digitalWrite(yellow, LOW);
      digitalWrite(red, LOW);
      count1++;
      count3 = 0;
      delay(200);
    }
      else if ((distanceInch >= 9) && (distanceInch <= 13 ))
    {
      digitalWrite(green, HIGH);
      digitalWrite(yellow, LOW);
      digitalWrite(red, LOW);
    }
    else if ((distanceInch >= 5) && (distanceInch <= 8 ))
    {
      digitalWrite(green, HIGH);
      digitalWrite(yellow, HIGH);
      digitalWrite(red, LOW);
    }
    else if ((distanceInch >= 0) && (distanceInch <= 4 && count3 == 0 ) )
    {
      digitalWrite(green, HIGH);
      digitalWrite(yellow, HIGH);
      digitalWrite(red, HIGH);
      count3++;
      count1 = 0;
      count2 = 0;
    }
    else if ((distanceInch >= 0) && (distanceInch <= 4 ) )
    {
     
      Serial.println("level 3");
      Serial.println("level 3");
      digitalWrite(green, HIGH);
      digitalWrite(yellow, HIGH);
      digitalWrite(red, HIGH);
      {
  SIM900A.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode   
  delay(1000);   
  SIM900A.println("AT+CMGS=\"01151376616\"\r"); //Write Mobile number to send message   
  delay(1000);    
  SIM900A.println("Dustbin is full, collect at room");// Messsage content   
  delay(100);   
  SIM900A.println((char)26);// ASCII code of CTRL+Z   
  delay(1000);   
          }  
    }
    else
    {
      digitalWrite(green, LOW);
      digitalWrite(yellow, LOW);
      digitalWrite(red, LOW);
    }

  delay(500);
}

void IR(){
    IRData = digitalRead(IRsensor);
  if (IRData == 1)
  {
    servo.write(180);
    delay(1000);
  }
  else
  {
    servo.write(0);
    delay(4000);
  }
}
