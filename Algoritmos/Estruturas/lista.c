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

void InsereListaSkbca(struct Bloco **p, int x){
 struct Bloco *n, *t;
 t = *p;
 n = AlocaNoLista();
 n->dado = x;
 n->prox = t;
 t = n;
}

void RemoveListaSkbca(struct Bloco **p){
 struct Bloco *r;
 r = *p;
 if(r != NULL){
  *p = r->prox;
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

struct Bloco *CriaNoKbcaCircular(){
 struct Bloco *q;
 q = AlocaNoLista();
 q->dado = -1;
 q->prox = q;
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
 struct Bloco *q;
 q = AlocaNoLista();
 q->dado = x;
 q->prox = p->prox;
 p->prox = q;
}

void RemoveAposCircular(struct Bloco *p){
 struct Bloco *q;
 q = p->prox;
 if(q != p){
  p->prox = q->prox;
  free(q);
 }
}

void InsereAposCircularSkbca(struct Bloco **p, int x){
 struct Bloco *q, *t;
 t = *p;
 q = AlocaNoLista();
 if(t == NULL){
  q->prox = q;
  t = q;
 }
 else{
  q->prox = t->prox;
  t->prox = q;
 }
}

void RemoveAposCircularSkbca(struct Bloco **p){
 struct Bloco *q;
 struct Bloco *t;
 t = *p;
 if(t == NULL) return;
 q = t->prox;
 if(q == t) t = NULL;
 else t->prox = q->prox;
 free(q);
}

void ImprimeLista(struct Bloco *L){
 struct Bloco *T;
 T = L;
 while(T != NULL){
  printf("%d ", T->dado);
  T = T->prox;
 }
 printf("\n");
}

void ImprimeCircular(struct Bloco *p){
 struct Bloco *q;
 q = p;
 if(q == NULL)
  printf("Lista vazia\n");
 else{
  do{
   printf(" %2d",q->dado);
   q = q->prox;
  }while(q != p);
 printf("\n");
 }
}

struct Bloco *BuscaCircular(struct Bloco *p, int x){
 struct Bloco *q;
 if(p == NULL) return NULL;
 q = p;
 do{
  if(q->dado == x) return q;
  q = q->prox;
 }while(q != p);
 return NULL;
}

/* O parâmetro p deve apontar para o nó-cabeça. 
A função devolve o apontador para o primeiro 
nó que contém o dado x. */
struct Bloco * BuscaCircularCkbca(struct Bloco *p, int x){
 struct Bloco *q;
 p->dado = x;
 q = p;
 do{
  q = q->prox;
 }while(q->dado != x);
 p->dado = -1;
 if(q == p) return NULL;
 else return q;
}
	

void LiberaLista(struct Bloco *L){
 struct Bloco *P;
  while(L != NULL){
  P = L->prox;
  free(L);
  L = P;
 }
}

struct Bloco *InverteLista(struct Bloco *L){
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
 ImprimeLista(L);
 
 /*inverter a lista sem gerar memoria, soh trocando os apontadores*/
 L = InverteLista(L);

 /*Imprimir a lista invertida*/
 ImprimeLista(L);
 
 /*Liberar Memoria*/
 LiberaLista(L);

 return 0;
}
