//2020.02.12 YONSEI ROBOIN, WINTER ROBOTIC ARM PROJECT. CONTROL.CPP

#include "control.h"

bool planar_inverse_kinematics(CRbtarm& _robotarm, CylCoord& coord, int spd) { 
  
  double y = coord.m_r - C2;
  double z = coord.m_z;
  double angle_buffer[3];
  double d, q1, q2;

  d = sqrt(y * 1.0L * y * 1.0L + z * 1.0L * z * 1.0L );
  q2 = acos ( (y * 1.0L * y * 1.0L + z * 1.0L * z * 1.0L - A1 * 1.0L * A1 * 1.0L - A2 * 1.0L * A2 * 1.0L ) / 2.0L / (A1 * 1.0L) / (A2 * 1.0L) ) * 180.0L / (PI * 1.0L);
  q1 = ( atan(z/y) + acos( ( A1 * 1.0L * A1 * 1.0L + y * 1.0L * y * 1.0L + z * 1.0L * z * 1.0L - A2 * 1.0L * A2 * 1.0L) / ( 2.0L * A1 * d ) ) ) * 180.0L / (PI * 1.0L);

  
  Serial.println(q1); Serial.println(q2);
  if ((d > A1 + A2) || (d < A2 - A1) ) return false;   // 해당 각도가 없는 경우 즉, 로봇팔의 최대 도달 범위에 벗어난 경우
																					                                        
  else {
  
    angle_buffer[0] = q1;
    angle_buffer[1] = q2;        //q2 + c2
    angle_buffer[2] = q2 - q1 + C3;
    
    _robotarm.m_move(shoulder, spd, angle_buffer[0]);
    _robotarm.m_move(elbow, spd, angle_buffer[1]);
    _robotarm.m_move(wrist_pitch, spd, angle_buffer[2]);

    return true;
  }
}
