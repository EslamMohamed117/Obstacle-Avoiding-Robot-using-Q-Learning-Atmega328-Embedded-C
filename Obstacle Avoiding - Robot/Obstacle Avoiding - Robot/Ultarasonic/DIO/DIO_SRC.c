#include "LIB/STD_TYPES.h"
#include "LIB/MATH.h"
#include <avr/io.h>
 
#include "DIO_Interface.h"

/*********************HEADER*************************************************************************/
/*Description:  DIO_SetPinDirection is a function to set the direction of the pin either input or output
			    and choose which pin that will be used and the port number that will be used as well
			
  parameters:   U8PortID_copy-->it takes range (PORT1,PORT2,PORT3)
  	  	  	  
			    U8PinID_Copy-->it takes range (PIN0-->7)
			  
  	  	  	    U8VA:Value_Copy--> it take on of two values (INPUT,OUTPUT)*/
/*******************************************************************************************************/			  
extern void DIO_SetPinDirection(u8 U8PortID_Copy, u8 U8PinID_Copy, u8 U8Value_Copy){

	if(((U8PortID_Copy<4) && (U8PortID_Copy>0)) && (U8PinID_Copy<=7)){
			if(U8Value_Copy == INPUT)
			{
				switch(U8PortID_Copy)
					{ 
						case PORT1 : CLR_BIT(DDRB, U8PinID_Copy);break;
						case PORT2 : CLR_BIT(DDRC, U8PinID_Copy);break;
						case PORT3 : CLR_BIT(DDRD, U8PinID_Copy);break;
					}
			}
			else if (U8Value_Copy == OUTPUT)
			{
				switch(U8PortID_Copy)
					{
					 
						case PORT1 : SET_BIT(DDRB, U8PinID_Copy);break;
						case PORT2 : SET_BIT(DDRC, U8PinID_Copy);break;
						case PORT3 : SET_BIT(DDRD, U8PinID_Copy);break;
					}
			}
			else{
				//Do Nothing
			}
	}
	else{
		//do nothing
	}
}
/***************************HEADER********************************************************************/
/* Description:   DIO_SetPinValue is a function to set the value of the pin to make the led illuminate
			     and choose which pin that will be used and the port number that will be used as well
   
   parameters: U8PortID_copy-->it takes range (PORT1,PORT2,PORT3)
  	  	  	  
			   U8PinID_Copy-->it takes range (PIN0-->7)
  	  	  	  
			   U8VA:Value_Copy--> it take on of two values (HIGH,LOW)*/
/******************************************************************************************************/
extern void DIO_SetPinValue(u8 U8PortID_Copy, u8 U8PinID_Copy, u8 U8Value_Copy)
{
	if(((U8PortID_Copy<4) && (U8PortID_Copy>0)) && (U8PinID_Copy<=7))
	{
		if(U8Value_Copy == HIGH)
		{
			switch(U8PortID_Copy)
			{
				 
				case PORT1 :SET_BIT(PORTB, U8PinID_Copy);break;
				case PORT2 :SET_BIT(PORTC, U8PinID_Copy);break;
				case PORT3 :SET_BIT(PORTD, U8PinID_Copy);break;
			}
		}
		else if(U8Value_Copy == LOW)
		{
			switch(U8PortID_Copy)
			{
				 
				case PORT1 :CLR_BIT(PORTB, U8PinID_Copy);break;
				case PORT2 :CLR_BIT(PORTC, U8PinID_Copy);break;
				case PORT3 :CLR_BIT(PORTD, U8PinID_Copy);break;
			}
		}
		else{
			//do nothing
		}

	}
	else{
		//do nothing
	}


}

/****************************************************HEADER************************************/

/*Description: DIO_GetPinValue is a function to toggle the value of the pin
			   and choose which pin that will be used and the port number that will be used as well
  
  parameters: U8PortID_copy-->it takes range (PORT1,PORT2,PORT3)
  	  	  	  
			  U8PinID_Copy-->it takes range (PIN0-->7)*/
/**************************************************************************************************/

extern u8 DIO_GetPinValue(u8 U8PortID_Copy, u8 U8PinID_Copy)
{
	      u8 U8ResultLocal;

	if(((U8PortID_Copy<4) && (U8PortID_Copy>0)) && (U8PinID_Copy<=7))
	{
		switch(U8PortID_Copy)
		{
		 
			case PORT1 : U8ResultLocal = GET_BIT(PINB , U8PinID_Copy);break;
			case PORT2 : U8ResultLocal = GET_BIT(PINC , U8PinID_Copy);break;
			case PORT3 : U8ResultLocal = GET_BIT(PIND , U8PinID_Copy);break;
		}
	}
	else{
		U8ResultLocal = 0xff;
	}
	return U8ResultLocal;
}


/********************************************HEADER**************************************************************/

/*Description: DIO_SetPortDirection is a function to set the direction of the port to make all the port avaliable
			   and choose which port id that will be used and the port direction that will be used as well
  
  parameters: U8PortID-->it takes range (PORT1,PORT2,PORT3)
  	  	  	  
			  U8PinDir-->it takes range (binary number to know which pin will be used in the port)*/

/****************************************************************************************************************/
extern void DIO_SetPortDirection(u8 U8PortID, u8 U8PortDir)
{
	switch(U8PortID)
	{
		 
		case PORT1: DDRB = U8PortDir;break;
		case PORT2: DDRC = U8PortDir;break;
		case PORT3: DDRD = U8PortDir;break;
		default: /*wrong port id*/ ;break;
	}
}


/*********************************************HEADER****************************8888**********************/

/*Description: DIO_SetPortDirection is a function to set the value of the port
			   and choose which port id that will be used and the port direction that will be used as well

  parameters: U8PortID-->it takes range (PORT1,PORT2,PORT3)
  	  	  	  
			  U8PinDir-->it takes range (binary number to know which pin will be used in the port)*/
/**********************************************************************************************************/

extern void DIO_SetPortValue(u8 U8PortID, u8 U8PortValue)
{
	switch(U8PortID)
	{
	 
		case PORT1: PORTB = U8PortValue;break;
		case PORT2: PORTC = U8PortValue;break;
		case PORT3: PORTD = U8PortValue;break;
		default: /* wrong port id*/ ;break;
	}
}


