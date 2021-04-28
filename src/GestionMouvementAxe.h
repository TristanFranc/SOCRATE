/*
 * @file    -> GestionMouvementAxe.h
 * @author  -> Justin Bélanger
 * @version -> 0.01
 * @Created -> 30 mars 2021
 * @brief   -> Classe qui fait la gestion des mouvements d'un axe du robot en fonction de sa position actuel et de ses limites
 */

#include <stdint-gcc.h>
#include "stm32f4xx.h"
#include "controlL297.h"
#include "PositionAxePotentiometre.h"
#include "L298x.h"

#ifndef GESTIONMOUVEMENTAXE_H_
#define GESTIONMOUVEMENTAXE_H_



class GestionMouvementAxe
{
private:
	uint8_t positionEncoPourcentage;
	uint8_t positionPotPourcentage;
	PositionAxePotentiometre *potentiometre;
	controlL297 *moteur;
	L298x *pince;
	uint8_t noMoteur;

public:

	/*
	 * @name   -> GestionMouvementAxe
	 * @brief  -> Constructeur de la classe
	 * @param  -> noMoteur: numéro du moteur à activée/crée (voir liste define dans le main)
	 * 			  noPot:	numéro du potentiomètre à activée/crée (voir liste define dans le main)
	 * @return -> None
	 */
	GestionMouvementAxe(uint8_t noMoteur, uint8_t noPot = 0);


	//setter

	/*
	 * @name   -> setPositionEncoPourcentage
	 * @brief  -> affecte la variable positionEncoPourcentage avec une nouvelle valeur
	 * @param  -> newPositionEncoPourcentage: nouvelle valeur qui affecteras positionEncoPourcentage
	 * @return -> None
	 */
	void setPositionEncoPourcentage(uint8_t newPositionEncoPourcentage);

	/*
	 * @name   -> setPositionPotPourcentage
	 * @brief  -> affecte la variable positionPotPourcentage avec une nouvelle valeur
	 * @param  -> newPositionPotPourcentage: ouvelle valeur qui affecteras positionPotPourcentage
	 * @return -> None
	 */
	void setPositionPotPourcentage(uint8_t newPositionPotPourcentage);


	//getter

	/*
	 * @name   -> getPositionEncoPourcentage
	 * @brief  -> renvoie la valeur en pourcentage associer à la position de l'encodeur de roue
	 * @param  -> None
	 * @return -> uint8_t
	 */
	uint8_t getPositionEncoPourcentage();

	/*
	 * @name   -> getPositionPotPourcentage
	 * @brief  -> renvoie la valeur en pourcentage associer à la position du potentiomètre
	 * @param  -> None
	 * @return -> uint8_t
	 */
	uint8_t getPositionPotPourcentage();

	/*
	 * @name   -> getPotRawPosition
	 * @brief  -> renvoie la valeur de conversion de l'adc associer à la position du potentiomètre
	 * @param  -> None
	 * @return -> uint8_t
	 */
	bool getDirectionMoteur();

	/*
	 * @name   -> getDirectionMoteur
	 * @brief  -> renvoie la direction actuel à laquelle le moteur est actuellement
	 * @param  -> None
	 * @return -> bool
	 */
	uint8_t getPotRawPosition();

	/*
	 * @name   -> getMoteurLockState
	 * @brief  -> renvoie l'état actuel du moteur (lock ou unlock)
	 * @param  -> None
	 * @return -> bool
	 */
	bool getMoteurLockState();


	//gestionMoteur

	/*
	 * @name   -> setMoteurLockState
	 * @brief  -> permet de changer l'état actuel du moteur (lock ou unlock)
	 * @param  -> state: état voulue du moteur (lock ou unlock)
	 * @return -> None
	 */
	void setMoteurLockState(bool state);

	/*
	 * @name   -> setMoteurEnableState
	 * @brief  -> permet de changer l'état actuel actuel du moteur (enable ou disable)
	 * @param  -> state: état voulue du moteur (enable ou disable)
	 * @return -> None
	 */
	void setMoteurEnableState(bool state);

	/*
	 * @name   -> setMoteurDirEtSpeed
	 * @brief  -> permet de changer la direction et la vitesse du moteur si la position physique le permet
	 * @param  -> speed: vitesse voulue
	 * 			  direction: direction voulue
	 * @return -> None
	 */
	void setMoteurDirEtSpeed(uint32_t speed, bool direction);

	/*
	 * @name   -> checkMovementLimit
	 * @brief  -> Vérifie si le moteur peut aller dans un sens ou l'autre en fonction de la position physique actuel du moteur
	 * @param  -> directionVoulue: direction que le moteur veut prendre
	 * @return -> bool
	 */
	bool checkMovementLimit(bool directionVoulue);

	//gestion Position

	/*
	 * @name   -> updatePositionPot
	 * @brief  -> fait l'acquisition d'une nouvelle valeur du potentiomètre associer
	 * @param  -> None
	 * @return -> None
	 */
	void updatePositionPot();

	//gestionPince

	/*
	 * @name   -> setDirectionPince
	 * @brief  -> set la direction que le moteur de la pince doit prendre (CW, CCW ou IDLE)
	 * @param  -> direction: direction voulue
	 * @return -> None
	 */
	void setDirectionPince(uint8_t direction);


	/*
	 * @name   -> ~GestionMouvementAxe
	 * @brief  -> destructeur de la classe
	 * @param  -> None
	 * @return -> None
	 */
	virtual ~GestionMouvementAxe();
};

#endif /* GESTIONMOUVEMENTAXE_H_ */
