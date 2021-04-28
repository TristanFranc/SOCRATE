/*
 * @file    -> GestionMouvementAxe.cpp
 * @author  -> Justin Bélanger
 * @version -> 0.01
 * @Created -> 30 mars 2021
 * @brief   -> Classe qui fait la gestion des mouvements d'un axe du robot en fonction de sa position actuel et de ses limites
 */

#include "GestionMouvementAxe.h"


/*
 * @name   -> GestionMouvementAxe
 * @brief  -> Constructeur de la classe
 * @param  -> noMoteur: numéro du moteur à activée/crée (voir liste define dans le main)
 * 			  noPot:	numéro du potentiomètre à activée/crée (voir liste define dans le main)
 * @return -> None
 */
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

/*
 * @name   -> setPositionEncoPourcentage
 * @brief  -> affecte la variable positionEncoPourcentage avec une nouvelle valeur
 * @param  -> newPositionEncoPourcentage: nouvelle valeur qui affecteras positionEncoPourcentage
 * @return -> None
 */
void GestionMouvementAxe::setPositionEncoPourcentage(uint8_t newPositionEncoPourcentage)
{
	this->positionEncoPourcentage = newPositionEncoPourcentage;
}


/*
 * @name   -> setPositionPotPourcentage
 * @brief  -> affecte la variable positionPotPourcentage avec une nouvelle valeur
 * @param  -> newPositionPotPourcentage: ouvelle valeur qui affecteras positionPotPourcentage
 * @return -> None
 */
void GestionMouvementAxe::setPositionPotPourcentage(uint8_t newPositionPotPourcentage)
{
	this->positionPotPourcentage = newPositionPotPourcentage;
}

//getter

/*
 * @name   -> getPositionEncoPourcentage
 * @brief  -> renvoie la valeur en pourcentage associer à la position de l'encodeur de roue
 * @param  -> None
 * @return -> uint8_t
 */
uint8_t GestionMouvementAxe::getPositionEncoPourcentage()
{
	return this->positionEncoPourcentage;
}


/*
 * @name   -> getPositionPotPourcentage
 * @brief  -> renvoie la valeur en pourcentage associer à la position du potentiomètre
 * @param  -> None
 * @return -> uint8_t
 */
uint8_t GestionMouvementAxe::getPositionPotPourcentage()
{
	return this->positionPotPourcentage;
}


/*
 * @name   -> getPotRawPosition
 * @brief  -> renvoie la valeur de conversion de l'adc associer à la position du potentiomètre
 * @param  -> None
 * @return -> uint8_t
 */
uint8_t GestionMouvementAxe::getPotRawPosition()
{
	return potentiometre->getRawPosition();
}


/*
 * @name   -> getDirectionMoteur
 * @brief  -> renvoie la direction actuel à laquelle le moteur est actuellement
 * @param  -> None
 * @return -> bool
 */
bool GestionMouvementAxe::getDirectionMoteur()
{
	return moteur->getDirection();
}


/*
 * @name   -> getMoteurLockState
 * @brief  -> renvoie l'état actuel du moteur (lock ou unlock)
 * @param  -> None
 * @return -> bool
 */
bool GestionMouvementAxe::getMoteurLockState()
{
	return moteur->getLockState();
}


//gestionMoteur

/*
 * @name   -> setMoteurLockState
 * @brief  -> permet de changer l'état actuel du moteur (lock ou unlock)
 * @param  -> state: état voulue du moteur (lock ou unlock)
 * @return -> None
 */
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


/*
 * @name   -> setMoteurEnableState
 * @brief  -> permet de changer l'état actuel actuel du moteur (enable ou disable)
 * @param  -> state: état voulue du moteur (enable ou disable)
 * @return -> None
 */
void GestionMouvementAxe::setMoteurEnableState(bool state)
{
	moteur->setEnable(state);
}


/*
 * @name   -> setMoteurDirEtSpeed
 * @brief  -> permet de changer la direction et la vitesse du moteur si la position physique le permet
 * @param  -> speed: vitesse voulue
 * 			  direction: direction voulue
 * @return -> None
 */
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


/*
 * @name   -> checkMovementLimit
 * @brief  -> Vérifie si le moteur peut aller dans un sens ou l'autre en fonction de la position physique actuel du moteur
 * @param  -> directionVoulue: direction que le moteur veut prendre
 * @return -> bool
 */
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


/*
 * @name   -> updatePositionPot
 * @brief  -> fait l'acquisition d'une nouvelle valeur du potentiomètre associer
 * @param  -> None
 * @return -> None
 */
void GestionMouvementAxe::updatePositionPot()
{
	potentiometre->acquisitionNewPositionAxe();
	this->positionPotPourcentage = potentiometre->getPositionPourcentage();
}


//gestion pince

/*
 * @name   -> setDirectionPince
 * @brief  -> set la direction que le moteur de la pince doit prendre (CW, CCW ou IDLE)
 * @param  -> direction: direction voulue
 * @return -> None
 */
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

/*
 * @name   -> ~GestionMouvementAxe
 * @brief  -> destructeur de la classe
 * @param  -> None
 * @return -> None
 */
GestionMouvementAxe::~GestionMouvementAxe()
{
	// TODO Auto-generated destructor stub
}

