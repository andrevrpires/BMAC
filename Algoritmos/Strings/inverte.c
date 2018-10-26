#include<stdio.h>
#include<stdlib.h>

int main(){

 int *V = NULL;
 int n, i, num;

 /*le tamanho do vetor*/
 scanf("%d", &n);

 /*aloca vetor*/
 V = malloc(n*sizeof(int));

 /*preenche vetor*/
 for(i = 0;i < n; i++){
  scanf("%d", &num);
  V[i] = num;
 }

 /*imprime invertido*/
 for(i = n-1;i >= 0; i--)
  printf(" %d", V[i]);
 printf("\n");

 /*libera memoria*/
 free(V);

 return 0;

}
