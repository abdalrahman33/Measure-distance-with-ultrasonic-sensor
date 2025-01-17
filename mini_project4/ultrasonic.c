/*
 * ultrasonic.c
 *
 *  Created on: Feb 28, 2024
 *      Author: Abdelrahman Salem
 */
#include <avr/io.h>
#include "ultrasonic.h"
#include "gpio.h"
#include "icu.h"
#include <util/delay.h>
#include "std_types.h"

Icu_ConfigType Icu_Config = {F_CPU_8,RISING};
uint8 g_edgeCount = 0;
uint16 g_timeHigh = 0;
uint16 g_timePeriod = 0;


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void Ultrasonic_init(void)
{
	Icu_init(&Icu_Config);
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(TRIGGER_PIN_PORT_ID,TRIGGER_PIN_ID,PIN_OUTPUT);

}

void Ultrasonic_Trigger(void)
{
	GPIO_writePin(TRIGGER_PIN_PORT_ID,TRIGGER_PIN_ID,LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(TRIGGER_PIN_PORT_ID,TRIGGER_PIN_ID,LOGIC_LOW);

}

uint16 Ultrasonic_readDistance(void)
{
	Ultrasonic_Trigger();
	if(g_edgeCount==2)
		{
			g_edgeCount = 0;
			return ((uint16)((uint32)g_timeHigh*10/588)); //equation

		}
}

void Ultrasonic_edgeProcessing(void)
{
	g_edgeCount++;
		if(g_edgeCount == 1)
		{
			/*
			 * Clear the timer counter register to start measurements from the
			 * first detected rising edge
			 */
			Icu_clearTimerValue();
			/* Detect falling edge */
			Icu_setEdgeDetectionType(FALLING);
		}
		else if(g_edgeCount == 2)
		{
			/* Store the High time value */
			g_timeHigh = Icu_getInputCaptureValue();
			/* Detect rising edge */
			Icu_setEdgeDetectionType(RISING);
		}

}
