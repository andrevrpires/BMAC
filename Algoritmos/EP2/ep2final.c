#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int TipoDado;

/* Pilha com lista ligada com no cabeca*/

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
 if(PilhaVazia(p)) exit(-1);
 q = p->prox;
 x = q->dado;
 p->prox = q->prox;
 free(q);
 return x;
}

int ValorExpressao(char pre[]){
 int v, i;
 Pilha P;
 P = CriaPilha();
 for(i = strlen(pre) - 1; i >= 0; i--){
  if(pre[i] >= '0' && pre[i] <= '9')
   Empilha(P, pre[i] - '0');
  else if(pre[i] == '+')
   Empilha(P, Desempilha(P) + Desempilha(P));
  else if(pre[i] == '*')
   Empilha(P, Desempilha(P) * Desempilha(P));
 }
 v = Desempilha(P);
 LiberaPilha(P);
 return v;
}

int main(){
 char pre[512];
 int v;
 
 scanf("%s", pre);
 v = ValorExpressao(pre);
 printf("%d\n",v);  
 return 0;
}
