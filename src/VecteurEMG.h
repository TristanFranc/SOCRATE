/*
 * VecteurEMG.h
 *
 *  Created on: 11 mars 2021
 *      Author: Justin
 */


#include <stdint-gcc.h>

#ifndef VECTEUREMG_H_
#define VECTEUREMG_H_

class VecteurEMG
{
private:
	uint8_t actualRobotPosition;
	uint8_t actualControlerPosition;
public:
	VecteurEMG();
	void setActualRobotPosition(uint8_t robotPosition);
	uint8_t getActualRobotPosition();

	void setActualControlerPosition(uint8_t controlerPosition);
	uint8_t getActualControlerPosition();
	virtual ~VecteurEMG();
};

#endif /* VECTEUREMG_H_ */
