#include "automate.h"
#include "etat.h"
#include <iostream>

Automate::Automate(string chaine) {
    lexer = new Lexer(chaine);
    Etat0 * etatInitial = new Etat0();
    etats.push_back(etatInitial);
}

void Automate::executer() {
    bool reconnu = true;
    while(reconnu) {
        Symbole * s = lexer->Consulter();
        reconnu = etats.back()->transition(*this, s);
    }
}
void Automate::decalage(Symbole * s, Etat * e) {
    symboles.push_back(s);
    etats.push_back(e);
    if (s->estTerminal()) { 
        lexer->Avancer();
    }
}

void Automate::transition(Etat * e) {
    etats.push_back(e);
}

void Automate::reduction(int n, Symbole * s) {
    for(int i = 0; i < n; i++) {
        delete etats.back();
        etats.pop_back();
    }

    int resultat = 0;

    if (n == 1) {
        Entier * entier = (Entier *)symboles.back();
        resultat = entier->valeur;
        delete symboles.back();
        symboles.pop_back();
    } 
    else if (n == 3) {
        Symbole * sDroit = symboles.back();
        symboles.pop_back();
        
        Symbole * sMilieu = symboles.back();
        symboles.pop_back();
        
        Symbole * sGauche = symboles.back();
        symboles.pop_back();

        if (*sMilieu == PLUS) {
            resultat = ((Expr *)sGauche)->valeur + ((Expr *)sDroit)->valeur;
        } 
        else if (*sMilieu == MULT) {
            resultat = ((Expr *)sGauche)->valeur * ((Expr *)sDroit)->valeur;
        }
        else if (*sMilieu == EXPR) { 
            resultat = ((Expr *)sMilieu)->valeur;
        }

        delete sDroit; delete sMilieu; delete sGauche;
    }

    Expr * nouvelleExpression = new Expr(resultat);
    
    symboles.push_back(nouvelleExpression);
    etats.back()->transition(*this, nouvelleExpression);
}

void Automate::accepter() {
    Expr * resultatFinal = (Expr *)symboles.back();
    cout << "Resultat de l'evaluation : " << resultatFinal->valeur << endl;
}
