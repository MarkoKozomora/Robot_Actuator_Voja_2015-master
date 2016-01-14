#include "system.h"
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define _MMIO_BYTE(mem_addr) (*(volatile uint8_t *)(mem_addr))

struct gpio
{
	volatile unsigned char *baseAddress;
	volatile unsigned char pinPosition;
	volatile unsigned char buffer[3];
};

struct output
{
	volatile unsigned char *baseAddress;
	volatile unsigned char pinPosition;
};

typedef struct gpio GPIOData;
typedef struct output GPIOOutData;

static volatile GPIOData *gpios[MAX_INPUTS];
static volatile GPIOOutData *outputs[MAX_OUTPUTS];
static volatile unsigned char inputsNumber = 0;
static volatile unsigned char outputsNumber = 0;

unsigned char GPIO_PinRegister(volatile unsigned char *baseAddress, unsigned char pin)
{
	if(inputsNumber >= MAX_INPUTS)
		return 0;

	unsigned char i;

	gpios[inputsNumber] = (GPIOData *)malloc(sizeof(GPIOData));
	if(gpios[inputsNumber] == NULL)
		return -1;

	gpios[inputsNumber]->baseAddress = baseAddress;
	gpios[inputsNumber]->pinPosition = pin;
	for(i = 0; i < 3; i++)
		gpios[inputsNumber]->buffer[i] = 0;

	_MMIO_BYTE(baseAddress - 1) &= ~(1 << pin);
	_MMIO_BYTE(baseAddress) |= (1 << pin);

	i = inputsNumber;
	inputsNumber++;

	return i;
}

signed char GPIO_OutputRegister(volatile unsigned char *baseAddress, unsigned char pin)
{
	if(outputsNumber >= MAX_OUTPUTS)
		return -1;
		
	unsigned char i;
	
	outputs[outputsNumber] = (GPIOOutData *)malloc(sizeof(GPIOOutData));
	if(outputs[outputsNumber] == NULL)
		return -1;
		
	outputs[outputsNumber]->baseAddress = baseAddress;
	outputs[outputsNumber]->pinPosition = pin;
	
	_MMIO_BYTE(baseAddress - 1) |= (1 << pin);
	_MMIO_BYTE(baseAddress) &= ~(1 << pin);
	
	i = outputsNumber;
	outputsNumber++;
	
	return i;
}

signed char GPIO_OutputSet(unsigned char outHandler)
{
	if(outHandler >= outputsNumber)
		return -1;
	
	_MMIO_BYTE(outputs[outHandler]->baseAddress) |= (1 << outputs[outHandler]->pinPosition);
	
	return 1;
}

signed char GPIO_OutputReset(unsigned char outHandler)
{
	if(outHandler >= outputsNumber)
		return -1;
	
	_MMIO_BYTE(outputs[outHandler]->baseAddress) &= ~(1 << outputs[outHandler]->pinPosition);
	
	return 0;
}

unsigned char GPIO_PinRead(unsigned char pinHandler)
{
	return !( (gpios[pinHandler]->buffer[0]) | (gpios[pinHandler]->buffer[1]) | (gpios[pinHandler]->buffer[2]) );
}

unsigned char GPIO_ReadFromRegister(unsigned char pinHandler)
{
	unsigned char state = 0;

	state = ((_MMIO_BYTE(gpios[pinHandler]->baseAddress - 2)) >> (gpios[pinHandler]->pinPosition)) & 0x01;

	return state;
}

void fillDebaunsingData(void)
{
	unsigned char i;
	static char j = 0;

	if(++j >= 3)
		j = 0;

	for(i = 0; i < inputsNumber; ++i)
		gpios[i]->buffer[j] = GPIO_ReadFromRegister(i);
}

void Timer_Init(unsigned int freq)
{
    TCCR1A = 0;
	TCCR1B = (1 << WGM12) | (1 << CS10);
	OCR1A = (double)F_CPU / freq + 0.5;
	TIMSK1 = 1 << OCIE1A;

	SREG |= 0x80;
}

ISR(TIMER1_COMPA_vect)
{
	fillDebaunsingData();
    #if USE_TIMER_HOOK == 1
    Timer_Hook();
    #endif // USE_TIMER_HOOK
}

void systemInit(void)
{
	Timer_Init(1000);
	
	chipSelect = GPIO_OutputRegister(GPIOF_BASE, 7);
	INA1 = GPIO_OutputRegister(GPIOF_BASE, 6);
	INB1 = GPIO_OutputRegister(GPIOF_BASE, 5);
	PWM = GPIO_OutputRegister(GPIOE_BASE, 3);
	pinE4 = GPIO_OutputRegister(GPIOE_BASE, 4);
	pinE5 = GPIO_OutputRegister(GPIOE_BASE, 5);
	
}
