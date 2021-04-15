/*
 * PositionAxePotentiometre.h
 *
 *  Created on: 22 mars 2021
 *      Author: Justin
 */

#include <stdint-gcc.h>
#include "Adc1Stm32f446re.h"
#include "FiltreFenetreGlissante.h"

#ifndef POSITIONAXEPOTENTIOMETRE_H_
#define POSITIONAXEPOTENTIOMETRE_H_

<<<<<<< Updated upstream
//noAxe 0

#define POSITION_MAX_COUDE 210
#define POSITION_MIN_COUDE 130
#define NBS_TOT_DEGREE_COUDE 0

//noAxe 1
#define POSITION_MAX_EPAULE 159

#define POSITION_MAX_COUDE 224
#define POSITION_MIN_COUDE 142
#define NBS_TOT_DEGREE_COUDE 0

//noAxe 1
#define POSITION_MAX_EPAULE 153

#define POSITION_MIN_EPAULE 130
=======
//noAxe 1
#define POSITION_MAX_COUDE 210
#define POSITION_MIN_COUDE 130
#define NBS_TOT_DEGREE_COUDE 0

//noAxe 0
#define POSITION_MAX_EPAULE 148
#define POSITION_MIN_EPAULE 126
>>>>>>> Stashed changes
#define NBS_TOT_DEGREE_EPAULE 90

//noAxe 2
#define POSITION_MAX_PINCE 255
#define POSITION_MIN_PINCE 186
#define NBS_TOT_DEGREE_PINCE 10


class PositionAxePotentiometre
{
private:
	Adc1Stm32f446re *adc;
	FiltreFenetreGlissante *filtreFenetreGlissante;

	uint8_t positionAxePourcentage;
	uint8_t noAxeRobot;
	uint8_t rawPosition;


public:

	PositionAxePotentiometre(uint8_t noAxeRobot);
	void setPositionPourcentage(uint8_t positionPourcentage);
	uint8_t getPositionPourcentage();
<<<<<<< Updated upstream

	uint8_t getRawPosition();

=======
	uint8_t getRawPosition();
	uint8_t getValueFiltreFenetreGlissante();
>>>>>>> Stashed changes
	void acquisitionNewPositionAxe();

	virtual ~PositionAxePotentiometre();
};

#endif /* POSITIONAXEPOTENTIOMETRE_H_ */
