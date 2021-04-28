/*
 * @file    -> Encodeur.h
 * @author  -> Justin Bélanger
 * @version -> 0.01
 * @Created -> 23 mars 2021
 * @brief 	-> Classe qui crée et gere les interruption relier à en encodeur de roue
 */

#include "stm32f4xx.h"
#include <stdint-gcc.h>

#ifndef ENCODEUR_H_
#define ENCODEUR_H_

#define FALLING_EDGE_TRIGGER 0
#define RISING_EDGE_TRIGGER 1
#define RISIN_FALLING_EDGE_TRIGGER 2


#define SYSCFG_EXTI_PB 1
#define SYSCFG_EXTI_PC 2



class Encodeur
{
private:

	uint8_t noPin;

public:

	/*
	 * @name   -> Encodeur
	 * @brief  -> constructeur de la classe Encodeur
	 * @param  -> gpioPort: port sur lequel la pin de trigger sera
	 * 			  noPin:	pin sur laquelle le trigger sera
	 * 			  trigger:	type de trigger voulue (rissing ou falling edge)
	 * @return -> None
	 */
	Encodeur(GPIO_TypeDef *gpioPort, uint8_t noPin, uint8_t trigger);

	/*
	 * @name   -> innitExternalInterupt
	 * @brief  -> innitialise l'interruption à trigger externe sur le port et al pin voulue avec le bon type de trigger
	 * @param  -> gpioPort: port sur lequel la pin de trigger sera
	 * 			  noPin:	pin sur laquelle le trigger sera
	 * 			  trigger:	type de trigger voulue (rissing ou falling edge)
	 * @return -> None
	 */
	void innitExternalInterupt(GPIO_TypeDef *gpioPort, uint8_t noPin, uint8_t trigger);

	/*
	 * @name   -> clearInterruptFlag
	 * @brief  -> clear le flag du registre EXTI_PR (Necessaire après chaque interruption)
	 * @param  -> None
	 * @return -> None
	 */
	void clearInterruptFlag();

	/*
	 * @name   -> ~Encodeur
	 * @brief  -> destructeur de la classe
	 * @param  -> None
	 * @return -> None
	 */
	virtual ~Encodeur();
};

#endif /* ENCODEUR_H_ */
