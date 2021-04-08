/*
 * GestionMouvementAxe.h
 *
 *  Created on: 30 mars 2021
 *      Author: Justin
 */

#include <stdint-gcc.h>
#include "stm32f4xx.h"
#include "controlL297.h"
#include "PositionAxePotentiometre.h"

#ifndef GESTIONMOUVEMENTAXE_H_
#define GESTIONMOUVEMENTAXE_H_



class GestionMouvementAxe
{
private:
	uint8_t positionEncoPourcentage;
	uint8_t positionPotPourcentage;
	PositionAxePotentiometre *potentiometre;
	controlL297 *moteur;
public:
	GestionMouvementAxe(uint8_t noMoteur, uint8_t noPot);

	//setter
	void setPositionEncoPourcentage(uint8_t newPositionEncoPourcentage);
	void setPositionPotPourcentage(uint8_t newPositionPotPourcentage);

	//getter
	uint8_t getPositionEncoPourcentage();
	uint8_t getPositionPotPourcentage();
	bool getDirectionMoteur();
	uint8_t getPotRawPosition();

	//gestionMoteur
	void setMoteurLockState(bool state);
	void setMoteurEnableState(bool state);
	void setMoteurDirEtSpeed(uint32_t speed, bool direction);
	bool checkMovementLimit(bool directionVoulue);

	//gestion Position
	void updatePositionPot();

	virtual ~GestionMouvementAxe();
};

#endif /* GESTIONMOUVEMENTAXE_H_ */
