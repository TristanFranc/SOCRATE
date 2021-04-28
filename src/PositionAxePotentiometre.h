/*
 * @file    -> PositionAxePotentiometre.h
 * @author  -> Justin Bélanger
 * @version -> 0.01
 * @Created -> 22 mars 2021
 * @brief   -> Classe qui fait la gestion de la position d'un axe en fonction d'un potentiomètre
 */

#include <stdint-gcc.h>
#include "Adc1Stm32f446re.h"
#include "FiltreFenetreGlissante.h"

#ifndef POSITIONAXEPOTENTIOMETRE_H_
#define POSITIONAXEPOTENTIOMETRE_H_

//noAxe 1
#define POSITION_MAX_COUDE 172
#define POSITION_MIN_COUDE 130
#define NBS_TOT_DEGREE_COUDE 0

//noAxe 0
#define POSITION_MAX_EPAULE 150
#define POSITION_MIN_EPAULE 126
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

	/*
	 * @name   -> PositionAxePotentiometre
	 * @brief  -> constucteur de la classe
	 * @param  -> noAxeRobot: no de l'axe que la classe feras la gestion
	 * @return -> None
	 */
	PositionAxePotentiometre(uint8_t noAxeRobot);

	/*
	 * @name   -> setPositionPourcentage
	 * @brief  -> défini une nouvelle valeur pour positionAxePourcentage
	 * @param  -> positionPourcentage: nouvelle valeur qui affecteras positionAxePourcentage
	 * @return -> None
	 */
	void setPositionPourcentage(uint8_t positionPourcentage);

	/*
	 * @name   -> getPositionPourcentage
	 * @brief  -> retourne la valeur en pourcentage de la position de l'axe calculée en fonction des résultat de la fenêtre glissante
	 * @param  -> None
	 * @return -> uint8_t
	 */
	uint8_t getPositionPourcentage();

	/*
	 * @name   -> acquisitionNewPositionAxe
	 * @brief  -> fait l'acquisiton d'une nouvelle valeur du potentiomètre associer, transforme cette valeur en pourcentage et l'ajoute à la fenêtre glissante
	 * @param  -> None
	 * @return -> None
	 */
	void acquisitionNewPositionAxe();

	/*
	 * @name   -> getRawPosition
	 * @brief  -> revoie la position de l'axe convertie par l'adc (pas transformer en pourcentage)
	 * @param  -> None
	 * @return -> uint8_t
	 */
	uint8_t getRawPosition();

	/*
	 * @name   -> ~PositionAxePotentiometre
	 * @brief  -> destructeur de la classe
	 * @param  -> None
	 * @return -> None
	 */
	virtual ~PositionAxePotentiometre();
};

#endif /* POSITIONAXEPOTENTIOMETRE_H_ */
