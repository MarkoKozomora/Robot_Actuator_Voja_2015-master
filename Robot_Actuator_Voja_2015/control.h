
#ifndef CONTROL_H_
#define CONTROL_H_
#include "can.h"

#define AX_SERVO1 1
#define AX_SERVO2 2
#define AX_SERVO3 3
#define AX_SERVO4 4

void TIMER3_Init(unsigned int f_pwm);
void TIMER1_Init(void);
void timeCheck(void);
void AX_UART_Init(void);
void AX_SendChar(unsigned char data);
unsigned char AX_ReadChar(void);
void AX_ReadStatus(void);
void AX_StopTransmitter(void);
void AX_ReleaseTransmitter(void);
void AX_StopReceiver(void);
void AX_ReleaseReceiver(void);
void AX_SetAngle(unsigned int angle, unsigned int speed, unsigned char direction, unsigned char id);
void AX_EndlessTurn(void);
void AX_SetSpeed(unsigned int direction, unsigned int speed);

#endif