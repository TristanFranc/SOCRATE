/*
 * @file    -> Adc1Stm32f446re.h
 * @author  -> Justin Bélanger
 * @version -> 0.01
 * @Created -> 16 mars 2021
 * @brief 	-> Classe permetttant la création et la gestion de différent channel de l'adc1
 * 			   du stm32f446re
 */
#include "stm32f4xx.h"
#include "Timer_PWM.h"

#ifndef ADC1STM32F446RE_H_
#define ADC1STM32F446RE_H_

//
#define TIMER_CORE_CLOCK 8000000

//Valeur par défault pour registre SMPx de ADC_SMPRx
#define CHANNEL_SAMPLING_TIME_3 0
#define CHANNEL_SAMPLING_TIME_15 1
#define CHANNEL_SAMPLING_TIME_28 2
#define CHANNEL_SAMPLING_TIME_56 3
#define CHANNEL_SAMPLING_TIME_84 4
#define CHANNEL_SAMPLING_TIME_112 5
#define CHANNEL_SAMPLING_TIME_144 6
#define CHANNEL_SAMPLING_TIME_480 7


class Adc1Stm32f446re
{
private:
	uint8_t noAxe;
	uint8_t nbsTotalConversionADC;
	uint32_t configFonctionnementADC[6][7];

public:

	/*
	 * @name   -> Adc1Stm32f446re
	 * @brief  -> Constructeur de la classe
	 * @param  -> noAxe: numéro de l'axe à auxquel l'adc sera associer
	 * @return -> none
	 */
	Adc1Stm32f446re(uint8_t noAxe);

	/*
	 * @name   -> innitADC
	 * @brief  -> Initialise tout les registre necessaire aux fonctionnement de l'ADC
	 * @param  -> none
	 * @return -> none
	 */
	void innitADC();

	/*
	 * @name   -> setGPIO
	 * @brief  -> Initialise la clock sur le GPIO voulue et la met en analog la pin associer au channel de l'adc voulue
	 * @param  -> none
	 * @return -> none
	 */
	void setGPIO();

	/*
	 * @name   -> setResolution
	 * @brief  -> Initialise la résolution de la conversion de l'ADC choisie
	 * @param  -> resolution
	 * @return -> none
	 */
	void setResolution(uint8_t resolution);

	/*
	 * @name   -> setChannelPositioningQueue
	 * @brief  -> Met à la bonne position dans la chaîne de conversion normal le channel de l'adc
	 * @param  -> noChannel: Numéro du channel à positionner
	 * 			  queuePosition: position dans la queue de conversion normal
	 * @return -> none
	 */
	void setChannelPositioningQueue(uint8_t noChannel, uint8_t queuePosition);

	/*
	 * @name   -> setADCConversionNbsCycle
	 * @brief  -> initialise le nombre de cycle par conversion
	 * @param  -> none
	 * @return -> none
	 */
	void setADCConversionNbsCycle();

	/*
	 * @name   -> getConversion
	 * @brief  -> renvoie la valeur de la dernière conversion faite pas l'adc
	 * @param  -> none
	 * @return -> uint16: valeur de la dernière conversion faite pas l'adc
	 */
	uint16_t getConversion();

	/*
	 * @name   -> enableADC
	 * @brief  -> Active l'adc
	 * @param  -> none
	 * @return -> none
	 */
	void enableADC();

	/*
	 * @name   -> desactivateADC
	 * @brief  -> Désactive l'adc
	 * @param  -> none
	 * @return -> none
	 */
	void desactivateADC();

	/*
	 * @name   -> startAdcConversion
	 * @brief  -> démarre la conversion de l'adc
	 * @param  -> none
	 * @return -> none
	 */
	void startAdcConversion();

	/*
	 * @name   -> waitEocFlag
	 * @brief  -> Flag de fin de conversion de l'adc
	 * @param  -> none
	 * @return ->
	 */
	uint8_t waitEocFlag();

	/*
	 * @name   -> clearEocFlag
	 * @brief  -> remise à zéro du flag de fin de conversion de l'adc
	 * @param  -> none
	 * @return -> none
	 */
	void clearEocFlag();

	/*
	 * @name   -> stopAdcConversion
	 * @brief  -> Arrête la conversion de l'adc
	 * @param  -> none
	 * @return -> none
	 */
	void stopAdcConversion();

	/*
	 * @name   -> ~Adc1Stm32f446re
	 * @brief  -> destructeur de la classe
	 * @param  -> none
	 * @return -> none
	 */
	virtual ~Adc1Stm32f446re();
};

#endif /* ADC1STM32F446RE_H_ */
