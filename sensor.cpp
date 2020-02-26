// 2020.2.11 YONSEI ROBOIN, WINTER ROBOTIC ARM PROJECT. WRIITEN BY YEWON LIM, GA06033@O365.YONSEI.AC.KR
// ULTRA SONIC SENSOR

#include "sensor.h"

NewPing sonar(trigPin, echoPin);
int carrier[180][2] = {0};

void radar_on_cw(CRbtarm& _robotarm, int (*_buffer)[2])
{
  for(int i = 0; i < 180; i++)
  {
    _robotarm.m_waist.write(i);
    
    _buffer[i][0] = i;
    _buffer[i][1] = howfar();
    if (_buffer[i][1] == 0)
    {
      _buffer[i][1] = 100;
    }

    Serial.print(i); Serial.print(","); Serial.print(_buffer[i][1]); Serial.print("."); 
    delay(33);
  }

}

void radar_on_ctcw(CRbtarm& _robotarm, int (*_buffer)[2])
{
  for(int i = 179; i >= 0; i--)
  {
    _robotarm.m_waist.write(i);
    
    _buffer[i][0] = i;
    _buffer[i][1] = howfar();
    if (_buffer[i][1] == 0)
    {
      _buffer[i][1] = 100;
    }

    Serial.print(i); Serial.print(","); Serial.print(_buffer[i][1]); Serial.print("."); 
    delay(33);
  }
}

int howfar()
{
   return sonar.ping_cm();
}

byte buffer_check(int (*buf_ptr)[2])
{
  int count = 0;
  int sum = 0;
  for(int i = 0; i < 180; i++)
  {
    if(buf_ptr[i][1] < DETECTION_DISTANCE)
    {
      sum += buf_ptr[i][1];
      count++;
    }
  }

  if (sum * PI / 180 > 3)            return count;
  else                               return 0;
}

int* data_process(CRbtarm& _robotarm, int (*buf_ptr)[2])
{
  byte count = 0;
  int w = 0;
  
  for (int i = 0; 1; i+=10)
  {
    _robotarm.m_move(shoulder, SPEED_50, 120-i);
    
    radar_on_cw(_robotarm, buf_ptr);
    count = buffer_check(buf_ptr);
    if (count)            
    {
      w = 120 - i;
      break;
    }

    radar_on_ctcw(_robotarm, buf_ptr);
    count = buffer_check(buf_ptr);
    if (count)            
    {
      w = 120 - i;
      break;
    }
    
    if(i == 90)           i = 0;
  }

  int sum = 0;
  int angle_sum = 0; 
    
  for(byte i = 0; i < 180; i++)
  {
    if(buf_ptr[i][1] < DETECTION_DISTANCE)     
    {
      sum += buf_ptr[i][1];
      angle_sum += i;
    }
    
  }
  
  static int data[3];
  
  data[0] = sum / count;                      // using least squares approximation to find out distance
  data[1] = (angle_sum / count);              // data[0] means a distance,r and data[1] means an angle
  data[2] =  w;                               // data[2] means a angle of shoulder, w
  
  _robotarm.m_move(waist, SPEED_50, data[1]);
  _robotarm.m_move(shoulder, SPEED_50, w);

  _robotarm.m_angle[0] = data[1];
  _robotarm.m_angle[1] = w;

  return data;
}

CylCoord seek_coord(CRbtarm& _robotarm)
{ 
  CylCoord a;                               // the unit length of m_r is 1 mm
  
  int* data_set = data_process(_robotarm, carrier);

  double w = (double)(data_set[2] * PI) / 180 ;
  for (int i = 0; i < 10; i++)
  {
    Serial.print(data_set[1]);Serial.print(","); Serial.print(data_set[0]); Serial.print(".");  
  }

  if (data_set[2] == 90)
  {
    a.m_z = D * 10;
  }
  else
  {
    a.m_z = ( D * tan(w) - R - data_set[0] ) * cos(w) * 10 ; // multiply 10 to transform cm to mm 
  }
  a.m_theta = data_set[1];
  
  a.m_r = ( (D - R * cos(w)) * cos(w) + data_set[0] * sin(w) + R) * 10 ; // multiply 10 to transform cm to mm 

  Serial.print("s: "); Serial.println(data_set[0]); 
  Serial.print("w: "); Serial.println(w); 
  return a;
     
}
