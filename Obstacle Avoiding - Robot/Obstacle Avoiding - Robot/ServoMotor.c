#include "Ultarasonic/DIO/LIB/MATH.h"
#include "Ultarasonic/DIO/LIB/STD_TYPES.h"
#include "Ultarasonic/DIO/DIO_Interface.h"

#include "ServoMotor.h"
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

 
void config_servo_timer()
{
	DIO_SetPinDirection(1,1,OUTPUT); //set portB pin 1 as output (OC1A)
	SET_BIT(TCCR1B,CS10);//
	SET_BIT(TCCR1B,CS11);// SET pre_scaler value = 64
	CLR_BIT(TCCR1B,CS12);//
	
	SET_BIT(TCCR1A,WGM11);//
	SET_BIT(TCCR1B,WGM12);// FAST PWM mode;
	SET_BIT(TCCR1B,WGM13);//
	
	CLR_BIT(TCCR1A,COM1A0);// NON INVERTING MODE COPMARE WITH OCR1A
	SET_BIT(TCCR1A,COM1A1);
	
	
	ICR1 = 4999;			//pre_load value to achieve 50hz (20mS) PWM signal at OC1A pin
	
	
	//set_servo_angel(0);     // servo starts at angel ZERO CENTER
}


void set_servo_angel(s8 angle)  //change the OCR0A value to control PWM Signal DutyCycle to control Servo Rotation angel
{
	config_servo_timer();
	switch(angle)
	{
	case -90:
		OCR1A=149;
		break; //to obtain a Positive pulse = 3% duty cycle
	case 0:
		OCR1A=349;
		break; //to obtain a Positive pulse = 7% duty cycle
	case 90:
		OCR1A=599;
		break; //to obtain a Positive pulse = 12% duty cycle
	}
	ICR1=0; // to hand the timer to Ultrasonic
}
