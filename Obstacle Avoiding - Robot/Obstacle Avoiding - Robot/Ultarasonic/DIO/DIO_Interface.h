#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_
// PINS

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

// PORTS


#define PORT1 1 // for portB 
#define PORT2 2
#define PORT3 3



// I/O

#define INPUT 0
#define OUTPUT 1
#define HIGH 1
#define LOW 0


//FUNCTIONS


extern void DIO_SetPinDirection(u8 U8PortID_Copy, u8 U8PinID_Copy, u8 U8Value_Copy);

extern void DIO_SetPinValue(u8 U8PortID_Copy, u8 U8PinID_Copy, u8 U8Value_Copy);

extern u8 DIO_GetPinValue(u8 U8PortID_Copy, u8 U8PinID_Copy);

extern void DIO_SetPortDirection(u8 U8PortID, u8 U8PortDir);

extern void DIO_SetPortValue(u8 U8PortID, u8 U8PortValue);


#endif /* DIO_INTERFACE_H_ */
