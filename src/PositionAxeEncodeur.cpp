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

	positionAxePourcentage = 0; //
	positionAxeNoDent = 0;

	directionMoteur = 0;
	validInterrupt = 0;
}

void PositionAxeEncodeur::conversionNbsDentPourcentage()
{
	switch(noPin)
	{
	case NO_PIN_COUDE:
		positionAxePourcentage = (100 * positionAxeNoDent) / NBS_TOTAL_DENT_COUDE;
		break;

	case NO_PIN_EPAULE:
		positionAxePourcentage = (100 * positionAxeNoDent) / NBS_TOTAL_DENT_EPAULE;
		break;
	}
	setPositionPourcentage(positionAxePourcentage);
}


void PositionAxeEncodeur::setPositionPourcentage(uint8_t positionPourcentage)
{
	this->positionAxePourcentage = positionPourcentage;
}

uint8_t PositionAxeEncodeur::getPositionPourcentage()
{
	return this->positionAxePourcentage;
}

void PositionAxeEncodeur::setPositionAxeNbsDent(uint8_t directionMoteur)
{
	switch(directionMoteur)
	{
	case MOTEUR_HORAIRE:
		this->positionAxeNoDent--;
		break;

	case MOTEUR_ANTIHORAIRE:
		this->positionAxeNoDent++;
		break;
	}
}

uint8_t PositionAxeEncodeur::getNoPin()
{
	return this->noPin;
}

bool PositionAxeEncodeur::getDirectionMoteur()
{
	return this->directionMoteur;
}

void PositionAxeEncodeur::clearInterruptFlag()
{
	encodeur->clearInterruptFlag();
}

PositionAxeEncodeur::~PositionAxeEncodeur()
{
	// TODO Auto-generated destructor stub
}


