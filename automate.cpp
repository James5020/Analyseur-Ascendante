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
        // On appelle la transition sur l'état au sommet de la pile
        reconnu = etats.back()->transition(*this, s);
    }
}
void Automate::decalage(Symbole * s, Etat * e) {
    symboles.push_back(s);
    etats.push_back(e);
    if (s->estTerminal()) { // Optionnel: vérification de sécurité
        lexer->Avancer();
    }
}

void Automate::transition(Etat * e) {
    etats.push_back(e);
}

void Automate::reduction(int n, Symbole * s) {
    // 1. On dépile n états
    for(int i = 0; i < n; i++) {
        delete etats.back();
        etats.pop_back();
    }

    // 2. On évalue la règle en dépilant les symboles
    int resultat = 0;

    if (n == 1) {
        // Règle E -> val
        Entier * entier = (Entier *)symboles.back();
        resultat = entier->valeur;
        delete symboles.back();
        symboles.pop_back();
    } 
    else if (n == 3) {
        // Règle E -> E + E, E -> E * E, ou E -> (E)
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
            // Cas E -> (E) : le milieu est l'expression, la gauche est '('
            resultat = ((Expr *)sMilieu)->valeur;
        }

        // Nettoyage de la mémoire
        delete sDroit; delete sMilieu; delete sGauche;
    }

    // 3. On crée le nouveau non-terminal avec le résultat et on l'empile
    Expr * nouvelleExpression = new Expr(resultat);
    
    symboles.push_back(nouvelleExpression);
    // 4. On demande à l'état qui se retrouve au sommet de faire sa transition avec ce nouveau symbole 'E'
    etats.back()->transition(*this, nouvelleExpression);
}

void Automate::accepter() {
    Expr * resultatFinal = (Expr *)symboles.back();
    cout << "Resultat de l'evaluation : " << resultatFinal->valeur << endl;
}