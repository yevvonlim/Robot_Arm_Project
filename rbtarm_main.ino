/* 2020.1.12 YONSEI ROBOIN, WINTER ROBOTIC ARM PROJECT. WRIITEN BY YEWON LIM, GA06033@O365.YONSEI.AC.KR, 
                                                                   WONSUK KIM, KIMWS27@YONSEI.AC.KR  */
                                                                   
/*-------------------------------Pin Setting---------------------------------------*/


#include "sensor.h"
#include "control.h"

CRbtarm robotarm;
  
void setup() 
{ 
  Serial.begin(9600);
  robotarm.initialize(WAIST_PIN, SHOULDER_PIN, ELBOW_PIN, WRIST_ROLL_PIN, WRIST_PITCH_PIN, GRIPPER_PIN);

  delay(1000);
}

void loop() 
{
  CylCoord A = seek_coord(robotarm);     // Cylindrical coordinate 형태의 좌표 A를 선언하고 물체의 위치를 받아온다

  Serial.print("\n\n\n\n\n\n\n"); 
  Serial.print("("); Serial.print(A.m_r); Serial.print(", "); Serial.print(A.m_theta); Serial.print(", "); Serial.print(A.m_z); Serial.println(")");  
  // 좌표 값을 시리얼로 출력해서 확인해본다. 테스트할 때 필요함 -> 추후 지울 예정
  
  if( ! planar_inverse_kinematics(robotarm, A, 20))
  {
    Serial.println("범위 밖의 물체는 잡을 수 없어요");
  }
 
  delay(1500);
  robotarm.grip();
  robotarm.m_move(shoulder, SPEED_40, 120);
  robotarm.m_move(elbow, SPEED_40, 60);
  
  robotarm.m_move(wrist_pitch, SPEED_50, 90);
  delay(300);
  robotarm.m_move(wrist_pitch, SPEED_50, 180);
  delay(300);
  robotarm.m_move(wrist_pitch, SPEED_50, 90);
  delay(300);
  robotarm.m_move(wrist_pitch, SPEED_50, 180);
  delay(300);
  
  while(1)
  {
            // 물체 탐지가 끝나고 그대로 멈춰있도록 한다 
  }
}
