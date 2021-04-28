/*
 * @file    -> PID.cpp
 * @author  -> Justin Bélanger
 * @version -> 0.01
 * @Created -> 8 avr. 2021
 * @brief   -> Classe fesant la gestion d'un pid servant au controle de la direction et de la vitesse de moteur
 */
#include "PID.h"

/*
 * @name   -> PID
 * @brief  -> Constructeur de la classe
 * @param  -> kp: constante de l'équation proportionnel
 * 			  Ki: constante de l'intégrale
 * 			  Kd: constante de la dérivée
 * @return -> None
 */
PID::PID(double kp, double ki, double kd)
{
	constanteKp = kp;
	constanteKi = ki;
	constanteKd = kd;

	valeurSortiePID = 0;
	valMesureePrecedente = 0;

	erreur = 0;
	erreurCumulee = 0;
	erreurRaw = 0;

	directionMoteur = 0;

}


/*
 * @name   -> calculPID
 * @brief  -> calcul du PID et définition de la direction que le moteur de l'axe doit prendre
 * @param  -> positionAxeActuel: position actuel de l'axe
 * 			  positionAxeVoulue: position voulue de l'axe
 * @return -> None
 */
void PID::calculPID(uint8_t positionAxeActuel, uint8_t positionAxeVoulue)
{
	erreur = positionAxeVoulue - positionAxeActuel;
	erreurRaw = abs(erreur);

	if(erreur < 0)
	{
		directionMoteur = MOTEUR_HORAIRE;
	}

	else if(erreur > 0)
	{
		directionMoteur = MOTEUR_ANTIHORAIRE;
	}


	if(erreurRaw <= 5)
	{
		erreurCumulee += erreur;
		erreur = abs(erreur);
		valeurSortiePID = (constanteKp * erreur) + (constanteKi * erreurCumulee) + (constanteKd *((positionAxeActuel - valMesureePrecedente)/1000));

	}

	else
	{
		erreur = abs(erreur);
		valeurSortiePID = (constanteKp * erreur)  + (constanteKd *(positionAxeActuel - valMesureePrecedente));
	}

	valMesureePrecedente = positionAxeActuel;
	valeurSortiePID = abs(valeurSortiePID);  //renvoie la valeur absolue de erreur



	if(valeurSortiePID > VITESSE_MAX_MOTEUR)
	{
		valeurSortiePID = VITESSE_MAX_MOTEUR;
	}

	else if(valeurSortiePID < VITESSE_MIN_MOTEUR)
	{
		valeurSortiePID = VITESSE_MAX_MOTEUR;
	}
}


/*
 * @name   -> getDirectionMoteur
 * @brief  -> retourne la dirtection que les moteur doivent prendre selon le calcul du PID
 * @param  -> None
 * @return -> bool
 */
bool PID::getDirectionMoteur()
{
	return directionMoteur;
}


/*
 * @name   -> getValuePID
 * @brief  -> retourne la calculer du PID
 * @param  -> None
 * @return -> uint32_t
 */
uint32_t PID::getValuePID()
{
	return valeurSortiePID;
}


/*
 * @name   -> getErreurRaw
 * @brief  -> retourne la valeur absolue de l'erreur calculée par le PID
 * @param  -> None
 * @return -> int16_t
 */
int16_t PID::getErreurRaw()
{
	return this->erreurRaw;
}

/*
 * @name   -> ~PID
 * @brief  -> destructeur de la classe
 * @param  -> None
 * @return -> None
 */
PID::~PID() {
	// TODO Auto-generated destructor stub
}

