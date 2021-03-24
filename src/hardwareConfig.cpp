/*
 * hardwareConfig.cpp
 *
 *  Created on: Mar 10, 2021
 *      Author: 201723940
 */

#include "hardwareConfig.h"

hardwareConfig::hardwareConfig() {

}

hardwareConfig::~hardwareConfig() {

}
// gère l'initialisation de base pour assurer le fonctionnement de base du nucle
//****dois être la première chose appeler dans le main.
void hardwareConfig::SysClockConfig(void)
{
	// active le hse
	RCC->CR = RCC_CR_HSEON;
	//attendre que le cristal soit activer
	while(!(RCC->CR & RCC_CR_HSERDY));

	//set le power enable et le regulateur de tension
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	PWR->CR |= PWR_CR_VOS; // corresponds à la valeure reset "11"

	// configuration du flash
	FLASH->ACR |= FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN |FLASH_ACR_LATENCY_5WS;

	// configuration des prescalers
	//AHB PR
	RCC->CFGR|= RCC_CFGR_HPRE_DIV1;

	//APB1
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4; //division par 4

	//APB1
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2; //division par 4

	//configuration du pll
	RCC->PLLCFGR =(PLL_M << 0) |(PLL_N << 6) | (PLL_P << 16) | (RCC_PLLCFGR_PLLSRC_HSE);

	// activerle pll et attendre qu'il soit pret
	RCC->CR |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY));

	//Sélectionner la source de la clock (pll dans ce cas ci)
	RCC-> CFGR |= RCC_CFGR_SW_PLL;
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}

//Permet de configurer facilement les modes de chaques io
void hardwareConfig::GPIO_Config(GPIO_TypeDef* gpio, uint8_t pin, _IO_MODES_t mode,
		uint8_t alterFunction)
{
	if (gpio == GPIOA)
		RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN);
	if (gpio == GPIOB)
		RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOBEN);
	if (gpio == GPIOC)
		RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOCEN);

	if (pin < 16)
	gpio->MODER |= mode << (2 * pin);

	if (mode == ALTERNATE) {
		if (pin < 8)
			gpio->AFR[0] |= (alterFunction << (4 * pin));
		else
			gpio->AFR[1] |= (alterFunction << (4 * (pin - 8)));
	}

}
void hardwareConfig::GPIO_Pin_Enable(GPIO_TypeDef* gpio, uint8_t pin)
{
	if (gpio == GPIOA)
		GPIOA->ODR |= 1<<pin;
	if (gpio == GPIOB)
		GPIOB->ODR |= 1<<pin;
	if (gpio == GPIOC)
		GPIOC->ODR |= 1<<pin;
}
void hardwareConfig::GPIO_Pin_Disable(GPIO_TypeDef* gpio, uint8_t pin)
{
	if (gpio == GPIOA)
		GPIOA -> ODR &= (~1<<pin);
	if (gpio == GPIOB)
		GPIOB -> ODR &= (~1<<pin);
	if (gpio == GPIOC)
		GPIOC -> ODR &= (~1<<pin);
}






