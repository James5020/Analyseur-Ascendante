#include "etat.h"
#include "automate.h"

Etat::Etat() {}
Etat::~Etat() {}

bool Etat0::transition(Automate & automate, Symbole * s) {
    switch(*s) {
        case INT: automate.decalage(s, new Etat3()); break;
        case OPENPAR: automate.decalage(s, new Etat2()); break;
        case EXPR: automate.transition(new Etat1()); break;
        default: return false;
    }
    return true;
}

bool Etat1::transition(Automate & automate, Symbole * s) {
    switch(*s) {
        case PLUS: automate.decalage(s, new Etat4()); break;
        case MULT: automate.decalage(s, new Etat5()); break;
        case FIN: automate.accepter(); return false ;
        default: return false;
    }
    return true;
}

bool Etat2::transition(Automate & automate, Symbole * s) {
    switch(*s) {
        case INT: automate.decalage(s, new Etat3()); break;
        case OPENPAR: automate.decalage(s, new Etat2()); break;
        case EXPR: automate.transition(new Etat6()); break;
        default: return false;
    }
    return true;
}

bool Etat3::transition(Automate & automate, Symbole * s) {
    switch(*s) {
        case PLUS: case MULT: case CLOSEPAR: case FIN:
            automate.reduction(1, s); return true;
        default: return false;
    }
}

bool Etat4::transition(Automate & automate, Symbole * s) {
    switch(*s) {
        case INT: automate.decalage(s, new Etat3()); break;
        case OPENPAR: automate.decalage(s, new Etat2()); break;
        case EXPR: automate.transition(new Etat7()); break;
        default: return false;
    }
    return true;
}

bool Etat5::transition(Automate & automate, Symbole * s) {
    switch(*s) {
        case INT: automate.decalage(s, new Etat3()); break;
        case OPENPAR: automate.decalage(s, new Etat2()); break;
        case EXPR: automate.transition(new Etat8()); break;
        default: return false;
    }
    return true;
}

bool Etat6::transition(Automate & automate, Symbole * s) {
    switch(*s) {
        case PLUS: automate.decalage(s, new Etat4()); break;
        case MULT: automate.decalage(s, new Etat5()); break;
        case CLOSEPAR: automate.decalage(s, new Etat9()); break;
        default: return false;
    }
    return true;
}

bool Etat7::transition(Automate & automate, Symbole * s) {
    switch(*s) {
        case PLUS: automate.reduction(3, s); return true;
        case MULT: automate.decalage(s, new Etat5()); return true;
        case CLOSEPAR: case FIN: automate.reduction(3, s); return true;
        default: return false;
    }
}

bool Etat8::transition(Automate & automate, Symbole * s) {
    switch(*s) {
        case PLUS: case MULT: case CLOSEPAR: case FIN:
            automate.reduction(3, s); return true;
        default: return false;
    }
}

bool Etat9::transition(Automate & automate, Symbole * s) {
    switch(*s) {
        case PLUS: case MULT: case CLOSEPAR: case FIN:
            automate.reduction(3, s); return true;
        default: return false;
    }
}