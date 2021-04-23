/*
 * @file    -> controlL297.h
 * @author  -> Tristan FRanc
 * @version -> n/a
 * @Created ->  Mar 16, 2021
 * @brief     -> Classe qui permet de contrôller les modules L297 de manière individuelle
 */

#ifndef CONTROLL297_H_
#define CONTROLL297_H_
#include "Timer_PWM.h"
#include "hardwareConfig.h"

enum _DIRECTION_ {CW=0,CCW=1};
enum _STEP_MODE_ {HALF=0,FULL=1};
enum _LOCK_STATE {LOCK=0,UNLOCK=1};
enum _L297_SELECT_{L297_1=0,L297_2=1,L297_3_4=2};

class controlL297 {

	hardwareConfig *config;
	Timer *timer;

	typedef enum _DIRECTION_ _DIRECTION_ ;
	typedef enum _STEP_MODE_ MODE ;
	typedef enum _L297_SELECT_ _L297_;
	typedef enum _LOCK_STATE _STATE_;


	uint32_t speed;
	uint8_t chanel;
	_L297_ _selection;

	bool lock;
	bool enabled;
public:
	/*
	 * @brief  -> Constructeur de la classe  controlL297 qui permet de
	 * contrôler tout les modules L297
	 * de la carte mère de socrate
	 * @param  -> prends en parametre une valeure de type _L297_SELECT_ propre à cette classe.
	 * ceci permet de distinguer quelle module est contrôlé
	 */
	controlL297(_L297_SELECT_ selection);
	/*
	 * @brief  -> destructeur de la calsse controlL297
	 */
	virtual ~controlL297();
	//setter
	/*
	 * @brief  -> permet de modifier la vitesse des moteurs
	 * @param  -> une valeure de 32 bit son signé qui déterminera la fréquance du pwm qui sera envoyé au moteur en Hz.
	 */
	void setSpeed(uint32_t speed);
	/*
	 * @brief  -> détermine la direction du moteur controlL297
	 * @param  -> prends un parametree ue variable de type _DIRECTION_ qui indique si le oteur ira dans le sense
	 * horraire ou anti horraire
	 */
	void setDirection(_DIRECTION_ dir);
	/*
	 * @brief  -> cette fonction détermine si un moteur est verouillé ou non. si le moteur est verouillé,
	 * il s'opposera aux déplacements exercé par des forces externes(le moteur restera dans sa positiin actuelle.
	 * @param  -> prends une variable de type _LOCK_STATE qui détermine si le moteur est LOCK ou UNLOCK
	 */
	void setLockState(_STATE_ state);
	/*
	 * @brief  -> cette fonction détermine si le moteur est dans un état actif ou non, quand le moteur est inactif.
	 * quand le moteur est inactif, il est possible de repositioner les moteurs sans résistance des mteurs.
	 * auterment le moteeur est en mouvement ou verouillé.
	 * @param  -> bool qui détermine si le moteur est actif ou non
	 */
	void setEnable(bool state);


	//getter
	uint32_t getSpeed(void);
	/*
	 * @brief  -> recupere la vitesse actuelle du moteur
	 * @return -> vitesse du moteur en Hz
	 */
	bool getDirection(void);
	/*
	 * @brief  -> recupere la direction actuelle du moteur
	 * @return -> horaire = 0 antihorraire =1
	 */
	bool getLockState(void);
	/*
	 * @brief  -> fourni l'état du moteur
	* @return -> enable=1 disable = 0
	 */
	bool isEnables(void);



};

#endif /* CONTROLL297_H_ */
