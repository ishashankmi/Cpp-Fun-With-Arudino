#include<Servo.h>
#include<AFMotor.h>

AF_DCMotor m1(1);
AF_DCMotor m2(2);
AF_DCMotor m3(3);
AF_DCMotor m4(4);



Servo myser;

#define tpin 2
#define epin 13

int duration, distance;

int dist(){
  digitalWrite(tpin,LOW);
  delayMicroseconds(2);
  digitalWrite(tpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(tpin,LOW);

  duration=pulseIn(epin,HIGH);

  distance=(duration/2)*0.0343;

  return distance;
}

int fiDir(){
  int x,y;

  myser.write(90);
  delay(8);
  myser.write(0);
  delay(400);
  x=dist();
  myser.write(180);
  delay(300);
  y=dist();
  delay(400);
  myser.write(90);
  delay(50);
  if(x<y){
    left();
  }else{
    right();
  }
  return 0;
}

int run(int x){
  int y=250;
  m1.setSpeed(y);
  m2.setSpeed(y);
  m3.setSpeed(y);
  m4.setSpeed(y);
  
  if(x==1){
    m1.run(FORWARD);
    m2.run(FORWARD);
    m3.run(FORWARD);
    m4.run(FORWARD);
  }else if(x==2){
    m1.run(BACKWARD);
    m2.run(BACKWARD);
    m3.run(BACKWARD);
    m4.run(BACKWARD);
  }
}

int forward(){
  int di=dist();
  if(di<=11){
    dback();
    delay(500);
    fiDir();
    delay(850);
    rele();
    delay(1000);
  }else{
    run(1);
  }
}

int right(){
  m1.run(RELEASE);
  m2.run(RELEASE);
  m3.run(RELEASE);
  m4.run(RELEASE);


  
  
  m1.run(FORWARD);
  m4.run(FORWARD);
}


int rele(){
  m1.run(RELEASE);
  m2.run(RELEASE);
  m3.run(RELEASE);
  m4.run(RELEASE);
}

int left(){
  m1.run(RELEASE);
  m2.run(RELEASE);
  m3.run(RELEASE);
  m4.run(RELEASE);
  
  m2.run(FORWARD);
  m3.run(FORWARD);
}

int dback(){
  int x,y;
  m1.run(RELEASE);
  m2.run(RELEASE);
  m3.run(RELEASE);
  m4.run(RELEASE);

  m1.run(BACKWARD);
  m2.run(BACKWARD);
  m3.run(BACKWARD);
  m4.run(BACKWARD);

  delay(700);
  m1.run(RELEASE);
  m2.run(RELEASE);
  m3.run(RELEASE);
  m4.run(RELEASE);
  return 0;
}



void setup(){
  Serial.begin(9600);
  myser.attach(9);
  pinMode(tpin,OUTPUT);
  pinMode(epin,INPUT);
}


void loop(){
  forward();
}
