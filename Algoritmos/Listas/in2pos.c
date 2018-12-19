#include<stdio.h>
#include<stdlib.h>

typedef int TipoDado;

#include "pilhas_lig.c"

int ValorOperador(char c){

 switch(c){
  case '(':
   return 0;
  case '+':
  case '-': 
   return 1;
  case '*':
  case '/':
   return 2;
  case '^':
   return 3;
 }
 exit(-1);
}

bool Precedencia(char t, char c){
 return (ValorOperador(t) > ValorOperador(c) && ValorOperador(t) != 3);
}

void In2Pos(char expr[]){
 Pilha P;
 int i;
 char c, t;

 P = CriaPilha();

 i = 0;
 Empilha(P,'(');
 do{
 
  c = expr[i];
  i++;

  switch(c){
   case '(':
    Empilha(P, c);
    break;
   case ')':
   case '\0':
    t = Desempilha(P);
    while(t != '('){
     printf("%c", t);
     t = Desempilha(P);
    }
    break;
   case '+':
   case '-':
   case '*':
   case '/':
   case '^':
    t = Desempilha(P);
    if(Precedencia(t, c)){
     printf("%c", t);
     Empilha(P, c);
    }
    else{
     Empilha(P, t);
     Empilha(P, c);
    }
    break;
   default:
    printf("%c", c);
  }
 
 }while(c != '\0');

 LiberaPilha(P);
 printf("\n");
}

int main(){

 char expr[]="a*(b+c)*(d-g)^h^i*j";
 
 In2Pos(expr);
 
 return 0;
}
