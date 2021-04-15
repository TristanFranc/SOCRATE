/*
 * GestionMouvementAxe.cpp
 *
 *  Created on: 30 mars 2021
 *      Author: Justin
 */

#include "GestionMouvementAxe.h"



GestionMouvementAxe::GestionMouvementAxe(uint8_t noMoteur, uint8_t noPot)
{
<<<<<<< Updated upstream

	potentiometre = new PositionAxePotentiometre(noPot);

=======
	potentiometre = new PositionAxePotentiometre(noPot);

	this->noMoteur = noMoteur;
>>>>>>> Stashed changes
	switch(noMoteur)
	{
	case 0:
		moteur = new controlL297(L297_2);
		moteur->setSpeed(100);
<<<<<<< Updated upstream
		moteur->setLockState(UNLOCK);
=======
		moteur->setLockState(LOCK);
		moteur->setEnable(true);
		moteur->setDirection(CCW);
>>>>>>> Stashed changes
		break;

	case 1:
		moteur = new controlL297(L297_1);
		moteur->setSpeed(100);
<<<<<<< Updated upstream
		moteur->setLockState(UNLOCK);
		break;

	case 2:
		moteur = new controlL297(L297_3_4);
		moteur->setLockState(LOCK);
		break;
	}
	moteur->setEnable(true);
	moteur->setDirection(CCW);


=======
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

>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
 return potentiometre->getRawPosition();
=======
	return potentiometre->getRawPosition();
>>>>>>> Stashed changes
}

bool GestionMouvementAxe::getDirectionMoteur()
{
	return moteur->getDirection();
}

<<<<<<< Updated upstream
=======
bool GestionMouvementAxe::getMoteurLockState()
{
	return moteur->getLockState();
}
>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
		if(speed < 400)
		{
			speed = 400;
		}

		else if(speed > 5000)
		{
			speed = 5000;
=======
		if(speed > 1000)
		{
			speed = 1000;
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
	if(directionVoulue == 0 && (potentiometre->getPositionPourcentage() < 1))
=======
	 if(noMoteur == 8)
	{
		return 1;
	}

	 else if(directionVoulue == 0 && (potentiometre->getPositionPourcentage() < 1))
>>>>>>> Stashed changes
	{
		return 0;
	}

<<<<<<< Updated upstream
	else if(directionVoulue == 1 && (potentiometre->getPositionPourcentage() > 100))
=======
	else if(directionVoulue == 1 && (potentiometre->getPositionPourcentage() > 99))
>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
=======
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
>>>>>>> Stashed changes

GestionMouvementAxe::~GestionMouvementAxe()
{
	// TODO Auto-generated destructor stub
}

