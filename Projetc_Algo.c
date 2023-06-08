#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nombre_max_etd 5000
#define nombre_max_mdl 15

typedef struct {
    float noteCC;
    float noteExamen;
    float moyenne;
    int coeff;
} Module;

typedef struct {
    char matricule[20];
    char nom[50];
    char prenom[50];
    char dateNaissance[20];
    char dateInscription[20];
    Module modules[nombre_max_etd];
    int nbModules;
} Etudiant;

Etudiant etudiants[nombre_max_etd];
int nbEtudiants = 0;

void inscrireEtudiant() {
    if (nbEtudiants >= nombre_max_etd) {
        printf("Nombre maximum d'etudiants atteint. Impossible d'inscrire un nouvel etudiant.\n");
        return;
    }

    Etudiant nouvelEtudiant;

    printf("Matricule : ");
    scanf("%s", nouvelEtudiant.matricule);
    printf("Nom : ");
    scanf("%s", nouvelEtudiant.nom);
    printf("Prenom : ");
    scanf("%s", nouvelEtudiant.prenom);
    printf("Date de naissance : ");
    scanf("%s", nouvelEtudiant.dateNaissance);
    printf("Date d'inscription : ");
    scanf("%s", nouvelEtudiant.dateInscription);

    nouvelEtudiant.nbModules = 0;

    etudiants[nbEtudiants++] = nouvelEtudiant;

    printf("Etudiant inscrit avec succes.\n");
}

void saisirNotes() {
    char matricule[20];
    printf("Matricule de l'etudiant : ");
    scanf("%s", matricule);

    int i;
    for (i = 0; i < nbEtudiants; i++) {
        if (strcmp(matricule, etudiants[i].matricule) == 0) {
            int j;
            printf("Combien de modules souhaitez-vous saisir ? : ");
            scanf("%d", &etudiants[i].nbModules);
            for (j = 0; j < etudiants[i].nbModules; j++) {
                printf("Le coeffition de module : ");
                scanf("%d",&etudiants[i].modules[j].coeff);
                printf("Note CC pour le module %d : ", j + 1);
                scanf("%f", &etudiants[i].modules[j].noteCC);
                printf("Note examen pour le module %d : ", j + 1);
                scanf("%f", &etudiants[i].modules[j].noteExamen);
                etudiants[i].modules[j].moyenne = etudiants[i].modules[j].noteCC*0.4 + etudiants[i].modules[j].noteExamen*0.6;
            }
            printf("Notes saisies avec succes pour l'etudiant %s %s.\n", etudiants[i].prenom, etudiants[i].nom);
            break;
        }
    }

    if (i == nbEtudiants) {
        printf("Aucun etudiant avec ce matricule n'a ete trouve.\n");
    }
}

void calculerMoyenne(Etudiant etudiant) {
    float somme = 0;
    float s_coeff = 0;
    int i;

    for (i = 0; i < etudiant.nbModules; i++) {
        somme = somme + etudiant.modules[i].moyenne;
        s_coeff = s_coeff + etudiant.modules[i].coeff;

    }

    float moyenne = somme / s_coeff;
    printf("La moyenne de l'etudiant %s %s est de : %.2f\n", etudiant.prenom, etudiant.nom, moyenne);
}

void afficherAdmis() {
    int nbAdmis = 0;
    int i;

    for (i = 0; i < nbEtudiants; i++) {
        Etudiant etudiant = etudiants[i];
        calculerMoyenne(etudiant);

        if (etudiant.modules[i].moyenne >= 10) {
            nbAdmis++;
        }
    }

    float pourcentageAdmis = (float)nbAdmis / nbEtudiants * 100;
    printf("Pourcentage des etudiants admis : %.2f%%\n", pourcentageAdmis);
}

void afficherAjourne() {
    int nbAjourne = 0;
    int i;

    for (i = 0; i < nbEtudiants; i++) {
        Etudiant etudiant = etudiants[i];
        calculerMoyenne(etudiant);

        if (etudiant.modules[i].moyenne < 10) {
            nbAjourne++;
        }
    }

    float pourcentageAjourne = (float)nbAjourne / nbEtudiants * 100;
    printf("Pourcentage des etudiants ajournes : %.2f%%\n", pourcentageAjourne);
}

int main() {
    int choix;

    do {
        printf("\n  Gestion des etudiants: \n");
        printf("1. Inscrire un etudiant\n");
        printf("2. Saisir les notes d'un etudiant\n");
        printf("3. Calculer la moyenne d'un etudiant\n");
        printf("4. Afficher les etudiants admis\n");
        printf("5. Afficher les etudiants ajournes\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                inscrireEtudiant();
                break;
            case 2:
                saisirNotes();
                break;
            case 3:
                printf("Matricule de l'etudiant : ");
                char matricule[20];
                scanf("%s", matricule);

                int i;
                for (i = 0; i < nbEtudiants; i++) {
                    if (strcmp(matricule, etudiants[i].matricule) == 0) {
                        calculerMoyenne(etudiants[i]);
                        break;
                    }
                }

                if (i == nbEtudiants) {
                    printf("Aucun etudiant avec ce matricule n'a ete trouve.\n");
                }
                break;
            case 4:
                afficherAdmis();
                break;
            case 5:
                afficherAjourne();
                break;
            case 0:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
                break;
        }
    } while (choix != 0);

    return 0;
}