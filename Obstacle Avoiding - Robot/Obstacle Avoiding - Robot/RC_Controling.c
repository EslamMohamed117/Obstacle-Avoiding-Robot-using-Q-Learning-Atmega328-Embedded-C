#include <avr/delay.h>
#include "Ultarasonic/DIO/LIB/STD_TYPES.h"
#include "Ultarasonic/DIO/LIB/MATH.h"
#include "Ultarasonic/DIO/DIO_Interface.h"
#include "RC_Controling_interface.h"
 #include <avr/io.h>
 
void config_RC_Driver()
{
	DIO_SetPinDirection(PORT3 , 5 , OUTPUT);
	DIO_SetPinDirection(PORT3 , 6 , OUTPUT);
	TCCR0A |= (1 << WGM01) | (1 << WGM00) | (1 << COM0A0);
	TCCR0B |= (1 << WGM02) | (1 << CS00);
	OCR0A = 80;
}
void forward(){
 DIO_SetPinValue(PORT3,0,1);
 DIO_SetPinValue(PORT3,1,0);
 DIO_SetPinValue(PORT3,2,1);
 DIO_SetPinValue(PORT3,3,0);
}

 void backward(){
 DIO_SetPinValue(PORT3,0,0);
 DIO_SetPinValue(PORT3,1,1);
 DIO_SetPinValue(PORT3,2,0);
 DIO_SetPinValue(PORT3,3,1);
 }
 
 void right(){
	 DIO_SetPinValue(PORT3,0,1);
	 DIO_SetPinValue(PORT3,1,0);
	 DIO_SetPinValue(PORT3,2,0);
	 DIO_SetPinValue(PORT3,3,1);
 
 }

 void left() {
	 DIO_SetPinValue(PORT3,0,0);
	 DIO_SetPinValue(PORT3,1,1);
	 DIO_SetPinValue(PORT3,2,1);
	 DIO_SetPinValue(PORT3,3,0);
 }
 
 void stop(){
	  DIO_SetPinValue(PORT3,0,0);
	  DIO_SetPinValue(PORT3,1,0);
	  DIO_SetPinValue(PORT3,2,0);
	  DIO_SetPinValue(PORT3,3,0);
  }
 
 
 
 
 