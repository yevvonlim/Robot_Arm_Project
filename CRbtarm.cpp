// 2020.1.12 YONSEI ROBOIN, WINTER ROBOTIC ARM PROJECT. WRIITEN BY YEWON LIM, GA06033@O365.YONSEI.AC.KR
// ROBOTIC ARM LIBRARY Ver 1.03 WITH ARDUINO UNO

#include "CRbtarm.h"

bool CRbtarm::m_move(joint _joint, int _speed, int _angle)
{
  switch(_joint)
  {
  case waist:
    if (_angle < MIN_WAIST_ANGLE || _angle > MAX_WAIST_ANGLE)
    {
      return false;
      break;
    }
    else if(_speed > 100 || _speed < 10)
    {
      return false;
      break;
    }
    else
    {
      angle_process(0, _angle, _speed);
      
      return true;
      break;
    } 
  case shoulder:
    if (_angle < MIN_SHOULDER_ANGLE || _angle > MAX_SHOULDER_ANGLE)
    {
      return false;
      break;
    }
    else if(_speed > 100 || _speed < 10)
    {
      return false;
      break;
    }
    else
    {
      angle_process(1, _angle, _speed);
      
      return true;
      break;
    }
  case elbow:
   if (_angle < MIN_ELBOW_ANGLE || _angle > MAX_ELBOW_ANGLE)
    {
      return false;
      break;
    }
    else if(_speed > 100 || _speed < 10)
    {
      return false;
      break;
    }
    else
    {
      angle_process(2, _angle, _speed);
      
      return true;
      break;
    }
  case wrist_roll:
   if (_angle < MIN_WRIST_ROLL_ANGLE || _angle > MAX_WRIST_ROLL_ANGLE)
    {
      return false;
      break;
    }
    else if(_speed > 100 || _speed < 10)
    {
      return false;
      break;
    }
    else
    {
      angle_process(3, _angle, _speed);
      
      return true;
      break;
    }
  case wrist_pitch:
   if (_angle < MIN_WRIST_PITCH_ANGLE || _angle > MAX_WRIST_PITCH_ANGLE)
    {
      return false;
      break;
    }
    else if(_speed > 100 || _speed < 10)
    {
      return false;
      break;
    }
    else
    {
      angle_process(4, _angle, _speed);
      
      return true;
      break;
    }
  case gripper:
   if (_angle < MIN_GRIPPER_ANGLE || _angle > MAX_GRIPPER_ANGLE)
    {
      return false;
      break;
    }
    else if(_speed > 100 || _speed < 10)
    {
      return false;
      break;
    }
    else
    {
      angle_process(5, _angle, _speed);
      
      return true;
      break;
    }
  }
}

CRbtarm::CRbtarm()
{
    m_init_angle[0] = INIT_WAIST_ANGLE;
    m_init_angle[1] = INIT_SHOULDER_ANGLE;
    m_init_angle[2] = INIT_ELBOW_ANGLE;
    m_init_angle[3] = INIT_WRIST_ROLL_ANGLE;
    m_init_angle[4] = INIT_WRIST_PITCH_ANGLE;
    m_init_angle[5] = INIT_GRIPPER_ANGLE;
}   
    
void CRbtarm::initialize(int wstpin, int shldrpin, int elbpin, int wrpin, int wppin, int grippin)
{
    m_waist.attach(wstpin);                            //사용하고자 하는 관절만 활성화 해야 함. 
    m_shoulder.attach(shldrpin);    
    m_elbow.attach(elbpin);   
    m_wrist_roll.attach(wrpin); 
    m_wrist_pitch.attach(wppin);      
    m_gripper.attach(grippin);

    delay(333);
  
    for(int i = 0; i < 6; i++)
    { 
      motor[i] -> write(m_init_angle[i]);
      m_angle[i] = m_init_angle[i];
    }   
}

void CRbtarm::angle_process(int index, int angle_, int speed_)
{
      int dt_angle = 10;                  //set dt_angle value to 10(number doesn't matter unless 0)
      
      while(dt_angle != 0)
      {
        dt_angle = angle_ - m_angle[index];
        
        if(dt_angle > 0)
        {
          motor[index] -> write(m_angle[index]+1);
          delay(1000/speed_);
          
          m_angle[index] += 1;
        }
        else if(dt_angle < 0)
        {
          motor[index] -> write(m_angle[index]-1);
          delay(1000/speed_);
          
          m_angle[index] -= 1;
        }
      }

}
void CRbtarm::grip()
{
  m_move(gripper, SPEED_50, 180);
  delay(1000);
  m_move(gripper, SPEED_50, 100);
}
