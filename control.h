//2020.02.12 YONSEI ROBOIN, WINTER ROBOTIC ARM PROJECT. CONTROL.H
#ifndef _CONTROL_
#define _CONTROL_

#include "Arduino.h"
#include "CRbtarm.h"
#include "Coords.h"

#define A1 118
#define A2 120

// 좌표상의 각도와 서보모터의 각도를 보정해주는 상수
#define C2 120
#define C3 90

bool planar_inverse_kinematics(CRbtarm& _robotarm, CylCoord& coord, int spd);

#endif
