/*!
*  \file carte.c
*  \author Hugo Pointereau <pointereau@eisti.eu>
*  \version 0.1
*  \date 15/12/2020
*  \brief toutes les fonctions des cartes
*/

#include "carte.h"


void inittab(struct carte* deck, int taille){
  /* initialise le tableau de carte */
  int compt;
  compt=0;
  for (size_t i = 0; i < 13; i++) {
    for (size_t j = 0; j < 4; j++) {
        deck[compt].int_pos = compt;
        deck[compt].int_val = i+1;
        deck[compt].cart_coul =j;
        compt++;
    }
  }
}

void initjeu(struct joueur* jeu, int taille){
  size_t nb1 ;
  int int_taille ;
  /* initialise le tableau de joueur */
  jeu[0].nom = "banque";
  for (int i = 1; i < taille; i++) {
    printf("Quel nom pour le joueur %d ?\n",i );
    jeu[i].nom = NULL;
    getchar();
    int_taille = getline(&jeu[i].nom, &nb1, stdin);
    jeu[i].nom[--(int_taille)] =0;
    jeu[i].etat = 1;
    printf("Quelle mise voulez vous mettre ?\n" );
    jeu[i].mise = SaisieEntier();
    jeu[i].nbcartes = 0;
    jeu[i].valeur=0;
  }
}
void afficarte(struct carte lcarte){
  char* char_coul;
  char* char_fig;
  switch (lcarte.cart_coul) {
    case 0:
    char_coul ="pique";
    break;
    case 1:
    char_coul ="tréfles";
    break;
    case 2:
    char_coul ="carreau";
    break;
    default:
    char_coul ="coeur";
    break;
  }
  switch (lcarte.int_val) {
    case 1:
    char_fig ="as";
    break;
    case 2:
    char_fig ="2";
    break;
    case 3:
    char_fig ="3";
    break;
    case 4:
    char_fig ="4";
    break;
    case 5:
    char_fig ="5";
    break;
    case 6:
    char_fig ="6";
    break;
    case 7:
    char_fig ="7";
    break;
    case 8:
    char_fig ="8";
    break;
    case 9:
    char_fig ="9";
    break;
    case 10:
    char_fig ="10";
    break;
    case 11:
    char_fig ="Valet";
    break;
    case 12:
    char_fig ="Dame";
    break;
    case 13:
    char_fig ="Roi";
    break;
    default:;
  }
  printf("Cartes : %s  %s\n",char_fig,char_coul );
}
int valeurCarte(struct joueur* jeu, struct carte* deck,int joueur,int ou){
  int valeur;
  int choix;
  valeur = jeu[joueur].main[ou].int_val;
  /* affecte la valeur des buches */
  if ((valeur==11)||(valeur==12)||(valeur==13)) {
    valeur =10;
  }
  if (valeur==1) {
    if (joueur==0) {
      if (jeu[joueur].valeur+11 >21) {
        valeur=1;
      } else {
        valeur =11;
      }
    }else{
      /* demande pour la valeur de l'as */
    printf("---------- %s ---------\n",jeu[joueur].nom );
    printf("Pour votre as, quelle valeur voulez vous ? 1 ou 11 ?\n" );
    printf("1: 1\n");
    printf("2: 11\n");
    choix=InterReel(1,2);
    if (choix==1) {
      valeur=1;
    } else {
      valeur=11;
    }
  }
}
  return valeur;
}
struct joueur distrib(struct joueur* jeu, struct carte* deck,int joueur, int posc){
  int ou;
  /* augmnte la taille du tableau de carte de la structure du joueur */
  jeu[joueur].main =realloc(jeu[joueur].main, (jeu[joueur].nbcartes+1) * sizeof(struct carte));
  jeu[joueur].main[jeu[joueur].nbcartes] = deck[posc];
  ou=jeu[joueur].nbcartes;
  jeu[joueur].nbcartes++;
  jeu[joueur].valeur=jeu[joueur].valeur +valeurCarte(jeu,deck,joueur,ou);
  return (jeu[joueur]);
}
struct carte* melange(struct carte* deck,int taille){
  struct carte tmp;
  int tri1;
  int tri2;
  int compt;
  compt =0;
  /* le melange a plein d'iteration pour un melange plus efficace */
  while (compt != 100000) {
    tri1 = rand() % 52;
    tri2 = rand() % 52;
    while (tri1==tri2) {
      tri2 = rand() % 52;
    }
    tmp = deck[tri1];
    deck[tri1]= deck[tri2];
    deck[tri2]=tmp;
    compt++;
  }

