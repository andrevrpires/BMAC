/*Este codigo contem toda a materia de listas ligadas da disciplina MAC0122, cursada no 2 semestre de 2018
  mais informacoes podem ser encontradas no site do professor:
  http://www.vision.ime.usp.br/~pmiranda/mac122_2s18/page/aulas_mac122.html#A6
*/


#include <stdio.h>
#include <stdlib.h>

/*Estrutura basica de um bloco de lista ligada (nao dupla)*/

struct Bloco{
 int dado;
 struct Bloco *prox;
};

/*Aloca um no (bloco)*/
struct Bloco *AlocaNoLista(){
 struct Bloco *q;
 q = (struct Bloco *)malloc(sizeof(struct Bloco)); 
 if(q == NULL)
  exit(1);
 return q;
}

/*Funcoes para listas Sem no cabeca*/
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

/*Funcoes para listas Com no cabeca*/
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

void RemoveAposCircular(struct Bloco *p){
 struct Bloco *q;
 q = p->prox;
 if(q != p){
  p->prox = q->prox;
  free(q);
 }
}

void ImprimeLista(struct Bloco *p){
 struct Bloco *q;
 q = p;
 while(q != NULL){
  printf("%d ", q->dado);
  q = q->prox;
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

struct Bloco *BuscaCircularCkbca(struct Bloco *p, int x){
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

void LiberaLista(struct Bloco *p){
 struct Bloco *q;
  while(p != NULL){
  q = p->prox;
  free(p);
  p = q;
 }
}

struct Bloco *InverteLista(struct Bloco *p){
 struct Bloco *q, *a = NULL;
 q = p;
 while(q != NULL){
  p = p->prox;
  q->prox = a;
  a = q;
  q = p;
 }
 return a;
}

/* Listas duplamente ligadas */
typedef int TipoDado;

typedef struct _BlocoDuplo{
 struct _BlocoDuplo *esq;
 TipoDado           dado;
 struct _BlocoDuplo *dir;
}BlocoDuplo;	

typedef *BlocoDuplo ListaDupla;

BlocoDuplo *AlocaNoListaDupla(){
 BlocoDuplo *q;
 q = (BlocoDuplo *)calloc(1, sizeof(BlocoDuplo));
 if(q == NULL) exit(1);
 return q;	
}

ListaDupla CriaNoKbcaDupla(){
 BlocoDuplo *q;
 q = AlocaNoListaDupla();
 q->esq = q;
 q->dado = -1;
 q->dir = q;
 return q;	
}

void ImprimeListaDuplaCircular(ListaDupla p){
 BlocoDuplo *q;
 q = p;
 do{
  ImprimeElemento(q->dado);
  q = q->dir;	
 }while(q!=p);
 printf("\n");
}

void ImprimeListaDuplaCircularReversa(ListaDupla p){
 BlocoDuplo *q;
 q = p;
 do{
  ImprimeElemento(q->dado);
  q = q->esq;	
 }while(q!=p);
 printf("\n");
}

void InsereDuplaCircular(BlocoDuplo *p, TipoDado x){
 BlocoDuplo *q;
 q = AlocaNoListaDupla();
 q->dado = x;
 q->dir = p->dir;
 p->dir = q;
 q->esq = p;
 q = q->dir;
 q->esq	 = p->dir;
}

/* Listas Duplamente Ligadas Permitem a remocao do proprio no recebido como argumento
 * Cuidado para nao remover o no kbca!!! */
void RemoveDuplaCircular(BlocoDuplo *p, TipoDado x){
 (p->esq)->dir = p->dir;
 (p->dir)->esq = p->esq;
 free(p);
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
