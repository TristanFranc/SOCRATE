/*
 * @file    -> PositionAxeEncodeur.h
 * @author  -> Justin Bélanger
 * @version -> 0.01
 * @Created -> 22 mars 2021
 * @brief   -> Classe qui fait la gestion de la position d'un axe en fonction d'un encodeur de roue
 */

#include <stdint-gcc.h>
#include "Encodeur.h"

#ifndef POSITIONAXEENCODEUR_H_
#define POSITIONAXEENCODEUR_H_


#define NBS_TOTAL_DENT_COUDE 113
#define NBS_TOTAL_DENT_EPAULE 120

#define NO_PIN_EPAULE 10
#define NO_PIN_COUDE 3

#define MOTEUR_HORAIRE 0 		// soustraction
#define MOTEUR_ANTIHORAIRE 1	// addition

extern "C"
{
void EXTI2_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);
}

class PositionAxeEncodeur
{
private:

	friend void EXTI2_IRQHandler(void);
	friend void EXTI9_5_IRQHandler(void);
	friend void EXTI15_10_IRQHandler(void);

	Encodeur *encodeur;
	uint8_t positionAxePourcentage;
	uint8_t positionAxeNoDent;
	bool directionMoteur;
	bool validInterrupt;
	uint8_t noPin;
public:

	/*
	 * @name   -> PositionAxeEncodeur
	 * @brief  -> Constructeur de la classe
	 * @param  -> gpioPort: port sur lequel la pin de trigger sera
	 * 			  noPin:	pin sur laquelle le trigger sera
	 * 			  trigger:	type de trigger voulue (rissing ou falling edge
	 * @return -> None
	 */
	PositionAxeEncodeur(GPIO_TypeDef *gpioPort, uint8_t noPin, uint8_t trigger);


	/*
	 * @name   -> conversionNbsDentPourcentage
	 * @brief  -> convertie la position actuel de l'encodeur en pourcentage
	 * @param  -> None
	 * @return -> None
	 */
	void conversionNbsDentPourcentage();


	/*
	 * @name   -> setPositionPourcentage
	 * @brief  -> définie une nouvelle valeur de positionAxePourcentage
	 * @param  -> positionPourcentage: nouvelle valeur qui sera affecter à positionPourcentage
	 * @return -> None
	 */
	void setPositionPourcentage(uint8_t positionPourcentage);

	/*
	 * @name   -> getPositionPourcentage
	 * @brief  -> retourne al position de l'axe en pourcentage
	 * @param  -> None
	 * @return -> uint8_t
	 */
	uint8_t getPositionPourcentage();

	/*
	 * @name   -> setPositionAxeNbsDent
	 * @brief  -> met a jours la position du moteur en fonction du nombre de dent passée depuis la position 0
	 * @param  -> directionMoteur: direction du moteur
	 * @return -> None
	 */
	void setPositionAxeNbsDent(uint8_t directionMoteur);


	/*
	 * @name   -> getNoPin
	 * @brief  -> retourne le no de la pin associer à l'interruption
	 * @param  -> None
	 * @return -> uint8_t
	 */
	uint8_t getNoPin();


	/*
	 * @name   -> getDirectionMoteur
	 * @brief  -> retourne la direction du moteur
	 * @param  -> None
	 * @return -> bool
	 */
	bool getDirectionMoteur();


	/*
	 * @name   -> clearInterruptFlag
	 * @brief  -> clear le flag du registre EXTI_PR (Necessaire après chaque interruption)
	 * @param  -> None
	 * @return -> None
	 */
	void clearInterruptFlag();


	/*
	 * @name   -> ~PositionAxeEncodeur
	 * @brief  -> destructeur de la classe
	 * @param  -> None
	 * @return -> None
	 */
	virtual ~PositionAxeEncodeur();
};

#endif /* POSITIONAXEENCODEUR_H_ */
