#ifndef SYSTEM_H_
#define SYSTEM_H_

#define MAX_INPUTS	    10
#define MAX_OUTPUTS	    10
#define USE_TIMER_HOOK  0

#define GPIOA_BASE 0x22
#define GPIOB_BASE 0x25
#define GPIOC_BASE 0x28
#define GPIOD_BASE 0x2B
#define GPIOE_BASE 0x2E
#define GPIOG_BASE 0x34
#define GPIOF_BASE 0x31

unsigned char GPIO_PinRegister(volatile unsigned char *baseAddress, unsigned char pin);
unsigned char GPIO_PinRead(unsigned char pinHandler);
unsigned char GPIO_ReadFromRegister(unsigned char pinHandler);
signed char GPIO_OutputRegister(volatile unsigned char *baseAddress, unsigned char pin);
signed char GPIO_OutputSet(unsigned char outHandler);
signed char GPIO_OutputReset(unsigned char outHandler);
void fillDebaunsingData(void);

void Timer_Init(unsigned int freq);

unsigned char chipSelect, PWM, INA1, INB1, pinE4, pinE5;

void systemInit(void);
int jumperCheck(void);
int sidesSwitchCheck(void);

#endif
