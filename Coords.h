// 2020.1.24 YONSEI ROBOIN, WINTER ROBOTIC ARM PROJECT. WRIITEN BY YEWON LIM, GA06033@O365.YONSEI.AC.KR
// COORDINATES LIBRARY VER 1.1

#ifndef _COORDINATES_
#define _COORDINATES_

#include "Arduino.h"

class SphCoord;
class CylCoord;

class CrtCoord
{
public:
  float m_x, m_y, m_z;
  
  CrtCoord(float x, float y, float z) : m_x(roundf(x*1000)/1000), m_y(roundf(y*1000)/1000), m_z(roundf(z*1000)/1000) {};
  CrtCoord() {};

  operator SphCoord();
  
};

class SphCoord
{
public:
  float m_rho, m_theta, m_pi;

  SphCoord() {};
  SphCoord(float rho, float theta, float pi) : m_rho(roundf(rho*100)/100), m_theta(roundf(theta*100)/100), m_pi(roundf(pi*100)/100) {};

  operator CrtCoord();
};

class CylCoord
{
public:
  float m_r; float m_theta; float m_z;

  CylCoord(float _r, float _theta, float _z): m_r(_r), m_theta(_theta), m_z(_z) {}; 
  CylCoord() {m_r = 0; m_theta = 0; m_z = 0;};

  operator CrtCoord();
};


#endif
