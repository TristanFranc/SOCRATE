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

//calis

// Classes spécifiques au STM32F446
#include "stm32f4xx.h"

#include <string>

volatile bool serialPcPauseCompleted = false;
enum COMM_STATE {WAIT, RXCMD, RXPAYLOAD, VALIDATE};
hardwareConfig *stm32F446;
Timer *timerTest;
Timer * timerTest1;
Timer * timertest2;
STM32F446Usart3 *testUsart;
controlL297 *testL297;
controlL297 *testL2972;
controlL297 *testL2973;
controlL297 *testL2974;
char tab[7]= {'<','F','u','c','k','>'};
std::string message= "<Fuck>";
COMM_STATE commState=WAIT;
uint8_t rxData=0;
uint16_t rxCnt=0;
uint8_t rxCmd=0;
const uint16_t PAYLOAD_SIZE[2]={3,10};
uint16_t rxPayload[15];
int main(void) {

	stm32F446 = new hardwareConfig();

	stm32F446->SysClockConfig();


	//testL297 = new controlL297(L297_2);
	//testL2972 = new controlL297(L297_1);
	//testL2973 = new controlL297(L297_3_4);


	//testL297->setSpeed(1000);
	//testL2972->setSpeed(1000);
	//testL2973->setSpeed(1000);


	//testL297->setEnable(true);
	//testL2972->setEnable(true);
	//testL2973->setEnable(true);


	//testL297->setDirection(CCW);
	//testL2972->setDirection(CCW);
	//testL2973->setDirection(CW);

//
//	testL297->setLockState(UNLOCK);
//	testL2972->setLockState(UNLOCK);
//	testL2973->setLockState(UNLOCK);






	stm32F446->GPIO_Config(GPIOA, 5, OUTPUT,2);// led activité

	testUsart = STM32F446Usart3::getInstance();
	testUsart->setBaudRate(9600);
	timerTest = new Timer(TIM5,10000,true);
	timerTest->enablePWM(2,100);

	timerTest->start();




	while(1)
	{

		while(testUsart->dataAvailable())
		{
			rxData= testUsart->read();
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
				break;
			case RXPAYLOAD:
				rxPayload[rxCnt++]=rxData;
				if(rxCnt>2)
					commState =VALIDATE;
				break;
			case VALIDATE:
				if(rxData=='>')
				{
					GPIOA -> ODR ^= 1<<5;// led d'activité


				}
				commState =WAIT;
				break;
			}
		}
		if (serialPcPauseCompleted)
		{

			testUsart->write(tab);

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





