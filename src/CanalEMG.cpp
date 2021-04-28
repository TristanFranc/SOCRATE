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

/*
 * @name   -> acquisitionNewPositionEmg
 * @brief  -> Fait l'acquisition de la valeur du capteur Emg associer via l'adc puis transforme cette valeur en pourcentage pour la mettre dans la fenêtre glissante
 * @param  -> None
 * @return -> None
 */
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


/*
 * @name   -> calculPidValue
 * @brief  -> Appel la fonction de calcul de pid. L'erreur du calcul est faite avec les valeur de position voulue (emg en pourcentage) et de position actuel (potentiomètre)
 * @param  -> positionActuelAxe: position actuel du robot en pourcentage (calculer en fonction des potentiomètre)
 * @return -> None
 */
void CanalEMG::calculPidValue(uint8_t positionActuelAxe)
{
	pid->calculPID(positionActuelAxe,positionEmgPourcentage);
}


/*
 * @name   -> getValuePID
 * @brief  -> renvoie la valeur calculée par le pid
 * @param  -> None
 * @return -> uint32_t: valeur calculée du Pid
 */
uint32_t CanalEMG::getValuePID()
{
	return pid->getValuePID();
}


/*
 * @name   -> getDirectionMoteur
 * @brief  -> renvoie la direction du moteur défini en fonction de l'erreur calculer par le PID
 * @param  -> None
 * @return -> bool: direction du moteur (CW ou CCW)
 */
bool CanalEMG::getDirectionMoteur()
{
	return pid->getDirectionMoteur();
}


/*
 * @name   -> getPositionEmgRaw
 * @brief  -> renvoie la valeur convertie par l'adc sans la convertir en pourcentage
 * @param  -> None
 * @return -> uint8_t
 */
uint8_t CanalEMG::getPositionEmgRaw()
{
	return this->positionEmgRaw;
}


/*
 * @name   -> getPositionEmgPourcentage
 * @brief  -> renvoie la valeur convertie par l'adc en pourcentage
 * @param  -> None
 * @return -> uint8_t
 */
uint8_t CanalEMG::getPositionEmgPourcentage()
{
	return this->positionEmgPourcentage;
	//return filtreFenetreGlissante->resultatFiltre();
}


/*
 * @name   -> getErreurPidRaw
 * @brief  -> Renvoie la valuer absolue de l'erreur calculée par l'équaiton de PID
 * @param  -> None
 * @return -> int16_t
 */
int16_t CanalEMG::getErreurPidRaw()
{
	return pid->getErreurRaw();
}

/*
 * @name   -> ~CanalEMG
 * @brief  -> destructeur de la classe
 * @param  -> None
 * @return -> None
 */
CanalEMG::~CanalEMG()
{


}

