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

