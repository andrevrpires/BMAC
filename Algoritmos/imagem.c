#include<stdio.h>
#include<stdlib.h>

int main(){

 char arquivo[100];
 char tipo[10];
 FILE *fp;
 int **M;
 int *tmp;
 int nlinhas, ncolunas, valmax, i, j;


 /*ler nome do arquivo*/
 printf("Digite o nome do arquivo: ");
 scanf("%s", arquivo);


 /*abrir arquivo*/
 fp = fopen(arquivo, "r");
 if(fp == NULL){
  printf("Erro ao abrir o arquivo\n");
  return 0;
 }


 /*ler cabecalho arquivo*/
 fscanf(fp, "%s", tipo);
 fscanf(fp, "%d %d", &ncolunas, &nlinhas);
 fscanf(fp, "%d", &valmax);


 /*aloca memoria matriz*/
 
 /*linhas*/
 M = (int **)malloc(sizeof(int *)*nlinhas);
 if(M == NULL){
  printf("Erro ao alocar a matriz\n");
  return 0;
 }
 
 /*colunas*/
 for(i = 0; i < nlinhas; i++){
  M[i] = (int *)malloc(sizeof(int)*ncolunas);
  if(M[i] == NULL){
   printf("Erro ao alocar a linha %d\n", i);
   return 0;
  }
 }


 /*preenche matriz com dados do arquivo*/
 for(i = 0; i < nlinhas; i++)
  for(j = 0; j < ncolunas; j++)
   fscanf(fp, "%d", &M[i][j]);

 fclose(fp);

 /*processa matriz*/
 for(i = 0; i < nlinhas/2; i++){
  tmp = M[i];
  M[i] = M[nlinhas -1 -i];
  M[nlinhas -1 -i] = tmp;
 }

 /*salva dados*/
 fp = fopen("saida.pgm", "w");
 fprintf(fp, "P2\n");
 fprintf(fp, "%d %d\n", ncolunas, nlinhas);
 fprintf(fp, "%d\n", valmax);
 for(i = 0; i < nlinhas; i++){
  for(j = 0; j < ncolunas; j++)
   fprintf(fp, "%d ", M[i][j]);
  fprintf(fp, "\n");
 }
 fclose(fp);
 
 /*libera memoria*/
 for(i = 0; i < nlinhas; i++)
  free(M[i]);
 free(M);

 return 0;

}
