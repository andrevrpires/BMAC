#include<stdio.h>
#include<stdlib.h>

typedef char TipoDado;
#include "pilhas_lig.c"

bool ParParenteses(char abre, char fecha){
 if(fecha == ')') return (abre == '(');
 if(fecha == ']') return (abre == '[');
 if(fecha == '}') return (abre == '{');
}

bool ParentesesBalanceados(char cadeia[]){

 int i;
 char c;
 Pilha P;
 bool r = false, continua = true;

 P = CriaPilha();
 i = -1;
 while(continua){
  i++;	 
  c = cadeia[i];
  switch(c){
   case '\0':
    r = PilhaVazia(P);
    continua = false;
    break;
   case '(':
   case '[':
   case '{':
    Empilha(P, c); 
    break;
   default:
    if(PilhaVazia(P) || !ParParenteses(Desempilha(P), c))
     continua = false;
  }
 }

 LiberaPilha(P);
 return r;
}

int main(){

 char cadeia[] = "(([](([{[[]]}]))[()])";
 
 if(ParentesesBalanceados(cadeia))
  printf("Correto\n");
 else
  printf("Incorreto\n");
 
 return 0;

}
