/*
 * PID.cpp
 *
 *  Created on: 8 avr. 2021
 *      Author: Justin
 */

#include "PID.h"

PID::PID(double kp, double ki, double kd)
{
	constanteKp = kp;
	constanteKi = ki;
	constanteKd = kd;

	valeurSortiePID = 0;
	valMesureePrecedente = 0;

	erreur = 0;
	erreurCumulee = 0;
	erreurRaw = 0;

	directionMoteur = 0;

}

void PID::calculPID(uint8_t positionAxeActuel, uint8_t positionAxeVoulue)
{
	erreur = positionAxeVoulue - positionAxeActuel;

	erreurRaw = abs(erreur);
	if(erreur < 0)
	{
		directionMoteur = MOTEUR_HORAIRE;
	}

	else if(erreur > 0)
	{
		directionMoteur = MOTEUR_ANTIHORAIRE;
	}


	erreurCumulee += erreur;
	erreur = abs(erreur);


	valeurSortiePID = (constanteKp * erreur) + (constanteKi * erreurCumulee) + (constanteKd *(positionAxeActuel - valMesureePrecedente));
	valMesureePrecedente = positionAxeActuel;
	valeurSortiePID = abs(valeurSortiePID);  //renvoie la valeur absolue de erreur



	if(valeurSortiePID > VITESSE_MAX_MOTEUR)
	{
		valeurSortiePID = VITESSE_MAX_MOTEUR;
	}

	else if(valeurSortiePID < VITESSE_MIN_MOTEUR)
	{
		valeurSortiePID = VITESSE_MAX_MOTEUR;
	}
}

bool PID::getDirectionMoteur()
{
	return directionMoteur;
}

uint32_t PID::getValuePID()
{
	return valeurSortiePID;
}

int16_t PID::getErreurRaw()
{
	return this->erreurRaw;
}

PID::~PID() {
	// TODO Auto-generated destructor stub
}
