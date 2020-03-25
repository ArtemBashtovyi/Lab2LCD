
#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include "button.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include "lcd.h"

static __IO uint32_t usTicks;

const char *messages[5];

void SysTick_Handler()
{
    if (usTicks != 0)
    {
        usTicks--;
    }
}
void DelayInit()
{
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / 1000);
}
 
void DelayMs(uint32_t ms)
{
    usTicks = ms;
    while (usTicks);
}

int generate_random(int lower, int upper) {
	
	int num = (rand() % (upper - lower + 1)) + lower; 
}

int main(void){
	unsigned int inputValue;
	DelayInit();
	userButtonInit();
	lcdPinInit();
	lcdInit();
	
	messages[0] = "Message1";
	messages[1] = "Message2";
  messages[2] = "Message3";
	messages[3] = "Message4";
	messages[4] = "Message5";
	
	srand(time(0)); // generate seed timestamp 
	
	while(1)
    {
    	inputValue = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
    	if (inputValue == 1) {
				int randomNumber = generate_random(0, 4);
				const char * randomMessage = messages[randomNumber];
				// write to LCD random string
    		lcdShowString(randomMessage);
				inputValue = 0;
				DelayMs(1000);
				lcdClear();
			}
    }
}
