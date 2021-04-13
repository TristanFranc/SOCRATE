/*
 * FiltreFenetreGlissante.cpp
 *
 *  Created on: 8 avr. 2021
 *      Author: Justin
 */

#include "FiltreFenetreGlissante.h"

FiltreFenetreGlissante::FiltreFenetreGlissante()
{
	compteur = 0;
	filtrePositionAxe[0] = 0;
	filtrePositionAxe[1] = 0;
	filtrePositionAxe[2] = 0;

}

void FiltreFenetreGlissante::miseNiveauFiltre(uint8_t positionActuelAxe)
{
	if(compteur >  2)
	{
		compteur = 0;
	}

	filtrePositionAxe[compteur] = positionActuelAxe;
	compteur += 1;
}

uint16_t FiltreFenetreGlissante::resultatFiltre()
{
	resultatFenetre = 0;
	for(uint8_t i = 0; i < 3; i++)
	{
		resultatFenetre += filtrePositionAxe[i];

	}
	resultatFenetre = resultatFenetre/3;

	return resultatFenetre;
}

FiltreFenetreGlissante::~FiltreFenetreGlissante() {
	// TODO Auto-generated destructor stub
}

