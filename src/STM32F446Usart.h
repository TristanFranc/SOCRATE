/*
 * STM32F446Usart.h
 *
 *  Created on: 12 mars 2021
 *      Author: 201723940
 *      Procédure : (proviens de la datasheet)
 *      Procedure:
1. Enable the USART by writing the UE bit in USART_CR1 register to 1.
2. Program the M bit in USART_CR1 to define the word length.
3. Program the number of stop bits in USART_CR2.
4. Select DMA enable (DMAT) in USART_CR3 if Multi buffer Communication is to take
place. Configure the DMA register as explained in multibuffer communication.
5. Select the desired baud rate using the USART_BRR register.
6. Set the TE bit in USART_CR1 to send an idle frame as first transmission.
7. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
for each data to be transmitted in case of single buffer.
8. After writing the last data into the USART_DR register, wait until TC=1. This indicates
that the transmission of the last frame is complete. This is required for instance when
the USART is disabled or enters the Halt mode to avoid corrupting the last
transmission.
 *
 */

#ifndef STM32F446USART_H_
#define STM32F446USART_H_

#include "stm32f4xx.h"
#include "hardwareConfig.h"
#include "templateBufferComm.h"


// D�claration du gestionnaire d'interruption en mode C pour �viter la modification du nom.
extern "C"
{
	void USART3_IRQHandler(void);
}

class STM32F446Usart3 {

	bool isTransmitting;
	BuffFifo<uint32_t,64> buffRx;
	BuffFifo<uint32_t,64> buffTx;
	hardwareConfig *config;
	static STM32F446Usart3 *instance;

	friend void USART3_IRQHandler(void);
	// constructeur privé
	STM32F446Usart3();
public:

	static STM32F446Usart3 * getInstance();

	virtual ~STM32F446Usart3();

	void write(uint8_t data);
	void write( char *string);
	void write( const char *string);
	uint8_t read(void);
	bool dataAvailable() const;
	void setBaudRate(uint32_t baudrate);


};

#endif /* STM32F446USART_H_ */
