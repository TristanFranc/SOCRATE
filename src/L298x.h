/*
 * L298x.h
 *
 *  Created on: 8 avr. 2021
 *      Author: 201723940
 */

#ifndef L298X_H_
#define L298X_H_
#include "hardwareConfig.h"

enum _DIRECTION_PINCE_ {CW_P=0,CCW_P=1,IDLE_P=3};

class L298x
{
	hardwareConfig *config;

	typedef enum _DIRECTION_PINCE_ _DIRECTION_ ;

	uint8_t direction;

public:
	L298x();
	virtual ~L298x();
	//setter
	void setDirection(_DIRECTION_PINCE_ dir);
	//getter
	uint8_t getDirection(void);
	uint8_t isEnables(void);
};

#endif /* L298X_H_ */
