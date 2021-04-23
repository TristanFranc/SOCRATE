/*
 * @file       main.cpp
 * @brief
 * @author    Tristan Franc & Justin Bélanger
 * @version    n/a
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
#include "FiltreFenetreGlissante.h"
#include "CanalEMG.h"

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

#define VITESSE_MANUEL_MOTEURS 70


//définitions
enum COMM_STATE {WAIT, RXCMD, RXPAYLOAD, VALIDATE};
enum MODE_ACTUEL:uint8_t{IDLE=0,CAPTEURS=1,MANUEL=2,CALIBRATION=3};

void initSysteme(void);
void initcommUsart3(void);
void initGestionMouvementAxe(void);
void innitCanalEMG(void);
void gestionCalibration(void);
void gestionModeManuel(void);
void gestionPid(void);

//objets
hardwareConfig *stm32F446;
Timer *cadanceComm;
Timer *timerConversionEMG;
STM32F446Usart3 *commAffichage;



CanalEMG *coudeEmg;
CanalEMG *pinceEmg;
CanalEMG *epauleEmg;

GestionMouvementAxe *coude;
GestionMouvementAxe *epaule;
GestionMouvementAxe *pince;


FiltreFenetreGlissante *filtreCoude;
FiltreFenetreGlissante *filtreEpaule;
FiltreFenetreGlissante *filtrePince;

PositionAxeEncodeur *encodeurCoude;
PositionAxeEncodeur *encodeurEpaule;


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

//variable du mode manuel
uint8_t valTargetEpaule=0;
uint8_t valTargetEpaulePrecedante=0;
uint8_t valTargetCoude=0;
uint8_t valTargetCoudePrecedante=0;
uint8_t valTargetPince =0;
uint8_t valTargetPincePrecedante=0;

uint8_t flag = 0;


int main(void) {

	initSysteme();
	initGestionMouvementAxe();
	innitCanalEMG();
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

								switch (rxPayload[1]) {
								case 100:
									valTargetEpaulePrecedante=valTargetEpaule;//conserve val précédante
									valTargetEpaule= rxPayload[2];
									break;
								case 101:
									valTargetCoudePrecedante=valTargetCoude;
									valTargetCoude= rxPayload[2];
									break;
								case 102:
									valTargetPincePrecedante=valTargetPince;
									valTargetPince = rxPayload[2];
									break;
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
		switch (modeSocrate)
		{
		case IDLE:
			coude->setMoteurLockState(0);//lock
			epaule->setMoteurLockState(0);//lock
			pince->setDirectionPince(2);// idle
			break;
		case CAPTEURS:
			gestionPid();
			break;
		case MANUEL:
			// mis à jour dees messages de position
			gestionModeManuel();

			break;
		case CALIBRATION:
			gestionCalibration();
			break;
		}

		/*************************** envoie des messages****************/
		if (serialPcPauseCompleted)
		{
			//position des axes
			for(uint8_t a=0;a<3;a++)
			{
				for(uint8_t b=0;b<6;b++)
				{
					commAffichage->write(messagePosition[a][b]);
				}
			}
			//commAffichage->write(epaule->getPotRawPosition());
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
void innitCanalEMG(void)
{
	timerConversionEMG = new Timer(TIM7,10000,true);

	coudeEmg = new CanalEMG(AXE_COUDE, 0.1,0.1,0.1);
	pinceEmg = new CanalEMG(AXE_PINCE, 0.1,0.1,0.1);
	epauleEmg = new CanalEMG(AXE_EPAULE, 0.1,0.1,0.1);

}

void initGestionMouvementAxe(void)
{

	coude = new GestionMouvementAxe(AXE_COUDE, POT_COUDE);
	epaule = new GestionMouvementAxe(AXE_EPAULE, POT_EPAULE);
	pince = new GestionMouvementAxe(AXE_PINCE, POT_PINCE);

	filtreCoude = new FiltreFenetreGlissante();
	filtreEpaule = new FiltreFenetreGlissante();
	filtrePince = new FiltreFenetreGlissante();

	//encodeurCoude = new PositionAxeEncodeur(GPIOB, NO_PIN_ENCO_COUDE, ENCO_RISING_TRIGGER); // peut être rajouter si on utilise les encodeurs éventuellement
	//encodeurEpaule = new PositionAxeEncodeur(GPIOB, NO_PIN_ENCO_EPAULE, ENCO_RISING_TRIGGER);

}
void gestionCalibration(void)
{

}
void gestionModeManuel(void)
{
	/*****************************Epaule**************************/
	if(valTargetEpaule != valTargetEpaulePrecedante)
	{

		if(valTargetEpaule < epaule->getPositionPotPourcentage())
		{
			epaule->setMoteurLockState(1);//unlock
			epaule->setMoteurDirEtSpeed(VITESSE_MANUEL_MOTEURS, 0);
			messagePosition[0][3]=(100+epaule->getPositionPotPourcentage());
		}
		else if(valTargetEpaule > epaule->getPositionPotPourcentage())
		{
			epaule->setMoteurLockState(1);//unlock
			epaule->setMoteurDirEtSpeed(VITESSE_MANUEL_MOTEURS, 1);
			messagePosition[0][3]=(100+epaule->getPositionPotPourcentage());
		}

		valTargetEpaulePrecedante = valTargetEpaule;
	}
	if((epaule->getPositionPotPourcentage()>=(valTargetEpaule-1))&&(epaule->getPositionPotPourcentage()<=(valTargetEpaule+1)))
	{
		epaule->setMoteurLockState(0);//lock
		messagePosition[0][3]=(100+epaule->getPositionPotPourcentage());
	}

	/*****************************Coude**************************/
	if(valTargetCoude != valTargetCoudePrecedante)
	{
		if(valTargetCoude <= coude->getPositionPotPourcentage())
		{
			coude->setMoteurLockState(1);//unlock
			coude->setMoteurDirEtSpeed(VITESSE_MANUEL_MOTEURS, 0);
			messagePosition[1][3]=(100+coude->getPositionPotPourcentage());
		}
		else if(valTargetCoude >= coude->getPositionPotPourcentage())
		{
			coude->setMoteurLockState(1);//unlock
			coude->setMoteurDirEtSpeed(VITESSE_MANUEL_MOTEURS, 1);
			messagePosition[1][3]=(100+coude->getPositionPotPourcentage());
		}
		valTargetCoudePrecedante=valTargetCoude;
	}
	if((coude->getPositionPotPourcentage()>=(valTargetCoude-1))&&(coude->getPositionPotPourcentage()<=(valTargetCoude+1)))
	{
		coude->setMoteurLockState(0);//lock
		messagePosition[1][3]=(100+coude->getPositionPotPourcentage());
	}
	//	/*****************************Pince**************************/
	if(valTargetPince != valTargetPincePrecedante)
	{
		if(valTargetPince <= pince->getPositionPotPourcentage())
		{
			pince->setDirectionPince(0);
			messagePosition[2][3]=(100+pince->getPositionPotPourcentage());
		}
		else if(valTargetPince >= pince->getPositionPotPourcentage())
		{
			pince->setDirectionPince(1);
			messagePosition[2][3]=(100+pince->getPositionPotPourcentage());
		}
		valTargetPincePrecedante=valTargetPince;
	}
	if((pince->getPositionPotPourcentage()>=(valTargetPince-1))&&(pince->getPositionPotPourcentage()<=(valTargetPince+1)))
	{
		pince->setDirectionPince(2);
		messagePosition[2][3]=(100+pince->getPositionPotPourcentage());
	}
	//	messagePosition[0][3]=(100+epaule->getPositionPotPourcentage());
	//	messagePosition[1][3]=(100+coude->getPositionPotPourcentage());
	//	messagePosition[2][3]=(100+pince->getPositionPotPourcentage());
}
void gestionPid(void)
{
	coudeEmg->calculPidValue(coude->getPositionPotPourcentage());
	if(coudeEmg->getErreurPidRaw() < 4)
	{
		coude->setMoteurLockState(false);
		//poignet->setMoteurLockState(false);
	}
	else
	{
		coude->setMoteurLockState(true);
		coude->setMoteurDirEtSpeed(coudeEmg->getValuePID(), coudeEmg->getDirectionMoteur());

		if(coude->getMoteurLockState())
		{
			//poignet->setMoteurDirEtSpeed(coudeEmg->getValuePID() / 3, coudeEmg->getDirectionMoteur());
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

	//usart->write(epauleEmg->getValuePID());


}
// interruptions
extern "C" void TIM7_IRQHandler(void)
{
	if (TIM7->SR & TIM_SR_UIF) // if UIF flag is set
	{
		TIM7->SR &= ~TIM_SR_UIF; // clear UIF flag

		epauleEmg->acquisitionNewPositionEmg();
		coudeEmg->acquisitionNewPositionEmg();
		pinceEmg->acquisitionNewPositionEmg();

		epaule->updatePositionPot();
		coude->updatePositionPot();
		pince->updatePositionPot();

		// filtrage des valeures de pourentage de pot à chaque foi qu'ils sont mis à jour
		//		filtreEpaule->miseNiveauFiltre(epaule->getPositionPotPourcentage());
		//		filtreCoude->miseNiveauFiltre(coude->getPositionPotPourcentage());
		//		filtrePince->miseNiveauFiltre(pince->getPositionPotPourcentage());
	}
}
extern "C" void TIM5_IRQHandler(void) {
	if (TIM5->SR & TIM_SR_UIF) // if UIF flag is set
	{
		TIM5->SR &= ~TIM_SR_UIF; // clear UIF flag
		serialPcPauseCompleted = true;

	}

}





