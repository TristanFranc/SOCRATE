/*
 * @file    -> CanalEMG.cpp
 * @author  -> Justin Bélanger
 * @version -> 0.01
 * @Created -> 11 mars 2021
 * @brief 	->
 */


#include "CanalEMG.h"

/*
 * @name   -> CanalEMG
 * @brief  -> Constructeur de la classe
 * @param  -> noAxe: uméro de l'axe à auxquel l'adc sera associer
 * @return -> None
 */
CanalEMG::CanalEMG(uint8_t noAxeEmg)
{
	adc = new Adc1Stm32f446re(noAxeEmg);
	vecteur = new VecteurEMG();

}

/*
 * @name   -> getAdcValue
 * @brief  -> démarre la conversion de l'adc et renvoie la valeur convertie
 * @param  -> None
 * @return -> uint8_t: dernière conversion de l'adc
 */
uint8_t CanalEMG::getAdcValue()
{
	uint8_t conversion;
	adc->startAdcConversion();
	if(adc->waitEocFlag())
	{
		conversion = adc->getConversion();
		adc->clearEocFlag();
		return conversion;
	}
	else return 0;
}

CanalEMG::~CanalEMG()
{


}

