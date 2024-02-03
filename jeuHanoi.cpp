/*
 ************************************************************************************
 * Authors: salma.aghrizen@etu.univ-cotedazur.fr, bastien.briat@etu.univ-cotedazur.fr
 ************************************************************************************
 * Ce script contient la déclaration des fonctions définit dans le jeuHanoi.hpp
 */

 /*
  * Rôle: déplacer le disque de la positio origine vers la position destination
  * paramètres:
  * --> po: position d'origine
  * --> pd:position de destination
  */
#include "jeuHanoi.hpp"
#include "Disque.hpp"
#include "Tours.hpp"
#include <thread>
#include <iostream>
using namespace std;

 /*
  * Rôle: déplacer le disque de la position origine vers la position destination
  * paramètres:
  * --> po: position d'origine
  * --> pd: position de destination
  */
bool ToursHanoi::deplacer(int po, int pd) {
	bool IsMovePossible;
	Tour* orig = m_tours[po];
	Tour* dest = m_tours[pd];

	IsMovePossible = orig->MoveDisk(dest);

	return IsMovePossible;
}

/*
 * La méthode principale récursive pour le jeu du Hanoi
 * Les variables:
 * --> n: le nombre des disques
 * --> orig: la tour origine
 * --> dest: la tour de la destination
 * --> inter: la tour intérmediaire
 */
void ToursHanoi::hanoi(int n, int orig, int dest, int inter) {
    // On définit la condition de l'arrêt récursif : si n=0, la fonction se termine.
    if (n > 0) {
        // Étape 1 : Déplacer (n-1) disques de la tour d'origine à la tour intermédiaire
        hanoi(n - 1, orig, inter, dest);

        // Étape 2 : Déplacer le disque restant de la tour d'origine à la tour de destination
        deplacer(orig, dest);

        // Étape 3 : Afficher l'état actuel des tours après le déplacement
        afficherTours();

        // Étape 4 : Afficher une nouvelle représentation graphique des tours (fonction non définie)
        afficherToursNew();

        // Étape 5 : Attente de 500ms pour voir les étapes de la résolution
        SDL_Event event;
        Uint32 startTime = SDL_GetTicks();

        while (SDL_GetTicks() - startTime < 500) {
            // On vérifie les événements de SDL
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    SDL_Quit(); // Quitter l'application si l'utilisateur ferme la fenêtre
                }
            }
        }

        // Étape 6 : Déplacer (n-1) disques de la tour intermédiaire à la tour de destination
        hanoi(n - 1, inter, dest, orig);
    }
}

/*
 * Cette fonction permet de initialiser certaines variable de la classe définit dans jeuHanoi.hpp
 */
void ToursHanoi::initialiser() {
	// initialiser le premier élément de m_tours avec m_hauteur éléments avec la valeur false
	m_tours[0] = new Tour(1, m_hauteur);
	// initialiser le deuxième élément de m_tours avec m_hauteur éléments avec la valeur true
	m_tours[1] = new Tour(2);
	// initialiser le troisième élément de m_tours avec m_hauteur éléments avec la valeur true
	m_tours[2] = new Tour(3);
	m_deplacement = 0;
	
}


/*
 * Cette fonction est un constructeur de la classe ToursHanoi définit dans jeuHanoi.hpp
 * Input: un entier n
 * Rôle: initialise l'objet ToursHanoi en utilisant une hauteur spécifiée
 */
ToursHanoi::ToursHanoi(int n)
// D_MAX: nombre maximum des disques 
	: m_hauteur(n < MAX_DISQUE ? n : MAX_DISQUE) {
	if (n >= MAX_DISQUE) {
		m_hauteur = MAX_DISQUE;
	}
}

/*
 * Cette fonction a pour but d'afficher l'état actuel du jeu
*/
void ToursHanoi::afficherTours() {

	//Disque vide en cas de tour vide, on affiche un disque vide pour prendre l'espace de caractere
	Disque tempDisque = Disque(0, m_hauteur);
	// variable 's' pour construire la représentation du jeu
	string s;
	for (int i = m_hauteur - 1; i >= 0; --i) {
		if (m_tours[0]->getDisque(i) != NULL)
			s += m_tours[0]->getDisque(i)->toString();
		else
			s += tempDisque.toString();
			
		if (m_tours[1]->getDisque(i) != NULL)
			s += m_tours[1]->getDisque(i)->toString();
		else
			s += tempDisque.toString();

		if (m_tours[2]->getDisque(i) != NULL)
			s += m_tours[2]->getDisque(i)->toString();
		else
			s += tempDisque.toString();
		s += "\n";
	}
	// construction d'une chaîne de caractères '*' qui représente le socle du jeu
	s += string(47, '-'); // 6*8 - 1 = 47 pour garder toujours même taille 
						  // de socle quelque soit le nombre des disques 
	s += "\n";
	// affichage de la chaîne du jeu
	cout << s << endl;
}

