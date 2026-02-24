#include <iostream>
#include "lexer.h"
#include "automate.h"

int main(void) {
   string chaine;
   cout << "Veuillez entrer une expression : ";
   cin >> chaine;
   /*
   Lexer l(chaine);

   Symbole * s;
   while(*(s=l.Consulter())!=FIN) {
      s->Affiche();
      cout<<endl;

      l.Avancer();
   }
      */
   Automate automate(chaine);
   automate.executer();

   return 0;
}

