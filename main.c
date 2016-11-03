/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include <Arduino.h>
#include "interrupt\interrupt_avr8.h"

#define LEDPIN 7
int mode;
int i = 0;
void init_timer()
{
	cli();
	pinMode(LEDPIN,OUTPUT);
	TCCR1A = 0;
	TCCR1B = 0x01;
	TCNT1 = 50000;
	DDRD |= 0x80;
	TCCR1B |= (1<<CS12);
	TIMSK1 |= (1<<TOIE1);
	sei();
	set_pwm(i);
	if (i==100)
	{
		i=0;
	}
	else 
	{
		i++;
	}
}
void set_pwm(int percentage)
{
	OCR0A = percentage/100 * 255;
}
ISR(TIMER1_OVF_vect)
{
	TCNT1 = 50000;
	int sw = mode % 4;
	
	/*switch(sw)
	{
	case 0:
			for (int i=0;i<=100;i++)
			{
				set_pwm(i);
			} 
	}*/
	//digitalWrite(LEDPIN,digitalRead(LEDPIN)^1);
	PORTD ^= 0x80;
}
int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	board_init();
	init_timer();
	while(1)
	{
	}
	/* Insert application code here, after the board has been initialized. */
}
