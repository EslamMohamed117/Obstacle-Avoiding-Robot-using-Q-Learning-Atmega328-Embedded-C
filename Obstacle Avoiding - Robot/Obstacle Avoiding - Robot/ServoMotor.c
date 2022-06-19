#include "Ultarasonic/DIO/LIB/MATH.h"
#include "Ultarasonic/DIO/LIB/STD_TYPES.h"
#include "Ultarasonic/DIO/DIO_Interface.h"

#include "ServoMotor.h"
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

 
void config_servo_timer()
{
	//set OC1A Pin as output
	DIO_SetPinDirection(PORT1,1,OUTPUT); 
	// pre scaler value = 64
	SET_BIT(TCCR1B,CS10);
	SET_BIT(TCCR1B,CS11);
	CLR_BIT(TCCR1B,CS12);
	// FAST PWM mode;
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	// NON INVERTING MODE COPMARE WITH OCR1A
	CLR_BIT(TCCR1A,COM1A0);
	SET_BIT(TCCR1A,COM1A1);
	
	/*pre load TOP value to achieve 50hz PWM signal at OC1A pin
	 TOP = (Fcpu / (prescaler * Fpwm)) - 1
	 ((16M / (64*50)) - 1) = 4999 */
	ICR1 = 4999;			
	TCNT1 = 0;
	
}


// Setting servo angel by adjusting the value of OCR01 to obtain the required duty cycle
void set_servo_angel(s8 angle)  
{
	
	config_servo_timer();
	/* OCR1A Value = (TOP * duty cycle%) - 1
	This duty cycle values for the SG90 servo motor*/
	switch(angle)
	{
	case -90:
	//3% duty cycle
	OCR1A=149;
	break; 
	case 0:
	//7% duty cycle
	OCR1A=349;
	break; 
	case 90:
	//12% duty cycle
	OCR1A=599;
	break; 
	}
}