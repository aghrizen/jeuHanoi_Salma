/*
 ************************************************************************************
 * Authors: salma.aghrizen@etu.univ-cotedazur.fr, bastien.briat@etu.univ-cotedazur.fr
 ************************************************************************************
 */
// pour éviter la double inclusion:
#ifndef TOUR_CLASS
#define TOUR_CLASS
#include <string>
#include "Disque.hpp"
using namespace std;
#include <vector>
#include <random>

const int MAX_DISQUE = 8; // Le nombre max des disques pour le jeu 
class Tour {
public:
	Tour(int TowerTag);
	Tour(int TowerTag, int n);
	int TourTag;
	int TourSize;
	bool MoveDisk(Tour* TourDestination);
	bool AddDisk(Disque* Disque);
	Disque* getDisque(long unsigned k);

private:
	//Liste de nos disques sur la Tour (dans l'ordre)
	vector <Disque*> ListeDisqueInOrder;
	// L'indice de notre sommet
	int top_index;
};
#endif
