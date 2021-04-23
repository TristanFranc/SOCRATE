/*
 * @file    -> Timer_PWM.h
 * @author  -> Tristan Franc
 * @version -> 0.01
 * @Created -> 11 mars 2021
 * @brief   -> classe qui permet de configurer les timer 1,2,3,4,5,7 et de configurer leurs divers onctions et modes
 */
#ifndef TIMER_PWM_H_
#define TIMER_PWM_H_

#include <stdint-gcc.h>
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"


class Timer
{
	TIM_TypeDef * timer;
public:
	/*
	 * Constructeur
	 */
	Timer(TIM_TypeDef * tmr, uint32_t us,bool interruptEnable);
	/*
	 * Destructeur
	 */
	virtual ~Timer(){};
	/**
	 * Configure la période du timer en us
	 * @param La période du timer en us (de 2 à 65535000 us)
	 */
	void setPeriod(uint32_t us);
	/**
	 * Active le PWM sur un canal avec une fréquence et une étendue
	 * Il faudra configurer le GPIO pour avoir le signal en sortie
	 * @param ch Le canal visé
	 * @param freq La fréquence du PWM en Hz.(Défaut à 10kHz)
	 * @param range Étentue du PWM. (Défaut à 255).
	 */
	void enablePWM(uint8_t ch, uint32_t freq=10000, uint16_t range = 255);
	/**
	 * Ajuste la durée à haut du signal PWM
	 * @param ch Canal visé
	 * @param lvl La durée du niveau haut.
	 *        Pour un duty cycle de 50% sur une étendue de 8 bits (255) lvl = 128.
	 */
	void setPWMLvl(uint8_t ch, uint16_t lvl);
	/**
	 * Démarre le timer
	 */
	void start();
	/**
	 * Arrêt du timer
	 */
	void stop();
};

#endif /* TIMER_PWM_H_ */
