#include <TimerOne.h>

/****以下，任意时间角度*****/
#define lr_which_lef 'x'  //任意时间转弯-左转
#define lr_which_rig 'y'
#define lr_which_time 1300 //任意时间转弯时间
int lr_which_lef_start = 0;   //任意时间转弯开始标志位-右转
int lr_which_rig_start = 0;
int lr_which_lef_close = 0;   //任意时间转弯完成标志位-左转
int lr_which_rig_close = 0;

int lr_which_cnt = 0;         //任意时间转弯累计值
/****以上，任意时间角度*****/

/*************以下，90度弯*************/
#define lef_90_pin A0 //90度弯引脚
#define rig_90_pin A1
#define lef_90 300  //90度弯阈值
#define rig_90 300 
int lr_90[4];       //90度弯读取值

#define lefgo_90 full*2.25//90度转弯角度
#define riggo_90 full*2.25

#define lef90 'm'         //90度弯-左弯
#define rig90 'n'
int lr90_this_vale[4];
/*************以上，90度弯*************/


#define ln1_left    6 //左电机1
#define ln2_left    7 //左电机2
#define ln3_right   8 //右电机1
#define ln4_right   9 //右电机2

#define ENA_left_pwm    10
#define ENB_right_pwm   11


#define hy1   2     //OUT5
#define hy2   3     //OUT4
#define hy3   4     //OUT3
#define hy4   5     //OUT2
#define hy5   12    //OUT1
#define hy6   13    //OUT6

#define STOP      'a'   //停止
#define RUN       'b'  //前进
#define BACK      'c'   //后退
#define LEFT      'd'   //左转
#define RIGHT     'e'   //右转

#define full 100
#define large_adjust full*1.5 //更改了1.2-1.5
#define big_adjust   full*1.3 //更改了1.5-1.2-1.3
#define small_adjust full*1.2 //更改了1-1.1-1.2
#define go  full*1
#define stop_car 0


int hw_in[10];     //红外采集

void car_runtime(char car_mode, int pwm);
void hy_invlue();

void setup() {
  pinMode(ln1_left, OUTPUT);
  pinMode(ln2_left, OUTPUT);
  pinMode(ln3_right, OUTPUT);
  pinMode(ln4_right, OUTPUT);
  pinMode(ENA_left_pwm, OUTPUT);
  pinMode(ENB_right_pwm, OUTPUT);
  pinMode(hy1, INPUT);//寻迹模块引脚初始化
  pinMode(hy2, INPUT);
  pinMode(hy3, INPUT);
  pinMode(hy4, INPUT);
  pinMode(hy5, INPUT);
  pinMode(hy6, INPUT);
  Serial.begin(9600);
  car_runtime(STOP, 0);
//  Timer1.initialize(1000); 
//  Timer1.attachInterrupt(trun_LR90);
}

void loop() {
/*******以下为，使用定时器中断*********/
//Serial.print("lr_which_cnt: "); Serial.print(lr_which_cnt); Serial.print('\t');
//Serial.print("lr_which_time: "); Serial.println(lr_which_time);
//  lr_anyangle(lr_which_lef);
/*******以上为，使用定时器中断*********/

////  hy_invlue();
lr_anyangle(lr_which_lef, lr_which_time);     //旋转任意时间

}


void hy_invlue()
{
  hw_in[1] = digitalRead(hy1);  //OUT5
  hw_in[2] = digitalRead(hy2);  //OUT4
  hw_in[3] = digitalRead(hy3);  //OUT3
  hw_in[4] = digitalRead(hy4);  //OUT2
  hw_in[5] = digitalRead(hy5);  //OUT1
  hw_in[6] = digitalRead(hy6);  //OUT6

  lr_90[1] = analogRead(lef_90_pin);
  lr_90[2] = analogRead(rig_90_pin);

  /*调试*/
  Serial.print(hw_in[1]); Serial.print('\t');
   Serial.print(hw_in[2]); Serial.print('\t');
    Serial.print(hw_in[3]); Serial.print('\t');
     Serial.print(hw_in[4]); Serial.print('\t');
      Serial.print(hw_in[5]); Serial.print('\t');
        Serial.print(hw_in[6]); Serial.print('\t'); 
  Serial.print("初始lr_90[1]:  ");  Serial.print(lr_90[1]); Serial.print("\t");  Serial.print("rig_90:  ");  Serial.println(rig_90);

  if(hw_in[5] == 1)//最大幅度-右偏
  {
    Serial.println("最大幅度-右偏");
    car_runtime(LEFT,large_adjust);
  }
  if(hw_in[6] == 1)//大幅度-左偏
  {
    Serial.println("最大幅度-左偏");
    car_runtime(RIGHT,large_adjust);
  }

  if(hw_in[1] == 1) //大幅度-右偏
  {
    Serial.println("大幅度-右偏");
    car_runtime(LEFT,big_adjust);
    
  }
  if(hw_in[4] == 1) //大幅度-左偏
  {
    Serial.println("大幅度-左偏");
    car_runtime(RIGHT,big_adjust);
  }
  
  if(hw_in[2] == 1) //小幅度-右偏
  {
    Serial.println("小幅度-右偏");
    car_runtime(LEFT,small_adjust);
  }
  if(hw_in[3] == 1) //小幅度-左偏
  {
    Serial.println("小幅度-左偏");
    car_runtime(RIGHT,small_adjust);
  }  

    if(lr_90[1] > lef_90) //左直角
    {
      Serial.println("左直角");
      Serial.print("lr_90[0]:  ");  Serial.print(lr_90[0]); Serial.print("\t");  Serial.print("lr_90:  ");  Serial.println(rig_90);
      car_runtime(BACK, 100);
      delay(50);
      car_runtime(STOP, 0);
      delay(500);
      lr90_time(lef90);
    }

    if(lr_90[2] > rig_90) //右直角
    {
      Serial.println("右直角");
      Serial.print("lr_90[1]:  ");  Serial.print(lr_90[1]); Serial.print("\t");  Serial.print("lr_90:  ");  Serial.println(rig_90);
      car_runtime(BACK, 100);
      delay(50);
      car_runtime(STOP, 0);
      delay(500);
      lr90_time(rig90);
    }

  if(hw_in[1]==0 && hw_in[2]==0 && hw_in[3] == 0 && hw_in[4] == 0 && hw_in[5] == 0 && hw_in[6] == 0) //在轨
  {
    if(hw_in[1]==0 && hw_in[2]==0 && hw_in[3] == 0 && hw_in[4] == 0 && hw_in[5] == 0 && hw_in[6] == 0 && !(lr_90[1] > rig_90) && !(lr_90[2] > rig_90)) //在轨
    {
      Serial.println("在轨");
      car_runtime(RUN,go);
    }
  } 
}