  return(deck);
}
int debutjeu(struct joueur* jeu,struct carte* deck, int joueur){
  int pos;
  pos =0;
  /* premier distribution de carte pour les joueurs */
  for (size_t i = 1; i < joueur; i++) {
    jeu[i]=distrib(jeu,deck,i,pos);
    pos++;
  }
  /* premier distribution de carte pour la banque */
  jeu[0]=distrib(jeu,deck,0,pos);
  pos++;
  /* deuxieme distribution de carte pour les joueurs */
  for (size_t i = 1; i < joueur; i++) {
    jeu[i]=distrib(jeu,deck,i,pos);
    pos++;
  }
  /* deuxieme distribution de carte pour la banque */
  jeu[0]=distrib(jeu,deck,0,pos);
  pos++;
  return (pos);
}
int midjeu(struct joueur* jeu,struct carte* deck, int joueur,int pos){
  pos++;
  for (size_t i = 1; i < joueur; i++) {
    /* tant que le joueur reste dans l'etat 1 il continue a prendre des cartes*/
    while (jeu[i].etat==1) {
      printf("%s, voulez vous une carte ou restez ?\n",jeu[i].nom );
      printf("1: Carte !\n" );
      printf("2: Je reste !\n" );
      jeu[i].etat=InterReel(1,2);
      if ((jeu[i].etat==1)&&(pos<52)) {
        jeu[i]=distrib(jeu,deck,i,pos);
        pos++;
      }
      if (jeu[i].valeur>21) {
        jeu[i].etat=3;
        printf("%s, Vous avez depasser 21, vous avez perdu\n",jeu[i].nom );
      }
      printf("Valeur main : %d\n",jeu[i].valeur );
      for (size_t j = 0; j < jeu[i].nbcartes; j++) {
        afficarte(jeu[i].main[j]);
      }
    }
    printf("------------------------\n");
    printf("\n" );
  }
  return (pos);
}

void labanquetire(struct joueur* jeu,struct carte* deck,int pos){
  while (jeu[0].valeur<17) {
    jeu[0]=distrib(jeu,deck,0,pos);
    pos++;
  }
  printf("La banque a joué\n" );
  for (size_t i = 0; i < jeu[0].nbcartes; i++) {
    afficarte(jeu[0].main[i]);
  }
  printf("\n" );
  printf("La valeur de la banque est: %d\n",jeu[0].valeur );
  printf("------------------------\n");
}
void affideb(struct joueur* jeu,int joueur){
  printf("------------------------\n");
  printf("%s\n",jeu[0].nom );
  afficarte(jeu[0].main[1]);
  for (size_t i = 1; i < joueur; i++) {
    printf("------------------------\n");
    printf("%s\n",jeu[i].nom );
    printf("Valeur main : %d\n",jeu[i].valeur );
    for (size_t j = 0; j < jeu[i].nbcartes; j++) {
      afficarte(jeu[i].main[j]);
    }
  }
  printf("------------------------\n");
  printf("\n" );
}
void resul(struct joueur* jeu,int joueur){
  for (size_t i = 1; i < joueur; i++) {
    printf("Resultat pour %s\n",jeu[i].nom );
    if (jeu[i].etat==3) {
      printf("Vous avez depassez 21 donc perdu votre mise\n" );
      jeu[i].mise=0;
    }else{
      if ((jeu[i].nbcartes==2)&&(jeu[i].valeur==21)) {
        printf("BLAKCJACK votre mise est doublée\n" );
        jeu[i].mise=jeu[i].mise*2;
      }
      if (jeu[0].valeur >21) {
        printf("la banque a perdu\n" );
      }
      if (jeu[0].valeur==jeu[i].valeur) {
        printf("Egalité vous gardez votre mise\n" );
      }
      if ((jeu[0].valeur>jeu[i].valeur)&&(jeu[0].valeur<=21)) {
        printf("La banque a gagner\n" );
        jeu[i].mise=0;
      }
      if (jeu[0].valeur<jeu[i].valeur) {
          printf("Vous avez battu la banque, votre mise est doublée\n" );
          jeu[i].mise=jeu[i].mise*2;
        }
      }
        printf("Votre mise actuel : %d\n",jeu[i].mise );
        printf("------------------------\n");
      }
    }

void BJ(int joueur){
  struct carte* deck;
  struct joueur* jeu;
  int pos;
  int etat;
  etat=1;
  joueur= joueur+1;
  deck=malloc(52*sizeof(struct carte));
  if (deck == NULL) {
      exit(-1);
  }
  jeu=malloc(joueur*sizeof(struct joueur));
  if (jeu == NULL) {
    exit(-1);
  }
  inittab(deck,52);
  initjeu(jeu,joueur);
  while (etat==1) {
    pos=0;
    deck=melange(deck,52);
    system("clear");
    pos =debutjeu(jeu,deck,joueur);
    affideb(jeu,joueur);
    pos =midjeu(jeu,deck,joueur,pos);
    labanquetire(jeu,deck,pos);
    resul(jeu,joueur);
    printf("------------------------\n");
    printf("Voulez vous faire une autre manche ?\n" );
    printf("1: oui\n" );
    printf("2: non \n" );
    etat= InterReel(1,2);
    if (etat==1) {
      for (size_t i = 0; i < joueur; i++) {
        free(jeu[i].main);
        jeu[i].nbcartes = 0;
        jeu[i].valeur=0;
        jeu[i].etat=1;
        if ((jeu[i].mise==0)&&(i!=0)) {
          printf("%s, quelle mise voulez vous mettre ?\n",jeu[i].nom );
          jeu[i].mise = SaisieEntier();
        }
    }
    }
  }
  printf("MERCI D'AVOIR JOUER !!!\n" );
}
