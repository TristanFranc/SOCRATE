
//Déclarations spécifiques au matériel
#include "hardwareConfig.h"
#include "Timer_PWM.h"



// Classes spécifiques au STM32F446
#include "stm32f4xx.h"



hardwareConfig *stm32F446;
Timer *timerTest;



int main(void) {

	stm32F446 = new hardwareConfig();

	stm32F446->SysClockConfig();
	stm32F446->GPIO_Config(GPIOA,5,OUTPUT);

	timerTest = new Timer(TIM4, 20000, false);
	stm32F446->GPIO_Config(GPIOB,6,ALTERNATE,2);// met pbs en modee pwm
	timerTest->enablePWM(1,100,100);
	timerTest->setPeriod(10000);
	timerTest->start();
	while(1)
	{

		GPIOA->BSRRH |= (1<<5);// set PA5
		GPIOA->BSRRL |= (1<<5);// reset PA5
	}
}

/**
 * Gestionnaire pour l'interruption du timer 5
 */



