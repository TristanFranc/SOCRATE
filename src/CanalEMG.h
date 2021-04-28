/*
 * @file    -> CanalEMG.h
 * @author  -> Justin Bélanger
 * @version -> 0.01
 * @Created -> 11 Mars 2021
 * @brief 	-> classe qui fait la gestion d'un des axe du robot du projet S.O.C.R.A.T.E. en mode Capteur
 */



#include <stdint-gcc.h>
#include "Adc1Stm32f446re.h"
#include "PID.h"
#include "FiltreFenetreGlissante.h"

#ifndef CANALEMG_H_
#define CANALEMG_H_

#define POSITION_MAX_EMG 100
#define POSITION_MIN_EMG 1

class CanalEMG
{
private:
	Adc1Stm32f446re *adc;
	FiltreFenetreGlissante *filtreFenetreGlissante;
	PID *pid;

	uint8_t positionEmgRaw;
	uint8_t positionEmgPourcentage;
	//AcquisitionEMG *acquisitionEMG;

public:

	/*
	 * @name   -> CanalEMG
	 * @brief  -> Constructeur de la classe
	 * @param  -> noAxe: uméro de l'axe à auxquel l'adc sera associer
	 * @return -> None
	 */
	CanalEMG(uint8_t noAxeEmg, double kp, double ki, double kd);

	/*
	 * @name   -> getAdcValue
	 * @brief  -> démarre la conversion de l'adc et renvoie la valeur convertie
	 * @param  -> None
	 * @return -> uint8_t: dernière conversion de l'adc
	 */
	uint8_t getAdcValue();

	/*
	 * @name   -> acquisitionNewPositionEmg
	 * @brief  -> Fait l'acquisition de la valeur du capteur Emg associer via l'adc puis transforme cette valeur en pourcentage pour la mettre dans la fenêtre glissante
	 * @param  -> None
	 * @return -> None
	 */
	void acquisitionNewPositionEmg();

	/*
	 * @name   -> calculPidValue
	 * @brief  -> Appel la fonction de calcul de pid. L'erreur du calcul est faite avec les valeur de position voulue (emg en pourcentage) et de position actuel (potentiomètre)
	 * @param  -> positionActuelAxe: position actuel du robot en pourcentage (calculer en fonction des potentiomètre)
	 * @return -> None
	 */
	void calculPidValue(uint8_t valueActuelAxe);

	/*
	 * @name   -> getValuePID
	 * @brief  -> renvoie la valeur calculée par le pid
	 * @param  -> None
	 * @return -> uint32_t: valeur calculée du Pid
	 */
	uint32_t getValuePID();

	/*
	 * @name   -> getDirectionMoteur
	 * @brief  -> renvoie la direction du moteur défini en fonction de l'erreur calculer par le PID
	 * @param  -> None
	 * @return -> bool: direction du moteur (CW ou CCW)
	 */
	bool getDirectionMoteur();

	/*
	 * @name   -> getPositionEmgRaw
	 * @brief  -> renvoie la valeur convertie par l'adc sans la convertir en pourcentage
	 * @param  -> None
	 * @return -> uint8_t
	 */
	uint8_t getPositionEmgRaw();

	/*
	 * @name   -> getPositionEmgPourcentage
	 * @brief  -> renvoie la valeur convertie par l'adc en pourcentage
	 * @param  -> None
	 * @return -> uint8_t
	 */
	uint8_t getPositionEmgPourcentage();

	/*
	 * @name   -> getErreurPidRaw
	 * @brief  -> Renvoie la valuer absolue de l'erreur calculée par l'équaiton de PID
	 * @param  -> None
	 * @return -> int16_t
	 */
	int16_t getErreurPidRaw();


	virtual ~CanalEMG();
};

#endif /* CANALEMG_H_ */
