/*
 * PositionAxeEncodeur.h
 *
 *  Created on: 22 mars 2021
 *      Author: Justin
 */

#include <stdint-gcc.h>
#include "Encodeur.h"

#ifndef POSITIONAXEENCODEUR_H_
#define POSITIONAXEENCODEUR_H_

#define NBS_TOTAL_DENT_COUDE 113
#define NBS_TOTAL_DENT_EPAULE 120

extern "C"
{
void EXTI2_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);
}

class PositionAxeEncodeur
{
private:

	friend void EXTI2_IRQHandler(void);
	friend void EXTI9_5_IRQHandler(void);
	friend void EXTI15_10_IRQHandler(void);

	Encodeur *encodeur;
	uint8_t PositionAxePourcentage;
	bool direction;
	uint8_t noPin;
public:

	PositionAxeEncodeur(GPIO_TypeDef *gpioPort, uint8_t noPin, uint8_t trigger);
	void innitEncodeur(GPIO_TypeDef *gpioPort, uint8_t noPin, uint8_t trigger);
	void conversionDegrePourcentage();
	void setPositionPourcentage(uint8_t positionPourcentage);
	void getPositionPourcentage();
	virtual ~PositionAxeEncodeur();
};

#endif /* POSITIONAXEENCODEUR_H_ */
