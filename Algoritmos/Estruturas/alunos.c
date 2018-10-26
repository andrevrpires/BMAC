#include <stdio.h>
#include <stdlib.h>

struct Aluno{
 char nome[100];
 int n_usp;
 float cr;
 char sexo;
};

void ImprimeAluno(struct Aluno A){
 printf("Nome: %s\n", A.nome);
 printf("N_USP: %d\n", A.n_usp);
 printf("CR: %.2f\n", A.cr);
 printf("Sexo: %c\n\n", A.sexo);
}

int main(){
 char arquivo[100];
 FILE *fp;
 int nalunos, i;
 struct Aluno *V;

 /*Recebe o nome do Arquivo*/
 printf("Digite o nome do arquivo: ");
 scanf("%s", arquivo);
 printf("\n");

 /*printf("size: %d", (int)sizeof(struct Aluno));*/

 /*A primeira linha do arquivo contem o numero total de alunos*/
 fp = fopen(arquivo, "r");
 fscanf(fp, "%d", &nalunos);

 /*Podemos entao alocar a memoria necessaria*/
 V = (struct Aluno *)malloc(sizeof(struct Aluno)*nalunos);

 /*Carregar os dados no vetor*/
 for(i = 0; i < nalunos; i++){
  fscanf(fp, " %[^,],", V[i].nome);
  fscanf(fp, "%d,", &V[i].n_usp);	
  fscanf(fp, "%f,", &V[i].cr);
  fscanf(fp, " %c", &V[i].sexo);
 }

 /*Fechar o arquivo de entrada de dados*/
 fclose(fp);

 /*Printa os dados do vetor*/
 for(i = 0; i < nalunos; i++)
  ImprimeAluno(V[i]);

 /*Salva no arquivo em binario e libera memoria*/
 fp = fopen("saida.bin", "wb");
 fwrite(V, sizeof(struct Aluno), nalunos, fp);
 fclose(fp);
 free(V);

 /*Testa o arquivo binario*/
 /*
 V = (struct Aluno *)malloc(sizeof(struct Aluno)*nalunos);
 fp = fopen("saida.bin", "rb");
 fread(V, sizeof(struct Aluno), nalunos, fp);
 fclose(fp);

 for(i = 0; i < nalunos; i++)
  ImprimeAluno(V[i]);

 free(V);
 */

 return 0;
}
