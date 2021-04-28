/*
 * @file    -> PositionAxeEncodeur.cpp
 * @author  -> Justin Bélanger
 * @version -> 0.01
 * @Created -> 22 mars 2021
 * @brief   -> Classe qui fait la gestion de la position d'un axe en fonction d'un encodeur de roue
 */

#include "PositionAxeEncodeur.h"

/*
 * @name   -> PositionAxeEncodeur
 * @brief  -> Constructeur de la classe
 * @param  -> gpioPort: port sur lequel la pin de trigger sera
 * 			  noPin:	pin sur laquelle le trigger sera
 * 			  trigger:	type de trigger voulue (rissing ou falling edge
 * @return -> None
 */
PositionAxeEncodeur::PositionAxeEncodeur(GPIO_TypeDef *gpioPort, uint8_t noPin, uint8_t trigger)
{
	this->noPin = noPin;
	encodeur = new Encodeur(gpioPort, noPin, trigger);

	positionAxePourcentage = 0; //
	positionAxeNoDent = 0;

	directionMoteur = 0;
	validInterrupt = 0;
}


/*
 * @name   -> conversionNbsDentPourcentage
 * @brief  -> convertie la position actuel de l'encodeur en pourcentage
 * @param  -> None
 * @return -> None
 */
void PositionAxeEncodeur::conversionNbsDentPourcentage()
{
	switch(noPin)
	{
	case NO_PIN_COUDE:
		positionAxePourcentage = (100 * positionAxeNoDent) / NBS_TOTAL_DENT_COUDE;
		break;

	case NO_PIN_EPAULE:
		positionAxePourcentage = (100 * positionAxeNoDent) / NBS_TOTAL_DENT_EPAULE;
		break;
	}
	setPositionPourcentage(positionAxePourcentage);
}


/*
 * @name   -> setPositionPourcentage
 * @brief  -> définie une nouvelle valeur de positionAxePourcentage
 * @param  -> positionPourcentage: nouvelle valeur qui sera affecter à positionPourcentage
 * @return -> None
 */
void PositionAxeEncodeur::setPositionPourcentage(uint8_t positionPourcentage)
{
	this->positionAxePourcentage = positionPourcentage;
}


/*
 * @name   -> getPositionPourcentage
 * @brief  -> retourne al position de l'axe en pourcentage
 * @param  -> None
 * @return -> uint8_t
 */
uint8_t PositionAxeEncodeur::getPositionPourcentage()
{
	return this->positionAxePourcentage;
}


/*
 * @name   -> setPositionAxeNbsDent
 * @brief  -> met a jours la position du moteur en fonction du nombre de dent passée depuis la position 0
 * @param  -> directionMoteur: direction du moteur
 * @return -> None
 */
void PositionAxeEncodeur::setPositionAxeNbsDent(uint8_t directionMoteur)
{
	switch(directionMoteur)
	{
	case MOTEUR_HORAIRE:
		this->positionAxeNoDent--;
		break;

	case MOTEUR_ANTIHORAIRE:
		this->positionAxeNoDent++;
		break;
	}
}


/*
 * @name   -> getNoPin
 * @brief  -> retourne le no de la pin associer à l'interruption
 * @param  -> None
 * @return -> uint8_t
 */
uint8_t PositionAxeEncodeur::getNoPin()
{
	return this->noPin;
}


/*
 * @name   -> getDirectionMoteur
 * @brief  -> retourne la direction du moteur
 * @param  -> None
 * @return -> bool
 */
bool PositionAxeEncodeur::getDirectionMoteur()
{
	return this->directionMoteur;
}


/*
 * @name   -> clearInterruptFlag
 * @brief  -> clear le flag du registre EXTI_PR (Necessaire après chaque interruption)
 * @param  -> None
 * @return -> None
 */
void PositionAxeEncodeur::clearInterruptFlag()
{
	encodeur->clearInterruptFlag();
}


/*
 * @name   -> ~PositionAxeEncodeur
 * @brief  -> destructeur de la classe
 * @param  -> None
 * @return -> None
 */
PositionAxeEncodeur::~PositionAxeEncodeur()
{
	// TODO Auto-generated destructor stub
}


