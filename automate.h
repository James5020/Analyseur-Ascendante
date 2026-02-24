#pragma once
#include <deque>
#include "symbole.h"
#include "lexer.h"
#include "etat.h"

using namespace std;

class Automate{
    public:
    Automate(string chaine);
    Automate();
    
    void executer(); // Lance l'analyse
    void decalage(Symbole * s, Etat * e);
    void reduction(int n, Symbole * s);
    void transition(Etat * e); // Utilisé par les non-terminaux
    void accepter();

protected:
    deque<Symbole *> symboles;
    deque<Etat *> etats;
    Lexer * lexer;
};