#include <stdio.h>
#define LIM 500
#define NLETRAS ('z' - 'a' + 1)

int main(){

	char texto[LIM];
	int freq[NLETRAS];
	int i;
	char c;

	/* Lê uma linha de texto */
	scanf("%[^\n]", texto);

	/*Inicializa com zeros o vetor de contadores*/
	for( i = 0 ; i < NLETRAS ; i++)
		freq[i] = 0;

	/*Percorre o texto contando as letras*/
	i = 0;
	while( texto[i] != '\0' ){
	
		c = texto[i];

		/*Identifica Maiúscula*/
		if (c <= 'z' && c >= 'a')
		       freq[ c - 'a' ]++;	

		/*Identifica Minúscula*/
		else if (c <= 'Z' && c >= 'A') 
			freq[ c - 'A' ]++;

		i++;

	} 

	/*Printa quantas ocorrências por letra*/
	for( i = 0 ; i < NLETRAS ; i++ ) {
		if( freq[i] != 0 )
			printf("%c = %d\n", 'a' + i, freq[i]);
	}

	return 0;
}
