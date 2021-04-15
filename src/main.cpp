/*
 * @file       main.cpp
 * @brief
 * @author    Tristan Franc & Justin Bélanger
 * @version    0.01
 * @date       4 mars 2019
 */

// Classes spécifiques au STM32F446
#include "stm32f4xx.h"
#include <string>


//Déclarations spécifiques au matériel
#include "hardwareConfig.h"
#include "STM32F446Usart.h"
#include "Timer_PWM.h"
#include "CanalEMG.h"
#include "Adc1Stm32f446re.h"
#include "PositionAxeEncodeur.h"
#include "GestionMouvementAxe.h"

//emplacement composant
#define AXE_EPAULE 0
#define AXE_COUDE 1
#define AXE_PINCE 2
#define POT_EPAULE 3
#define POT_COUDE 4
#define POT_PINCE 5
#define ENCO_EPAULE 6
#define ENCO_COUDE 7
#define ENCO_PINCE_MASTER 8
#define ENCO_PINCE_SLAVE 9


#define ENCO_FALLING_TRIGGER 0
#define ENCO_RISING_TRIGGER 1

#define NO_PIN_ENCO_COUDE 2
#define NO_PIN_ENCO_EPAULE 10

// Definnition de fonction
void innitSysteme(void);
void innitCanalEMG(void);
void innitComUsart3(void);
void innitGestionMouvementAxe(void);

//création emplacement Objet
hardwareConfig *stm32F446;
CanalEMG *coudeEmg;
CanalEMG *pinceEmg;
CanalEMG *epauleEmg;

GestionMouvementAxe *coude;
GestionMouvementAxe *epaule;
GestionMouvementAxe *pince;
//GestionMouvementAxe *poignet;

PositionAxeEncodeur *encodeurCoude;
PositionAxeEncodeur *encodeurEpaule;

Timer *timerConversionEMG;


STM32F446Usart3 *usart;
Timer *timerUsart;


// Variable
bool validInterruptEnco = 0;
bool serialPcPauseCompleted = 0;
uint8_t flag = 0;
uint8_t adcConversionFlag = 0;
int16_t erreur = 0;
bool direction = 0;

int main(void)
{
	innitSysteme();
	innitCanalEMG();
	innitGestionMouvementAxe();
	innitComUsart3();
	timerConversionEMG->start();
	pince->setDirectionPince(1);
	while(1)
	{
		if(flag)
		{


			coudeEmg->calculPidValue(coude->getPositionPotPourcentage());
			if(coudeEmg->getErreurPidRaw() < 4)
			{
				coude->setMoteurLockState(false);
//				poignet->setMoteurLockState(false);
			}
			else
			{
				coude->setMoteurLockState(true);
				coude->setMoteurDirEtSpeed(coudeEmg->getValuePID(), coudeEmg->getDirectionMoteur());

				if(coude->getMoteurLockState())
				{
//					poignet->setMoteurDirEtSpeed(coudeEmg->getValuePID() / 3, coudeEmg->getDirectionMoteur());
				}

			}

			pinceEmg->calculPidValue(pince->getPositionPotPourcentage());
			if(pinceEmg->getErreurPidRaw() < 1)
			{
				pince->setDirectionPince(2);
			}
			else
			{
				pince->setDirectionPince(pinceEmg->getDirectionMoteur());
			}



			epauleEmg->calculPidValue(epaule->getPositionPotPourcentage());
			if(epauleEmg->getErreurPidRaw() < 5)
			{
				epaule->setMoteurLockState(false);
			}
			else
			{
				epaule->setMoteurLockState(true);
				epaule->setMoteurDirEtSpeed(epauleEmg->getValuePID(), epauleEmg->getDirectionMoteur());

			}

			usart->write(epauleEmg->getValuePID());
			flag = 0;
		}
	}
}


/*
 * @name   -> innitSysteme
 * @brief  -> initialisation du hardware et de la clock du stm32f446re
 * @param  -> None
 * @return -> None
 */
void innitSysteme(void)
{
	stm32F446 = new hardwareConfig();
	stm32F446->SysClockConfig();
}

/*
 * @name   -> innitCanalEMG
 * @brief  -> initialisation des différents composant necessaire aux différents canalEMG
 * @param  -> None
 * @return -> None
 */
void innitCanalEMG(void)
{
	timerConversionEMG = new Timer(TIM7,20000,true);


	coudeEmg = new CanalEMG(AXE_COUDE, 0.1,0.1,0.1);
	pinceEmg = new CanalEMG(AXE_PINCE, 0.1,0.1,0.1);
	epauleEmg = new CanalEMG(AXE_EPAULE, 0.1,0.1,0.1);

}

void innitGestionMouvementAxe()
{
	coude = new GestionMouvementAxe(AXE_COUDE, POT_COUDE);
	epaule = new GestionMouvementAxe(AXE_EPAULE, POT_EPAULE);
	pince = new GestionMouvementAxe(AXE_PINCE, POT_PINCE);
	//poignet = new GestionMouvementAxe(ENCO_PINCE_MASTER, POT_COUDE);
	encodeurCoude = new PositionAxeEncodeur(GPIOB, NO_PIN_ENCO_COUDE, ENCO_RISING_TRIGGER);
	encodeurEpaule = new PositionAxeEncodeur(GPIOB, NO_PIN_ENCO_EPAULE, ENCO_RISING_TRIGGER);
}


