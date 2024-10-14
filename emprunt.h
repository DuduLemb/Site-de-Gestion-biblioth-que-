#ifndef EMPRUNT_H_INCLUDED
#define EMPRUNT_H_INCLUDED
int choix3;
typedef struct {
    int idemprunt;
    char nomemprunt[50];
    char nometudiantempr[50];
    char dateemprunt[50];
    char dateremise[50];
}Emprunt;
void MenuEmprunt()
{
    printf("\n                   -------GESTION DES EMPRUNTS--------\n");
    printf("\n1.Ajouter un livre emprunte\n");
    printf("2.Modifier un livre emprunte\n");
    printf("3.Consulter un livre emprunte\n");
    printf("4.Supprimer un livre emprunte\n");
    printf("0. Retour\n");
    Choixemprunt();
}

void Choixemprunt()
{
    printf("Entrer votre choix : ");
    scanf("%d", &choix3);
    switch(choix3)
    {
    case 1 :
        ajouterunlivreemprunte();
        MenuEmprunt();
        break;
    case 2:
        modifierunlivreemprunte();
        MenuEmprunt();
        break;
    case 3:
        consulterEmprunt();
        MenuEmprunt();
        break;
    case 4:
        supprimerunlivreemprunte();
        MenuEmprunt();
        break;
    case 0 :
        Menu();
        break;
    default:
        printf("Erreur de choix.");
        break;
    }
}

