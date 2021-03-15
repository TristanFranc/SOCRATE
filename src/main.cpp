/*
 * @file       main.cpp
 * @brief
 * @author    Tristan Franc & Justin Bélanger
 * @version    0.01
 * @date       4 mars 2019
 */

//Déclarations spécifiques au matériel
#include "hardwareConfig.h"
#include "Timer_PWM.h"
#include "STM32F446Usart.h"

//calis

// Classes spécifiques au STM32F446
#include "stm32f4xx.h"

#include <string>

 volatile bool serialPcPauseCompleted = false;

hardwareConfig *stm32F446;
Timer *timerTest;
STM32F446Usart3 *testUsart;

char tab[7]= {'<','F','u','c','k','>'};
std::string message= "<Fuck>";
int main(void) {

	stm32F446 = new hardwareConfig();

	stm32F446->SysClockConfig();

	stm32F446->GPIO_Config(GPIOA, 5, OUTPUT,2);

	testUsart = STM32F446Usart3::getInstance();
	testUsart->setBaudRate(9600);
	timerTest = new Timer(TIM5,50000,true);
	timerTest->enablePWM(2, 40000, 100);

	timerTest->start();


	//timerTest = new Timer(TIM4, 50000, false);
	//stm32F446->GPIO_Config(GPIOB,6,ALTERNATE,2);// met pbs en modee pwm
	//timerTest->enablePWM(1,100);
	//timerTest->start();

	while(1)
	{

		//GPIOA->BSRRH |= (1<<5);// set PA5
		//GPIOA->BSRRL |= (1<<5);// reset PA5

		if (serialPcPauseCompleted)
		{
			//testUsart->write('<');
			//testUsart->write('T');
			//testUsart->write('>');
			//testUsart->write(tab);
			testUsart->write(tab);

			serialPcPauseCompleted = false;
		}
		if(testUsart->read()=='T')
		{
			GPIOA->ODR ^= 1<<5;
			//GPIOA->BSRRL |= (1<<5);// reset PA5
			//GPIOA->BSRRH |= (1<<5);// set PA5

		}
	}
}
extern "C" void TIM5_IRQHandler(void) {
	if (TIM5->SR & TIM_SR_UIF) // if UIF flag is set
	{
		TIM5->SR &= ~TIM_SR_UIF; // clear UIF flag
		serialPcPauseCompleted = true;

	}

}





