#include "Ultarasonic/DIO/LIB/MATH.h"
#include "Ultarasonic/DIO/LIB/STD_TYPES.h"
#include "Ultarasonic/DIO/DIO_Interface.h"

#include "ServoMotor.h"
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

 
void config_servo_timer()
{
	DIO_SetPinDirection(3,6,HIGH); //set portD pin 6 as output (OC0A)
	CLR_BIT(TCCR0B,CS00);//
	CLR_BIT(TCCR0B,CS01);// SET pre-scaler value = 256
	SET_BIT(TCCR0B,CS02);//
	
	SET_BIT(TCCR0A,WGM00);//
	SET_BIT(TCCR0A,WGM01);// FAST PWM mode;
	CLR_BIT(TCCR0B,WGM02);//
	
	CLR_BIT(TCCR0A,COM0A0);// NON INVERTING MODE COPMARE WITH OCR0A
	SET_BIT(TCCR0A,COM0A1);
	
	sei();					//enable global interrupt
	SET_BIT(TIMSK0,TOIE0);	//enable Timer 0 Overflow interrupt
	
	TCNT0=178;				//pre-load value to achieve 50hz (20mS) PWM signal at OC0A pin
	set_servo_angel(0);     // servo starts at angel ZERO CENTER

}


void set_servo_angel(s8 angle)  //change the OCR0A value to control PWM Signal DutyCycle to control Servo Rotation angel

{
	switch(angle)
	{
	case 0:
	OCR0A=183;break; // to obtain a Positive pulse =(1.5mS)
	case -90:
	OCR0A=179;break; //to obtain a Positive pulse =(1.5mS)
	case 90:
	OCR0A=187;break;//to obtain a Positive pulse >(2mS)
	}
}

/*u8 port_id,pin_number;

void config_servo_output_pin(u8 p_id, u8 pin_num)
{		
	if( (( (p_id==1)||(p_id==3) )&&(pin_num<8) )||( (p_id==2)&&(pin_num<7) ) )
		{
		DIO_SetPinDirection(p_id,pin_num,OUTPUT);
		port_id=p_id;
		pin_number=pin_num;
		}
}


void set_servo_angel(s8 angle) 

{
	switch(angle)
	{
		case 0:
			DIO_SetPinValue(port_id,pin_number,1);
			_delay_us(1430);							// to obtain a Positive pulse =(1.5mS)
			DIO_SetPinValue(port_id,pin_number,0);	
			break; 
		case -90:
			DIO_SetPinValue(port_id,pin_number,1);
			_delay_us(500);							//to obtain a Positive pulse =(1mS)
			DIO_SetPinValue(port_id,pin_number,0);
			break;
		case 90:
			DIO_SetPinValue(port_id,pin_number,1);
			_delay_us(2450);							 //to obtain a Positive pulse =(2mS)
			DIO_SetPinValue(port_id,pin_number,0);
			break; 
	}
}
*/

ISR(TIMER0_OVF_vect)   //Timer0 Overflow Interrupt service routine
{
	TCNT0=178;		//pre-load value to TCNT0 register
	sei();			// reEnable global interrupt
}
