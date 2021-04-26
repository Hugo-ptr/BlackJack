/*!
*  \file carte.h
*  \author Hugo Pointereau <pointereau@eisti.eu>
*  \version 0.1
*  \date 15/12/2020
*  \brief fonctions sur les cartes ainsi que la structure
*/
#ifndef CARTE_H_
#define CARTE_H_
/* Inclusion des entêtes de librairies */
#include <stdlib.h>
#include <stdio.h>
#include "Saisie.h"

enum couleur{pique,trefle,carreau,coeur};
/*! \def carte
 *  Structure pour définir une carte
 */
struct carte{
  int int_pos;
  int int_val;
  enum couleur cart_coul;
};
/*! \def joueur
 *  Structure pour définir un joueur
 */
struct joueur {
  int mise;
  char* nom;
  struct carte* main;
  int valeur;
  int nbcartes;
  int etat;
};

/*!
\fn void inittab(carte* deck, int taille)
\brief initialise le deck de carte
\author Hugo Pointereau <pointereau@eisti.eu>
\param deck: le paquet de carte
\param taill: la taille du paquet de carte
\version 0.1
\date 15/12/2020
*/
void inittab(struct carte* deck, int taille);
/*!
\fn void initjeu(struct joueur* jeu, int taille)
\brief initialise le jeu
\param jeu: le tableau de joueur
\param taille: la taille du tab
\author Hugo Pointereau <pointereau@eisti.eu>
\version 0.1
\date 18/12/2020
*/
void initjeu(struct joueur* jeu, int taille);
/*!
\fn int valeurCarte(struct joueur* jeu, struct carte* deck,int joueur,int ou)
\brief donne la valeur de la carte
\author Hugo Pointereau <pointereau@eisti.eu>
\param ou: la position des cartes dans le paquet de cartes
\param jeu: le tableau de joueur
\param taille: le nombre de joueur
\param deck: le paquet de carte
\version 0.1
\date 19/12/2020
*/
int valeurCarte(struct joueur* jeu, struct carte* deck,int joueur,int ou);
/*!
\fn void afficarte(struct carte lcarte);
\brief affiche les valeurs de la carte
\author Hugo Pointereau <pointereau@eisti.eu>
param lcarte: une carte
\version 0.1
\date 18/12/2020
*/
void afficarte(struct carte lcarte);
/*!
\fn struct joueur* distrib(struct joueur* jeu, struct carte* deck,int joueur,int posc)
\brief donne une carte a un joueur
\author Hugo Pointereau <pointereau@eisti.eu>
\return retourne le jeu
\param posc: la position des cartes dans le paquet de cartes
\param jeu: le tableau de joueur
\param taille: le nombre de joueur
\param deck: le paquet de carte
\version 0.1
\date 18/12/2020
*/
struct joueur distrib(struct joueur* jeu, struct carte* deck,int joueur, int posc);
/*!
\fn struct carte* melange(struct carte*,int taille)
\brief melange le paquet de cartes
\author Hugo Pointereau <pointereau@eisti.eu>
\param jeu: le tableau de joueur
\param taille: la taille du tab
\return la structure des joueurs
\version 0.1
\date 16/12/2020
*/
struct carte* melange(struct carte* deck,int taille);
/*!
\fn int debutjeu(struct joueur* jeu, carte* deck, int joueur)
\brief fait le premier tour du black jack
\author Hugo Pointereau <pointereau@eisti.eu>
\return la poition du curseur de carte
\param jeu: le tableau de joueur
\param joueur: le nombre de joueur
\param deck: le paquet de carte
\version 0.1
\date 18/12/2020
*/
int debutjeu(struct joueur* jeu,struct carte* deck, int joueur);
/*!
\fn void affideb(struct joueur* jeu,int joueur);
\brief affiche le debut de la partie
\author Hugo Pointereau <pointereau@eisti.eu>
\param jeu: le tableau de joueur
\param joueur: le nombre de joueur
\param deck: le paquet de carte
\version 0.1
\date 18/12/2020
*/
void affideb(struct joueur* jeu,int joueur);
/*!
\fn int midjeu(struct joueur* jeu,struct carte* deck, int joueur,int pos)
\brief fait la partie apres la premiere tournée de carte
\author Hugo Pointereau <pointereau@eisti.eu>
\param posc: la position des cartes dans le paquet de cartes
\param jeu: le tableau de joueur
\param joueur: le nombre de joueur
\param deck: le paquet de carte
\return la position du curseur de carte
\version 0.1
\date 19/12/2020
*/
int midjeu(struct joueur* jeu,struct carte* deck, int joueur,int pos);
/*!
\fn void labanquetire(struct joueur* jeu,struct carte* deck,int pos)
\brief fait le jeu de la banque
\author Hugo Pointereau <pointereau@eisti.eu>
\param jeu: le tableau de joueur
\param joueur: le nombre de joueur
\param deck: le paquet de carte
\version 0.1
\date 12/12/2020
*/
void labanquetire(struct joueur* jeu,struct carte* deck,int pos);
/*!
\fn void resul(struct joueur* jeu,int joueur)
\brief fait le resultat des paris
\author Hugo Pointereau <pointereau@eisti.eu>
\param jeu: le tableau de joueur
\param joueur: le nombre de joueur
\version 0.1
\date 19/12/2020
*/
void resul(struct joueur* jeu,int joueur);
/*!
\fn void BJ(int joueur)
\brief fonction principal du blackjack
\author Hugo Pointereau <pointereau@eisti.eu>
\param jeu: le tableau de joueur
\param joueur: le nombre de joueur
\version 0.1
\date 15/12/2020
*/
void BJ(int joueur);


#endif
