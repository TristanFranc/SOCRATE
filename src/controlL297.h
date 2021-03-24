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
enum _LOCK_STATE {LOCK=0,UNLOCK=1};
enum _L297_SELECT_{L297_1=0,L297_2=1,L297_3_4=2};

class controlL297 {

	hardwareConfig *config;
	Timer *timer;

	typedef enum _DIRECTION_ _DIRECTION_ ;
	typedef enum _STEP_MODE_ MODE ;
	typedef enum _L297_SELECT_ _L297_;
	typedef enum _LOCK_STATE _STATE_;


	uint32_t speed;
	uint8_t chanel;
	_L297_ _selection;

	bool lock;
	bool enabled;
public:
	controlL297(_L297_SELECT_ selection);
	virtual ~controlL297();
	//setter
	void setSpeed(uint32_t speed);
	void setDirection(_DIRECTION_ dir);
	void setLockState(_STATE_ state);
	void setEnable(bool state);

	//getter
	uint32_t getSpeed(void);
	bool getDirection(void);
	bool getLockState(void);
	bool isEnables(void);



};

#endif /* CONTROLL297_H_ */
