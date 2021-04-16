/*
 * GccApplication4.c
 *
 * Created: 03-04-2021 4.48.29 PM
 * Author : mintu
 */ 

#define F_CPU 16000000UL //16 MHz clock speed
#include <avr/io.h>
#include <util/delay.h>

#define LCD_DATA PORTB
#define LCD_ctrl PORTD
#define en PD7
#define rw PD6
#define rs PD5

void LCD_init(void);
void LCD_cmd(unsigned char cmd);

void init_LCD(void);

void LCD_write(unsigned char data);

void init_LCD(void)

{

	LCD_cmd(0x38);           // initialization in 8bit mode of 16X2 LCD

	_delay_ms(1);

	LCD_cmd(0x01);          // make clear LCD

	_delay_ms(1);

	LCD_cmd(0x02);          // return home

	_delay_ms(1);

	LCD_cmd(0x06);          // make increment in cursor

	_delay_ms(1);

	LCD_cmd(0x80);          // force cursor to the beginning of first line

	_delay_ms(1);

	

	return;

}

void LCD_cmd(unsigned char cmd)

{

	LCD_DATA = cmd;      // data lines are set to send command

	PORTD  &= ~(1<<rs);  // RS sets 0

	PORTD  &= ~(1<<rw);  // RW sets 0

	PORTD  |= (1<<en);   // make enable from high to low

	_delay_ms(10);

	PORTD  &= ~(1<<en);

	

	return;

}



void LCD_write(unsigned char data)

{

	PORTD  |= (1<<rs);    // RS sets 1

	PORTD  &= ~(1<<rw);   // RW sets 0

	PORTD  |= (1<<en);    // make enable from high to low
	
	LCD_DATA = data;    // data lines are set to send command

	_delay_ms(20);

	PORTD &= ~(1<<en);

	

	return ;

}



int main(void)
{
	
	DDRB=0xFF;

	DDRD=0xE0;

	init_LCD();

	_delay_ms(20);

	

	LCD_cmd(0x0C);          // display on, cursor off

	_delay_ms(20);

	

	LCD_write('m');

	_delay_ms(1);

	LCD_write('a');

	_delay_ms(1);

	LCD_write('k');

	_delay_ms(1);

	LCD_write('e');

	_delay_ms(1);

	LCD_write('r');

	_delay_ms(1);


	LCD_cmd(0x0C);

	return 0;

}

