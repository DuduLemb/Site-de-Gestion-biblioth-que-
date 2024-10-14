#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include "livres.h"


void MenuLivre()
{
    printf("\n                    --------GESTION DES LIVRES--------\n");
    printf("\n 1.Ajouter un livre\n");
    printf(" 2.Modifier un livre\n");
    printf(" 3.Consulter un livre\n");
    printf(" 4.Supprimer un livre\n");
    printf(" 0. Retour\n");
    ChoixLivre();
}

void ChoixLivre()
{
    printf("Entrer votre choix : ");
    scanf("%d", &choix);
    switch(choix)
    {
    case 1 :
        ajouterLivre();
        MenuLivre();
        break;
    case 2:
        modifierLivre();
        MenuLivre();
        break;
    case 3:
        consulterlivre();
        MenuLivre();
        break;
    case 4:
        supprimerLivre();
        MenuLivre();
        break;
    case 0 :
        Menu();
        break;
    default:
        printf("Erreur de choix.\n");
        break;
    }
}

int genererId() {
    FILE* fichier_id = fopen("last_id.txt", "r+");

    if (fichier_id == NULL) {
        // Le fichier n'existe pas, on le crée avec la valeur initiale 0
        fichier_id = fopen("last_id.txt", "w");
        if (fichier_id == NULL) {
            printf("Erreur lors de la creation du fichier d'ID.\n");
            return -1;
        }
        fprintf(fichier_id, "0");
        fclose(fichier_id);

        // On rouvre le fichier pour la lecture/écriture
        fichier_id = fopen("last_id.txt", "r+");
        if (fichier_id == NULL) {
            printf("Erreur lors de l'ouverture du fichier d'ID.\n");
            return -1;
        }
    }

    int last_id;
    fscanf(fichier_id, "%d", &last_id);
    last_id++;

    // Réécrire le nouveau last_id dans le fichier
    fseek(fichier_id, 0, SEEK_SET);
    fprintf(fichier_id, "%d", last_id);

    fclose(fichier_id);

    return last_id;
}


void ajouterLivre()
{
    FILE* fichier = fopen("livres.txt", "a");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    Livre livre;

    livre.id = genererId();

    printf("    Nom du livre : ");
    fgets(livre.nom, sizeof(livre.nom), stdin);
    livre.nom[strcspn(livre.nom, "\n")] = '\0';

    while (strlen(livre.nom) == 0) {
        printf("    Le nom du livre ne peut pas etre vide. Veuillez entrer le nom du livre : ");
        fgets(livre.nom, sizeof(livre.nom), stdin);
        livre.nom[strcspn(livre.nom, "\n")] = '\0';
    }

    printf("    Auteur du livre : ");
    fgets(livre.auteur, sizeof(livre.auteur), stdin);
    livre.auteur[strcspn(livre.auteur, "\n")] = '\0';

    while (strlen(livre.auteur) == 0) {
        printf("    L'auteur du livre ne peut pas être vide. Veuillez entrer l'auteur du livre : ");
        fgets(livre.auteur, sizeof(livre.auteur), stdin);
        livre.auteur[strcspn(livre.auteur, "\n")] = '\0';
    }

    printf("    Edition du livre : ");
    fgets(livre.edition, sizeof(livre.edition), stdin);
    livre.edition[strcspn(livre.edition, "\n")] = '\0';

    while (strlen(livre.edition) == 0) {
        printf("    L'edition du livre ne peut pas être vide. Veuillez entrer l'édition du livre : ");
        fgets(livre.edition, sizeof(livre.edition), stdin);
        livre.edition[strcspn(livre.edition, "\n")] = '\0';
    }

    fprintf(fichier, "%d;%s;%s;%s\n", livre.id, livre.nom, livre.auteur, livre.edition);

    fclose(fichier);

    printf("\n               Enregistrement du livre effectue avec succes.\n");
}


void consulterlivre() {
    FILE* fichier = fopen("livres.txt", "r");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    char ligne[256];

    printf("\nListe des livres :\n");
    while (fgets(ligne, sizeof(ligne), fichier)) {
        char* token = strtok(ligne, ";");

        // Assurez-vous que la structure de la ligne est : id;nom;auteur;edition
        if (token != NULL) {
            printf("\nID : %s\n", token);

            token = strtok(NULL, ";");
            printf("Nom du livre : %s\n", token);

            token = strtok(NULL, ";");
            printf("Auteur du livre : %s\n", token);

            token = strtok(NULL, ";");
            printf("Edition du livre : %s\n", token);

            printf("----------------------------------\n");
        }
    }

    fclose(fichier);
}




