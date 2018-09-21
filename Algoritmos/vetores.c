#include <stdio.h>
#include <stdlib.h>

/*Inverte um vetor lido do prompt, onde o primeiro elemento eh seu tamanho*/



int main(){

 int tam, i, num;
 int *vet = NULL;

 /*leh tamanho do vetor*/
 scanf("%d", &tam);

 /*aloca vetor com n inteiros*/
 vet = (int *)malloc(tam*sizeof(int));

 /*grava no vetor*/
 for(i = 0;i < tam;i++){
  scanf("%d", &num);
  vet[i] = num;
 }

 /*printa invertido*/
 for(i = tam - 1;i >= 0;i--)
  printf("%d ", vet[i]);

 printf("\n");

 /*libera memoria*/
 free(vet);
 return 0;

}
