/*
 * @file    -> Adc1Stm32f446re.h
 * @author  -> Justin Bélanger
 * @version -> 0.01
 * @Created -> 16 mars 2021
 * @brief 	-> Classe permetttant la création et la gestion de différent channel de l'adc1
 * 			   du stm32f446re
 */

#include "Adc1Stm32f446re.h"


/*
 * @name   -> Adc1Stm32f446re
 * @brief  -> Constructeur de la classe
 * @param  -> noAxe: numéro de l'axe à auxquel l'adc sera associer
 * @return -> none
 */
Adc1Stm32f446re::Adc1Stm32f446re(uint8_t noAxe)
{
	this->noAxe = noAxe;
	nbsTotalConversionADC = 1;

	//Config ADC axe 0	(Épaule)
	configFonctionnementADC[0][0] = 'A';               			//GPIO à activer
	configFonctionnementADC[0][1] = GPIO_MODER_MODER2; 			//no de la pin MODER à activer en mode analogique
	configFonctionnementADC[0][2] = 1;                 			//no de l'ADC à activer
	configFonctionnementADC[0][3] = 2;							//no du channel à activer
	configFonctionnementADC[0][4] = 1;							//position dans la chaine de conversion
	configFonctionnementADC[0][5] = 8;							//nbs de bit de Résolution
	configFonctionnementADC[0][6] = CHANNEL_SAMPLING_TIME_84;	//Channel sampling time

	//Config ADC axe 1 (Coude)
	configFonctionnementADC[1][0] = 'A';               			//GPIO à activer
	configFonctionnementADC[1][1] = GPIO_MODER_MODER0; 			//no de la pin MODER à activer en mode analogique
	configFonctionnementADC[1][2] = 1;                 			//no de l'ADC à activer
	configFonctionnementADC[1][3] = 0;							//no du channel à activer
	configFonctionnementADC[1][4] = 1;							//position dans la chaine de conversion
	configFonctionnementADC[1][5] = 8;							//nbs de bit de Résolution
	configFonctionnementADC[1][6] = CHANNEL_SAMPLING_TIME_84;	//Channel sampling time

	//Config ADC axe 2 (Pince)
	configFonctionnementADC[2][0] = 'A';               			//GPIO à activer
	configFonctionnementADC[2][1] = GPIO_MODER_MODER1; 			//no de la pin MODER à activer en mode analogique
	configFonctionnementADC[2][2] = 1;                 			//no de l'ADC à activer
	configFonctionnementADC[2][3] = 1;							//no du channel à activer
	configFonctionnementADC[2][4] = 1;							//position dans la chaine de conversion
	configFonctionnementADC[2][5] = 8;							//nbs de bit de Résolution
	configFonctionnementADC[2][6] = CHANNEL_SAMPLING_TIME_84;	//Channel sampling time

	//Config potentiometre épaule
	configFonctionnementADC[3][0] = 'A';               			//GPIO à activer
	configFonctionnementADC[3][1] = GPIO_MODER_MODER5; 			//no de la pin MODER à activer en mode analogique
	configFonctionnementADC[3][2] = 1;                 			//no de l'ADC à activer
	configFonctionnementADC[3][3] = 5;							//no du channel à activer
	configFonctionnementADC[3][4] = 1;							//position dans la chaine de conversion
	configFonctionnementADC[3][5] = 8;							//nbs de bit de Résolution
	configFonctionnementADC[3][6] = CHANNEL_SAMPLING_TIME_84;	//Channel sampling time

	//Config potentiometre coude
	configFonctionnementADC[4][0] = 'A';               			//GPIO à activer
	configFonctionnementADC[4][1] = GPIO_MODER_MODER4; 			//no de la pin MODER à activer en mode analogique
	configFonctionnementADC[4][2] = 1;                 			//no de l'ADC à activer
	configFonctionnementADC[4][3] = 4;							//no du channel à activer
	configFonctionnementADC[4][4] = 1;							//position dans la chaine de conversion
	configFonctionnementADC[4][5] = 8;							//nbs de bit de Résolution
	configFonctionnementADC[4][6] = CHANNEL_SAMPLING_TIME_84;	//Channel sampling time


	//Config potentiometre pince
	configFonctionnementADC[5][0] = 'A';               			//GPIO à activer
	configFonctionnementADC[5][1] = GPIO_MODER_MODER6; 			//no de la pin MODER à activer en mode analogique
	configFonctionnementADC[5][2] = 1;                 			//no de l'ADC à activer
	configFonctionnementADC[5][3] = 6;							//no du channel à activer
	configFonctionnementADC[5][4] = 1;							//position dans la chaine de conversion
	configFonctionnementADC[5][5] = 8;							//nbs de bit de Résolution
	configFonctionnementADC[5][6] = CHANNEL_SAMPLING_TIME_84;	//Channel sampling time

	innitADC();
	enableADC();
	ADC1->SR &= ~ADC_SR_EOC;
	ADC1->SR &= ~ADC_SR_OVR;

}


