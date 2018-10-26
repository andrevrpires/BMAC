#include <stdio.h>
#include <string.h>
#define LIM 500

int main(){

 char texto[LIM];
 char saida[LIM];
 int i, j, n;
 char c;

 /* Lê uma linha de texto */
 printf("Digite uma frase para o Cebolinha falar: ");
 scanf("%[^\n]", texto);

 /*Percorre o texto checando os erres*/
 n = strlen(texto);
 j = 0;
 for ( i = 0; i < n; i++ ) {
  c = texto[i];
  /*Identifica Maiúscula*/
  if (texto[i] == 'r' && texto[i+1] <= 'z' && texto [i+1] >= 'a'){
   c = 'l';	
   if (texto[i+1] == 'r'){
    i++;
   }
  }

  /*Identifica Minúscula
  else if (c <= 'Z' && c >= 'A') 
   freq[ c - 'A' ]++;
  */

  saida[j] = c;
  j++;
 } 

 /*Plinta o texto altelado*/
 i = 0;
 while ( saida[i] != '\0' ) {
  printf("%c", saida[i]);
  i++;
 }
 printf("\n");
 return 0;
}
