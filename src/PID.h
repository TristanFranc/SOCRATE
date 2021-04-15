/*
 * PID.h
 *
 *  Created on: 8 avr. 2021
 *      Author: Justin
 */

#ifndef PID_H_
#define PID_H_
#include "stm32f4xx.h"
#include "stdlib.h"

#define VITESSE_MAX_MOTEUR 1000
#define VITESSE_MIN_MOTEUR 1

#define MOTEUR_HORAIRE 0
#define MOTEUR_ANTIHORAIRE 1

class PID
{
private:

	double constanteKp;
	double constanteKi;
	double constanteKd;

	int16_t valeurSortiePID;
	uint8_t valMesureePrecedente;

	int16_t erreur;
	double erreurCumulee;
	int16_t erreurRaw;

	bool directionMoteur;

public:

	PID(double kp, double ki, double kd);
	void calculPID(uint8_t positionAxeActuel, uint8_t positionAxeVoulue);
	bool getDirectionMoteur();
	uint32_t getValuePID();
	int16_t getErreurRaw();
	virtual ~PID();
};

#endif /* PID_H_ */
