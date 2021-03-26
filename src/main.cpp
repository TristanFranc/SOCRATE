/*
 * @file       main.cpp
 * @brief
 * @author    Tristan Franc & Justin Bélanger
 * @version    0.01
 * @date       4 mars 2019
 */

//Déclarations spécifiques au matériel
#include "hardwareConfig.h"
#include "Timer_PWM.h"
#include "STM32F446Usart.h"
#include "controlL297.h"



// Classes spécifiques au STM32F446
#include "stm32f4xx.h"
//classes standares
#include <string>
//définitions
enum COMM_STATE {WAIT, RXCMD, RXPAYLOAD, VALIDATE};
enum MODE_ACTUEL:uint8_t{IDLE=0,CAPTEURS=1,MANUEL=2,CALIBRATION=3};
//objets
hardwareConfig *stm32F446;
Timer *cadanceComm;
STM32F446Usart3 *commAffichage;
controlL297 *testL297;
controlL297 *testL2972;
controlL297 *testL2973;
controlL297 *testL2974;
//communication
//volatiles
volatile bool serialPcPauseCompleted = false;
char messagePosition[6]= {'<','P',100,200,'>'};
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

	stm32F446 = new hardwareConfig();

	stm32F446->SysClockConfig();

	testL297= new controlL297(L297_1);
	testL2972= new controlL297(L297_2);
	testL2973= new controlL297(L297_3_4);

	testL297->setSpeed(100);
	testL2972->setSpeed(100);
	testL2973->setSpeed(100);

	testL297->setDirection(CW);
	testL2972->setDirection(CW);
	testL2973->setDirection(CW);

	testL297->setEnable(true);
	testL2972->setEnable(true);
	testL2973->setEnable(true);


	testL297->setLockState(LOCK);
	testL2972->setLockState(LOCK);
	testL2973->setLockState(LOCK);//pb12 cause des problemes

	stm32F446->GPIO_Config(GPIOA, 5, OUTPUT,2);// led activité

	commAffichage = STM32F446Usart3::getInstance();
	commAffichage->setBaudRate(9600);
	cadanceComm = new Timer(TIM5,10000,true);
	cadanceComm->enablePWM(2,100);

	cadanceComm->start();




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
						GPIOA -> ODR ^= 1<<5;// led d'activité ** dois être enlever

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
		}
		if (serialPcPauseCompleted)
		{

			//commAffichage->write(messageComm[1].c_str());
			commAffichage->write(messagePosition);
			//commAffichage->write(messageCalibration);
			serialPcPauseCompleted = false;
		}


	}
}
extern "C" void TIM5_IRQHandler(void) {
	if (TIM5->SR & TIM_SR_UIF) // if UIF flag is set
	{
		TIM5->SR &= ~TIM_SR_UIF; // clear UIF flag
		serialPcPauseCompleted = true;

	}

}





