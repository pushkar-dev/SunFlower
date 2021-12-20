#include<Servo.h>
// library for servo

Servo srv1;
int OutputPin=2;

const int MIN_ANGLE =30;
const int MAX_ANGLE =180;
const int N_Sensor =5;

int current=MIN_ANGLE; // let current angle be 10 degrees

void setup()
{
 srv1.attach(OutputPin);
 srv1.write(current);
 Serial.begin(9600);
}

int readAngle()
{
    int maxLightIndex=0;
    int maxLight=0;
    for(int i=0; i<N_Sensor; i++)
    {
      int temp=analogRead(i);
      //Serial.print(temp);
        if(i==0) maxLight=analogRead(i);
        else if(maxLight<analogRead(i))
        {
            maxLight=analogRead(i);
            maxLightIndex=i;
        }
    }
    // 30-180 divided into 5 parts
    int res= MIN_ANGLE + int(((MAX_ANGLE-MIN_ANGLE)/N_Sensor)*maxLightIndex);
    if(res==current) return -1;
    else return res;

}

void loop()
{
  	//Serial.println(10);
    int angle=readAngle();
  	
    if (angle!=-1)
    {
        srv1.write(angle);
      	current=angle;
      	Serial.println(angle);
    }

    delay(500);        
}