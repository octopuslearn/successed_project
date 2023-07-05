#include <SoftwareSerial.h>
SoftwareSerial second_arduino(2, 3);  //虚拟串口2-rxd,3-txd

#define lef_90 200  
#define rig_90 200 

#define lef_90 200
#define rig_90 200

int lr_90[2];


void lefrig_90();

void setup() {
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  // put your setup code here, to run once:
  Serial.begin(9600);
  second_arduino.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  lr_90[0] = digitalRead(0);
  lr_90[1] = digitalRead(1);
  Serial.print("lr_90[0]: "); Serial.print(lr_90[0]); Serial.print("\t"); 
  Serial.print("lr_90[1]: "); Serial.println(lr_90[1]); 

  lefrig_90();
}

void lefrig_90()
{
  if(lr_90[0] == 1) //左直角
  {
//    Serial.println("左直角");
second_arduino.println("左直角");
//    car_runtime(RIGHT,0,riggo_90);
  }
  if(lr_90[1] == 1) //右直角
  {
//    Serial.println("右直角");
second_arduino.println("右直角");
//    car_runtime(LEFT,lefgo_90,0);
  }
}
