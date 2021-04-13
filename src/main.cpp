/*
 * @file       main.cpp
 * @brief
 * @author    Tristan Franc & Justin Bélanger
 * @version    0.01
 * @date       4 mars 2019
 */


//branche justin
// branche tristan



//Déclarations spécifiques au matériel
// Classes spécifiques au STM32F446
#include "stm32f4xx.h"
//classes standares
#include <string>
#include "hardwareConfig.h"
#include "Timer_PWM.h"
#include "STM32F446Usart.h"
#include "controlL297.h"
#include "L298x.h"
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




//définitions
enum COMM_STATE {WAIT, RXCMD, RXPAYLOAD, VALIDATE};
enum MODE_ACTUEL:uint8_t{IDLE=0,CAPTEURS=1,MANUEL=2,CALIBRATION=3};

void initSysteme(void);
void initcommUsart3(void);
void initGestionMouvementAxe(void);

//objets
hardwareConfig *stm32F446;
Timer *cadanceComm;
Timer *timerConversionEMG;
STM32F446Usart3 *commAffichage;
//L298x *testL298;

GestionMouvementAxe *coude;
GestionMouvementAxe *epaule;
GestionMouvementAxe *pince;



//communication

volatile bool serialPcPauseCompleted = false;

char messagePosition[3][6]={{'<','P',100,100,'>'}, {'<','P',101,100,'>'},{'<','P',102,100,'>'}};
char messageCalibration[7] =	{'<','C','A','L',100,'>'};
std::string messageComm[2]= {"<ACK>","<ERR>"};
COMM_STATE commState=WAIT;
MODE_ACTUEL modeSocrate = IDLE;
uint8_t rxData=0;
uint16_t rxCnt=0;
uint8_t rxCmd=0;
const uint16_t PAYLOAD_SIZE[4]={1,2,3,10};
uint16_t rxPayload[15];





int main(void) {

	initSysteme();
	initGestionMouvementAxe();
	initcommUsart3();
	timerConversionEMG->start();


	//testL298= new L298x();

	while(1)
	{

		while(commAffichage->dataAvailable())
		{
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
						//GPIOA -> ODR ^= 1<<5;// led d'activité ** dois être enlever dans code final

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
							if(modeSocrate==MANUEL)
							{
								if(coude->getPositionPotPourcentage()<rxPayload[2])
								{
									coude->setMoteurDirEtSpeed(100, 1);
								}
							}
							break;
						case 2:
							//preset calibratin

							break;
						case 3:
							//erreure

							break;
						}

					}

					commState =WAIT;
					break;
			}
		}
		/********************Gestion du Menu*****************************/
		switch (modeSocrate) {
		case IDLE:

			break;
		case CAPTEURS:

			break;
		case MANUEL:
			// mis à jour dees messages de position
			messagePosition[0][3]=(100+epaule->getPositionPotPourcentage());
				messagePosition[1][3]=(100+coude->getPositionPotPourcentage());
				messagePosition[2][3]=(100+pince->getPositionPotPourcentage());

			break;
		case CALIBRATION:

			break;
		}

		/*************************** envoie des messages****************/
		if (serialPcPauseCompleted)
		{

			for(int a=0;a<3;a++)
			{
				for(int b=0;b<6;b++)
				{
					commAffichage->write(messagePosition[a][b]);
				}
			}

			serialPcPauseCompleted = false;
		}

	}
}
void initSysteme(void)
{
	stm32F446 = new hardwareConfig();
	stm32F446->SysClockConfig();
}
void initcommUsart3(void)
{
	commAffichage = STM32F446Usart3::getInstance();
	commAffichage->setBaudRate(9600);
	cadanceComm = new Timer(TIM5,10000,true);
	cadanceComm->enablePWM(2,100);
	cadanceComm->start();
}
void initGestionMouvementAxe(void)
{
	timerConversionEMG = new Timer(TIM7,10000,true);

	coude = new GestionMouvementAxe(AXE_COUDE, POT_COUDE);
	epaule = new GestionMouvementAxe(AXE_EPAULE, POT_EPAULE);
	pince = new GestionMouvementAxe(AXE_PINCE, POT_PINCE);
	//encodeurCoude = new PositionAxeEncodeur(GPIOB, NO_PIN_ENCO_COUDE, ENCO_RISING_TRIGGER); // peut être rajouter si on utilise les encodeurs éventuellement
	//encodeurEpaule = new PositionAxeEncodeur(GPIOB, NO_PIN_ENCO_EPAULE, ENCO_RISING_TRIGGER);

}
// interruptions
extern "C" void TIM7_IRQHandler(void)
{
	if (TIM7->SR & TIM_SR_UIF) // if UIF flag is set
	{
		TIM7->SR &= ~TIM_SR_UIF; // clear UIF flag

		coude->updatePositionPot();
		epaule->updatePositionPot();
		pince->updatePositionPot();
	}
}
extern "C" void TIM5_IRQHandler(void) {
	if (TIM5->SR & TIM_SR_UIF) // if UIF flag is set
	{
		TIM5->SR &= ~TIM_SR_UIF; // clear UIF flag
		serialPcPauseCompleted = true;

	}

}





