/*
 * @file    -> PID.h
 * @author  -> Justin Bélanger
 * @version -> 0.01
 * @Created -> 8 avr. 2021
 * @brief   -> Classe fesant la gestion d'un pid servant au controle de la direction et de la vitesse de moteur
 */

#ifndef PID_H_
#define PID_H_
#include "stm32f4xx.h"
#include "stdlib.h"

#define VITESSE_MAX_MOTEUR 1000
#define VITESSE_MIN_MOTEUR 1

#define MOTEUR_HORAIRE 0
#define MOTEUR_ANTIHORAIRE 1

class PID
{
private:

	double constanteKp;
	double constanteKi;
	double constanteKd;

	int16_t valeurSortiePID;
	uint8_t valMesureePrecedente;

	int16_t erreur;
	double erreurCumulee;
	int16_t erreurRaw;

	bool directionMoteur;

public:

	/*
	 * @name   -> PID
	 * @brief  -> Constructeur de la classe
	 * @param  -> kp: constante de l'équation proportionnel
	 * 			  Ki: constante de l'intégrale
	 * 			  Kd: constante de la dérivée
	 * @return -> None
	 */
	PID(double kp, double ki, double kd);

	/*
	 * @name   -> calculPID
	 * @brief  -> calcul du PID et définition de la direction que le moteur de l'axe doit prendre
	 * @param  -> positionAxeActuel: position actuel de l'axe
	 * 			  positionAxeVoulue: position voulue de l'axe
	 * @return -> None
	 */
	void calculPID(uint8_t positionAxeActuel, uint8_t positionAxeVoulue);

	/*
	 * @name   -> getDirectionMoteur
	 * @brief  -> retourne la dirtection que les moteur doivent prendre selon le calcul du PID
	 * @param  -> None
	 * @return -> bool
	 */
	bool getDirectionMoteur();

	/*
	 * @name   -> getValuePID
	 * @brief  -> retourne la calculer du PID
	 * @param  -> None
	 * @return -> uint32_t
	 */
	uint32_t getValuePID();

	/*
	 * @name   -> getErreurRaw
	 * @brief  -> retourne la valeur absolue de l'erreur calculée par le PID
	 * @param  -> None
	 * @return -> int16_t
	 */
	int16_t getErreurRaw();

	/*
	 * @name   -> ~PID
	 * @brief  -> destructeur de la classe
	 * @param  -> None
	 * @return -> None
	 */
	virtual ~PID();
};

#endif /* PID_H_ */
