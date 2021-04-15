/*
 * FiltreFenetreGlissante.h
 *
 *  Created on: 8 avr. 2021
 *      Author: Justin
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
	FiltreFenetreGlissante();

	void miseNiveauFiltre(uint8_t positionAxeActuel);
	uint16_t resultatFiltre();

	virtual ~FiltreFenetreGlissante();
};

#endif /* FILTREFENETREGLISSANTE_H_ */
