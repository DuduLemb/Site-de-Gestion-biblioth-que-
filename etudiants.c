#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "etudiants.h"




/*int genererIdetudiant{
  srand(time(NULL));
    return rand() % (99999 - 10000 + 1) + 10000;
}
void ajouterEtudiant(){
    FILE*f = fopen("etudiants.txt", "a");
    if(f == NULL){
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    Etudiant etudiant;
    printf("Nom:");
    fgets(etudiant.nom,50,stdin);
    etudiant.nometudiant[strcspn(etudiant.nometudiant,"\n")] = '\0';

    while (strlen(etudiant.nometudiant) == 0) {
        printf("    Le nom de l'etudiant ne peut pas être vide. Veuillez entrer le nom de l'etudiant : ");
        fgets(etudiant.nometudiant, sizeof(etudiant.nometudiant), stdin);
        etudiant.nometudiant[strcspn(etudiant.nometudiant, "\n")] = '\0';
    }

    printf("Prénom:");
    fgets(etudiant.prenometudiant,50,stdin);
    etudiant.prenometudiant[strcspn(etudiant.prenometudiant,"\n")] = '\0';

    while (strlen(etudiant.prenometudiant) == 0) {
        printf("    Le prenom de l'etudiant ne peut pas être vide. Veuillez entrer le prenom de l'etudiant : ");
        fgets(etudiant.prenometudiant, sizeof(etudiant.nometudiant), stdin);
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


    printf("Date");
    fgets(etudiant.dateNaissance,50,stdin);
    etudiant.dateNaissance[strcspn(etudiant.dateNaissance,"\n")] = '\0';


    while (strlen(etudiant.dateNaissance) == 0) {
        printf("    La date de naissance de l'etudiant ne peut pas être vide. Veuillez entrer la date de naissance de l'etudiant : ");
        fgets(etudiant.dateNaissance, sizeof(etudiant.dateNaissance), stdin);
        etudiant.dateNaissance[strcspn(etudiant.dateNaissance, "\n")] = '\0';
    }
    fprintf(fichier,"%s;%s;%d;%s;%s\n",etudiant.nometudiant.prenometudiant,etudiant.age, etudiant.lieuNaissance,etudiant.dateNaissance);
    fclose(fichier);
}

