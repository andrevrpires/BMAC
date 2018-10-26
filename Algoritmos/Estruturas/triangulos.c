#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Vertice{
 float x;
 float y;
};

struct Triangulo{
 struct Vertice A;
 struct Vertice B;
 struct Vertice C;
};

float Distancia(struct Vertice A, struct Vertice B){
 float dx, dy, d;
 dx = B.x - A.x;
 dy = B.y - A.y;
 d = sqrtf(dx*dx + dy*dy);
 return d;
}

float Perimetro(struct Triangulo T){
 float p = 0.0;
 p += Distancia(T.A, T.B);
 p += Distancia(T.B, T.C);
 p += Distancia(T.C, T.A);
 return p;
}

int main(){
 FILE *fp = NULL;
 int nentrada, nsaida = 0, i;
 struct Triangulo *T = NULL;

 /* Abrir arquivo de entrada*/
 fp = fopen("triangulos.txt", "r");
 if(fp == NULL){
  printf("Erro na leitura do arquivo de entrada\n");
  exit(1);
 }

 /* A primeira linha do arquivo contém a quantidade de triangulos*/
 fscanf(fp, "%d", &nentrada);
 
 /* Alocar vetor de estruturas e preencher com os dados do arquivo */
 T = (struct Triangulo *)malloc(nentrada*sizeof(struct Triangulo));
 if(T == NULL){
  printf("Erro na alocacao de memoria\n");
  exit(1); 
 }

 /* Preencher o vetor de triângulos*/
 for(i = 0; i < nentrada; i++){
  fscanf(fp, "%f %f", &T[i].A.x, &T[i].A.y);
  fscanf(fp, "%f %f", &T[i].B.x, &T[i].B.y);
  fscanf(fp, "%f %f", &T[i].C.x, &T[i].C.y);
  if(Perimetro(T[i]) > 0.5) nsaida++;
 }

 /* Fechar arquivo de entrada*/
 fclose(fp);


 /* Criar um arquivo de saida que contem somente os dados dos triangulos com perimetro > 0.5 */
 /* Obs.: A primeira linha do arquivo deve conter o num de registros. As demais linhas devem conter os dados(um triangulo por linha) */
 /* Abrir arquivo de saida*/
 fp = fopen("saidatriangulos.txt", "w");
 
 /* A primeira linha do arquivo deve conter a quantidade de triangulos*/
 fprintf(fp, "%d\n", nsaida);
 
 /* Preencher o arquivo */
 for(i = 0; i < nentrada; i++){
  if(Perimetro(T[i]) > 0.5){
   fprintf(fp, "%.2f %.2f ", T[i].A.x, T[i].A.y);
   fprintf(fp, "%.2f %.2f ", T[i].B.x, T[i].B.y);
   fprintf(fp, "%.2f %.2f\n", T[i].C.x, T[i].C.y);
  }
 }
 
 /* Fechar arquivo de saida e desalocar o vetor*/
 fclose(fp);
 free(T);
 return 0;
}
