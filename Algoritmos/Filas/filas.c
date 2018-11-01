#include<stdlib.h>
#include<stdio.h>

typedef int TipoDado;

typedef struct _BlocoFila{
 TipoDado           dado;
 struct _BlocoFila *prox;
}BlocoFila;


typedef BlocoFila *Fila;
typedef enum boolean {true, false} bool;

BlocoFila *AlocaNoFila(){
 BlocoFila *q;
 q = (BlocoFila *)calloc(1, sizeof(BlocoFila));
 if(q == NULL) exit(-1);
 return q;
}

Fila CriaFila(){
 Fila q;
 q = AlocaNoFila();
 q->dado = -1;
 q->prox = q;
 return q;
}

void LiberaFila(Fila f){
 Fila q, t;
 q = f->prox;
 while(q != f){
  t = q; 
  q = q->prox;
  free(t);
 }
 free(q);
}

bool FilaVazia(Fila f){
 return f->prox == f;
}

void InsereFila(Fila *f, TipoDado x){
 BlocoFila *q, *t;
 q = AlocaNoFila();
 if(q == NULL) exit(-1);
 t = *f;
 q->dado = x;
 q->prox = t->prox;
 t->prox = q;
 *f = q;
}

TipoDado RemoveFila(Fila *f){
 BlocoFila *q, *t;
 TipoDado x;
 t = (*f)->prox;
 if(FilaVazia(t)) exit(-1);
 q = t->prox;
 x = q->dado;
 t->prox = q->prox;
 if(q == *f) *f = t;
 free(q);
 return x;
}

/*
int main(){

 Fila f;
 f = CriaFila();
 InsereFila(&f, 1);
 InsereFila(&f, 3);
 InsereFila(&f, 5);
 InsereFila(&f, 8);
 while(!FilaVazia(f))
  printf("%d ", RemoveFila(&f));
 printf("\n");
 LiberaFila(f);
 return 0;

}
*/
