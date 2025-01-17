
 // application.c

 // Created on: Feb 28, 2024
 //      Author: Abdelrahman Salem


#include "lcd.h"
#include "icu.h"
#include <avr/io.h> /* To use the SREG register */
#include "ultrasonic.h"
#include "std_types.h"

int main(void)
{
	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);
	LCD_init();
	Ultrasonic_init();

	for(;;)
	{
		 uint16 reading =0;
		 reading = Ultrasonic_readDistance();
		 Ultrasonic_Trigger();
		 LCD_moveCursor(0,0);
		 LCD_displayString("Distance=    CM");
		 LCD_moveCursor(0,9);
		 LCD_intgerToString(reading);
	}
}
