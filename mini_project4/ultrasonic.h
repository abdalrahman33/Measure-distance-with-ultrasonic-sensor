/*
 * ultrasonic.h
 *
 *  Created on: Feb 28, 2024
 *      Author: Abdelrahman Salem
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"
#include "gpio.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define TRIGGER_PIN_PORT_ID		PORTB_ID
#define TRIGGER_PIN_ID			PIN5_ID
#define ECHO_PIN_PORT_ID		PORTD_ID
#define ECHOPIN_PIN_ID			PIN6_ID
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void Ultrasonic_init(void);

void Ultrasonic_Trigger(void);

uint16 Ultrasonic_readDistance(void);

void Ultrasonic_edgeProcessing(void);


#endif /* ULTRASONIC_H_ */
