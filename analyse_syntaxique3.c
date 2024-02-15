#include "analyse_syntaxique.h"
#include "lecture_caracteres.h"
#include "analyse_lexicale.h"

#include <stdio.h>
// Fonctions récursives pour reconnaître les éléments de la grammaire
void Rec_eag();
void Rec_seq_terme();
void Rec_suite_seq_terme();
void Rec_terme();
void Rec_seq_facteur();
void Rec_suite_seq_facteur();
void Rec_facteur();
void Rec_op1();
void Rec_op2();




void analyser(char *fichier) {
    demarrer(fichier);
    Rec_eag();
    if (lexeme_courant().nature != FIN_SEQUENCE) {
        printf("Erreur syntaxique.\n");
        exit(0);
    }
    arreter();
}

/*eag → seq terme*/
void Rec_eag() {
    Rec_seq_terme();
    if (lexeme_courant().nature != FIN_SEQUENCE) {
        printf("Erreur syntaxique : Fin de séquence attendue.\n");
        exit(0);
    }
}

/*seq terme → terme suite seq terme*/
void Rec_seq_terme() {
    Rec_terme();
    Rec_suite_seq_terme();
}


/*suite seq terme → op1 terme suite seq terme [PLUS, MOINS]
suite seq terme → ε
*/
void Rec_suite_seq_terme() {
    switch (lexeme_courant().nature) {
        case PLUS:
        case MOINS:
            Rec_op1();
            Rec_terme();
            Rec_suite_seq_terme();
            break;
        default:
            // Rien à faire, epsilon
            break;
    }
}

/* Terme -> Seq_facteur*/
void Rec_terme() {
    Rec_seq_facteur();
}

/*Seq_facteur -> Facteur Suite_seq_facteur*/
void Rec_seq_facteur() {
    Rec_facteur();
    Rec_suite_seq_facteur();
}

/*suite seq f acteur → op2 f acteur suite seq f acteur*/

void Rec_suite_seq_facteur() {
    switch (lexeme_courant().nature) {
        case MUL:
            Rec_op2();
            Rec_facteur();
            Rec_suite_seq_facteur();
            break;
        default:
            // Rien à faire, epsilon
            break;
    }
}


/*facteur → ENTIER
facteur → PARO eag PARF*/
void Rec_facteur() {
    switch (lexeme_courant().nature) {
        case ENTIER:
            avancer();
            break;
        case PARO:
            avancer();
            Rec_eag();
            if (lexeme_courant().nature == PARF) {
                avancer();
            } else {
                printf("Erreur syntaxique : Parenthèse fermante attendue.\n");
                exit(0);
            }
            break;
        default:
            printf("Erreur syntaxique : Facteur attendu (ENTIER ou PARO).\n");
            exit(0);
    }
}


/*op1 → PLUS
op1 → MOINS*/
void Rec_op1() {
    switch (lexeme_courant().nature) {
        case PLUS:
        case MOINS:
            avancer();
            break;
        default:
            printf("Erreur syntaxique : Opérateur d'addition ou soustraction attendu.\n");
            exit(0);
    }
}


/*Idem pour Rec op2 -> MUL*/
void Rec_op2() {
    if (lexeme_courant().nature == MUL) {
        avancer();
    } else {
        printf("Erreur syntaxique : Opérateur de multiplication attendu.\n");
        exit(0);
    }
}