void lr90_time(char lr90_time_value)
{
  switch(lr90_time_value)
  {
    case lef90:
      car_runtime(LEFT, riggo_90);  Serial.println("左直角-开始转");
      while(1)
      {               
        do{          
          lr90_this_vale[1]=digitalRead(hy3);         
        }while(lr90_this_vale[1]==0);
        Serial.println("左直角-转完了"); 
        break;
//        lr90_this_vale[2]=digitalRead(hy3);
//        if(lr90_this_vale[2]==1)
//        {
//          Serial.println("左直角-转完了");
//          break;
//        }  
      }      
    break;

    case rig90:
      while(1)
      {
        car_runtime(RIGHT, riggo_90);  Serial.println("右直角-开始转");
        do{          
          lr90_this_vale[2]=digitalRead(hy2);  //OUT2;         
        }while(lr90_this_vale[2]==0);
        Serial.println("右直角-转完了");
        break;
      } 
    break;

    default:break;

  }
}

void car_runtime(char car_mode, int pwm)
{
  analogWrite(ENA_left_pwm, pwm);     //PWM控制
  analogWrite(ENB_right_pwm, pwm);

  switch(car_mode)
  {
    case RUN:
      Serial.println("RUN"); //前进输出状态
      digitalWrite(ln1_left,  HIGH);
      digitalWrite(ln2_left,  LOW);
      digitalWrite(ln3_right, HIGH);
      digitalWrite(ln4_right, LOW);
      break;
      
     case BACK:
      Serial.println("BACK"); //后退输出状态
      digitalWrite(ln1_left,  LOW);
      digitalWrite(ln2_left,  HIGH);
      digitalWrite(ln3_right, LOW);
      digitalWrite(ln4_right, HIGH);
      break;

     case RIGHT:
      Serial.println("LEFT"); //左转输出状态
      digitalWrite(ln1_left,  HIGH);  //左轮开机
      digitalWrite(ln2_left,  LOW);
      digitalWrite(ln3_right, LOW);
      digitalWrite(ln4_right, LOW);
      break;
  
     case LEFT:
      Serial.println("RIGHT"); //右转弯输出状态
      digitalWrite(ln1_left,  LOW);
      digitalWrite(ln2_left,  LOW);
      digitalWrite(ln3_right, HIGH);  //右轮开机
      digitalWrite(ln4_right, LOW);
      break;

     default:
      Serial.println("STOP"); //停止输出状态
      digitalWrite(ln1_left,  LOW);
      digitalWrite(ln2_left,  LOW);
      digitalWrite(ln3_right, LOW);
      digitalWrite(ln4_right, LOW);
      break;
  }
}


/*******以下为，使用定时器中断*********/
//想法很好但是方法错了，因为在中断里不能完成复杂的事，所以失败了
//void trun_LR90()
//{
//  if(lr_which_lef_start == 1)
//  {    while(1);
////    do{
////      lr_which_cnt++;
////    }while(!(lr_which_cnt>lr_which_time));
////    lr_which_cnt++;
////    if(lr_which_cnt>lr_which_time)
////    {
////      lr_which_cnt = 0;
////      lr_which_lef_close = 1;
////    }
//    lr_which_cnt = 0;
//    lr_which_lef_close = 1;
////    lr_which_lef_start = 0;
//  }
//} 
//
//
//void lr_anyangle(char lr_which)
//{
//  switch(lr_which)
//  {
//   case lr_which_lef:
//    Serial.println("开始-任意时间转弯");
//    lr_which_lef_start = 1;  //开始左转标志置一
//    Serial.print("lr_which_lef_start:  "); Serial.println(lr_which_lef_start);
//    while(1)
//    {
//      
//      car_runtime(LEFT, riggo_90); //左转
//      
//      if(lr_which_lef_close == 1)
//      {
//        car_runtime(BACK, 100);
//        delay(50);
//        car_runtime(STOP, 0);
//        Serial.println("任意时间转弯完成");
//        break;
//      }
//     }
//    break;
//
//    default:break;
//  } 
//}
/*******以上为，使用定时器中断*********/


void lr_anyangle(char lr_which, int lr_which_ms)
{
  switch(lr_which)
  {
    case lr_which_lef:
      Serial.println("开始-任意时间转弯");
      Serial.print("转弯时间： "); Serial.println(lr_which_ms);
      car_runtime(LEFT, riggo_90); //左转
      delay(lr_which_ms);     
    break;

    default:break;
  }
  car_runtime(BACK, 100);
  delay(50);
  car_runtime(STOP, 0);
  Serial.println("任意时间转弯完成");

  while(1);
}