/*
 * Cette fonction affiche l'état mis à jour des tours en utilisant SDL
 */
void ToursHanoi::afficherToursNew() 
{
	int SpaceBetweenTower = 20;
	int MinimumXSize = SIZE_X_GAME_BOARD / T_MAX * 0.2F;
	int MaximumXSize = SIZE_X_GAME_BOARD / T_MAX - SpaceBetweenTower * T_MAX;
	int SizeY = SIZE_Y_GAME_BOARD / m_hauteur * 0.8F;

	int SizeCurrentDisque;
	int CurentTowerCenterX;

	// Définir la couleur de dessin du rendu en noir et effacer le rendu 
	SDL_SetRenderDrawColor(myRenderer, 0, 0, 0, 255);
	SDL_RenderClear(myRenderer);

	// Itérer à travers chaque tour pour dessiner leur état actuel 
	for (int indexTower = 0; indexTower < T_MAX; indexTower++)
	{
		// Calculer la position X pour le centre de la tour actuelle 
		if (indexTower == 0)
		{
			CurentTowerCenterX = MaximumXSize / 2;
		}
		else
		{
			CurentTowerCenterX = CurentTowerCenterX + MaximumXSize + SpaceBetweenTower;
		}
		//Itérer à travers chaque disque sur la tour actuelle et le dessiner 
		for (int indexDisque = 0; indexDisque < m_hauteur; indexDisque++)
		{
			// vérifier si le disque actuel existe sur la tour 
			if (m_tours[indexTower]->getDisque(indexDisque) != NULL)
			{
				// obtenir la taille du disque actuel et appeler la fct DrawDisque
				SizeCurrentDisque = m_tours[indexTower]->getDisque(indexDisque)->getTaille();
				DrawDisque
				(
					SizeCurrentDisque, indexTower, indexDisque, MinimumXSize, MaximumXSize, SizeY, CurentTowerCenterX
				);
			}
		}
	}
	// présenter le contenu rendu à l'écran
	SDL_RenderPresent(myRenderer);

}

/*
 * Cette fonction dessine un disque sur l'écran en utilisant SDL
 */
void ToursHanoi::DrawDisque(int SizeCurrentDisque, int indexTower, int indexDisque, int MinimumXSize, int MaximumXSize, int SizeY, int CurentTowerCenterX)
{


	int DisqueSizeX = MinimumXSize + (MaximumXSize - MinimumXSize) * SizeCurrentDisque / m_hauteur;
	int DisqueXpos = CurentTowerCenterX - DisqueSizeX / 2;
	int DisqueYpos = SIZE_Y_GAME_BOARD - ( 10 + indexDisque * SizeY) - SizeY;
	
	// Déclaration des couleurs utiliser pour des disques plus claires
	// Nous avons 8 couleurs dans chaque disque a une couleur différente de l'autre 
	unsigned char   COLOR_1[3]={170,219,225};
	unsigned char	COLOR_2[3]={255,182,193};
	unsigned char	COLOR_3[3]={218,242,164};
	unsigned char	COLOR_4[3]={245,245,220};
	unsigned char	COLOR_5[3] ={200,162,200};
	unsigned char	COLOR_6[3]={219,187,255};
	unsigned char	COLOR_7[3]={222,184,135};
	unsigned char	COLOR_8[3]={255,211,210};


	switch (SizeCurrentDisque % 8)
	{
		case 0:
			CreateRect(DisqueXpos, DisqueYpos, DisqueSizeX, SizeY, COLOR_1);
			break;

		case 1:
			CreateRect(DisqueXpos, DisqueYpos, DisqueSizeX, SizeY, COLOR_2);
			break;

		case 2:
			CreateRect(DisqueXpos, DisqueYpos, DisqueSizeX, SizeY, COLOR_3);
			break;
			
		case 3:
			CreateRect(DisqueXpos, DisqueYpos, DisqueSizeX, SizeY, COLOR_4);
			break;
			
		case 4:
			CreateRect(DisqueXpos, DisqueYpos, DisqueSizeX, SizeY, COLOR_5);
			break;

		case 5:
			CreateRect(DisqueXpos, DisqueYpos, DisqueSizeX, SizeY, COLOR_6);
			break;
			
		case 6:
			CreateRect(DisqueXpos, DisqueYpos, DisqueSizeX, SizeY, COLOR_7);
			break;
		case 7:
			CreateRect(DisqueXpos, DisqueYpos, DisqueSizeX, SizeY, COLOR_8);
			break;

		default:
			CreateRect(DisqueXpos, DisqueYpos, DisqueSizeX, SizeY, COLOR_1);
		
	}


	

}

