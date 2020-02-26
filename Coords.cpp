// 2020.1.24 YONSEI ROBOIN, WINTER ROBOTIC ARM PROJECT. WRIITEN BY YEWON LIM, GA06033@O365.YONSEI.AC.KR
// COORDINATES LIBRARY VER 1.1

#include "Coords.h"


CrtCoord::operator SphCoord()
{
  SphCoord A;

  A.m_rho = roundf(sqrt(pow(m_x, 2) + pow(m_y, 2) + pow(m_z, 2))*100)/100;
  A.m_pi = roundf(acos(m_z / A.m_rho)*100)/100;
  A.m_theta = roundf(acos(m_x / sqrt(pow(m_x, 2) + pow(m_y, 2)))*100)/100;

  return A;
}

SphCoord::operator CrtCoord()
{
  CrtCoord B;

  B.m_x = roundf(m_rho * sin(m_pi) * cos(m_theta)*100)/100;
  B.m_y = roundf(m_rho * sin(m_pi) * sin(m_theta)*100)/100;
  B.m_z = roundf(m_rho * cos(m_pi)*100)/100;

  return B;
}

CylCoord::operator CrtCoord()
{
  CrtCoord C;

  C.m_x = m_r * cos(m_theta);
  C.m_y = m_r * sin(m_theta);
  C.m_z = m_z;

  return C;
  
}
