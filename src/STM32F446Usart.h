/*
 * @file    -> STM32F446Usart.h
 * @author  -> Tristan Franc basé sur le manuel de référance du stm32 f446re
 * Lien:(https://www.st.com/resource/en/reference_manual/dm00135183-stm32f446xx-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf)
 * *** parties du code adapté de Marc Juneau (marcjuneau@gmail.com)
 * @version -> 0.02
 * @Created -> 12 mars 2021
 * @brief   -> Classe singelton qui permet de faire la gestion du port de communication USART3 en mode asyncrone.
 * la classe fait usage de la template BuffFifo pour conserver les données à envoyer et recu en mémoire avant leur traitement/envoie.
 *
 *      Procédure : (proviens de la datasheet)
 * 1. Enable the USART by writing the UE bit in USART_CR1 register to 1.
 * 2. Program the M bit in USART_CR1 to define the word length.
 * 3. Program the number of stop bits in USART_CR2.
 * 4. Select DMA enable (DMAT) in USART_CR3 if Multi buffer Communication is to take
 *    place. Configure the DMA register as explained in multibuffer communication.
 * 5. Select the desired baud rate using the USART_BRR register.
 * 6. Set the TE bit in USART_CR1 to send an idle frame as first transmission.
 * 7. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
 *    for each data to be transmitted in case of single buffer.
 * 8. After writing the last data into the USART_DR register, wait until TC=1. This indicates
 *    that the transmission of the last frame is complete. This is required for instance when
 *    the USART is disabled or enters the Halt mode to avoid corrupting the last
 *    transmission.
 */

#ifndef STM32F446USART_H_
#define STM32F446USART_H_

#include "stm32f4xx.h"
#include "hardwareConfig.h"
#include "templateBufferComm.h"


// Déclaration du gestionnaire d'interruption en mode C pour éviter la modification du nom.
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
	/*
	 * @brief  -> le gestionaire d'interruption est ami pour simplifier la manipulation des données recu et envoyée
	 */
	friend void USART3_IRQHandler(void);
	/*
	 * @brief  -> Constructeur de la classe STM32F446Usart3. Le constructeur est privée pour éviter la création d'autres instances de STM32F446Usart3
	 */
	STM32F446Usart3();
public:
	/**
	 * @brief -> getInstance retourne le pointeur de l'instance de ce singleton.
	 * si une instance n'existe pas, cette fonction vas aussi créer linstance avant de rla retourner.
	 * @return pointeur de l'instance
	 */
	static STM32F446Usart3 * getInstance();
	/*
	 * @brief -> destructeur de STM32F446Usart3
	 */
	virtual ~STM32F446Usart3();
	/*
	 * @brief  -> fonction qui permet d'ajouter un char non signé au buffer d'envoie
	 * @param  -> uint8_t à ajouter
	 */
	void write(uint8_t data);
	/*
	 * @brief  -> fonction qui permet d'ajouter une séquance de char au buffer d'envoie
	 * @param  -> pointeur de la séquance à ajouter au buffer
	 */
	void write( char *string);
	/*
	 * @brief  -> fonction qui permet d'ajouter une séquance de char au buffer d'envoie
	 * @param  -> pointeur de la séquance à ajouter au buffer
	 */
	void write( const char *string);
	/*
		 * @brief  -> fonction qui permet de récupérer les valeures reçu sur le port série
		 * @return -> valeure reçu
		 */
	uint8_t read(void);
	/*
	 * @brief  -> fonction qui permet de vérifier si une valeure à été reçu au port série
	 * @return -> bool qui indique si une valeure à été reçu
	 */
	bool dataAvailable() const;
	/*
	 * @brief  -> fonction qui permet de change la cadance d'envoie du port série
	 * @param  -> bauderate est la cadance d'envoie
	 */
	void setBaudRate(uint32_t baudrate);


};

#endif /* STM32F446USART_H_ */