int genererIdemprunt() {
    FILE* fichier_id = fopen("lasti.txt", "r+");

    if (fichier_id == NULL) {
        // Le fichier n'existe pas, on le crée avec la valeur initiale 0
        fichier_id = fopen("lasti.txt", "w");
        if (fichier_id == NULL) {
            printf("Erreur lors de la creation du fichier d'ID.\n");
            return -1;
        }
        fprintf(fichier_id, "0");
        fclose(fichier_id);

        // On rouvre le fichier pour la lecture/écriture
        fichier_id = fopen("lasti.txt", "r+");
        if (fichier_id == NULL) {
            printf("Erreur lors de l'ouverture du fichier d'ID.\n");
            return -1;
        }
    }

    int lasti;
    fscanf(fichier_id, "%d", &lasti);
    lasti++;

    // Réécrire le nouveau last_id dans le fichier
    fseek(fichier_id, 0, SEEK_SET);
    fprintf(fichier_id, "%d", lasti);

    fclose(fichier_id);

    return lasti;
}
void ajouterunlivreemprunte(){
     FILE* fi = fopen("emprunt.txt", "a");

    if (fi == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    Emprunt emprunt;

    emprunt.idemprunt = genererIdemprunt();

    printf("    Nom du livre emprunte : ");
    fgets(emprunt.nomemprunt, sizeof(emprunt.nomemprunt), stdin);
    emprunt.nomemprunt[strcspn(emprunt.nomemprunt, "\n")] = '\0';

    while (strlen(emprunt.nomemprunt) == 0) {
        printf("    Le nom du livre  emprunte ne peut pas etre vide.Veuillez entrer le nom du livre emprunte : ");
        fgets(emprunt.nomemprunt, sizeof(emprunt.nomemprunt), stdin);
        emprunt.nomemprunt[strcspn(emprunt.nomemprunt, "\n")] = '\0';
    }

    printf("    nom etudiant qui emprunte le livre: ");
    fgets(emprunt.nometudiantempr, sizeof(emprunt.nometudiantempr), stdin);
    emprunt.nometudiantempr[strcspn(emprunt.nometudiantempr, "\n")] = '\0';

    while (strlen(emprunt.nometudiantempr) == 0) {
        printf("    Le nom de l'etudiant qui emprunte le livre ne peut pas être vide. Veuillez entrer le nom de l'etudiant qui emprunte le livre  : ");
        fgets(emprunt.nometudiantempr, sizeof(emprunt.nometudiantempr), stdin);
        emprunt.nometudiantempr[strcspn(emprunt.nometudiantempr, "\n")] = '\0';
    }

    printf("    date emprunt: ");
    fgets(emprunt.dateemprunt, sizeof(emprunt.dateemprunt), stdin);
    emprunt.dateemprunt[strcspn(emprunt.dateemprunt, "\n")] = '\0';

    while (strlen(emprunt.dateemprunt) == 0) {
        printf("   La date d'emprunt du livre ne peut pas etre vide. Veuillez entrer la date d'emprunt du livre : ");
        fgets(emprunt.dateemprunt, sizeof(emprunt.dateemprunt), stdin);
        emprunt.dateemprunt[strcspn(emprunt.dateemprunt, "\n")] = '\0';
    }

    printf("    date remise: ");
    fgets(emprunt.dateremise, sizeof(emprunt.dateremise), stdin);
    emprunt.dateremise[strcspn(emprunt.dateremise, "\n")] = '\0';

    while (strlen(emprunt.dateremise) == 0) {
        printf("   La date de remise du livre ne peut pas etre vide. Veuillez entrer la date de remise du livre : ");
        fgets(emprunt.dateremise, sizeof(emprunt.dateremise), stdin);
        emprunt.dateremise[strcspn(emprunt.dateremise, "\n")] = '\0';
    }

    fprintf(fi, "%d;%s;%s;%s;%s\n", emprunt.idemprunt, emprunt.nomemprunt, emprunt.nometudiantempr, emprunt.dateemprunt, emprunt.dateremise);

    fclose(fi);

    printf("\n               Enregistrement du livre effectue avec succes.\n");

}

void modifierunlivreemprunte() {
    int id, choix;
    printf("    Entrez l'ID de l'etudiant a modifier : ");
    scanf("%d", &id);

    FILE* fi = fopen("emprunt.txt", "r");
    FILE* tempa = fopen("tempa.txt", "w");

    int trouve = 0;

    char ligne[256];

    while (fgets(ligne, sizeof(ligne), fi)) {
        Emprunt emprunt;
        sscanf(ligne, "%d;%[^;];%[^;];%[^;];%[^\n]", &emprunt.idemprunt, emprunt.nomemprunt, emprunt.nometudiantempr, emprunt.dateemprunt, emprunt.dateremise);

        if (emprunt.idemprunt == id)
            {
                        trouve = 1;

    printf("    Nom emprunt : ");
    scanf("%s", emprunt.nomemprunt);

    printf("    Entrez le nouveau nom de l'etudiant qui a emprunte : ");
    scanf("%s", emprunt.nometudiantempr);

    printf("    Entrez la nouvelle date d'emprunt : ");
    scanf("%s", emprunt.dateemprunt);


    printf("    Entrez la nouvelle date de remise  :");
    scanf("%s", emprunt.dateremise);




            }




       fprintf(tempa, "%d;%s;%s;%s;%s\n", emprunt.idemprunt, emprunt.nomemprunt, emprunt.nometudiantempr, emprunt.dateemprunt, emprunt.dateremise);
        }
     printf("               L'emprunt a ete modifie avec succes.\n");

    fclose(fi);
    fclose(tempa);



    remove("emprunt.txt");
    rename("tempa.txt", "emprunt.txt");

    if (trouve == 0) {
        printf("               L'ID entrée est inexistent dans le fichier.\n");
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
                    modifierunlivreemprunte();
                    break;
                case 2:
                    MenuEmprunt();
                    break;
                default:
                    printf("    Choix invalide. Veuillez reessayer.\n");
                    break;
                }
            }
        }
    }

    void supprimerunlivreemprunte() {
    int id ;
    printf("    Entrez l'ID de L'etudiant à supprimer : ");
    scanf("%d", &id);

    FILE* fi = fopen("emprunt.txt", "r");
    FILE* tempa = fopen("tempa.txt", "w");

    int trouve = 0;

    char ligne[256];
    while (fgets(ligne, sizeof(ligne), fi)) {
        Emprunt emprunt;
        sscanf(ligne, "%d;%[^;];%[^;];%[^;];%[^\n]", &emprunt.idemprunt, emprunt.nomemprunt, emprunt.nometudiantempr, emprunt.dateemprunt, emprunt.dateremise);

        if (emprunt.idemprunt != id) {
           fprintf(tempa, "%d;%s;%s;%s;%s\n", emprunt.idemprunt, emprunt.nomemprunt, emprunt.nometudiantempr, emprunt.dateemprunt, emprunt.dateremise);

        } else {
            trouve = 1; // L'ID du livre a été trouvé
        }
    }

    fclose(fi);
    fclose(tempa);

    remove("emprunt.txt");
    rename("tempa.txt", "emprunt.txt");

    if(trouve == 1) {
        printf("               L'emprunt a ete supprime avec succes.\n");
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
                    supprimerunlivreemprunte();
                    break;
                case 2:
                    MenuEmprunt();
                    break;
                default:
                    printf("    Choix invalide. Veuillez reessayer.\n");
                    break;
            }
        }
    }

}

void consulterEmprunt() {
    FILE* fi = fopen("emprunt.txt", "r");

    if (fi == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    char ligne[256];

    printf("\nListe des livres :\n");
    while (fgets(ligne, sizeof(ligne), fi)) {
        char* token = strtok(ligne, ";");

        // Assurez-vous que la structure de la ligne est : id;nom;auteur;edition
        if (token != NULL) {
            printf("\nID : %s\n", token);

            token = strtok(NULL, ";");
            printf("Nom de l'emprunt : %s\n", token);

            token = strtok(NULL, ";");
            printf("Nom de l'etudiant ayant emprunte le livre : %s\n", token);

            token = strtok(NULL, ";");
            printf("Date emprunt : %s\n", token);

            token = strtok(NULL, ";");
            printf("Date remise : %s\n", token);


            printf("----------------------------------\n");
        }
    }

    fclose(fi);
}




#endif // EMPRUNT_H_INCLUDED
