
//Déclarations spécifiques au matériel
#include "hardwareConfig.h"




// Classes spécifiques au STM32F446
#include "stm32f4xx.h"


hardwareConfig *stm32F446;




int main(void) {

	stm32F446 = new hardwareConfig();
	stm32F446->SysClockConfig();
	stm32F446->GPIO_Config(GPIOA,5,OUTPUT);

	while(1)
	{

		GPIOA->BSRRH |= (1<<5);// set PA5
		GPIOA->BSRRL |= (1<<5);// reset PA5
	}
}

/**
 * Gestionnaire pour l'interruption du timer 5
 */



