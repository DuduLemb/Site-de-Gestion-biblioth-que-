#ifndef ETUDIANTS_H
#define ETUDIANTS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int idetudiant;
    char nometudiant[50];
    char prenometudiant[50];
    int age;
    char lieuNaissance[50];
    char dateNaissance[50];
} Etudiant;

#endif // ETUDIANTS_H



int choix2;

void Menuetudiant()
{
    printf("\n                    --------GESTION DES ETUDIANTS--------\n");
    printf("\n1.Ajouter un etudiant\n");
    printf("2.Modifier un etudiant\n");
    printf("3.Consulter un etudiant\n");
    printf("4.Supprimer un etudiant\n");
    printf("0. Retour\n");
    ChoixEtudiant();
}
void ChoixEtudiant()
{
    printf("Entrer votre choix : ");
    scanf("%d", &choix2);
    switch(choix2)
    {
    case 1 :
        ajouterEtudiant();
        Menuetudiant();
        break;
    case 2 :
        modifierEtudiant();
        Menuetudiant();
        break;
    case 3:
        consulterEtudiant();
        Menuetudiant();
        break;
    case 4:
        supprimerEtudiant();
        Menuetudiant();
        break;
    case 0 :
        Menu();
        break;
    default:
        printf("Erreur de choix.");
        break;
    }
}

int generer() {
    FILE* fichier_id = fopen("last.txt", "r+");

    if (fichier_id == NULL) {
        // Le fichier n'existe pas, on le crée avec la valeur initiale 0
        fichier_id = fopen("last.txt", "w");
        if (fichier_id == NULL) {
            printf("Erreur lors de la creation du fichier d'ID.\n");
            return -1;
        }
        fprintf(fichier_id, "0");
        fclose(fichier_id);

        // On rouvre le fichier pour la lecture/écriture
        fichier_id = fopen("last.txt", "r+");
        if (fichier_id == NULL) {
            printf("Erreur lors de l'ouverture du fichier d'ID.\n");
            return -1;
        }
    }

    int last;
    fscanf(fichier_id, "%d", &last);
    last++;

    // Réécrire le nouveau last_id dans le fichier
    fseek(fichier_id, 0, SEEK_SET);
    fprintf(fichier_id, "%d", last);

    fclose(fichier_id);

    return last;
}


void ajouterEtudiant(){
    FILE*f = fopen("etudiants.txt", "a");
    if(f == NULL){
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    Etudiant etudiant;

    etudiant.idetudiant = generer();
    printf("Nom:");
    fgets(etudiant.nometudiant,50,stdin);
    etudiant.nometudiant[strcspn(etudiant.nometudiant,"\n")] = '\0';

    while (strlen(etudiant.nometudiant) == 0) {
        printf("    Le nom de l'etudiant ne peut pas etre vide. Veuillez entrer le nom de l'etudiant : ");
        fgets(etudiant.nometudiant, sizeof(etudiant.nometudiant), stdin);
        etudiant.nometudiant[strcspn(etudiant.nometudiant, "\n")] = '\0';
    }

    printf("Prénom:");
    fgets(etudiant.prenometudiant,50,stdin);
    etudiant.prenometudiant[strcspn(etudiant.prenometudiant,"\n")] = '\0';

    while (strlen(etudiant.prenometudiant) == 0) {
        printf("    Le prenom de l'etudiant ne peut pas etre vide. Veuillez entrer le prenom de l'etudiant : ");
        fgets(etudiant.prenometudiant, sizeof(etudiant.prenometudiant), stdin);
        etudiant.prenometudiant[strcspn(etudiant.prenometudiant, "\n")] = '\0';
    }

    char ageStr[10];
    int ageValide = 0;
    while(!ageValide){
       printf("Age:");
    fgets(ageStr,10,stdin);
    ageStr[strcspn(ageStr,"\n")] = '\0';
    ageValide = 1;
    for(int i=0;i<strlen(ageStr);i++){
        if(ageStr[i] < '0' || ageStr[i] > '9'){
            ageValide = 0;
            break;
        }
    }
    if(!ageValide){
        printf("L'age doit etre un nombre entier positif. Veuillez reessayer .\n");
    }
    }
    etudiant.age = atoi(ageStr);

    printf("Lieu de naissance:");
    fgets(etudiant.lieuNaissance,50,stdin);
    etudiant.lieuNaissance[strcspn(etudiant.lieuNaissance,"\n")] = '\0';

    while (strlen(etudiant.lieuNaissance) == 0) {
        printf("    Le lieu de naissance de l'etudiant ne peut pas être vide. Veuillez entrer le lieu de naissance de l'etudiant : ");
        fgets(etudiant.lieuNaissance, sizeof(etudiant.lieuNaissance), stdin);
        etudiant.lieuNaissance[strcspn(etudiant.lieuNaissance, "\n")] = '\0';
    }


    printf("Date:");
    fgets(etudiant.dateNaissance,50,stdin);
    etudiant.dateNaissance[strcspn(etudiant.dateNaissance,"\n")] = '\0';


    while (strlen(etudiant.dateNaissance) == 0) {
        printf("    La date de naissance de l'etudiant ne peut pas être vide. Veuillez entrer la date de naissance de l'etudiant : ");
        fgets(etudiant.dateNaissance, sizeof(etudiant.dateNaissance), stdin);
        etudiant.dateNaissance[strcspn(etudiant.dateNaissance, "\n")] = '\0';
    }
            fprintf(f, "%d;%s;%s;%d;%s;%s\n", etudiant.idetudiant, etudiant.nometudiant, etudiant.prenometudiant, etudiant.age, etudiant.lieuNaissance, etudiant.dateNaissance);

    fclose(f);
    printf("\n               Enregistrement de l'etudiant effectue avec succes.\n");
}

void modifierEtudiant() {
    int id, choix;
    printf("    Entrez l'ID de l'etudiant a modifier : ");
    scanf("%d", &id);

    FILE* f = fopen("etudiants.txt", "r");
    FILE* tempo = fopen("tempo.txt", "w");

    int trouve = 0;

    char ligne[256];

    while (fgets(ligne, sizeof(ligne), f)) {

        Etudiant etudiant;
        sscanf(ligne, "%d;%[^;];%[^;];%d;%[^;];%[^\n]", &etudiant.idetudiant, etudiant.nometudiant, etudiant.prenometudiant, &etudiant.age, etudiant.lieuNaissance, etudiant.dateNaissance);

        if (etudiant.idetudiant == id) {
            trouve = 1;
            printf("    Entrer le nouveau nom : ");
            scanf("%s", etudiant.nometudiant);

            printf("    Entrez le nouveau prenom de l'etudiant : ");
            scanf("%s", etudiant.prenometudiant);

            printf("    Entrer le nouvel age de l'etudiant : ");
            scanf("%d", &etudiant.age);

            printf("    Entrer le nouveau lieu de naissance : ");
            scanf("%s", etudiant.lieuNaissance);

            printf("    Entrer la nouvelle date : ");
            scanf("%s", etudiant.dateNaissance);

            printf("               L'etudiant a ete modifie avec succes.\n");
        }

        fprintf(tempo, "%d;%s;%s;%d;%s;%s\n", etudiant.idetudiant, etudiant.nometudiant, etudiant.prenometudiant, etudiant.age, etudiant.lieuNaissance, etudiant.dateNaissance);
    }

    fclose(f);
    fclose(tempo);

    remove("etudiants.txt");
    rename("tempo.txt", "etudiants.txt");

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
                    modifierEtudiant();
                    break;
                case 2:
                    Menuetudiant();
                    break;
                default:
                    printf("    Choix invalide. Veuillez reessayer.\n");
                    break;
            }
        }
    }
}


