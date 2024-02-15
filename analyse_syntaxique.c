

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













