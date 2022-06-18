#include <avr/delay.h>
#include "Ultarasonic/DIO/LIB/STD_TYPES.h"
#include "Ultarasonic/DIO/LIB/MATH.h"
#include "Ultarasonic/DIO/DIO_Interface.h"
#include "RC_Controling_interface.h"
 

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
 
 
 
 
 