#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include "analyse_syntaxique.h"
// ?
#include "lecture_caracteres.h"
#include "analyse_lexicale.h"


// void reconaitre_lexeme()

// аналог demarer в analyse lexicale 
void analyser (char *fichier, int *resultat) {
    // demarre l'analyse lexicale sur le fichier transmis en argument

    Nature_Lexeme operateur;

   	demarrer (fichier); // * ? 

    typedef enum {E_INIT, E_ENTIER, E_OPERATEUR} Etat_Automate ;

    Etat_Automate etat = E_INIT;

    Lexeme LC = lexeme_courant();
    afficher (LC) ;

    while (LC.nature != C_FIN_SEQUENCE) {//condition {

        switch (etat){ //transitions
            case E_INIT:

                switch (LC.nature){ //
                    case ENTIER:
                        // garder et calculer les valeurs
                        (*resultat) = LC.valeur;  
                        etat = E_ENTIER;
                        break;
                    default:
                        printf("Erreur syntaxique");
                        exit(0);
                }
            
            case E_ENTIER:
                switch (LC.nature){
                    case PLUS: // decrire plus precisement operations
                    case MOINS: // pour calculer le resultat
                    case MUL:
                    case DIV:
                        operateur = LC.nature;
                        etat = E_OPERATEUR;
                        break;
                    default:
                        printf("Erreur syntaxique");
                        exit(0);
                    }

            case E_OPERATEUR:
                switch (LC.nature){
                    case ENTIER:
                        //logique de calcul
                        
                        switch (operateur){
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
                        operateur = NULL; // почистить переменную  
                        etat = E_ENTIER;
                        break;

                    default:
                        printf("Erreur syntaxique");
                        exit(0);
                    }
        avancer();
        LC = lexeme_courant();
        }
    }

    arreter() ; // termine l'analyse lexicale

}

// получить lexeme courant - локальная переменная в analyse_lexicale
// нужно получить expression arithmetique / msg d’erreur - как мы его будем хранить?
