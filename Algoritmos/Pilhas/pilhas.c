#include<stdlib.h>
#include<stdio.h>

/* Pilha com lista ligada */

typedef int TipoDado;

typedef struct _BlocoPilha{
 TipoDado            dado;
 struct _BlocoPilha *prox;
}BlocoPilha;

typedef BlocoPilha *Pilha;

typedef enum boolean {false, true} bool;

BlocoPilha *AlocaPilha(){
 BlocoPilha *q;
 q = (BlocoPilha *)calloc(1, sizeof(BlocoPilha));
 if(q == NULL) exit(-1);
 return q;
}

Pilha CriaPilha(){
 Pilha q;
 q = AlocaPilha();
 q->prox = NULL;
 return q;
}

void LiberaPilha(Pilha p){
 Pilha q;
 q = p;
 while(q != NULL){
  p = p->prox;
  free(q);
  q = p;
 }
}

bool PilhaVazia(Pilha p){
 return (p->prox == NULL);
}

void Empilha(Pilha p, TipoDado x){
 Pilha q;
 q = AlocaPilha();
 q->dado = x;
 q->prox = p->prox;
 p->prox = q;
}

TipoDado Desempilha(Pilha p){
 TipoDado x;
 Pilha q;
 if(PilhaVazia) exit(-1);
 q = p->prox;
 x = q->dado;
 p->prox = q->prox;
 free(q);
 return x;
}


/* Pilha sequencial */

#define TAM_MAX 1000

typedef struct _VetorPilha{
 int          topo;
 TipoDado     array[TAM_MAX];
}VetorPilha;

typedef VetorPilha *PilhaSeq;

PilhaSeq CriaPilhaSeq(){
 PilhaSeq q;
 q = (PilhaSeq)calloc(1, sizeof(VetorPilha));
 if(q == NULL) exit(-1);
 q->topo = 0;
 return q;
}

void LiberaPilhaSeq(PilhaSeq p){
 free(p);
}

bool PilhaSeqVazia(PilhaSeq p){
 return (p->topo == 0);
}

void EmpilhaSeq(PilhaSeq p, TipoDado x){
 if(p->topo == TAM_MAX) exit(-1);
 p->array[p->topo] = x;
 p->topo++;
}

TipoDado DesempilhaSeq(PilhaSeq p){
 if(p->topo == 0) exit(-1);
 p->topo--;
 return p->array[p->topo];
}

int main(){

 Pilha p;
 PilhaSeq ps;
 TipoDado x;
 
 p = CriaPilha();
 ps = CriaPilhaSeq();
 
 Empilha(p, 1);
 Empilha(p, 3);
 Empilha(p, 5);
 Empilha(p, 8);
 while(!PilhaVazia(p));
  x = Desempilha(p);
  EmpilhaSeq(ps, x);
 while(!PilhaSeqVazia(ps));
  x = DesempilhaSeq(ps);
  printf("%d ", x);
 printf("\n");
 return 0;

}
