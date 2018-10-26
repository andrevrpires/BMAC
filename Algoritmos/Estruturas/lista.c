#include <stdio.h>
#include <stdlib.h>

struct Bloco{
 int dado;
 struct Bloco *prox;
};

struct Bloco *AlocaNoLista(){
 struct Bloco *q;
 q = (struct Bloco *)malloc(sizeof(struct Bloco)); 
 if(q == NULL)
  exit(1);
 return q;
}

void InsereAposListaLSskbca(struct Bloco **p, int x){
 struct Bloco *n, *q;
 q = *p
 n = AlocaNoLista();
 n->dado = x;
 n->prox = q;
 *p = n;
}

void RemoveAposListaLSskbca(struct Bloco **p){
 struct Bloco *r;
 r = *p;
 if(r != NULL){
  *p = r-prox;
  free(r);
 }
}

struct Bloco *CriaNoKbca(){
 struct Bloco *q;
 q = AlocaNoLista();
 q->dado = -1;
 q->prox = NULL;
 return q;
}

void InsereAposLista(struct Bloco *p, int x){
 struct Bloco *q;
 q = AlocaNoLista();
 q->dado = x;
 q->prox = p->prox;
 p->prox = q;
}

void RemoveAposLista(struct Bloco *p){
 struct Bloco *q;
 q = p->prox;
 if(q != NULL){
  p->prox = q->prox;
  free(q);
 }
}

void InsereAposCircular(struct Bloco *p, int x){

}

void RemoveAposCircular(struct Bloco *p){

}

void Imprimelista(struct Bloco *L){
 struct Bloco *T;
  T = L;
  while(T != NULL){
  printf("%d ", T->dado);
  T = T->prox;
 }
 printf("\n");
}

void ImprimeCircular(struct Bloco *p){

}

void BuscaCircular(struct Bloco *p, int x)

{}

void Liberalista(struct Bloco *L){
 struct Bloco *P;
  while(L != NULL){
  P = L->prox;
  free(L);
  L = P;
 }
}

struct Bloco *Invertelista(struct Bloco *L){
 struct Bloco *I, *A = NULL;
 I = L;
 while(I != NULL){
  L = L->prox;
  I->prox = A;
  A = I;
  I = L;
 }
 return A;
}

int main(){
 struct Bloco *L = NULL, *N;
 int i;

 for (i = 0; i < 4; i++){
  N = (struct Bloco  *)malloc(sizeof(struct Bloco)); 
  N->dado = i;
  N->prox = L;
  L = N;
 }

 /*Imprimir a lista*/
 Imprimelista(L);
 
 /*inverter a lista sem gerar memoria, soh trocando os apontadores*/
 L = Invertelista(L);

 /*Imprimir a lista invertida*/
 Imprimelista(L);
 
 /*Liberar Memoria*/
 Liberalista(L);

 return 0;
}
