/*
 * GestionMouvementAxe.cpp
 *
 *  Created on: 30 mars 2021
 *      Author: Justin
 */

#include "GestionMouvementAxe.h"



GestionMouvementAxe::GestionMouvementAxe(uint8_t noMoteur, uint8_t noPot)
{

	potentiometre = new PositionAxePotentiometre(noPot);

	switch(noMoteur)
	{
	case 0:
		moteur = new controlL297(L297_2);
		moteur->setSpeed(100);
		moteur->setLockState(LOCK);
		break;

	case 1:
		moteur = new controlL297(L297_1);
		moteur->setSpeed(100);
		moteur->setLockState(LOCK);
		break;

	case 2:
		moteur = new controlL297(L297_3_4);
		moteur->setLockState(LOCK);
		break;
	}
	moteur->setEnable(true);
	moteur->setDirection(CCW);


}

//setter
void GestionMouvementAxe::setPositionEncoPourcentage(uint8_t newPositionEncoPourcentage)
{
	this->positionEncoPourcentage = newPositionEncoPourcentage;
}

void GestionMouvementAxe::setPositionPotPourcentage(uint8_t newPositionPotPourcentage)
{
	this->positionPotPourcentage = newPositionPotPourcentage;
}

//getter
uint8_t GestionMouvementAxe::getPositionEncoPourcentage()
{
	return this->positionEncoPourcentage;
}

uint8_t GestionMouvementAxe::getPositionPotPourcentage()
{
	return this->positionPotPourcentage;
}

uint8_t GestionMouvementAxe::getPotRawPosition()
{
 return potentiometre->getRawPosition();
}

bool GestionMouvementAxe::getDirectionMoteur()
{
	return moteur->getDirection();
}


//gestionMoteur
void GestionMouvementAxe::setMoteurLockState(bool state)
{
	switch(state)
	{
	case 0:
		moteur->setLockState(LOCK);
		break;

	case 1:
		moteur->setLockState(UNLOCK);
		break;
	}
}

void GestionMouvementAxe::setMoteurEnableState(bool state)
{
	moteur->setEnable(state);
}

void GestionMouvementAxe::setMoteurDirEtSpeed(uint32_t speed, bool direction)
{
	if(checkMovementLimit(direction))
	{
		if(speed < 400)
		{
			speed = 400;
		}

		else if(speed > 5000)
		{
			speed = 5000;
		}

		moteur->setSpeed(speed);

		switch(direction)
		{
		case 0:
			moteur->setDirection(CW);
			break;

		case 1:
			moteur->setDirection(CCW);
			break;
		}
		moteur->setLockState(UNLOCK);
	}

	else
	{
		moteur->setLockState(LOCK);
	}
}

bool GestionMouvementAxe::checkMovementLimit(bool directionVoulue)
{
	if(directionVoulue == 0 && (potentiometre->getPositionPourcentage() < 1))
	{
		return 0;
	}

	else if(directionVoulue == 1 && (potentiometre->getPositionPourcentage() > 100))
	{
		return 0;
	}

	else
	{
		return 1;
	}

}

void GestionMouvementAxe::updatePositionPot()
{
	potentiometre->acquisitionNewPositionAxe();
	this->positionPotPourcentage = potentiometre->getPositionPourcentage();
}


GestionMouvementAxe::~GestionMouvementAxe()
{
	// TODO Auto-generated destructor stub
}

