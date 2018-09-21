#include <stdio.h>
#include <stdlib.h>

int main(){
	char nome[120];
	char tipo[10];
	FILE *fp;
	int **M;
	int *tmp;
	int nlinhas, ncolunas, valmax, i, j;

	printf("Digite o nome do arquvo: ");
	scanf("%s", nome);

	fp = fopen(nome, "r");
	if(fp == NULL){
		printf("Erro na leitura\n");
		return 0;
	}

	fscanf(fp, "%s", tipo);
	fscanf(fp, "%d %d", &ncolunas, &nlinhas);
	fscanf(fp, "%d", &valmax);


	M = (int **)malloc(sizeof(int*)*nlinhas);
	if(M == NULL){
		printf("Erro ao alocar a matriz\n");
		return 0;
	}

	for(i = 0; i < nlinhas; i++)
		M[i] = (int *)malloc(sizeof(int)*ncolunas);
		if(M == NULL){
			printf("Erro ao alocar a matriz\n");
			return 0;
		}

	for(i = 0; i < nlinhas; i++)
		for(j = 0; j < ncolunas; j++)
			fscanf(fp, "%d", &M[i][j]);

	fclose(fp);

	/*processamento da imagem*/

	for(i = 0; i < nlinhas/2; i++)
		tmp = M[i];
		M[i] = M[nlinhas - i];
		M[nlinhas - i] = tmp;

	/*gravacao da imagem*/

	fp = fopen("saida.pgm", "w");

	fprintf(fp, "P2\n");
	fprintf(fp, "%d %d\n", ncolunas, nlinhas);
	fprintf(fp, "%d\n", valmax);

	for(i = 0; i < nlinhas; i++)
		for(j = 0; j < ncolunas; j++)
			fprintf(fp, "%d ", M[i][j]);
		fprintf(fp, "\n");
	
	fclose(fp);
	
	/*liberacao de memoria*/
	for(i = 0; i < nlinhas; i++)
		free(M[i]);
	free(M);

	return(0);
}

