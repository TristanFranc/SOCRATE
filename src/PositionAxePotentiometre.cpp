/*
 * PositionAxePotentiometre.cpp
 *
 *  Created on: 22 mars 2021
 *      Author: Justin
 */

#include "PositionAxePotentiometre.h"

PositionAxePotentiometre::PositionAxePotentiometre(uint8_t noAxeRobot)
{
	adc =  new Adc1Stm32f446re(noAxeRobot);
	filtreFenetreGlissante = new FiltreFenetreGlissante();
	positionAxePourcentage = 0;
<<<<<<< Updated upstream

	rawPosition = 0;


=======
	rawPosition = 0;
>>>>>>> Stashed changes
	this->noAxeRobot = noAxeRobot;
	//rawPosition = 1;
}

void PositionAxePotentiometre::setPositionPourcentage(uint8_t positionPourcentage)
{
	this->positionAxePourcentage = positionPourcentage;
}

uint8_t PositionAxePotentiometre::getPositionPourcentage()
{
//	return this->positionAxePourcentage;
	return filtreFenetreGlissante->resultatFiltre();
}

void PositionAxePotentiometre::acquisitionNewPositionAxe()
{
	adc->startAdcConversion();
	if(adc->waitEocFlag())
	{
		rawPosition = adc->getConversion();
		switch(noAxeRobot)
		{
<<<<<<< Updated upstream


		case 3:

=======
		case 4:
>>>>>>> Stashed changes
			if(rawPosition < POSITION_MIN_COUDE)
			{
				rawPosition = POSITION_MIN_COUDE;
			}
			positionAxePourcentage = (100 * (rawPosition - POSITION_MIN_COUDE))/ (POSITION_MAX_COUDE - POSITION_MIN_COUDE);
			break;

<<<<<<< Updated upstream

		case 4:

=======
		case 3:
>>>>>>> Stashed changes
			if(rawPosition < POSITION_MIN_EPAULE)
			{
				rawPosition = POSITION_MIN_EPAULE;
			}
			positionAxePourcentage = (100 * (rawPosition - POSITION_MIN_EPAULE))/ (POSITION_MAX_EPAULE - POSITION_MIN_EPAULE);
			break;

		case 5:
			if(rawPosition < POSITION_MIN_PINCE)
			{
				rawPosition = POSITION_MIN_PINCE;
			}

			positionAxePourcentage = (100 * (rawPosition - POSITION_MIN_PINCE))/ (POSITION_MAX_PINCE - POSITION_MIN_PINCE);
			break;
		}

		if(positionAxePourcentage > 100)
		{
			positionAxePourcentage = 100;
		}
		setPositionPourcentage(positionAxePourcentage);
		filtreFenetreGlissante->miseNiveauFiltre(positionAxePourcentage);
		adc->clearEocFlag();
	}

}

<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes
uint8_t PositionAxePotentiometre::getRawPosition()
{
	return this->rawPosition;
}

<<<<<<< Updated upstream
=======
uint8_t PositionAxePotentiometre::getValueFiltreFenetreGlissante()
{

}
>>>>>>> Stashed changes

PositionAxePotentiometre::~PositionAxePotentiometre()
{
	// TODO Auto-generated destructor stub
}

