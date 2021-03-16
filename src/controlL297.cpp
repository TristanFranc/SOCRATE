/*
 * controlL297.cpp
 *
 *  Created on: Mar 16, 2021
 *      Author: 201723940
 */

#include "controlL297.h"

controlL297::controlL297(_L297_SELECT_ selection)
{
	config = new hardwareConfig();
	speed = 0;// vitesse en HZ
	lock = true;// actif bas
	chopperControl = false; // voir page 3 de la datasheet du L297
	enabled = false;


	switch (selection) {
		case L297_1://master
			config->GPIO_Config(GPIOB, 3, ALTERNATE,1);

			timer = new Timer(TIM2,50000,false);
			timer->enablePWM(2,speed);
			//timer->start();
			break;
		case L297_2://master

				break;
		case L297_3: // master

				break;
		case L297_4: // slave de L297_3

				break;
	}

}

controlL297::~controlL297()
{
	if(config)
		delete config;
	if(timer)
		delete timer;
}
void controlL297::setSpeed(uint16_t speed)
{

}
void controlL297::setDirection(_DIRECTION_ dir)
{

}
void controlL297::setLockState(bool state)
{

}
void controlL297::setEnable(bool state)
{

}
uint16_t controlL297::getSpeed(void)
{

}
bool controlL297::getDirection(void)
{

}
bool controlL297::getLockState(void)
{

}
bool controlL297::isEnables(void)
{

}
