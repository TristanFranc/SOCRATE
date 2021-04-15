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

	this->noMoteur = noMoteur;
	switch(noMoteur)
	{
	case 0:
		moteur = new controlL297(L297_2);
		moteur->setSpeed(100);
		moteur->setLockState(LOCK);
		moteur->setEnable(true);
		moteur->setDirection(CCW);
		break;

	case 1:
		moteur = new controlL297(L297_1);
		moteur->setSpeed(100);
		moteur->setLockState(LOCK);
		moteur->setEnable(true);
		moteur->setDirection(CCW);
		break;

	case 2:
		pince = new L298x();
		//		moteur = new controlL297(L297_3_4);
		//		moteur->setLockState(LOCK);
		break;

	case 8:
		moteur = new controlL297(L297_3_4);
		moteur->setSpeed(100);
		moteur->setLockState(LOCK);
		moteur->setEnable(true);
		moteur->setDirection(CCW);
		break;

	}



	positionEncoPourcentage = 0;
	positionPotPourcentage = 0;

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

bool GestionMouvementAxe::getMoteurLockState()
{
	return moteur->getLockState();
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
		if(speed > 1000)
		{
			speed = 1000;
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
	 if(noMoteur == 8)
	{
		return 1;
	}

	 else if(directionVoulue == 0 && (potentiometre->getPositionPourcentage() < 1))
	{
		return 0;
	}

	else if(directionVoulue == 1 && (potentiometre->getPositionPourcentage() > 99))
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

//gestion pince
void GestionMouvementAxe::setDirectionPince(uint8_t direction)
{
	switch(direction)
	{
	case 0:
		pince->setDirection(CW_P);
		break;
	case 1:
		pince->setDirection(CCW_P);
		break;
	case 2:
		pince->setDirection(IDLE_P);
		break;
	}
}

GestionMouvementAxe::~GestionMouvementAxe()
{
	// TODO Auto-generated destructor stub
}

