/*
 * PositionAxeEncodeur.h
 *
 *  Created on: 22 mars 2021
 *      Author: Justin
 */

#include <stdint-gcc.h>
#include "Encodeur.h"

#ifndef POSITIONAXEENCODEUR_H_
#define POSITIONAXEENCODEUR_H_



#define NBS_TOTAL_DENT_COUDE 113
#define NBS_TOTAL_DENT_EPAULE 120

#define NO_PIN_EPAULE 10
#define NO_PIN_COUDE 3

#define MOTEUR_HORAIRE 0 		// soustraction
#define MOTEUR_ANTIHORAIRE 1	// addition

#define NBS_TOTAL_DENT_COUDE 113
#define NBS_TOTAL_DENT_EPAULE 120


extern "C"
{
void EXTI2_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);
}

class PositionAxeEncodeur
{
private:

	friend void EXTI2_IRQHandler(void);
	friend void EXTI9_5_IRQHandler(void);
	friend void EXTI15_10_IRQHandler(void);

	Encodeur *encodeur;

	uint8_t positionAxePourcentage;
	uint8_t positionAxeNoDent;
	bool directionMoteur;
	bool validInterrupt;

	uint8_t PositionAxePourcentage;
	bool direction;

	uint8_t noPin;
public:

	PositionAxeEncodeur(GPIO_TypeDef *gpioPort, uint8_t noPin, uint8_t trigger);


	void conversionNbsDentPourcentage();

	void setPositionPourcentage(uint8_t positionPourcentage);
	uint8_t getPositionPourcentage();

	void setPositionAxeNbsDent(uint8_t directionMoteur);

	uint8_t getNoPin();

	bool getDirectionMoteur();

	void clearInterruptFlag();

	void innitEncodeur(GPIO_TypeDef *gpioPort, uint8_t noPin, uint8_t trigger);
	void conversionDegrePourcentage();
	void setPositionPourcentage(uint8_t positionPourcentage);
	void getPositionPourcentage();

	virtual ~PositionAxeEncodeur();
};

#endif /* POSITIONAXEENCODEUR_H_ */
