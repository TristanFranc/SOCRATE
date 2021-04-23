/*
 * @file    -> hardwareConfig.h
 * @author  -> Tristan Franc basé sur le manuel de référance du stm32 f446re
 * Lien:(https://www.st.com/resource/en/reference_manual/dm00135183-stm32f446xx-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf)
 * @version -> 0.01
 * @Created -> Mar 10, 2021
 * @brief   -> gère l'initialisation de base pour assurer le fonctionnement de base du nucleo. permet aussi de faire la configuration des IO.
 * @Warning ->****dois être la première chose appeler dans le main.
 */
#ifndef HARDWARECONFIG_H_
#define HARDWARECONFIG_H_

#include "stm32f4xx.h"

#define PLL_M 4
#define PLL_N 180
#define PLL_P 0// dois être shifter à la bonne position 16 das le registre RCC_pll

enum _IO_MODES_ {INPUT=0,OUTPUT=1,ALTERNATE=2,ANALOG=3};

class hardwareConfig
{
public:
	typedef enum _IO_MODES_ _IO_MODES_t;
	/*
	 * @brief  -> Constructeur de le calsse hardwareConfig
	 */
	hardwareConfig();
	/*
	 * @brief  -> destructeur de le calsse hardwareConfig
	 */
	virtual ~hardwareConfig();
	/*
	 * @brief  -> fonction qui fait l'initialisatiion de la clock du stm32 f446re
	 * cette fonction dois toujours être appeler en premier après l'a création d'un objet hardwareConfig
	 */
	void SysClockConfig(void);
	/*
	 * @brief  ->  foction qui qui permet de configurer le mode de fonctionnement des broches du stm32 f446re
	 * @param  -> gpio est le le GPIO qui sera modifiert. pin est la broche du gpio ciblé. mode est le mode d'opération voulu.
	 * alterFunction est utilisé pour définire les mode de fonctionnement alternatifs si il ya lieux.
	 */
	void GPIO_Config(GPIO_TypeDef* gpio, uint8_t pin, _IO_MODES_t mode,
			uint8_t alterFunction=0);
	/*
	 * @brief  -> fonction qui permet d'activer une broche quand elle est en mode output
	 * @param  -> gpio est le Gpio qu'on veut affecter et pin est la brochr ciblé
	 */
	void GPIO_Pin_Enable(GPIO_TypeDef* gpio, uint8_t pin);
	/*
	 * @brief  -> fonction qui permet desactiver une broche quand elle est en mode output
	 * @param  -> gpio est le Gpio qu'on veut affecter et pin est la brochr ciblé
	 */
	void GPIO_Pin_Disable(GPIO_TypeDef* gpio, uint8_t pin);
};

#endif /* HARDWARECONFIG_H_ */
