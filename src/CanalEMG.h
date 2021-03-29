/*
 * @file    -> CanalEMG.h
 * @author  -> Justin Bélanger
 * @version -> 0.01
 * @Created -> 11 Mars 2021
 * @brief 	-> classe qui fait la gestion d'un des axe du robot du projet S.O.C.R.A.T.E. en mode Capteur
 */


#include "VecteurEMG.h"
#include <stdint-gcc.h>
#include "Adc1Stm32f446re.h"

#ifndef CANALEMG_H_
#define CANALEMG_H_



class CanalEMG
{
private:
	Adc1Stm32f446re *adc;
	VecteurEMG *vecteur;
	//AcquisitionEMG *acquisitionEMG;

public:

	/*
	 * @name   -> CanalEMG
	 * @brief  -> Constructeur de la classe
	 * @param  -> noAxe: uméro de l'axe à auxquel l'adc sera associer
	 * @return -> None
	 */
	CanalEMG(uint8_t noAxeEmg);

	/*
	 * @name   -> getAdcValue
	 * @brief  -> démarre la conversion de l'adc et renvoie la valeur convertie
	 * @param  -> None
	 * @return -> uint8_t: dernière conversion de l'adc
	 */
	uint8_t getAdcValue();


	virtual ~CanalEMG();
};

#endif /* CANALEMG_H_ */
