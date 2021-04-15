/*
 * VecteurEMG.cpp
 *
 *  Created on: 11 mars 2021
 *      Author: Justin
 */

#include "VecteurEMG.h"

VecteurEMG::VecteurEMG()
{
	actualRobotPosition = 0;
	actualControlerPosition = 0;
}

void VecteurEMG::setActualRobotPosition(uint8_t robotPosition)
{
	this->actualRobotPosition = robotPosition;
}

uint8_t VecteurEMG::getActualRobotPosition()
{
	return this->actualRobotPosition;
}

void VecteurEMG::setActualControlerPosition(uint8_t controlerPosition)
{
	this->actualControlerPosition = controlerPosition;
}

uint8_t VecteurEMG::getActualControlerPosition()
{
	return this->actualControlerPosition;
}

VecteurEMG::~VecteurEMG() {
	// TODO Auto-generated destructor stub
}

