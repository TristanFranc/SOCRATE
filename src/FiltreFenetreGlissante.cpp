/*
 * @file    -> FiltreFenetreGlissante.cpp
 * @author  -> Justin Bélanger
 * @version -> 0.01
 * @Created -> 8 avr. 2021
 * @brief   -> Classe qui crée et fait la gestion d'un filtre de type fenêtre glissante
 */

#include "FiltreFenetreGlissante.h"

/*
 * @name   -> FiltreFenetreGlissante
 * @brief  -> Constructeur de la classe
 * @param  -> None
 * @return -> None
 */
FiltreFenetreGlissante::FiltreFenetreGlissante()
{
	compteur = 0;
	filtrePositionAxe[0] = 0;
	filtrePositionAxe[1] = 0;
	filtrePositionAxe[2] = 0;

}

/*
 * @name   -> miseNiveauFiltre
 * @brief  -> Met à jours les valeur à l'intérieur du filtre de la même façons qu'une pile FIFO
 * @param  -> positionActuelAxe: Nouvelle valeur à insérer dans le filtre
 * @return -> None
 */
void FiltreFenetreGlissante::miseNiveauFiltre(uint8_t positionActuelAxe)
{
	if(compteur >  2)
	{
		compteur = 0;
	}

	filtrePositionAxe[compteur] = positionActuelAxe;
	compteur += 1;
}

/*
 * @name   -> resultatFiltre
 * @brief  -> calcul la moyenne de toute les valeur présente dans le filtre
 * @param  -> None
 * @return -> None
 */
uint16_t FiltreFenetreGlissante::resultatFiltre()
{
	resultatFenetre = 0;
	for(uint8_t i = 0; i < 3; i++)
	{
		resultatFenetre += filtrePositionAxe[i];

	}
	resultatFenetre = resultatFenetre / 3;

	return resultatFenetre;
}


/*
 * @name   -> ~FiltreFenetreGlissante
 * @brief  -> destructeur de la classe
 * @param  -> None
 * @return -> None
 */
FiltreFenetreGlissante::~FiltreFenetreGlissante() {
	// TODO Auto-generated destructor stub
}

