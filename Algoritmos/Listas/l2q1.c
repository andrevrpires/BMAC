#include<stdio.h>
#include<stdlib.h>

typedef char TipoDado;
#include "./pilhas_lig.c"

int main(){

 char frase[] = "EXERCICIO MUITO COMPLICADO";
 char c;
 Pilha p;
 int i;

 p = CriaPilha();
 i = -1;
 do{
  i++;
  c = frase[i];
  if(c >= 'A' && c <= 'Z')
   Empilha(p, c);
  else{
   while(!PilhaVazia(p)){
    printf("%c", Desempilha(p));
   }
   printf("%c", c);
  }
 }while(c != '\0');
 printf("\n"); 
 LiberaPilha(p);
 return 0;

}

