#include <avr/delay.h>
#include "Ultarasonic/DIO/LIB/STD_TYPES.h"
#include "Ultarasonic/DIO/LIB/MATH.h"
#include "Ultarasonic/DIO/DIO_Interface.h"
#include "RC_Controling_interface.h"
 #include <avr/io.h>
 
void config_RC_Driver()
{
	//set OC0A Pin as output
	DIO_SetPinDirection(PORT3 , 6 , OUTPUT); 
	// FAST PWM mode;
	SET_BIT(TCCR0A,WGM00);
	SET_BIT(TCCR0A,WGM01);
	SET_BIT(TCCR0B,WGM02);
	// Toggle output wave on OC0A pin @ Compare match
	SET_BIT(TCCR0A,COM0A0);
	// Fti = Fcpu @ pre scaler value = 1
	SET_BIT(TCCR0B,CS00);
	// 50% duty cycle @ about 30% from the timer cycle
	OCR0A = 80;
}
void forward(){
	//Left motor
	DIO_SetPinValue(PORT3,0,1);
	DIO_SetPinValue(PORT3,1,0);
	//Right motor
	DIO_SetPinValue(PORT3,2,1);
	DIO_SetPinValue(PORT3,3,0);
}

 void backward(){
	//Left motor
	DIO_SetPinValue(PORT3,0,0);
	DIO_SetPinValue(PORT3,1,1);
	//Right motor
	DIO_SetPinValue(PORT3,2,0);
	DIO_SetPinValue(PORT3,3,1);
 }
 
 void right(){
	 //Left motor
	 DIO_SetPinValue(PORT3,0,1);
	 DIO_SetPinValue(PORT3,1,0);
	 //Right motor
	 DIO_SetPinValue(PORT3,2,0);
	 DIO_SetPinValue(PORT3,3,1);
 }

 void left() {
	 //Left motor
	 DIO_SetPinValue(PORT3,0,0);
	 DIO_SetPinValue(PORT3,1,1);
	 //Right motor
	 DIO_SetPinValue(PORT3,2,1);
	 DIO_SetPinValue(PORT3,3,0);
 }
 
 void stop(){
	  //Left motor
	  DIO_SetPinValue(PORT3,0,0);
	  DIO_SetPinValue(PORT3,1,0);
	  //Right motor
	  DIO_SetPinValue(PORT3,2,0);
	  DIO_SetPinValue(PORT3,3,0);
  }
 
 
 
 
 