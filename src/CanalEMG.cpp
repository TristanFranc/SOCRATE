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
CanalEMG::CanalEMG(uint8_t noAxeEmg, double kp, double ki, double kd)
{
	adc = new Adc1Stm32f446re(noAxeEmg);
	filtreFenetreGlissante = new FiltreFenetreGlissante();
	pid = new PID(kp, ki, kd);

	positionEmgRaw = 0;
	positionEmgPourcentage = 0;

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

void CanalEMG::acquisitionNewPositionEmg()
{
	positionEmgRaw = getAdcValue();

	if(positionEmgRaw < POSITION_MIN_EMG)
	{
		positionEmgRaw = POSITION_MIN_EMG;
	}

	positionEmgPourcentage = (100 * (positionEmgRaw - POSITION_MIN_EMG)) / (POSITION_MAX_EMG - POSITION_MIN_EMG);

	if(positionEmgPourcentage > 100)
	 {
		 positionEmgPourcentage = 100;
	 }

	filtreFenetreGlissante->miseNiveauFiltre(positionEmgPourcentage);
}

void CanalEMG::calculPidValue(uint8_t positionActuelAxe)
{
	pid->calculPID(positionActuelAxe,positionEmgPourcentage);
}

uint32_t CanalEMG::getValuePID()
{
	return pid->getValuePID();
}

bool CanalEMG::getDirectionMoteur()
{
	return pid->getDirectionMoteur();
}

uint8_t CanalEMG::getPositionEmgRaw()
{
	return this->positionEmgRaw;
}

uint8_t CanalEMG::getPositionEmgPourcentage()
{
	return this->positionEmgPourcentage;
	//return filtreFenetreGlissante->resultatFiltre();
}

int16_t CanalEMG::getErreurPidRaw()
{
 return pid->getErreurRaw();
}

CanalEMG::~CanalEMG()
{


}
