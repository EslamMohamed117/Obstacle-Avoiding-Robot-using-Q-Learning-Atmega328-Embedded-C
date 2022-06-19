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
	//Set the Arduino led as output
	DIO_SetPinDirection(PORT1,5,OUTPUT);
	//Set the motor directions pins as output
	DIO_SetPinDirection(PORT3,0,OUTPUT);
	DIO_SetPinDirection(PORT3,1,OUTPUT);
	DIO_SetPinDirection(PORT3,2,OUTPUT);
	DIO_SetPinDirection(PORT3,3,OUTPUT);
	//Set Trigger pin of the ultrasonic as output	
	DIO_SetPinDirection(PORT3,PIN7,OUTPUT);
	// Configuration + center position
	set_servo_angel(0); 
	_delay_ms(1000);
	// Config the motor speed 
	config_RC_Driver(); 
	//Clear the Arduino led
    DIO_SetPinValue(PORT1,5,0);
    Train(); 
	//Set the Arduino led
    DIO_SetPinValue(PORT1,5,1);
    Test();

   while (1) 
    {
	
	}
}


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 