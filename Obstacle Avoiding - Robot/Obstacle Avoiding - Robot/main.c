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
	//DIO_SetPinDirection(PORT2,4,OUTPUT);
	//DIO_SetPinDirection(PORT2,3,OUTPUT);
	//DIO_SetPinDirection(PORT2,2,OUTPUT);
	DIO_SetPinDirection(PORT1,5,OUTPUT);
	
	DIO_SetPinDirection(PORT3,0,OUTPUT);
	DIO_SetPinDirection(PORT3,1,OUTPUT);
	DIO_SetPinDirection(PORT3,2,OUTPUT);
	DIO_SetPinDirection(PORT3,3,OUTPUT);
	
	DIO_SetPinDirection(PORT3,PIN7,OUTPUT);
	//config_servo_timer();
	set_servo_angel(0); // Configuration + center position
	_delay_ms(1000);
	config_RC_Driver(); // Config the motor speed 
	 // led1>>left   led2>>right   led3>>backward    led4>>forward 
   DIO_SetPinValue(PORT1,5,0);
   Train(); 
   DIO_SetPinValue(PORT1,5,1);
   Test();
   // forward();
// _delay_ms(3000);
 // set_servo_angel(90);
//   _delay_ms(3000);
 //  set_servo_angel(-90);
	
  // int d;
 
	
   while (1) 
    {
	//	right();
	 //forward();
	 
	 
	 
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


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 