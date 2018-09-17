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
	printf("Digite o nome do arquivo: ");
	scanf("%s", arquivo);

	printf("size: %d", (int)sizeof(struct Aluno));

	fp = fopen(arquivo, "r");
	fscanf(fp, "%d", &nalunos);

	V = (struct Aluno *)malloc(sizeof(struct Aluno)*nalunos);

	for(i = 0; i < nalunos; i++)

		fscanf(fp, " %[^,],", V[i].nome);
		fscanf(fp, "%d,", &V[i].n_usp);	
		fscanf(fp, "%f,", &V[i].cr);
		fscanf(fp, " %c", &V[i].sexo);
		
	fclose(fp);

	for(i = 0; i < nalunos; i++)
		ImprimeAluno(V[i]);

	/*fp = fopen("saida.bin", "wb");

	fwrite(V, sizeof(struct Aluno), nalunos, fp);

	fclose(fp);

	V = (struct Aluno *)malloc(sizeof(struct Aluno)*nalunos);

	fp = fopen("saida.bin", "rb");

	fread(V, sizeof(struct Aluno), nalunos, fp);

	fclose(fp);*/

	free(V);

	return 0;
}
