

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include "analyse_syntaxique.h"
#include "lecture_caracteres.h"
#include "analyse_lexicale.h"

void analyser(char *fichier, int *resultat) {
    Nature_Lexeme operateur;

    demarrer(fichier);

    typedef enum {E_INIT, E_ENTIER, E_OPERATEUR} Etat_Automate;
    Etat_Automate etat = E_INIT;

    Lexeme LC = lexeme_courant();
    afficher(LC);

    while (LC.nature != FIN_SEQUENCE) {
        switch (etat) {
            case E_INIT:
                switch (LC.nature) {
                    case ENTIER:
                        *resultat = LC.valeur;
                        etat = E_ENTIER;
                        break;
                    default:
                        printf("Erreur syntaxique");
                        exit(0);
                }
                break;

            case E_ENTIER:
                switch (LC.nature) {
                    case PLUS:
                    case MOINS:
                    case MUL:
                    case DIV:
                        operateur = LC.nature;
                        etat = E_OPERATEUR;
                        break;
                    default:
                        printf("Erreur syntaxique");
                        exit(0);
                }
                break;

            case E_OPERATEUR:
                switch (LC.nature) {
                    case ENTIER:
                        switch (operateur) {
                            case PLUS: 
                                *resultat += LC.valeur;
                                break;
                            case MOINS: 
                                *resultat -= LC.valeur;
                                break;
                            case MUL:
                                *resultat *= LC.valeur;
                                break;
                            case DIV:
                                *resultat /= LC.valeur;
                                break;
                            default:
                                printf("Erreur syntaxique");
                                exit(0);
                        }
                        etat = E_ENTIER;
                        break;

                    default:
                        printf("Erreur syntaxique");
                        exit(0);
                }
                break;
        }

        avancer();
        LC = lexeme_courant();
    }

    arreter();
}
