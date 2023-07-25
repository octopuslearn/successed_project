#include <Arduino.h>
#include <PID_v1.h>

/*以下，编码电机相关*/
#define AIN1 22
#define AIN2 23
#define PWMA_LEFT  4//NC
#define ENCODER_LEFT_A_1_PIN 2 //编码器
#define ENCODER_LEFT_B_1_PIN 3 //编码器
volatile int LEFT_A_posi=0;
volatile int LEFT_B_posi=0;

// #define AIN3 24
// #define AIN4 25
// #define PWMB_RIGHT 5
// #define ENCODER_RIGHT_A_1_PIN 18 //编码器
// #define ENCODER_RIGHT_B_1_PIN 19 //编码器
// volatile int RIGHT_A_posi=0;
// volatile int RIGHT_B_posi=0;
 
int PPR = 11;                //一圈11个脉冲
volatile long now_encoder=0; //当前编码器数值
volatile long lastEncoded=0;//上一次编码器数值
int  set_REV=0;              //设定点所需编码器数值
int User_Input=120;            //设定角度
/*以上，编码电机相关*/







/*以下，PID相关*/
// double kp=1,ki=1,kd=0.05;//kp=5,ki=1,kd=0.01;
// double kp=1,ki=1,kd=0.01;//kp=5,ki=1,kd=0.01;
// double kp=1,ki=0.8,kd=0.01;//kp=5,ki=1,kd=0.01;
// double kp=6,ki=0.8,kd=0.01;//kp=5,ki=1,kd=0.01;
 //double kp=3*0.6,ki=0.1,kd=0.01;//kp=5,ki=1,kd=0.01;
  double kp=1.6*0.6,ki=0.03,kd=0.01;//kp=5,ki=1,kd=0.01;
// double kp=0.4,ki=0,kd=0.001;//kp=5,ki=1,kd=0.01;//成功
double input=0,output=0,setpoint=0;
PID motor_A_PID(&input, &output, &setpoint, kp, ki, kd, DIRECT);
/*以上，PID相关*/






int lastMSB = 0;
int lastLSB = 0;








/*以下，范围*/
int MIN_PWM=-125, MAX_PWM=125;
unsigned long SAMPLE_TIME = 10;//采样时间
/*以上，范围*/


/*以下，函数声明*/
void initPID();/*设定pid(pwm包括范围，模式等)*/
void initMotors();/*初始化电机*/
void initEncoders();/*初始化编码器*/
void ISR_Encoder_LEFT_A_1_PIN();
void pwmOut(int out);
void forwardA(int pwm);
void reverseA(int pwm);
void brakeA();
/*以上，函数声明*/







void setup() {
  Serial.begin(9600);
  initMotors();/*初始化电机*/
  initEncoders();/*初始化编码器*/
  initPID();/*设定pid(pwm包括范围，模式等)*/
}

void loop() {
// /*调试*/Serial.print("目标角度: "); Serial.print(User_Input); Serial.print("\t");
// set_REV = map (User_Input, 0, 360, 0, 506); //将度数映射为脉冲
set_REV=11*46*2*2;
setpoint=set_REV;//PID工作时达到此值视为SET值
/*调试*/Serial.print("目标角度对应脉冲数: "); Serial.print(setpoint); Serial.print("\t");
input=now_encoder;//来自编码器的数据被视为过程值
motor_A_PID.Compute();//计算新的值输出
/*调试*/Serial.print("被调值: "); Serial.print(input); Serial.print("\t");
pwmOut(output);
/*调试*/Serial.print("输出情况: "); Serial.println(output); 
//  brakeA();
// Serial.println("调整完成###");
}








/*设定pid(pwm包括范围，模式等)*/
void initPID()
{
  motor_A_PID.SetMode(AUTOMATIC);//自动模式
  motor_A_PID.SetSampleTime(SAMPLE_TIME);//设置采样时间-默认200ms 
  motor_A_PID.SetOutputLimits(MIN_PWM, MAX_PWM);//设定PWM范围
}

/*初始化电机*/
void initMotors(){
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA_LEFT, OUTPUT);
  

  // pinMode(AIN3, OUTPUT);
  // pinMode(AIN4, OUTPUT);
  // pinMode(PWMB_RIGHT, OUTPUT);
}


/*初始化编码器*/
void initEncoders(){
  pinMode(ENCODER_LEFT_A_1_PIN,INPUT);
  pinMode(ENCODER_LEFT_B_1_PIN,INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT_A_1_PIN), ISR_Encoder_LEFT_A_1_PIN, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT_A_1_PIN), ISR_Encoder_LEFT_A_1_PIN, CHANGE);
  
  
  // pinMode(ENCODER_RIGHT_A_1_PIN,INPUT);
  // pinMode(ENCODER_RIGHT_A_1_PIN,INPUT);
  // attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT_A_1_PIN), ISR_Encoder_RIGHT_A_1_PIN, RISING);
  // attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT_A_1_PIN), ISR_Encoder_RIGHT_B_1_PIN, RISING);
}


void ISR_Encoder_LEFT_A_1_PIN(){
  if(digitalRead(ENCODER_LEFT_A_1_PIN)==HIGH)
  {
    if(digitalRead(ENCODER_LEFT_B_1_PIN)==LOW)
      now_encoder++;
    else
      now_encoder--;
  }
  else 
  {
    if(digitalRead(ENCODER_LEFT_B_1_PIN)==HIGH)
      now_encoder++;
    else
      now_encoder--;
  }
//  int MSB = digitalRead(ENCODER_LEFT_A_1_PIN); //MSB = most significant bit
//  int LSB = digitalRead(ENCODER_LEFT_B_1_PIN); //LSB = least significant bit
//  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
//  int sum = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

//  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) now_encoder ++;
//  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) now_encoder --;

//  lastEncoded = encoded; //store this value for next time
}


void pwmOut(int out)
{
  if(out>0)
  {
    forwardA(out);
  }
  else
  {
    reverseA(abs(out));
  }
}

void forwardA(int pwm){
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA_LEFT, pwm);
}


 void reverseA(int pwm){
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA_LEFT, pwm);
} 


void brakeA(){
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
}