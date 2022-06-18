#include <avr/io.h>
#include <avr/delay.h>
#include <math.h>
#include "Ultarasonic/DIO/LIB/STD_TYPES.h"
#include "Ultarasonic/DIO/LIB/MATH.h"
#include "Ultarasonic/DIO/DIO_Interface.h"
#include "Ultarasonic/Ultrasonic_Interface.h"
#include "ServoMotor.h"
#include "RC_Controling_interface.h"
#include "Q_learn.h"
#define  F_CPU 16000000UL
#include <util/delay.h>
 
int main(void)
{
	DIO_SetPinDirection(PORT2,5,OUTPUT);
	DIO_SetPinDirection(PORT2,4,OUTPUT);
	DIO_SetPinDirection(PORT2,3,OUTPUT);
	DIO_SetPinDirection(PORT2,2,OUTPUT);
	DIO_SetPinDirection(PORT2,1,OUTPUT);
	DIO_SetPinDirection(PORT3,PIN7,OUTPUT);
	//config_servo_timer();
	set_servo_angel(0); // Configuration + center position
	 // led1>>left   led2>>right   led3>>backward    led4>>forward 
	 
   Train(); 
   DIO_SetPinValue(PORT2,5,1);
   Test();
   int d;
 
 
 
   
   while (1) 
    {
	 
	 
	 
	 
	//DIO_SetPinValue()
 
		
/*	d=ultarasonic_distance();
	if(d<20)
{ 
  		DIO_SetPinValue(PORT2,5,1);
	}
	else
	{
		DIO_SetPinValue(PORT2,5,0);
	}
	*/
	}
}


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 