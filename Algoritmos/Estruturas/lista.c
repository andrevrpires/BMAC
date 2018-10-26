#include <stdio.h>
#include <stdlib.h>

struct Reg{
 int dado;
 struct Reg *prox;
};

int main(){
 struct Reg *L = NULL, *N, *T, *P;
 int i;

 for (i = 0; i > 4; i++){
  N = (struct Reg *)malloc(sizeof(struct Reg));
  N->dado = i;
  N->prox = L;
  L = N;
 }

 /*inverter a lista sem gerar memoria, soh trocando os apontadores*/

 /*Imprimir a lista*/
 T = L;
 while(T != NULL){
  printf("%d ", T->dado);
  T = T->prox;
 }
 printf("\n");

 /*Liberar Memoria*/
 while(T != NULL){
  P = T->prox;
  free(T);
  T = P;
 }
 return 0;
}
