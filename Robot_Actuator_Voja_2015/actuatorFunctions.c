#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "actuatorFunctions.h"
#include "control.h"
#include "uart.h"
#include "can.h"
#include "system.h"

#define ACTIVATE	1
#define DEACTIVATE	-1
#define CLOSE		2


void rightDiafram(signed char state)
{
	DDRE |= (1 << PINE4);
	
	if(state == ACTIVATE)
	{
		PORTE |= (1 << PINE4);
	}else
	{
		PORTE &= ~(1 << PINE4);
	}
	
}//END OF rightDiafram

void leftDiafram(signed char state)
{
	DDRE |= (1 << PINE5);
	
	if(state == ACTIVATE)
	{
		PORTE |= (1 << PINE5);
	}else
	{
		PORTE &= ~(1 << PINE5);
	}

}//END OF leftDiafram

void liftStates(signed char state)
{

	GPIO_OutputSet(chipSelect);
	GPIO_OutputSet(INA1);
	GPIO_OutputSet(PWM);
	GPIO_OutputReset(INB1);
	
	if(state == ACTIVATE)
	{
		GPIO_OutputSet(PWM);
	}else
	{
		GPIO_OutputReset(PWM);
	}
	
}//END OF liftMove

void action(canMsg msg)
{
	unsigned char command = msg.data[0];
	unsigned char state, direction;
	unsigned int angle, speed;
	angle = 0;
	speed = 0;
	
	switch(command)
	{
		case 'A':
		angle = msg.data[1] << 8 | msg.data[2];
		speed = msg.data[3] << 8 | msg.data[4];
		direction = msg.data[5];
		AX_SetAngle(angle,speed,direction,AX_SERVO1);
		break;
		
		case 'B':
		angle = msg.data[1] << 8 | msg.data[2];
		speed = msg.data[3] << 8 | msg.data[4];
		direction = msg.data[5];
		AX_SetAngle(angle,speed,direction,AX_SERVO2);
		break;
		
		case 'C':
		state = msg.data[1];
		leftDiafram(state);
		break;
		
		case 'D':
		state = msg.data[1];
		rightDiafram(state);
		break;
		
		case 'E':
		state = msg.data[1];
		liftStates(state);
		break;
	}
}