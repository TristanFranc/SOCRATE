/*
 * Encodeur.h
 *
 *  Created on: 23 mars 2021
 *      Author: Justin
 */
#include "stm32f4xx.h"
#include <stdint-gcc.h>

#ifndef ENCODEUR_H_
#define ENCODEUR_H_

#define FALLING_EDGE_TRIGGER 0
#define RISING_EDGE_TRIGGER 1
#define RISIN_FALLING_EDGE_TRIGGER 2


#define SYSCFG_EXTI_PB 1
#define SYSCFG_EXTI_PC 2

class Encodeur
{
private:
	uint8_t noPin;

public:
	Encodeur(GPIO_TypeDef *gpioPort, uint8_t noPin, uint8_t trigger);
	void innitExternalInterupt(GPIO_TypeDef *gpioPort, uint8_t noPin, uint8_t trigger);
	void clearInterruptFlag();
	virtual ~Encodeur();
};

#endif /* ENCODEUR_H_ */
