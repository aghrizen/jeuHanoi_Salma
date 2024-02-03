/*
 ************************************************************************************
 * Authors: salma.aghrizen@etu.univ-cotedazur.fr, bastien.briat@etu.univ-cotedazur.fr
 ************************************************************************************
 * Ce script contient la déclaration de la classe ToursHanoi
 */

#include <SDL2/SDL.h>
#include "Tours.hpp"
const int T_MAX = 3; // le nombre MAX des tours
class ToursHanoi
{
public:
	void jouer(); // fonction pour jouer le jeu
	void resoudre(); //fonction pour résoudre automatiquement le jeu
	explicit ToursHanoi(int n); //constructeur explicite avec le nombre initial de disques 
private:
	// fonction pour effectuer le déplacement des disques 
	bool deplacer(int o, int d);
	// fonction pour vérifier si le joueur a gagné ou pas 
	bool checkWin();
	// fonction récursive pour résoudre l'algorithme du jeu
	void hanoi(int n, int orig, int dest, int inter);
	// fonction pour afficher l'état actuel des tours 
	void afficherTours();
	// pour afficher l'état mis à jour des tours:
	void afficherToursNew();
	// pour initialiser le jeu 
	void initialiser();
	// pour déssiner un disque sur l'écran 
	void DrawDisque(int SizeCurrentDisque, int indexTower, int indexDisque, int MinimumXSize, int MaximumXSize, int SizeY, int CurentTowerCenterX);
	// pour créer un rectangle qui représente un disque 
	void CreateRect(int posX, int posY, int sizeX, int sizeY, unsigned char Color[3]);
	unsigned char InitSDL(SDL_Window **window);

	// la taille de la fenêtre du jeu 
	const int SIZE_X_GAME_BOARD = 1536/2;
	const int SIZE_Y_GAME_BOARD = 864/2;

	

	// les directions possibles:
	enum direction
	{
		LEFT = 1,
		DOWN = 2,
		UP = 3,
		RIGHT = 4,
		ENTER = 5,

	};

	// pointeur vers la fenêtre et le renderer SDL
	SDL_Window *window = NULL;
	SDL_Renderer *myRenderer;
	Tour* m_tours[T_MAX]; // les tours
	int m_hauteur; // nombre de disques
	
	int m_deplacement; // nombre de deplacements
};
