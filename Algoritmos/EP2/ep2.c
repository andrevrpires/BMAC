#include<stdio.h>
#include<stdlib.h>




/* Pilha com lista ligada */

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
 Pilha Z, op;
 int i, n, ultimoz;
 char c;


/* Pilha dos operadores */
 typedef char TipoDado;
 op = CriaPilha();

 /* Pilha dos inteiros*/
 typedef int TipoDado;
 Z = CriaPilha();

 /* Itera sobre a string */
 i = 0;
 while(pre[i] != '\0' || !PilhaVazia(op)){

  c = pre[i];

  /* verifica se eh inteiro */
  while(c == '+'||c == '*'){
   Empilha(op, c);
   i++;
   c = pre[i];
  }

  n = c - '0';
  if((i - 1) == ultimoz){
   if(Desempilha(op) == '+')
    Empilha(Z, n + Desempilha(Z));
   else if(Desempilha(op) == '*')
    Empilha(Z, n * Desempilha(Z));
   }
  }
  Empilha(Z, n);
  ultimoz = i;
  i++;
 }

 /* Salva o resultado */
 n = Desempilha(Z);

 /* Libera a memoria */
 LiberaPilha(op);
 LiberaPilha(Z);

 return n;
}

int main(){
 char pre[512];
 int v;
 
 scanf("%s", pre);
 v = ValorExpressao(pre);
 printf("%d\n",v);  
 return 0;
}
