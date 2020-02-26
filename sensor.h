// 2020.2.11 YONSEI ROBOIN, WINTER ROBOTIC ARM PROJECT. WRIITEN BY YEWON LIM, GA06033@O365.YONSEI.AC.KR
// ULTRA SONIC SENSOR

#ifndef _ULTRA_SONIC_SENSOR_
#define _ULTRA_SONIC_SENSOR_


#include "Arduino.h"
#include "Coords.h"
#include "CRbtarm.h"
#include <NewPing.h>


#define echoPin 12                //setting pin num of ultra sonic sensor
#define trigPin 13

#define DETECTION_DISTANCE 30
#define D       4.8              // distance from origin to the sensor
#define R       2.5

class CRbtarm;

void radar_on_cw(CRbtarm& _robotarm, int (*_buffer)[2]);
void radar_on_ctcw(CRbtarm& _robotarm, int (*_buffer)[2]);
int* data_process(CRbtarm& _robotarm, int (*buf_ptr)[2]);
int howfar();
byte buffer_check(int (*buf_ptr)[2]);

CylCoord seek_coord(CRbtarm& _robotarm);


#endif
