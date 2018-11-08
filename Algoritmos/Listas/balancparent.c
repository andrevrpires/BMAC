#include<stdio.h>
#include<stdlib.h>

typedef char TipoDado;
#include "pilhas_lig.c"

bool AbreParenteses(char c){
 return (c == '('||c == '['||c == '{');
}

bool ParParenteses(char abre, char fecha){
 if(fecha == ')') return (abre == '(');
 if(fecha == ']') return (abre == '[');
 if(fecha == '}') return (abre == '{');
}

bool ParentesesBalanceados(char cadeia[]){

 int i;
 char c;
 Pilha P;
 bool r = true;

 P = CriaPilha();
 i = 0;
 while(cadeia[i] != '\0'){
  c = cadeia[i];
  if(AbreParenteses(c)) Empilha(P, c); 
  else{
   if(PilhaVazia(P)) { r = false; break; }
   if(!ParParenteses(Desempilha(P), c)) { r = false; break; }
  }
  i++;
 }

 if(!PilhaVazia(P)) r = false;
 LiberaPilha(P);

 return r;
}

int main(){

 char cadeia[] = "([](([{[[]]}]))[()])}";
 
 if(ParentesesBalanceados(cadeia))
  printf("Correto\n");
 else
  printf("Incorreto\n");
 
 return 0;

}
