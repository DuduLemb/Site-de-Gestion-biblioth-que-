#include <stdio.h>
#include <stdlib.h>
#include "livres.h"
#include "etudiants.h"
#include "emprunt.h"



int choix;

int main()
{
    printf("\n  BIENVENUE DANS LA BIBLIOTHEQUE DE L'INSTITUT SUPERIEURE KEYCE INFORMATIQUE ET IA\n");
    Menu();
}

void Menu(){
    printf("\n                    --------MENU PRINCIPAL--------\n");
    printf("\n 1.GESTION DES LIVRES\n");
    printf("\n 2.GESTION DES EMPRUNTS DE LIVRES\n");
    printf("\n 3.GESTION DES ETUDIANTS\n");
    printf("\n 0. Sortir\n");
    Choix();
}

void Choix()
{
    do {
        printf("\n Entrer votre choix : ");
        scanf("%d", &choix);
        switch(choix)
        {
        case 1 :
            MenuLivre();
            break;
        case 2:
            MenuEmprunt();
            break;
        case 3 :
            Menuetudiant();
            break;
        case 0 :
            printf("Fin du programme\n");
            printf("A bientôt\n");
            break;
        default:
            printf("Erreur de choix.\n");
            Menu();
        }
    } while(choix != 0);
}
