#include<stdio.h>
#include<stdlib.h>


typedef char TipoDado;
#include "./pilhas_lig.c"

int LiberaPilhaInt(Pilha p){
 Pilha q;
 q = p;
 while(q != NULL){
  p = p->prox;
  free(q);
  q = p;
 }
 return 0;
}

bool formaWcM(char X[]){

 char c, x;
 int i;
 Pilha p;

 p = CriaPilha();
 i = 0;

 do{
  c = X[i];
  if(c == 'c') return LiberaPilhaInt(p);
  Empilha(p, c); 
  i++;
 }while(X[i] != 'c');

 i++;

 do{
  if(PilhaVazia(p)) return LiberaPilhaInt(p);
  c = X[i];
  x = Desempilha(p);
  if(c != x) return false;
  i++;
 }while(X[i] != '\0');

 if(!PilhaVazia(p)) return LiberaPilhaInt(p);
 
 return LiberaPilhaInt(p) + 1;
} 

int main(){ 
  char X[] = "baabbcbbaab"; 
  if( formaWcM(X) ) 
    printf("Pertence\n"); 
  else 
    printf("Falso\n"); 
  return 0; 
}
