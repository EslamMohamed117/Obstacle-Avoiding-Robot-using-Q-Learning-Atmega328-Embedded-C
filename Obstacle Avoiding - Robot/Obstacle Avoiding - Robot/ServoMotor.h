#include "Ultarasonic/DIO/LIB/STD_TYPES.h"

#ifndef SERVOMOTOR_H_
#define SERVOMOTOR_H_

void config_servo_timer();
void config_servo_output_pin(u8 p_id, u8 pin_num);
void set_servo_angel(s8 angle);

#define RIGHT 90
#define LEFT -90
#define CENTER 0

#endif /* SERVOMOTOR_H_ */