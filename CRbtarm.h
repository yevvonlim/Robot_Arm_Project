// 2020.1.12 YONSEI ROBOIN, WINTER ROBOTIC ARM PROJECT. WRIITEN BY YEWON LIM, GA06033@O365.YONSEI.AC.KR
// ROBOTIC ARM LIBRARY Ver 1.03 WITH ARDUINO UNO

#ifndef _ROBOTIC_ARM_
  
#define _ROBOTIC_ARM_ 

/*---------------------------------angle 범위---------------------------------------*/
/*         [waist]       0~180                   initial position: 90              */
/*         [shoulder]    0~120                   initial pisition: 120             */
/*         [elbow]       60~180                  initial position: 120             */
/*         [wrist_roll]  0~180                   initial position: 0               */  
/*         [wrist_pitch] 0~90                    initial position: 10              */    
/*         [gripper]     90~180                  initial position: 135             */
/*----------------------------------Values-----------------------------------------*/
#define SPEED_100  100
#define SPEED_90    90
#define SPEED_80    80
#define SPEED_70    70
#define SPEED_60    60
#define SPEED_50    50
#define SPEED_40    40
#define SPEED_30    30
#define SPEED_20    20
#define SPEED_10    10

#define INIT_WAIST_ANGLE        90
#define INIT_SHOULDER_ANGLE     90
#define INIT_ELBOW_ANGLE        0               
#define INIT_WRIST_ROLL_ANGLE   90
#define INIT_WRIST_PITCH_ANGLE  100
#define INIT_GRIPPER_ANGLE      180

#define MIN_WAIST_ANGLE             0
#define MAX_WAIST_ANGLE             180

#define MIN_SHOULDER_ANGLE          0
#define MAX_SHOULDER_ANGLE          180

#define MIN_ELBOW_ANGLE             0
#define MAX_ELBOW_ANGLE             180

#define MIN_WRIST_ROLL_ANGLE        0
#define MAX_WRIST_ROLL_ANGLE        180

#define MIN_WRIST_PITCH_ANGLE       0
#define MAX_WRIST_PITCH_ANGLE       180

#define MIN_GRIPPER_ANGLE           0
#define MAX_GRIPPER_ANGLE           180

#define WAIST_PIN 5
#define SHOULDER_PIN 6
#define ELBOW_PIN 7
#define WRIST_ROLL_PIN 8
#define WRIST_PITCH_PIN 9
#define GRIPPER_PIN 10

enum joint {waist, shoulder, elbow, wrist_roll, wrist_pitch, gripper};
/*------------------------------------------------------------------------------*/

#include <Servo.h>
#include "Arduino.h"
#include "sensor.h"

class CRbtarm
{
friend void radar_on_cw(CRbtarm& _robotarm, int (*_buffer)[2]);
friend void radar_on_ctcw(CRbtarm& _robotarm, int (*_buffer)[2]);
friend int* data_process(CRbtarm& _robotarm, int (*buf_ptr)[2]);

private:
  int m_init_angle[6];                                      // 관절의 초기각도를 의미. 생성시 정해져 있으므로 굳이 전달할 필요 x
  int m_angle[6];                                           //index는 0~5까지 순서대로 각각 관절에 해당함, 각 관절의 현재 각도를 저장 
  Servo m_waist, m_shoulder, m_elbow, m_wrist_roll, m_wrist_pitch, m_gripper; //Servo m_waist, m_shoulder, m_elbow, m_wrist_roll, m_wrist_pitch, m_gripper; //각각 관절에 해당하는 Servo 객체 선언
  Servo* const motor[6] = {&m_waist, &m_shoulder, &m_elbow, &m_wrist_roll, &m_wrist_pitch, &m_gripper};

  void angle_process(int index, int angle_, int speed_);
  
public:
  CRbtarm();
  bool m_move(joint _joint, int _speed, int _angle);          // _joint는 움직이고자 하는 관절(joint 열거체 참고), speed는 10~100사이의 값으로, 전처리 상수를 이용, _angle은 움직이고자 하는 각도
  void initialize(int wstpin, int shldrpin, int elbpin, int wrpin, int wppin, int grippin);  // 움직이고자 하는 각도를 의미한다. 각 관절이 움직일 수 있는 범위를 넘어서면 false를 반환함.
  void grip();
};

#endif
