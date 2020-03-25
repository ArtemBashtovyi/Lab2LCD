#include "lcd.h"

void writeByte(uint8_t data);

void lcdPinInit(void) {
	GPIO_InitTypeDef  GPIO_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = LCD_PIN_RS | LCD_PIN_RW | LCD_PIN_EN | LCD_PIN_D7 | LCD_PIN_D6 | LCD_PIN_D5 | LCD_PIN_D4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_ResetBits(LCD_PORT, LCD_PIN_RW);
}


void executeData(u8 data){		
		GPIO_ResetBits(GPIOE,GPIO_Pin_7);
		lcd_delay_func(100);
    if((data&0x80)==0x80) GPIO_SetBits(GPIOE,GPIO_Pin_15);  else GPIO_ResetBits(GPIOE,GPIO_Pin_15);
    if((data&0x40)==0x40) GPIO_SetBits(GPIOE,GPIO_Pin_14);  else GPIO_ResetBits(GPIOE,GPIO_Pin_14);
    if((data&0x20)==0x40) GPIO_SetBits(GPIOE,GPIO_Pin_13);  else GPIO_ResetBits(GPIOE,GPIO_Pin_13);
    if((data&0x10)==0x10) GPIO_SetBits(GPIOE,GPIO_Pin_12);  else GPIO_ResetBits(GPIOE,GPIO_Pin_12);
    GPIO_SetBits(GPIOE,GPIO_Pin_11);
    lcd_delay_func(100);
		GPIO_ResetBits(GPIOE,GPIO_Pin_11);
    if((data&0x08)==0x08) GPIO_SetBits(GPIOE,GPIO_Pin_15); else GPIO_ResetBits(GPIOE,GPIO_Pin_15); 
    if((data&0x04)==0x04) GPIO_SetBits(GPIOE,GPIO_Pin_14); else GPIO_ResetBits(GPIOE,GPIO_Pin_14);
    if((data&0x02)==0x02) GPIO_SetBits(GPIOE,GPIO_Pin_13); else GPIO_ResetBits(GPIOE,GPIO_Pin_13);
    if((data&0x01)==0x01) GPIO_SetBits(GPIOE,GPIO_Pin_12); else GPIO_ResetBits(GPIOE,GPIO_Pin_12);
    GPIO_SetBits(GPIOE,GPIO_Pin_11);
    lcd_delay_func(100);
		GPIO_ResetBits(GPIOE,GPIO_Pin_11);
}

void lcdShowChar(const char oneByte) {
    executeData((u8)oneByte);
}

void lcdShowString(char* message) {
	  char * t; 
    int size = 0;
    for (t = message; *t != '\0'; t++) {
			lcdShowChar(*t);
		}
}

void writeFullByte(uint8_t data) {
	writeByte(data);
	writeByte(data >> 4);
}

void writeByte(uint8_t data) {
	GPIO_SetBits(GPIOE, ((data & 0x0F)) << LCD_PIN_OFFSET);
	GPIO_SetBits(GPIOE, LCD_PIN_EN);
	lcd_delay_func(100);
	GPIO_ResetBits(GPIOE, LCD_PIN_EN);
	GPIO_ResetBits(GPIOE, 0x0F<<LCD_PIN_OFFSET);
}

void lcdInit(void) {
	writeFullByte(0x20);
	lcd_delay_func(100);
	writeFullByte(0x28);
	lcd_delay_func(100);
	writeFullByte(0x28);
	lcd_delay_func(100);
	writeFullByte(0x0f);
	lcd_delay_func(100);
	writeFullByte(0x01);
	lcd_delay_func(100);
	writeFullByte(0x06);
	lcd_delay_func(100);
}


void lcd_delay_func(unsigned int p) {
	unsigned long i;
	for(i=0;i<(p*10);i++){
	  __nop();
	}
}

void lcdClear(void) {
		GPIO_ResetBits(GPIOE, GPIO_Pin_7);
		writeFullByte(0x01);
		lcd_delay_func(100);
		GPIO_SetBits(LCD_PORT, GPIO_Pin_7);
		writeFullByte(1);
}


