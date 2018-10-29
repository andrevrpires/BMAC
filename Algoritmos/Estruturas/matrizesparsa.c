#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

/* define um bloco de uma matriz esparsa */
typedef struct _BlocoEsparsa{
 float valor;
 int linha;
 int coluna;
 struct _BlocoEsparsa *direita;
 struct _BlocoEsparsa *abaixo;
}BlocoEsparsa;

typedef BlocoEsparsa* MatrizEsparsa;

/* aloca um bloco para uma matriz esparsa */
BlocoEsparsa *AlocaBlocoEsparsa(){
 BlocoEsparsa *q;
 q = (BlocoEsparsa *)calloc(1, sizeof(BlocoEsparsa));
 return q;
}

/* prepara uma matriz esparsa com m linhas e n colunas */
MatrizEsparsa CriaMatrizEsparsa(int m, int n){

 MatrizEsparsa a;
 BlocoEsparsa *p,*pp;
 int k;
 
 a = AlocaBlocoEsparsa();
 a->linha  = m;
 a->coluna = n;
 a->abaixo  = a;
 a->direita = a;
 pp = a;
 for(k = 0; k < n; k++){
  p = AlocaBlocoEsparsa();
  p->linha  = INT_MAX;  
  p->coluna = k;
  p->abaixo  = p;
  p->direita = pp->direita;
  pp->direita = p;
  pp = p;
 }
 pp = a;
 for(k = 0; k < m; k++){
  p = AlocaBlocoEsparsa();
  p->linha  = k;
  p->coluna = INT_MAX;
  p->direita = p;
  p->abaixo  = pp->abaixo;
  pp->abaixo = p;
  pp = p;
 }
 return a;
}


void AtribuiMEsparsa(MatrizEsparsa a,int i,int j,float x){
 
 BlocoEsparsa *p,*q,*pp,*qq,*r;
 int k;
 
 p = a;
 q = a;

 for(k = 0; k <= i; k++) 
  p = p->abaixo;
 for(k = 0; k <= j; k++) 
  q = q->direita;
 
 do{
  pp = p;
  p  = p->direita;
 }while(p->coluna < j);
 
 do{
  qq = q;
  q  = q->abaixo;
 }while(q->linha < i);

 if(p->coluna == j){
  if(x != 0.0)
   p->valor = x;
  else{ 
  /*Remove elemento:*/
   qq->abaixo  = p->abaixo;
   pp->direita = p->direita;
   free(p);
  }
 }
 /*Insere elemento:*/
 else if(x != 0.0){ 
  r = AlocaBlocoEsparsa();
  r->coluna = j;
  r->linha  = i;
  r->valor  = x;    
  r->abaixo  = q;
  r->direita = p;
  qq->abaixo  = r;
  pp->direita = r;
 }
}

/*Consultar posição (i,j) da matriz.*/
float ValorMatrizEsparsa(MatrizEsparsa a,int i,int j){

 BlocoEsparsa *p;
 int k;

 p = a;
 for(k = 0; k <= i; k++) p = p->abaixo;

 do{
  p = p->direita;
 }while(p->coluna < j);

 if(p->coluna == j)
  return p->valor;
 else
  return 0.0;

}

void ImprimeMatrizEsparsa(MatrizEsparsa a){

 BlocoEsparsa *p,*q;
 int k,j;
 
 p = a;
 for(k = 1; k <= a->linha; k++){
  p = p->abaixo;
  q = p->direita;
  j = 0;
  
  while (q != p){
   for(; j < q->coluna; j++)
    printf(" %6.2f ", 0.0);
   printf(" %6.2f ", q->valor);
   j++;
   q = q->direita;
  }

  for(; j < a->coluna; j++)
    printf(" %6.2f ", 0.0);
  printf("\n");
 }
}

int main(){

 MatrizEsparsa a;
 int m,n;
 m = 4;
 n = 4;
 a = CriaMatrizEsparsa(m, n);
 AtribuiMEsparsa(a, 1, 2, 73);
 AtribuiMEsparsa(a, 3, 2, 90);
 AtribuiMEsparsa(a, 3, 0, 20);
 AtribuiMEsparsa(a, 0, 0, 82);
 AtribuiMEsparsa(a, 1, 0, 45);
 AtribuiMEsparsa(a, 3, 3, 18);

 ImprimeMatrizEsparsa(a);

 return 0;

}