/*
 * @name   -> innitADC
 * @brief  -> Initialise tout les registre necessaire aux fonctionnement de l'ADC
 * @param  -> none
 * @return -> none
 */
void Adc1Stm32f446re::innitADC()
{

	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;					//Act de la clock sur l'adc
	setGPIO();											//seeting du GPIO demander

	ADC->CCR |= ADC_CCR_ADCPRE_0;						//Set prescaler clock ADC
	ADC1->CR1 |= ADC_CR1_SCAN;							//Scan mode

	setResolution(configFonctionnementADC[noAxe][5]);	// Bit Résolution

	//	ADC1->CR2 |= ADC_CR2_CONT;	 						//Mode conversion continue
	ADC1->CR2 &= ~(ADC_CR2_CONT);						//Mode single
	ADC1->CR2 |= ADC_CR2_EOCS;							// Flag EOC après chaque conversion

	ADC1->CR2 &= ~ADC_CR2_ALIGN; 						//Alignement registre à droite

	setADCConversionNbsCycle(); //sampling time par cycle

	ADC1->SQR1 &= ~(0b1111 << 20); 	// remise à zéro  du nbs de conversion
	ADC1->SQR1 |= 0 << 20;			//nbs total de conversion
	setChannelPositioningQueue(configFonctionnementADC[noAxe][3],configFonctionnementADC[noAxe][4]);

}

/*
 * @name   -> setGPIO
 * @brief  -> Initialise la clock sur le GPIO voulue et la met en analog la pin associer au channel de l'adc voulue
 * @param  -> none
 * @return -> none
 */
void Adc1Stm32f446re::setGPIO()
{
	if (configFonctionnementADC[noAxe][0] == 'A' )
	{
		RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN); //activation de la clock sur GPIOA
		GPIOA->MODER |= configFonctionnementADC[noAxe][1]; //mise en mode analog de la pin voulu
		GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR0 << (configFonctionnementADC[0][3] * 2);
	}

	if (configFonctionnementADC[noAxe][0] == ('B' || 'b'))
	{
		RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOBEN); //activation de la clock sur GPIOB
		GPIOB->MODER |= configFonctionnementADC[noAxe][1];//mise en mode analog de la pin voulu
	}

	else if (configFonctionnementADC[noAxe][0] == ('C' || 'c'))
	{
		RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOCEN); //activation de la clock sur GPIOC
		GPIOC->MODER |= configFonctionnementADC[noAxe][1];//mise en mode analog de la pin voulu
	}
}


/*
 * @name   -> setResolution
 * @brief  -> Initialise la résolution de la conversion de l'ADC choisie
 * @param  -> resolution
 * @return -> none
 */
void Adc1Stm32f446re::setResolution(uint8_t resolution)
{
	switch(resolution)
	{
	case 6:
		ADC1->CR1 |= ADC_CR1_RES_1;
		ADC1->CR1 |= ADC_CR1_RES_0;
		break;

	case 8:
		ADC1->CR1 |= ADC_CR1_RES_1;
		ADC1->CR1 &= ~ADC_CR1_RES_0;
		break;

	case 10:
		ADC1->CR1 |= ADC_CR1_RES_1;
		ADC1->CR1 &= ~ADC_CR1_RES_0;
		break;

	case 12:
		ADC1->CR1 &= ~ADC_CR1_RES_0;
		ADC1->CR1 &= ADC_CR1_RES_1;
		break;
	}
}

/*
 * @name   -> setChannelPositioningQueue
 * @brief  -> Met à la bonne position dans la chaîne de conversion normal le channel de l'adc
 * @param  -> noChannel: Numéro du channel à positionner
 * 			  queuePosition: position dans la queue de conversion normal
 * @return -> none
 */
