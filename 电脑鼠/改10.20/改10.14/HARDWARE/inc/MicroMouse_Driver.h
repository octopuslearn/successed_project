#ifndef _MICROMOUSE_DRIVER_H_
#define _MICROMOUSE_DRIVER_H_
#include "MicroMouse_Define.h"
#include "math.h"
#define MICROMOUSE_ACC                  1
#define MAZE_SEARCH_SPEED               80   //搜索速度
#define MICROMOUSE_TRUN_DIST_GO_AHEAD   2.7  //先调2.5  转完后是否是在格子中心//  转弯后距 大靠前 最小2.5左右	////转完后，调大了车往前，调小了车往后，最小2.5----10.14
#define MICROMOUSE_TRUN_DIST_GO_AHEAD_COR  0.25 //0.25   //转弯前 ，小靠左，大靠右 转弯前//0.3//0.35  ////（转弯前，调小车往左，调大车往右---一般不动，调完就不动了）----10.14
#define MICROMOUSE_PAUSE_GO_AHEAD       40000
#define MICROMOUSE_PAUSE_PER_CM         1376    //一格的脉冲数
#define MICROMOUSE_POS_1_PAULSE         (2*5*MICROMOUSE_PAUSE_PER_CM)  
#define MICROMOUSE_POS_2_PAULSE         (2*13*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_POS_3_PAULSE         (2*13.5*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_POS_4_PAULSE         (2*15.5*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_POS_5_PAULSE         (2*16*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_POS_6_PAULSE         (2*18*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_ONE_BLOCK_PAULSE     (18*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_D_ONE_BLOCK_PAULSE   (2*18*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_PAULSE_COR_MIN       (2*4*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_PAULSE_COR_MAX       (2*14*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_CTRL_DELAY           0
#define MICROMOUSE_POS_COR_DIST_CM      9.5   //
#define MICROMOUSE_POS_COR_PAULSE       (int)(MICROMOUSE_PAUSE_PER_CM*MICROMOUSE_POS_COR_DIST_CM - MICROMOUSE_CTRL_DELAY*MAZE_SEARCH_SPEED)
#define MICROMOUSE_IR_DIST_COR          16
#define MICROMOUSE_IR_DIST_COR_BELOW    12
#define MICROMOSUE_TR90_ACC_TIME        43
#define MICROMOUSE_TR90_GYRO_ANGLE      71.5
#define MICROMOSUE_TL90_ACC_TIME        43
#define MICROMOUSE_TL90_GYRO_ANGLE      -71.5
#define MICROMOUSE_PAUSE_TURN_BACK      40000
#define MICROMOSUE_TB90_ACC_TIME        40
#define MICROMOUSE_TB90_GYRO_ANGLE      165
#define MICROMOUSE_TB90_SLEEP_TIME      0
#define MICROMOUSE_SEARCH_ACC           0.5
#define MICROMOUSE_SEARCH_MAX_SPEED     110
#define MICROMOUSE_SEARCH_BEGIN_ADD_DIST                 (4)
#define MICROMOUSE_SEARCH_BEGIN_ADD_PAULSE               (MICROMOUSE_SPURT_BEGIN_ADD_DIST*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_SEARCH_DEC_FINSH_DIST                 (4+18)
#define MICROMOUSE_SEARCH_DEC_FINSH_PAULSE               (MICROMOUSE_SPURT_DEC_FINSH_DIST*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_SEARCH_ADD_MIN_DIST                   (8)
#define MICROMOUSE_SEARCH_ADD_MIN_PAULSE                 (MICROMOUSE_SPURT_ADD_MIN_DIST*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_SGA_POS_1_PAULSE     (2*6*MICROMOUSE_PAUSE_PER_CM) 
#define MICROMOUSE_SGA_POS_2_PAULSE     (2*12*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_SGA_POS_3_PAULSE     (2*17.5*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_SGA_POS_4_PAULSE     (2*18*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_SGA_POS_COR_PAULSE   (int)(MICROMOUSE_PAUSE_PER_CM*MICROMOUSE_POS_COR_DIST_CM - MICROMOUSE_CTRL_DELAY*MAZE_SEARCH_SPEED)
#define MICROMOUSE_SGA_POS_COR_U_CM      7
#define MICROMOUSE_SGA_POS_COR_U_PAULSE (int)(MICROMOUSE_PAUSE_PER_CM*MICROMOUSE_SGA_POS_COR_U_CM - MICROMOUSE_CTRL_DELAY*MAZE_SEARCH_SPEED)
#define MICROMOUSE_SGA_LB_COR_PAULSE    (2*15*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_SGA_IR_DIST_COR_UP   16
#define MICROMOUSE_SGA_IR_DIST_COR_BLOW 12
#define MICROMOUSE_SPURT_LEAN_POS_COR_TIME              (5)
#define MICROMOUSE_SPURT_SPEED                          (110)
#define MICROMOUSE_SPURT_MAX_SPEED                      (260)   //冲刺速度  最大300
#define MICROMOUSE_SPURT_BEGIN_ADD_DIST                 (3)
#define MICROMOUSE_SPURT_BEGIN_ADD_PAULSE               (MICROMOUSE_SPURT_BEGIN_ADD_DIST*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_SPURT_DEC_FINSH_DIST                 (3+18)
#define MICROMOUSE_SPURT_DEC_FINSH_PAULSE               (MICROMOUSE_SPURT_DEC_FINSH_DIST*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_SPURT_ADD_MIN_DIST                   (8)
#define MICROMOUSE_SPURT_ADD_MIN_PAULSE                 (MICROMOUSE_SPURT_ADD_MIN_DIST*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_SPURT_START_POS		        		(2.8)
#define MICROMOUSE_SPURT_LEAN_POSCOR_TO_DIST	          (15.8)
#define MICROMOUSE_SPURT_LEAN_POSCOR_TO_PAULSE	        (MICROMOUSE_SPURT_LEAN_POSCOR_TO_DIST*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_SPURT_LEAN_STARTPOSCOR_DIST	        (MICROMOUSE_SPURT_LEAN_POSCOR_TO_DIST + 3)
#define MICROMOUSE_SPURT_LEAN_STARTPOSCOR_PAULSE				(2*MICROMOUSE_SPURT_LEAN_STARTPOSCOR_DIST*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_SPURT_LEAN_STARTADJ_FRONT_CORDIST    (15)
#define MICROMOUSE_SPURT_LEAN_STARTADJ_FRONT_CORPAULSE  (2*MICROMOUSE_SPURT_LEAN_STARTADJ_FRONT_CORDIST*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_SPURT_STARTADJ_FRONT_CORDIST         (13)
#define MICROMOUSE_SPURT_STARTADJ_FRONT_CORPAULSE       (2*MICROMOUSE_SPURT_STARTADJ_FRONT_CORDIST*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_SPURT_LEAN_ONE_BLOCK_PAULSE          ((int)(2*12.726*MICROMOUSE_PAUSE_PER_CM))
#define MICROMOUSE_SPURT_LEAN_POS_1_PAULSE              (2*12*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_SPURT_LEAN_POS_2_PAULSE              (MICROMOUSE_SPURT_LEAN_ONE_BLOCK_PAULSE)
#define MICROMOUSE_SPURT_POS_1_PAUSE                    (2*6*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_SPURT_POS_2_PAUSE                    (2*12*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_SPURT_POS_3_PAUSE                    (2*17.5*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_SPURT_POS_4_PAUSE                    (2*18*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_SPURT_BEGIN_POSCOR_DIST              (2*4*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_SPURT_END_POSCOR_DIST                (2*14*MICROMOUSE_PAUSE_PER_CM)
#define MICROMOUSE_SPURT_TRL90_AVR_SPEED                 (110)
#define MICROMOUSE_SPURT_TRL90V_AVR_SPEED                (110)
#define MICROMOUSE_SPURT_TR90_ACC_TIME				(46)
#define MICROMOUSE_SPURT_TR90_GYRO_ANGLE			(70)
#define MICROMOUSE_SPURT_TL90_ACC_TIME				(46)
#define MICROMOUSE_SPURT_TL90_GYRO_ANGLE			(-70)
#define MICROMOUSE_SPURT_TR90V_ACC_TIME				(46)
#define MICROMOUSE_SPURT_TR90V_GYRO_ANGLE			(70)
#define MICROMOUSE_SPURT_TL90V_ACC_TIME				(46)
#define MICROMOUSE_SPURT_TL90V_GYRO_ANGLE			(-70)
#define MICROMOUSE_SPURT_TRL45_AVR_SPEED 			(110)
#define MICROMOUSE_SPURT_TR45_ACC_TIME				(46)
#define MICROMOUSE_SPURT_TR45_GYRO_ANGLE			(26)
#define MICROMOUSE_SPURT_TL45_ACC_TIME				(46)
#define MICROMOUSE_SPURT_TL45_GYRO_ANGLE			(-23)
#define MICROMOUSE_SPURT_TR45X_ACC_TIME				(46)
#define MICROMOUSE_SPURT_TR45X_GYRO_ANGLE			(26)
#define MICROMOUSE_SPURT_TL45X_ACC_TIME				(46)
#define MICROMOUSE_SPURT_TL45X_GYRO_ANGLE			(-23)
#define MICROMOUSE_SPURT_TRL180_AVR_SPEED   		     (110)
#define MICROMOUSE_SPURT_TR180_ACC_TIME				(42)
#define MICROMOUSE_SPURT_TR180_GYRO_ANGLE			(161)
#define MICROMOUSE_SPURT_TL180_ACC_TIME				(43)
#define MICROMOUSE_SPURT_TL180_GYRO_ANGLE			(-162)
#define MICROMOUSE_SPURT_TRL135_AVR_SPEED     		(110)
#define MICROMOUSE_SPURT_TR135_ACC_TIME				(46)
#define MICROMOUSE_SPURT_TR135_GYRO_ANGLE			(118)
#define MICROMOUSE_SPURT_TL135_ACC_TIME				(46)
#define MICROMOUSE_SPURT_TL135_GYRO_ANGLE			(-112)
#define MICROMOUSE_SPURT_TR135Z_ACC_TIME			(46)
#define MICROMOUSE_SPURT_TR135Z_GYRO_ANGLE			(117)
#define MICROMOUSE_SPURT_TL135Z_ACC_TIME			(46)
#define MICROMOUSE_SPURT_TL135Z_GYRO_ANGLE			(-112)
extern  char      CrossWayInf;
extern  char      GucMapBlock[MAZETYPE][MAZETYPE];
extern  char      GucMouseDir ;
extern  char      GucMapStep[MAZETYPE][MAZETYPE];
extern  long      Step;
extern  char      SRC_X,SRC_Y,DEST_X,DEST_Y;
extern  long      SpeedChangeTime;
extern  char      Test;
extern  SPURTSTEP SpurtStep[MAZETYPE*MAZETYPE];
extern  MAZECOOR  GmcMouseCoor;
void MicroMouse_GoAhead(float Dist);
void MicroMouse_CrosswayChoice(char drad);
void MicroMouse_TurnRight90(void);
void MicroMouse_TurnLeft90(void);
void MicroMouse_TurnBack(BOOL bACC,BOOL bPosCor);
void MicroMouse_CoorUpdate(void);
void MicroMouse_SpurtCrosswayChoice(long drad);
void MicroMouse_SpurtTurnRight45(void);
void MicroMouse_SpurtTurnRight90(void);
void MicroMouse_SpurtTurnRight135(void);
void MicroMouse_SpurtTurnRight180(void);
void MicroMouse_SpurtTurnLeft45(void);
void MicroMouse_SpurtTurnLeft90(void);
void MicroMouse_SpurtTurnLeft135(void);
void MicroMouse_SpurtTurnLeft180(void);
void MicroMouse_ChangeSpeed(float a,long DestSpeed,long StartSpeed,BOOL *Finished);
void MicroMouse_Speed_Change_Calc(void);
void MicroMouse_Speed_Change_Sys(long Pos,BOOL *Dec_Finish,long PulseCtl,float acc);
void MicroMouse_MazeBlockDataGet(char  ucDirTemp,char *Block,char *Step);
void MicroMouse_SearchGoAhead(long Pos);
void MicroMouse_SearchObjectTo(void);
void MicroMouse_SpurtToGoal(void);
void MicroMouse_HandleStartPos(void);
void MicroMouse_SearchSpeedChangeCalc(void);
void MicroMouse_SimpleAhead(float back_distance,float go_distance);
#endif

