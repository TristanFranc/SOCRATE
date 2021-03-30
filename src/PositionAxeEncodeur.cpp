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


