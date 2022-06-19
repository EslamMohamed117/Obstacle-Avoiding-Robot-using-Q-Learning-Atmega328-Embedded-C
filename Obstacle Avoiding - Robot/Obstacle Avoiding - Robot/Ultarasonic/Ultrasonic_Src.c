#include "DIO/LIB/STD_TYPES.h"
#include "DIO/LIB/MATH.h"
#include <avr/io.h>
#include "DIO/DIO_Interface.h"
#include "Ultrasonic_Interface.h"
#define  F_CPU 16000000UL
#include <util/delay.h>

u16 ultarasonic_distance()
{
	u16 rising,falling,high,distance;
	//Reset TCCR1A @ Not used
	TCCR1A = 0;
	//Clear the ICF 
	SET_BIT(TIFR1,ICF1);
	//Sending a pulse with 50us to trigger the ultrasonic to begin
	DIO_SetPinValue(PORT3,PIN7,1);
	_delay_us(500);
	DIO_SetPinValue(PORT3,PIN7,0); 
	
	/*Fti = Fcpu/8 @ pre scaler value = 8
	  Enable noise cancellation
	  Adjust ICES1 at rising edge  */
	TCCR1B = 0xc2;
	//Wait till the rising edge of the ultrasonic ECHO wave occur
	while ((TIFR1&(1<<ICF1)) == 0);
	//Get the value at rising edge @ from capture register
	rising = ICR1; 
	//Clear ICF
	SET_BIT(TIFR1,ICF1);

	/* Fti = Fcpu/8 @ pre scaler value = 8
	   Enable noise cancellation
	   Adjust ICES1 at falling edge	 */
	TCCR1B = 0x82;  	
	//Wait till the falling edge of the ultrasonic ECHO wave occur
	while ((TIFR1&(1<<ICF1)) == 0);
	//Get the value at falling edge @ from capture register
	falling = ICR1;  		
	//Clear ICF
	SET_BIT(TIFR1,ICF1);	
	
	//Clear TCNT1
	TCNT1=0;
	//Reset TCCR1B @ Stop timer
	TCCR1B = 0;
	//Getting the high pulse duration
	high=falling-rising;
	// distance = (duration * speed of sound) / (Frequency *2)
	distance=((high*34600)/((F_CPU/8)*2 )) ;
	return distance;
}