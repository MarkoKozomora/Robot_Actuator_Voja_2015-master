#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "control.h"
#include "qei.h"
#include "system.h"


#define START	0xFF

#define LENGTH  0x07
#define INSTR	0x03
#define ADDRESS 0x1E

#define SPEED_H 0x02
#define SPEED_L 0x00

void TIMER3_Init(unsigned int f_pwm)
{
	DDRE |= (1 << PINE3) | (1 << PINE4) | (1 << PINE5);
	
	TCNT3 = 0;
	OCR3A = 0;
	OCR3B = 0;
	OCR3C = 0;
	
	TCCR3A = (1 << COM3B1) | (1 << COM3B0) | (1 << COM3C1) | (1 << COM3C0) | (1 << WGM31);
	TCCR3B = (1 << WGM32) | (1 << WGM33) | (1 << CS30); // PRESKALER = 1
	ICR3 = (double)F_CPU / f_pwm - 0.5;
}

void TIMER1_Init(void)
{
	TCCR0A = (1 << WGM01) | (1 << CS02);
	TIMSK0 |= (1 << OCIE0A);
	OCR0A = 43;
	
	SREG |= 0x80;
}

void AX_UART_Init(void)
{
	//DDRE &= ~((1 << PINE0) | (1 << PINE1));
	//DDRE |= 0xFC;
	DDRE &= ~((1 << 0x00) | (1 << 0x01));
	//PORTE = 0;
	UCSR0A = 0;
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
	
	UBRR0H = 0;
	UBRR0L = 5;
	
	_delay_ms(100);
}

void AX_SendChar(unsigned char data)
{
	while ( !( UCSR0A & (1<<UDRE0)) );
	UDR0 = data;	
}
unsigned char AX_ReadChar(void)
{
   //UART1_Write('I');
   while( !( UCSR0A & (1<< RXC0)) );
   return UDR0;
}

/*************************************************************************************************************************************************************************************
*															 Funkcije za upravljanje AX-12A servoima                                                                                                                                      *
*************************************************************************************************************************************************************************************/

void AX_ReadStatus(void)
{
	 unsigned char status[7] = {0,0,0,0,0,0};
		 
	status[0] = AX_ReadChar();
	status[1] = AX_ReadChar();
	status[2] = AX_ReadChar();
	status[3] = AX_ReadChar();
	status[4] = AX_ReadChar();
	status[5] = AX_ReadChar();
}

void AX_StopTransmitter(void)
{
	while( !(UCSR0A & (1<<TXC0)) );
	UCSR0B &= 0xF7;
	UCSR0A |= 0x40;
}

void AX_ReleaseTransmitter(void)
{
	UCSR0B |= 0x08;
}

void AX_StopReceiver(void)
{
	UCSR0B &= 0xEF;
}

void AX_ReleaseReceiver(void)
{
	UCSR0B |= 0x10;
}

void AX_SetAngle(unsigned int angle, unsigned int speed, unsigned char direction, unsigned char id)
{
	unsigned char angle_H, angle_L;
	unsigned char speed_H, speed_L;
	unsigned int checksum;
	
	angle = (unsigned int)(1023 *((double)angle/300.0));
	
	angle_H = (unsigned char)(angle >> 8);
	angle_L = (unsigned char)(angle & 0x00FF);
	
	speed |= (direction << 10);
	speed_H = (unsigned char)(speed >> 8);
	speed_L = (unsigned char)(speed & 0x00FF);
	
	/*
	* CHECKSUM = ~(ID + LENGTH + INSTR + PARAM0 (ADDRESS) + ... +PARAMN)
	*/
	checksum = ~(id + 0x28 + speed_H + speed_L + angle_H + angle_L);
	
	AX_StopReceiver();
	
	AX_SendChar(START);
	AX_SendChar(START);
	AX_SendChar(id);
	AX_SendChar(LENGTH);
	AX_SendChar(INSTR);
	AX_SendChar(ADDRESS);
	AX_SendChar(angle_L);
	AX_SendChar(angle_H);
	AX_SendChar(speed_L);
	AX_SendChar(speed_H);
	AX_SendChar(checksum);
	
	AX_StopTransmitter();
	AX_ReleaseReceiver();
	
	_delay_ms(50);
	
	AX_ReleaseTransmitter();
}


void AX_EndlessTurn(void)
{

	unsigned int checksum;

	checksum = ~(0x01 + 0x07 + 0x03 + 0x06 + (1023 & 0xFF) + (1023 >> 8) & 0xFF);

	AX_StopReceiver();

	AX_SendChar(0xFF);
	AX_SendChar(0xFF);
	AX_SendChar(0x01);
	AX_SendChar(0x07);
	AX_SendChar(0x03);
	AX_SendChar(0x06);
	AX_SendChar(0x00);
	AX_SendChar(0x00);
	AX_SendChar(1023 & 0xFF);
	AX_SendChar(1023 >> 8);
	AX_SendChar(checksum);

	AX_StopTransmitter();
	AX_ReleaseReceiver();
	
	//AX_ReadStatus();
	_delay_ms(50);
	
	AX_ReleaseTransmitter();
}

void AX_SetSpeed(unsigned int direction, unsigned int speed)
{
	/*
		direction ---> TurnDirection -> 1 - ClockWise   0 - CounterClockWise
	*/

	unsigned int data = 0x0000;
	unsigned int checksum = 0;

	data = speed;
	data |= (direction << 10);

	
	checksum = ~(0x01 + 0x05 + 0x03 + 0x20 + data);	

	AX_StopReceiver();	

	AX_SendChar(0xFF);
	AX_SendChar(0xFF);
	AX_SendChar(0x01);
	AX_SendChar(0x05);
	AX_SendChar(0x03);
	AX_SendChar(0x20);
	AX_SendChar(data);
	AX_SendChar(data >> 8);
	AX_SendChar(checksum);

	AX_StopTransmitter();
	AX_ReleaseReceiver();
	
	AX_ReadStatus();
	
	AX_ReleaseTransmitter();
}