void consulterEtudiant() {
    FILE* f = fopen("etudiants.txt", "r");

    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    char ligne[256];

    printf("\nListe des livres :\n");
    while (fgets(ligne, sizeof(ligne), f)) {
        char* token = strtok(ligne, ";");

        // Assurez-vous que la structure de la ligne est : id;nom;auteur;edition
        if (token != NULL) {
            printf("\nID : %s\n", token);

            token = strtok(NULL, ";");
            printf("Nom de l'etudiant : %s\n", token);

            token = strtok(NULL, ";");
            printf("Prenom de l'etudiant : %s\n", token);

            token = strtok(NULL, ";");
            printf("age de l'etudiant : %d\n", token);

            token = strtok(NULL, ";");
            printf("Lieu de naissance : %s\n", token);

            token = strtok(NULL, ";");
            printf("Date de naissance : %s\n", token);



            printf("----------------------------------\n");
        }
    }

    fclose(f);
}

void supprimerEtudiant() {
    int id, choix;
    printf("    Entrez l'ID de l'etudiant a supprimer : ");
    scanf("%d", &id);

    FILE* f = fopen("etudiants.txt", "r");
    FILE* tempo = fopen("tempo.txt", "w");

    int trouve = 0;

    char ligne[256];
    while (fgets(ligne, sizeof(ligne), f)) {
        Etudiant etudiant;
        sscanf(ligne, "%d;%[^;];%[^;];%d;%[^;];%[^\n]", &etudiant.idetudiant, etudiant.nometudiant, etudiant.prenometudiant, &etudiant.age, etudiant.lieuNaissance, etudiant.dateNaissance);

        if (etudiant.idetudiant != id) {
            fprintf(tempo, "%d;%s;%s;%d;%s;%s\n", etudiant.idetudiant, etudiant.nometudiant, etudiant.prenometudiant, etudiant.age, etudiant.lieuNaissance, etudiant.dateNaissance);
        } else {
            trouve = 1; // L'ID de l'etudiant a été trouvé
        }
    }

    fclose(f);
    fclose(tempo);

    remove("etudiants.txt");
    rename("tempo.txt", "etudiants.txt");

    if (trouve == 1) {
        printf("               L'etudiant a ete supprime avec succes.\n");
    } else {
        printf("    L'ID entree est inexistant dans le fichier.\n");
        printf("    Impossible de continuer l'action");

        while (choix != 2) {
            printf("\n    Voulez-vous ?\n");
            printf("    1. Reessayer l'action\n");
            printf("    2. Annuler l'action\n");
            printf("    Entrer votre choix : ");
            scanf("%d", &choix);

            switch (choix) {
                case 1:
                    supprimerEtudiant();
                    break;
                case 2:
                    Menuetudiant();
                    break;
                default:
                    printf("    Choix invalide. Veuillez reessayer.\n");
                    break;
            }
        }
    }
}


