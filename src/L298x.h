/*
 * @file    -> L298x.h
 * @author  -> Tristan Franc
 * @version -> n/a
 * @Created -> 8 avr. 2021
 * @brief     -> Classe qui permet de contrôler un L298 configuré en pont en H
 */
#ifndef L298X_H_
#define L298X_H_
#include "hardwareConfig.h"

enum _DIRECTION_PINCE_ {CW_P=0,CCW_P=1,IDLE_P=3};

class L298x
{
	hardwareConfig *config;

	typedef enum _DIRECTION_PINCE_ _DIRECTION_ ;

	uint8_t direction;

public:
	/*
	 * @brief  -> constructteur de la classe L298x
	 */
	L298x();
	/*
	 * @brief  -> destructeur de la classe L298x
	 */
	virtual ~L298x();
	//setter
	/*
	 * @brief  -> constructteur de la classe L298x
	 * @param  -> variable de type _DIRECTION_PINCE_ qui détermine l'état et la direction du moteur controllé par le l298.
	 * ( horaire = 0, antihorraire= 1, idle= 3)
	 */
	void setDirection(_DIRECTION_PINCE_ dir);
	//getter
	/*
	 * @brief  -> donne la direction/état du moteur controllé par le l298
	 * @return -> ( horaire = 0, antihorraire= 1, idle= 3)
	 */
	uint8_t getDirection(void);


};

#endif /* L298X_H_ */
