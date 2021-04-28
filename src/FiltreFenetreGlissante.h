/*
 * @file    -> FiltreFenetreGlissante.h
 * @author  -> Justin Bélanger
 * @version -> 0.01
 * @Created -> 8 avr. 2021
 * @brief   -> Classe qui crée et fait la gestion d'un filtre de type fenêtre glissante
 */

#ifndef FILTREFENETREGLISSANTE_H_
#define FILTREFENETREGLISSANTE_H_
#include "stm32f4xx.h"

class FiltreFenetreGlissante
{
private:
	uint8_t compteur;
	uint8_t filtrePositionAxe[3];
	uint16_t resultatFenetre;
public:

	/*
	 * @name   -> FiltreFenetreGlissante
	 * @brief  -> Constructeur de la classe
	 * @param  -> None
	 * @return -> None
	 */
	FiltreFenetreGlissante();

	/*
	 * @name   -> miseNiveauFiltre
	 * @brief  -> Met à jours les valeur à l'intérieur du filtre de la même façons qu'une pile FIFO
	 * @param  -> positionActuelAxe: Nouvelle valeur à insérer dans le filtre
	 * @return -> None
	 */
	void miseNiveauFiltre(uint8_t positionAxeActuel);

	/*
	 * @name   -> resultatFiltre
	 * @brief  -> calcul la moyenne de toute les valeur présente dans le filtre
	 * @param  -> None
	 * @return -> None
	 */
	uint16_t resultatFiltre();

	/*
	 * @name   -> ~FiltreFenetreGlissante
	 * @brief  -> destructeur de la classe
	 * @param  -> None
	 * @return -> None
	 */
	virtual ~FiltreFenetreGlissante();
};

#endif /* FILTREFENETREGLISSANTE_H_ */
