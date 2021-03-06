#include <stdio.h>
#include <stdlib.h>

/*Conta palavras numa string*/

void ContaPalavras(char str[], int *numpalavras){

 int i;

 i = 0;
 while(str[i] != '\0'){

  while(str[i] == ' ') i++;
  if(str[i] != '\0'){
   (*numpalavras)++;
   while(str[i] != ' '&& str[i] != '\0') i++;
  }
 }
}


void CopiaSubstr(char str[], char strcopia[], int inic, int fim){

 int i, j;

 j = 0;
 for(i = inic; i < fim; i++){ 
  strcopia[j] = str[i];
  j++;
 }

 strcopia[j] = '\0';
}


/*Separa uma frase-vetor em palavras-vetores. Retorna apontador duplo*/

char **VetordePalavras(char str[], int *numpalavras){

 char **VP = NULL, *palavra = NULL;
 int i, j, k;

 /*Conta Quantidade de Palavras*/
 ContaPalavras(str, numpalavras);

 /*Aloca memoria para o Vetor de Palavras*/
 VP = (char **)malloc((*numpalavras)*sizeof(char *));

 /*Encontra cada uma das palavras, cria seu vetor separado e coloca no Vetor de palavras*/
 j = 0;
 for(i = 0; i < (*numpalavras); i++){
 
  /*apaga espacos em branco até encontrar o comeco da palavra*/ 
  while(str[j] == ' ') j++;
  
  /*percorre a palavra até encontrar seu final*/
  k = j;
  while(str[k] != ' ' && str[k] != '\0') k++;

  /*aloca a memoria para a palavra*/
  palavra = malloc((k - j + 1)*sizeof(char));

  /*grava os caracteres da palavra na memoria alocada*/
  CopiaSubstr(str, palavra, j, k);

  /*grava o endereço da palavra no Vetor de Palavras*/
  VP[i] = palavra;
  j = k;
 }

 return VP;

}


int main(){
	
 char frase[200];
 int qtdpalavras = 0, i;
 char **F; 

 printf("Digite uma frase para ser splitada: ");
 scanf("%[^\n]", frase);

 F = VetordePalavras(frase, &qtdpalavras);

 for(i = 0; i < qtdpalavras; i++)
  printf("%s\n", F[i]);

 for(i = 0; i < qtdpalavras; i++)
  free(F[i]);
 free(F);

}