/*
 * Cette fonction crée un rectangle avec une couleur donnée en utilisant SDL
 */
void ToursHanoi::CreateRect(int posX, int posY, int sizeX, int sizeY, unsigned char Color[3])

{

	SDL_Rect rect;
	rect.x = posX;
	rect.y = posY;
	rect.w = sizeX;
	rect.h = sizeY;

	//SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(myRenderer, Color[0], Color[1], Color[2], 255);
	SDL_RenderDrawRect(myRenderer, &rect);
	SDL_RenderFillRect(myRenderer, &rect);
}


/*
 * Rôle: cette fonction permet de vérifier si le joueur a gagné
 * Output: elle retourne 'vrai' si tous les disques sont placés vers la tour de destination
 * Sinon, elle retourne 'false'
 */
bool ToursHanoi::checkWin() {
	// Si la derniere tour a atteint la hauteur max --> Tout les disques sont sur la derniee tour
	if (m_tours[2]->TourSize >= m_hauteur)
	{
		return true;
	}
	// si aucun disque maquant n'est trouvé, le joueur a gagné
	return false;
}


/*
 * Cette fonction permet d'éxecuter le jeu
*/
void ToursHanoi::resoudre() {
	initialiser();
	InitSDL(&window);
	afficherTours();
	afficherToursNew();
	
	
	hanoi(m_hauteur, 0, 2, 1);
	cout << "Nombre de deplacements = " << m_deplacement << endl;

	if (checkWin()) {
		cout << "Félicitations ^^ vous avez gangé :) !" << endl;
	}
	else {
		cout << "Vous n'avez pas gagné :( ." << endl;
	}
}

/*
 * Cette fonction exécute le jeu en permettant au joueur de jouer manuellement
 */
void ToursHanoi::jouer() {
	initialiser(); // initialiser le jeu 

	// variables pour la saisir du joueur 
	string reponse = "";
	int origine_index;
	int destination_index;
	bool IsMoveLegal;
	// Initialisation de SDL 
	InitSDL(&window);

	// boucle principale du jeu tant que le joueur n'a pas gagné
	while (checkWin() == false)
	{
		afficherToursNew();
		afficherTours();

		cout << "Choisir la colonne origine, puis la colonne destination, de 1 à 3, sans espace" << endl;
		while(reponse.size() < 1)   // attendre que le oueur saisie la réponse 
		cin >> reponse;
		// extraction des indices de la réponse du joueur 
		origine_index = reponse[0] - '0';
		destination_index = reponse[1] - '0';
		reponse = "";
		// vérifions si les indices sont valides 
		if (origine_index >= 1 && origine_index <= 3 && destination_index >= 1 && destination_index <= 3)
		{
			// vérifions si le déplacement est légal et l'effectuer si c'est le cas 
			IsMoveLegal = m_tours[origine_index - 1]->MoveDisk(m_tours[destination_index - 1]);

			if (IsMoveLegal == true)
			{
				continue;
			}
			else
			{
				//Aficher message indiquant le numéro invalide 
				cout << "Numéro de tour invalide, veuillez recommencer" << endl;
			}
		}
		else
		{
			//Aficher messsage indiquant numér invalide 
			cout << "Numéro de tour invalide, veuillez recommencer" << endl;
		}

	}



	cout << "Nombre de deplacements = " << m_deplacement << endl;

	if (checkWin()) {
		cout << "Félicitations ^^ vous avez gangé :) !" << endl;
	}
	else {
		cout << "Vous n'avez pas gagné :( ." << endl;
	}
}

/*
 * Cette fonction initialise la bibliothèque SDL
 */
unsigned char ToursHanoi::InitSDL(SDL_Window **window) {
	if (0 != SDL_Init(SDL_INIT_VIDEO)) // vérifions l'initialisation du SDL
	{
		return EXIT_FAILURE;
	}
	// Création de la fenêtre de jeu avec la taille spécifiée 
	*window = SDL_CreateWindow("SDL2", 0, 0,
		SIZE_X_GAME_BOARD, SIZE_Y_GAME_BOARD, SDL_WINDOW_SHOWN);
	if (NULL == *window)
	{
		return EXIT_FAILURE;
	}

	SDL_CreateRenderer(*window, 0, SDL_INIT_VIDEO); // créer le renderer pour la fenêtre 
	myRenderer = SDL_GetRenderer(*window); // obtenir le renderer de la fenêtre 
	return 0;
}
