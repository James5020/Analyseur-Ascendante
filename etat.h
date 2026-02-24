#pragma once
#include "symbole.h"

class Automate;

class Etat {
public:
    Etat();
    virtual ~Etat();
    virtual bool transition(Automate & automate, Symbole * s) = 0;
};

class Etat0 : public Etat { public: bool transition(Automate & automate, Symbole * s) override; };
class Etat1 : public Etat { public: bool transition(Automate & automate, Symbole * s) override; };
class Etat2 : public Etat { public: bool transition(Automate & automate, Symbole * s) override; };
class Etat3 : public Etat { public: bool transition(Automate & automate, Symbole * s) override; };
class Etat4 : public Etat { public: bool transition(Automate & automate, Symbole * s) override; };
class Etat5 : public Etat { public: bool transition(Automate & automate, Symbole * s) override; };
class Etat6 : public Etat { public: bool transition(Automate & automate, Symbole * s) override; };
class Etat7 : public Etat { public: bool transition(Automate & automate, Symbole * s) override; };
class Etat8 : public Etat { public: bool transition(Automate & automate, Symbole * s) override; };
class Etat9 : public Etat { public: bool transition(Automate & automate, Symbole * s) override; };