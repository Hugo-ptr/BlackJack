/*!
*  \file main.c
*  \author Hugo Pointereau <pointereau@eisti.eu>
*  \version 0.1
*  \date 28/11/2020
*  \brief main du BLACKJACK
*/

/* Inclusion des entêtes de librairies */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "carte.h"

/*!
\fn int main(int argc, char const *argv[])
\brief Fonction principale
\author author Hugo Pointereau <pointereau@eisti.eu>
\version 0.1
\date 28/11/2020
\param argc nombre d'arguments en entree
\param argv valeur des arguments en entree
\return 0 Si tout s'est bien passé
*/
int main(int argc, char const *argv[]){
  long int_nbjoueur;
  srand(time(NULL));
  if (argc !=2) {
    printf("Mauvaise entré, veuillez mettre en argument seulement le nombre de joueur\n");
    exit(-1);
  }
  int_nbjoueur = strtol(argv[1],NULL,10);
  BJ(int_nbjoueur);
  return 0;
}
