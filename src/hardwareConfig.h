/*
 * hardwareConfig.h
 *
 *  Created on: Mar 10, 2021
 *      Author: Tristan Franc
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
	hardwareConfig();
	virtual ~hardwareConfig();

	void SysClockConfig(void);
	void GPIO_Config(GPIO_TypeDef* gpio, uint8_t pin, _IO_MODES_t mode,
			uint8_t alterFunction=0);
	void GPIO_Pin_Enable(GPIO_TypeDef* gpio, uint8_t pin);
	void GPIO_Pin_Disable(GPIO_TypeDef* gpio, uint8_t pin);
};

#endif /* HARDWARECONFIG_H_ */