void Adc1Stm32f446re::setChannelPositioningQueue(uint8_t noChannel, uint8_t queuePosition)
{
	//	//Gestion de la position du channel dans la chaine de conversion
	if(queuePosition < 7)
	{
		ADC1->SQR3 &= ~(ADC_SQR3_SQ1 << ((queuePosition-1)*5));
		ADC1->SQR3 |= (noChannel << ((queuePosition-1)*5));
	}

	if(queuePosition > 6 && queuePosition < 13)
	{
		ADC1->SQR2 &= ~(ADC_SQR2_SQ7 << ((queuePosition-1)*5));
		ADC1->SQR2 |= (noChannel << ((queuePosition-1)*5));
	}

	if(queuePosition > 12 && queuePosition < 17)
	{
		ADC1->SQR1 &= ~(ADC_SQR1_SQ13 << ((queuePosition - 1)*5));
		ADC1->SQR1 |= (noChannel << ((queuePosition - 1)*5));
	}
}

/*
 * @name   -> setADCConversionNbsCycle
 * @brief  -> initialise le nombre de cycle par conversion
 * @param  -> none
 * @return -> none
 */
void Adc1Stm32f446re::setADCConversionNbsCycle()
{
	if(configFonctionnementADC[noAxe][4] < 10)
	{
		ADC1->SMPR2 |= configFonctionnementADC[noAxe][6] << (configFonctionnementADC[noAxe][3] * 3);  //Channel sampling time
	}

	if((configFonctionnementADC[noAxe][4] < 19) && (configFonctionnementADC[noAxe][4] > 9))
	{
		ADC1->SMPR1 |= configFonctionnementADC[noAxe][6] << ((configFonctionnementADC[noAxe][3] - 9) * 3);  //Channel sampling time
	}
}


/*
 * @name   -> getConversion
 * @brief  -> renvoie la valeur de la dernière conversion faite pas l'adc
 * @param  -> none
 * @return -> uint16: valeur de la dernière conversion faite pas l'adc
 */
uint16_t Adc1Stm32f446re::getConversion()
{
	return ADC1->DR;
}

/*
 * @name   -> enableADC
 * @brief  -> Active l'adc
 * @param  -> none
 * @return -> none
 */
void Adc1Stm32f446re::enableADC()
{
	ADC1->CR2 |= ADC_CR2_ADON;  //enable ADON

	uint32_t delay = 10000; //Wait for ADC to stabillize
	while(delay--);
}

/*
 * @name   -> desactivateADC
 * @brief  -> Désactive l'adc
 * @param  -> none
 * @return -> none
 */
void Adc1Stm32f446re::desactivateADC()
{

	ADC1->CR2 &= ~ADC_CR2_ADON;
}

/*
 * @name   -> startAdcConversion
 * @brief  -> démarre la conversion de l'adc
 * @param  -> none
 * @return -> none
 */
void Adc1Stm32f446re::startAdcConversion()
{
	setChannelPositioningQueue(configFonctionnementADC[this->noAxe][3],1);
	ADC1->CR2 |= ADC_CR2_SWSTART;
}

/*
 * @name   -> waitEocFlag
 * @brief  -> Flag de fin de conversion de l'adc
 * @param  -> none
 * @return ->
 */
uint8_t Adc1Stm32f446re::waitEocFlag()
{
	uint32_t delay = 10000; //Wait for ADC to stabillize
	while(!(ADC1->SR & (1 << 1)) || !delay)
	{
		delay--;
	}

	if(!delay)
		return 0;
	else
		return 1;
}

/*
 * @name   -> clearEocFlag
 * @brief  -> remise à zéro du flag de fin de conversion de l'adc
 * @param  -> none
 * @return -> none
 */
void Adc1Stm32f446re::clearEocFlag()
{
	ADC1->SR &= ~ADC_SR_EOC;
	ADC1->SR &= ~ADC_SR_OVR;
}

/*
 * @name   -> stopAdcConversion
 * @brief  -> Arrête la conversion de l'adc
 * @param  -> none
 * @return -> none
 */
void Adc1Stm32f446re::stopAdcConversion()
{
	ADC1->CR2 &= ~ADC_CR2_SWSTART;
}

/*
 * @name   -> ~Adc1Stm32f446re
 * @brief  -> destructeur de la classe
 * @param  -> none
 * @return -> none
 */
Adc1Stm32f446re::~Adc1Stm32f446re() {
	// TODO Auto-generated destructor stub
}

