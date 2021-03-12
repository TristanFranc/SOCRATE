/*
 * STM32F446Usart.cpp
 *
 *  Created on: 12 mars 2021
 *      Author: 201723940
 */

#include "STM32F446Usart.h"



STM32F446Usart3::STM32F446Usart3()
{
	config = new hardwareConfig();
	//active la clk du gpio B et du usart 3
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;//(1<<18)
	RCC->APB1ENR |= RCC_AHB1ENR_GPIOBEN;


	//mode alternatif pour pb10 et 11
	config->GPIO_Config(GPIOB, 10, ALTERNATE, 2);
	config->GPIO_Config(GPIOB, 11 , ALTERNATE, 2);
	GPIOB->AFR[0] |= (7<<8); // registre af7 fction alternative USART3
	GPIOB->AFR[0] |= (7<<12);

	//sélection du baud 8N1 @9600
	USART3->CR1 &= ~USART_CR1_UE;// usart disable
	NVIC_EnableIRQ(USART3_IRQn);
	NVIC_SetPriority(USART3_IRQn,3);
	//active le tx et rx + les interruptions dee chaqu'un
	USART3->CR1 |=  USART_CR1_TE | USART_CR1_RE |  USART_CR1_RXNEIE | USART_CR1_TXEIE;
	setBaudRate(9600);
	USART3->CR1 |= USART_CR1_UE; //usart enable


	isTransmitting = false;
}

STM32F446Usart3::~STM32F446Usart3()
{
	if (instance)
		delete instance;
	if(config)
		delete config;
}
STM32F446Usart3 * STM32F446Usart3::getInstance()
{
	if(instance==0)
		instance=new STM32F446Usart3();
	return instance;
}
void STM32F446Usart3::write(uint8_t data)
{
	buffTx.add(data);
	if(!isTransmitting)
	{
		isTransmitting =true;
		USART3->CR1 |= USART_CR1_TXEIE;
	}
}
void STM32F446Usart3::write(char *data)
{

}
uint8_t STM32F446Usart3:: read(void)
{

}
bool STM32F446Usart3::dataAvailable() const
{

}
void STM32F446Usart3::setBaudRate(uint32_t baudrate)
{
	if(baudrate > 2810000)
		USART3->CR1 |= USART_CR1_OVER8;
	else
		USART3->CR1 &= ~USART_CR1_OVER8;

	USART3->BRR |= (SystemCoreClock>>2) / baudrate;
}
