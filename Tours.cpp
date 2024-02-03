/*
 ************************************************************************************
 * Authors: salma.aghrizen@etu.univ-cotedazur.fr, bastien.briat@etu.univ-cotedazur.fr
 ************************************************************************************
 *
 * Ce script contient la déscription des fonctions du fichier Tours.hpp
 */

#include "Tours.hpp"
#include "Disque.hpp"
#include <iostream>

 //Tour vide
Tour::Tour(int TowerTag)
{
	TourTag = TowerTag;
	TourSize = 0;
}

//Constructeur de la classe tour, initialise la tour avec les disques 
// Tour rempli de 1 à n
Tour::Tour(int TowerTag, int n)
{
	TourTag = TowerTag; // attribuer un tag à la tour 
	TourSize = 0; // initialiser la taille de la tour à 0 

	// remplir la tour avec des disques de 1 à n
	for (int indexDisque = n; indexDisque > 0; indexDisque--)
	{
		// créer un nouveau disque avec la taille correspondante 
		Disque* tempDisque = new Disque(indexDisque, n);
		// ajouter le disque à la liste des disques dans l'ordre 
		ListeDisqueInOrder.push_back(tempDisque);
		TourSize++;
	}
}

/**
  Accesseur au disque k
  @param[in] k - numero du disque
  @return disque k
*/
Disque* Tour::getDisque(long unsigned k)
{
	if (ListeDisqueInOrder.size() > k)
	{
		return ListeDisqueInOrder.at(k);
	}
	else
	{
		return NULL;
	}
}

/**
  Accesseur a l'indice du sommet
  @return indice du sommet
*/
bool Tour::MoveDisk(Tour *TourDestination)
{
	if (ListeDisqueInOrder.empty() == true)
		return true;

	Disque* myTopDisk = ListeDisqueInOrder.back();
	bool DidItSuccess;
	DidItSuccess = TourDestination->AddDisk(myTopDisk);
	//Si on a réussi à déplacer le disque
	if (DidItSuccess)
	{
		//Supprime le disque de la tour actuelle
		ListeDisqueInOrder.pop_back();
		TourSize--;
	}
	return DidItSuccess;
}

/**
  Met un disque au sommet du pilier
  @param[in] d - un Disque
*/
bool Tour::AddDisk(Disque *newDisque)
{

	if (ListeDisqueInOrder.empty() == false)
	{
		//Obtient le dernier element 
		Disque* TopDisque = ListeDisqueInOrder.back();

		//Regarde si on a le droit d'ajouter le disque
		if (TopDisque->getTaille() > newDisque->getTaille())
		{
			ListeDisqueInOrder.push_back(newDisque);
			TourSize++;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		ListeDisqueInOrder.push_back(newDisque);
		TourSize++;
		return true;
	}
	return false;
	
}
