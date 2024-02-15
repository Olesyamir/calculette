#include <stdio.h>
#include <stdlib.h>
#include "analyse_lexicale.h"

// Fonctions prototypes
void Rec_eaep(int *resultat);
void Rec_op(char *op);
int Evaluer(int vald, char op, int valg);



void analyser(char *nom_fichier) {
    // Démarrer l'analyse lexicale
    demarrer(nom_fichier);

    // Récupérer le résultat de l'analyse syntaxique
    int resultat;
    Rec_eaep(&resultat);

    // Vérifier la fin de l'expression
    if (lexeme_courant().nature != FIN_SEQUENCE) {
        printf("Erreur : Fin de l'expression inattendue.\n");
        exit(EXIT_FAILURE);
    }

    // Arrêter l'analyse lexicale
    arreter();

    // Afficher le résultat
    printf("Le résultat de l'expression est : %d\n", resultat);
}

void Rec_eaep(int *resultat) {
    switch (lexeme_courant().nature) {
        case ENTIER:
            *resultat = lexeme_courant().valeur;
            avancer();
            break;
        case PARO:
            avancer();
            Rec_eaep(resultat); // Analyser l'expression entre parenthèses
            if (lexeme_courant().nature == PARF) {
                avancer(); // Avancer le lexème pour déplacer le curseur après la parenthèse fermante
            } else {
               printf("Erreur : Parenthèse fermante manquante.\n");
               exit(EXIT_FAILURE);
            }
            break;
        default:
            printf("Erreur : Attendu ENTIER ou PARO.\n");
            exit(EXIT_FAILURE);
            break;
    }
}

// Procédure pour reconnaître et analyser un opérateur
void Rec_op(char *op) {
    switch (lexeme_courant().nature) {
        case PLUS:
        case MOINS:
        case MUL:
        case DIV:
            *op = lexeme_courant().nature;
            avancer();
            break;
        default:
           printf ("Erreur : Attendu un opérateur.\n");
           exit(EXIT_FAILURE);
           break;
    }
}

// Fonction pour évaluer une opération arithmétique
int Evaluer(int vald, char op, int valg) {
    switch (op) {
        case PLUS:
            return vald + valg;
        case MOINS:
            return vald - valg;
        case MUL:
            return vald * valg;
        case DIV:
            if (valg == 0) {
                printf("Erreur : Division par zéro.\n");
                exit(EXIT_FAILURE);
            }
            return vald / valg;
        default:
            printf("Erreur : Opérateur non reconnu.\n");
            exit(EXIT_FAILURE);
    }
}

/*
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include "analyse_syntaxique.h"
#include "lecture_caracteres.h"
#include "analyse_lexicale.h"


void Rec_eaep(); 
void Rec_op(); 

void Rec_eaep (){
    Lexeme LC = lexeme_courant();

    switch (LC.nature){
        case ENTIER : 
            avancer();
        case PARO_lex : 
            avancer ();
            Rec_eaep();
            Rec_op ();
            Rec_eap();
            if (LC.nature = PARF){
                avancer(); }
            else {
                printf ("erreur syntaxique ");
                exit (1); 
            }
            break;

        default :
                break;     


            }    


    }


void Rec_op() {
    Lexeme LC = lexeme_courant();

    switch (LC.nature) {
        case PLUS:
        case MOINS:
        case MUL:
        case DIV:
            avancer();
            break;
        default:
            printf ("erreur syntaxique"); 
            break;
    }
}

void analyser_eaep(char *fichier) {
    demarrer(fichier);
    Rec_eaep();
    if (lexeme_courant().nature != FIN_SEQUENCE) {
        erreur_syntaxique("Séquence incorrecte.");
    }
    arreter();
}
*/












