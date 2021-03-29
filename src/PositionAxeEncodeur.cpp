/*
 * PositionAxeEncodeur.cpp
 *
 *  Created on: 22 mars 2021
 *      Author: Justin
 */

#include "PositionAxeEncodeur.h"

PositionAxeEncodeur::PositionAxeEncodeur(GPIO_TypeDef *gpioPort, uint8_t noPin, uint8_t trigger)
{
	this->noPin = noPin;
	encodeur = new Encodeur(gpioPort, noPin, trigger);
	PositionAxePourcentage = 0;
}

void PositionAxeEncodeur::setPositionPourcentage(uint8_t positionPourcentage)
{

}

void PositionAxeEncodeur::getPositionPourcentage()
{

}


PositionAxeEncodeur::~PositionAxeEncodeur()
{
	// TODO Auto-generated destructor stub
}

extern "C" void EXTI2_IRQHandler(void)
{
	encodeur->clearInterruptFlag();
}

extern "C" void EXTI9_5_IRQHandler(void)
{
	if((EXTI->PR & EXTI_PR_PR5) && (noPin == 5))
	{
		encodeur->clearInterruptFlag();
	}

	if((EXTI->PR & EXTI_PR_PR6) && (noPin == 6))
	{
		encodeur->clearInterruptFlag();
	}

	if((EXTI->PR & EXTI_PR_PR7) && (noPin == 7))
	{
		encodeur->clearInterruptFlag();
	}

	if((EXTI->PR & EXTI_PR_PR8) && (noPin == 8))
	{
		encodeur->clearInterruptFlag();
	}

	if((EXTI->PR & EXTI_PR_PR9) && (noPin == 9))
	{
		encodeur->clearInterruptFlag();
	}

}

extern "C" void EXTI15_10_IRQHandler(void)
{
	if((EXTI->PR & EXTI_PR_PR10) && (noPin == 10))
	{
		encodeur->clearInterruptFlag();
	}

	if((EXTI->PR & EXTI_PR_PR11) && (noPin == 11))
	{
		encodeur->clearInterruptFlag();
	}

	if((EXTI->PR & EXTI_PR_PR12) && (noPin == 12))
	{
		encodeur->clearInterruptFlag();
	}

	if((EXTI->PR & EXTI_PR_PR13) && (noPin == 13))
	{
		encodeur->clearInterruptFlag();
	}

	if((EXTI->PR & EXTI_PR_PR14) && (noPin == 14))
	{
		encodeur->clearInterruptFlag();
	}

	if((EXTI->PR & EXTI_PR_PR15) && (noPin == 15))
	{
		encodeur->clearInterruptFlag();
	}


}