void modifierLivre() {
    int id;
    printf("Entrez l'ID du livre a modifier : ");
    scanf("%d", &id);

    FILE* fichier = fopen("livres.txt", "r");
    FILE* temp = fopen("temp.txt", "w");

    int trouve = 0;

    char ligne[256];
    while (fgets(ligne, sizeof(ligne), fichier)) {
        Livre livre;
        sscanf(ligne, "%d;%[^;];%[^;];%[^\n]", &livre.id, livre.nom, livre.auteur, livre.edition);

        if (livre.id == id) {
            trouve = 1;

            printf("Entrez le nouveau nom du livre : ");
            scanf("%s", livre.nom);

            printf("Entrez le nouvel auteur du livre : ");
            scanf("%s", livre.auteur);

            printf("Entrez la nouvelle edition du livre : ");
            scanf("%s", livre.edition);

            printf("Le livre a ete modifie avec succes.\n");
        }

        fprintf(temp, "%d;%s;%s;%s\n", livre.id, livre.nom, livre.auteur, livre.edition);
    }

    fclose(fichier);
    fclose(temp);

    remove("livres.txt");
    rename("temp.txt", "livres.txt");


    if (trouve == 0) {
        printf("               L'ID entree est inexistent dans le fichier.\n");
        printf("               Impossible de continuer l'action");
        while(choix != 2)
        {
            printf("\n    Voulez-vous ?\n");
            printf("    1. Reessayer l'action\n");
            printf("    2. Annuler l'action\n");
            printf("    Entrer votre choix : ");
            scanf("%d", &choix);

            switch (choix) {
                case 1:
                    modifierLivre();
                    break;
                case 2:
                    MenuLivre();
                    break;
                default:
                    printf("    Choix invalide. Veuillez reessayer.\n");
                    break;
            }
        }
    }

}
void supprimerLivre() {
    int id;
    printf("Entrez l'ID du livre à supprimer : ");
    scanf("%d", &id);

    FILE* fichier = fopen("livres.txt", "r");
    FILE* temp = fopen("temp.txt", "w");

    if (fichier == NULL || temp == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }

    int trouve = 0;
    char ligne[256];

    while (fgets(ligne, sizeof(ligne), fichier)) {
        Livre livre;
        sscanf(ligne, "%d;%[^;];%[^;];%[^\n]", &livre.id, livre.nom, livre.auteur, livre.edition);

        if (livre.id != id) {
            fprintf(temp, "%d;%s;%s;%s;%s\n", livre.id, livre.nom, livre.auteur, livre.edition);
        } else {
            trouve = 1; // L'ID du livre a été trouvé
        }
    }

    fclose(fichier);
    fclose(temp);

    remove("livres.txt");
    rename("temp.txt", "livres.txt");

    if(trouve == 1) {
        printf("               Le livre a ete supprime avec succes.\n");
    } else {
        printf("    L'ID entree est inexistent dans le fichier.\n");
        printf("    Impossible de continuer l'action");
        while(choix != 2)
        {
            printf("\n    Voulez-vous ?\n");
            printf("    1. Reessayer l'action\n");
            printf("    2. Annuler l'action\n");
            printf("    Entrer votre choix : ");
            scanf("%d", &choix);

            switch (choix) {
                case 1:
                    supprimerLivre();
                    break;
                case 2:
                    MenuLivre();
                    break;
                default:
                    printf("    Choix invalide. Veuillez reessayer.\n");
                    break;
            }
        }
    }

}






/*void supprimerLivre() {
    FILE* fichier = fopen("livres.txt", "r");
    FILE* temp = fopen("temp.txt", "w");

    if (fichier == NULL || temp == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }

    char nomSuppression[100];
    printf("Entrez le nom du livre à supprimer : ");
    fgets(nomSuppression, sizeof(nomSuppression), stdin);
    nomSuppression[strcspn(nomSuppression, "\n")] = '\0';

    while (strlen(nomSuppression) == 0) {
        printf("Le nom du livre ne peut pas être vide. Veuillez entrer le nom du livre à supprimer : ");
        fgets(nomSuppression, sizeof(nomSuppression), stdin);
        nomSuppression[strcspn(nomSuppression, "\n")] = '\0';
    }

    char ligne[256];
    int trouve = 0;

    while (fgets(ligne, sizeof(ligne), fichier)) {
        char* token = strtok(ligne, ";");
        if (strcmp(token, nomSuppression) != 0) {
            fputs(ligne, temp);
        } else {
            trouve = 1;
        }
    }

    fclose(fichier);
    fclose(temp);

    if (!trouve) {
        printf("Livre introuvable.\n");
        remove("temp.txt");
        return;
    }

    if (remove("livres.txt") != 0) {
        printf("Erreur lors de la suppression du fichier original.\n");
        return;
    }

    if (rename("temp.txt", "livres.txt") != 0) {
        printf("Erreur lors du renommage du fichier temporaire.\n");
        return;
    }

    printf("Suppression du livre effectuée avec succès.\n");
}

void modifierLivre() {
    FILE* fichier = fopen("livres.txt", "r+");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    char nomRecherche[100];
    printf("Entrez le nom du livre à modifier : ");
    fgets(nomRecherche, sizeof(nomRecherche), stdin);
    nomRecherche[strcspn(nomRecherche, "\n")] = '\0';

    while (strlen(nomRecherche) == 0) {
        printf("Le nom du livre ne peut pas être vide. Veuillez entrer le nom du livre à supprimer : ");
        fgets(nomRecherche, sizeof(nomRecherche), stdin);
        nomRecherche[strcspn(nomRecherche, "\n")] = '\0';
    }

    char ligne[256];
    long position = -1;
    int trouve = 0;

    while (fgets(ligne, sizeof(ligne), fichier)) {
        position = ftell(fichier);
        char* token = strtok(ligne, ";");
        if (strcmp(token, nomRecherche) == 0) {
            trouve = 1;
            break;
        }
    }

    if (!trouve) {
        printf("Livre introuvable.\n");
        fclose(fichier);
        return;
    }

    Livre livre;

    printf("Nouveau nom du livre : ");
    fgets(livre.nom, sizeof(livre.nom), stdin);
    livre.nom[strcspn(livre.nom, "\n")] = '\0';

    printf("Nouveau nom de l'auteur : ");
    fgets(livre.auteur, sizeof(livre.auteur), stdin);
    livre.auteur[strcspn(livre.auteur, "\n")] = '\0';

    printf("Nouveau nom de l'édition : ");
    fgets(livre.edition, sizeof(livre.edition), stdin);
    livre.edition[strcspn(livre.edition, "\n")] = '\0';

    fseek(fichier, position, SEEK_SET);
    fprintf(fichier, "%s;%s;%s\n", livre.nom, livre.auteur, livre.edition);

    fclose(fichier);

    printf("Modification du livre effectuée avec succès.\n");


}*/