<<<<<<< Updated upstream
	//stm32F446->GPIO_Config(GPIOA, 5, OUTPUT,2);// led activité

	stm32F446->GPIO_Config(GPIOA, 8, OUTPUT,2);
	stm32F446->GPIO_Config(GPIOA, 9, OUTPUT,2);
	stm32F446->GPIO_Pin_Enable(GPIOA, 8);
	stm32F446->GPIO_Pin_Disable(GPIOA, 9);
=======
void innitComUsart3(void)
{
	stm32F446->GPIO_Config(GPIOA, 3, OUTPUT,2);
	usart = STM32F446Usart3::getInstance();
	usart->setBaudRate(9600);
>>>>>>> Stashed changes

	timerUsart = new Timer(TIM5,10000,true);
	timerUsart->enablePWM(2,100);
	timerUsart->start();
}

/*
 * @name   -> TIM7_IRQHandler
 * @brief  -> interruption global du timer 7
 * @param  -> None
 * @return -> None
 */
extern "C" void TIM7_IRQHandler(void)
{
	if (TIM7->SR & TIM_SR_UIF) // if UIF flag is set
	{
		TIM7->SR &= ~TIM_SR_UIF; // clear UIF flag


		epauleEmg->acquisitionNewPositionEmg();
		coudeEmg->acquisitionNewPositionEmg();
		pinceEmg->acquisitionNewPositionEmg();

		coude->updatePositionPot();
		epaule->updatePositionPot();
		pince->updatePositionPot();

		flag = 1;

	}
}

extern "C" void EXTI2_IRQHandler(void)
{
	if(EXTI->PR & EXTI_PR_PR2)
	{

		validInterruptEnco = 1;

		if(validInterruptEnco)
		{
<<<<<<< Updated upstream
			rxData= commAffichage->read();
			switch (commState) {
			case WAIT:
				if(rxData=='<')
					commState=RXCMD;
				break;
			case RXCMD:
				commState=RXPAYLOAD;
				rxCnt=0;
				//rxCmd=rxData;//commande à executer
				rxPayload[rxCnt++]=rxData;
				switch (rxData) {
				case 'M':
					//mode
					rxCmd=0;
					break;
				case 'P':
					//position
					rxCmd=1;
					break;
				case 'C':
					//calibration
					rxCmd=2;
					break;
				case 'E':
					//erreure
					rxCmd=3;
					break;
				}
				break;
				case RXPAYLOAD:
					rxPayload[rxCnt++]=rxData;
					if(rxCnt>PAYLOAD_SIZE[rxCmd])
					{
						commState =VALIDATE;
					}
					break;
				case VALIDATE:
					if(rxData=='>')
					{
						//GPIOA -> ODR ^= 1<<5;// led d'activité ** dois être enlever

						switch (rxCmd) {
						case 0:
							//mode
							if(rxPayload[1]==0)
								modeSocrate=IDLE;
							if(rxPayload[1]==1)
								modeSocrate=CAPTEURS;
							if(rxPayload[1]==2)
								modeSocrate=MANUEL;
							if(rxPayload[1]==3)
								modeSocrate=CALIBRATION;

							break;

						case 1:
							//position

							break;
						case 2:
							//preset calibratin

							break;
						case 3:
							//erreure

							break;
						}

					}
					if( modeSocrate==IDLE)
							{
								testL297->setLockState(LOCK);
								testL2972->setLockState(LOCK);
								testL2973->setLockState(LOCK);
							}
							else if (modeSocrate==CAPTEURS)
							{
								testL297->setLockState(UNLOCK);
								testL2972->setLockState(LOCK);
								testL2973->setLockState(LOCK);
							}
							else if (modeSocrate==MANUEL)
							{
								testL297->setLockState(LOCK);
								testL2972->setLockState(UNLOCK);
								testL2973->setLockState(LOCK);
							}
							else if (modeSocrate==CALIBRATION)
								{
									testL297->setLockState(LOCK);
									testL2972->setLockState(LOCK);
									testL2973->setLockState(UNLOCK);
								}
					commState =WAIT;
					break;
			}
=======
			encodeurCoude->setPositionAxeNbsDent(coude->getDirectionMoteur());
			encodeurCoude->conversionNbsDentPourcentage();
			validInterruptEnco = 0;
>>>>>>> Stashed changes
		}
		encodeurCoude->clearInterruptFlag();
	}

}

extern "C" void EXTI9_5_IRQHandler(void)
{

	//PC6


}

extern "C" void EXTI15_10_IRQHandler(void)
{
	//encodeurEpaule PB10
	if(EXTI->PR & EXTI_PR_PR10)
	{
		validInterruptEnco = 1;

		if(validInterruptEnco)
		{
			encodeurEpaule->setPositionAxeNbsDent(epaule->getDirectionMoteur());
			encodeurEpaule->conversionNbsDentPourcentage();
			validInterruptEnco = 0;
		}

		encodeurEpaule->clearInterruptFlag();
	}

	//PB15
}


extern "C" void TIM5_IRQHandler(void) {
	if (TIM5->SR & TIM_SR_UIF) // if UIF flag is set
	{
		TIM5->SR &= ~TIM_SR_UIF; // clear UIF flag
		serialPcPauseCompleted = true;
	}

}
