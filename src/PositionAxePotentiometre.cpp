/*
 * @file    -> PositionAxePotentiometre.cpp
 * @author  -> Justin Bélanger
 * @version -> 0.01
 * @Created -> 22 mars 2021
 * @brief   -> Classe qui fait la gestion de la position d'un axe en fonction d'un potentiomètre
 */

#include "PositionAxePotentiometre.h"


/*
 * @name   -> PositionAxePotentiometre
 * @brief  -> constucteur de la classe
 * @param  -> noAxeRobot: no de l'axe que la classe feras la gestion
 * @return -> None
 */
PositionAxePotentiometre::PositionAxePotentiometre(uint8_t noAxeRobot)
{
	adc =  new Adc1Stm32f446re(noAxeRobot);
	filtreFenetreGlissante = new FiltreFenetreGlissante();
	positionAxePourcentage = 0;
	rawPosition = 0;
	this->noAxeRobot = noAxeRobot;
	rawPosition = 1;
}


/*
 * @name   -> setPositionPourcentage
 * @brief  -> défini une nouvelle valeur pour positionAxePourcentage
 * @param  -> positionPourcentage: nouvelle valeur qui affecteras positionAxePourcentage
 * @return -> None
 */
void PositionAxePotentiometre::setPositionPourcentage(uint8_t positionPourcentage)
{
	this->positionAxePourcentage = positionPourcentage;
}


/*
 * @name   -> getPositionPourcentage
 * @brief  -> retourne la valeur en pourcentage de la position de l'axe calculée en fonction des résultat de la fenêtre glissante
 * @param  -> None
 * @return -> uint8_t
 */
uint8_t PositionAxePotentiometre::getPositionPourcentage()
{
//	return this->positionAxePourcentage;
	return filtreFenetreGlissante->resultatFiltre();
}


/*
 * @name   -> acquisitionNewPositionAxe
 * @brief  -> fait l'acquisiton d'une nouvelle valeur du potentiomètre associer, transforme cette valeur en pourcentage et l'ajoute à la fenêtre glissante
 * @param  -> None
 * @return -> None
 */
void PositionAxePotentiometre::acquisitionNewPositionAxe()
{
	adc->startAdcConversion();
	if(adc->waitEocFlag())
	{
		rawPosition = adc->getConversion();
		switch(noAxeRobot)
		{
		case 4:
			if(rawPosition < POSITION_MIN_COUDE)
			{
				rawPosition = POSITION_MIN_COUDE;
			}
			positionAxePourcentage = (100 * (rawPosition - POSITION_MIN_COUDE))/ (POSITION_MAX_COUDE - POSITION_MIN_COUDE);
			break;

		case 3:
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



		setPositionPourcentage(positionAxePourcentage);
		filtreFenetreGlissante->miseNiveauFiltre(positionAxePourcentage);
		adc->clearEocFlag();
	}
}


/*
 * @name   -> getRawPosition
 * @brief  -> revoie la position de l'axe convertie par l'adc (pas transformer en pourcentage)
 * @param  -> None
 * @return -> uint8_t
 */
uint8_t PositionAxePotentiometre::getRawPosition()
{
	return this->rawPosition;
}



/*
 * @name   -> ~PositionAxePotentiometre
 * @brief  -> destructeur de la classe
 * @param  -> None
 * @return -> None
 */
PositionAxePotentiometre::~PositionAxePotentiometre()
{
	// TODO Auto-generated destructor stub
}

