/*
 * controlL297.h
 *
 *  Created on: Mar 16, 2021
 *      Author: Tristan Franc
 */

#ifndef CONTROLL297_H_
#define CONTROLL297_H_

#include "Timer_PWM.h"
#include "hardwareConfig.h"

enum _DIRECTION_ {CW=0,CCW=1};
enum _STEP_MODE_ {HALF=0,FULL=1};
enum _L297_SELECT_{L297_1=0,L297_2=1,L297_3=2,L297_4=3};

class controlL297 {

	hardwareConfig *config;
	Timer *timer;

	typedef enum _DIRECTION_ _DIRECTION_ ;
	typedef enum _STEP_MODE_ MODE;
	typedef enum _L297_SELECT_ _L297_;

	uint32_t speed;
	bool lock;
	bool enabled;
	bool chopperControl;
public:
	controlL297(_L297_SELECT_ selection);
	virtual ~controlL297();
	//setter
	void setSpeed(uint16_t speed);
	void setDirection(_DIRECTION_ dir);
	void setLockState(bool state);
	void setEnable(bool state);
	//getter
	uint16_t getSpeed(void);
	bool getDirection(void);
	bool getLockState(void);
	bool isEnables(void);



};

#endif /* CONTROLL297_H_ */
