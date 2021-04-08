/*
 * L298x.cpp
 *
 *  Created on: 8 avr. 2021
 *      Author: 201723940
 */

#include "L298x.h"

L298x::L298x() {
	//pince pas de clock ou de chanal
	//ouverture = cw
	//fermeture = ccw
	config = new hardwareConfig();
	config->GPIO_Config(GPIOA, 8, OUTPUT,2);// controle de la pince A
	config->GPIO_Config(GPIOA, 9, OUTPUT,2);// controle de la pince B

}

L298x::~L298x() {
	if(config)
		delete config;
}
void L298x::setDirection(_DIRECTION_PINCE_ dir)
{
	if(dir==CW_P)
	{
		direction=0;
		config->GPIO_Pin_Enable(GPIOA, 8);
		config->GPIO_Pin_Disable(GPIOA, 9);
	}
	else if(dir==CCW_P)
	{
		direction=1;
		config->GPIO_Pin_Enable(GPIOA, 9);
		config->GPIO_Pin_Disable(GPIOA, 8);
	}
	else if (dir==IDLE_P)
	{
		direction=2;
		config->GPIO_Pin_Disable(GPIOA, 9);
		config->GPIO_Pin_Disable(GPIOA, 8);
	}
}

uint8_t L298x::getDirection(void)
{
 return direction;
}
