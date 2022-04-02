#include"Arduino.h"
#include"speed_ir.h"
float ir_speed(int timer1, int timer2, float distance)  {
	while (digitalRead (A0) != LOW)  {
		delay(50);
		if (digitalRead (A0) == LOW)  {
      		timer1 = millis();
			break;
		}
	}
	while (digitalRead (A1) != LOW)  {
		delay(50);
		if (digitalRead (A1) == LOW)  {
      		timer2 = millis();
			break;
		}
	}

      float Time = timer2 - timer1;
      Time = Time / 1000; //convert millisecond to second
      float speed = (distance / Time); //v = d/t
      speed = speed * 3.6; //km per hr
	return speed;
}