#include<stdio.h>
#include<stdlib.h>


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

void Calcular(int n, Pilha Z, Pilha op){

 /* Calcula uma operacao simples, a partir de:
    
    um inteiro dado
    inteiro no topo de uma pilha de inteiros
    operador no topo de uma pilha de operadores
    
    Empilha o resultado na pilha de inteiros */

 char c; 
 c = Desempilha(op);
 if(c == '+')
  Empilha(Z, n + Desempilha(Z));
 else if(c == '*')
  Empilha(Z, n * Desempilha(Z));

}

void EmpilhaPre(char pre[], Pilha Z, Pilha op){
 
 /* Trata os dados de uma expressao prefixa para que possam ser calculados corretamente
   
    a funcao separa os dados em duas pilhas:
    uma com os operadores
    outra com os inteiros da expressao

    no caso de haver subproblemas(subexpressoes dentro da expressao, resultado de parenteses, que mudam a ordem dos operadores)
    a funcao resolve o subproblema primeiro, e empilha o resultado, simplificando a expressao */ 

 int i, n, ultimoz;
 char c;

 i = 0;
 ultimoz = 0;
 while(pre[i] != '\0'){

  c = pre[i];

  /* processa todos os sinais em sequencia */
  while(c == '+'||c == '*'){
   Empilha(op, c);
   i++;
   c = pre[i];
  }

  n = c - '0';
  
  /* decide se deve:
  /* - calcular e empilhar o resultado(dois inteiros consecutivos na expressao: subexpressoes)
  /* - apenas empilhar um inteiro */
  if((i - 1) == ultimoz) 
   Calcular(n, Z, op);
  else
   Empilha(Z, n);
  
  ultimoz = i;
  i++;
 }
}

int ValorExpressao(char pre[]){

 /* Calcula o valor de uma expressao prefixa simples */

 Pilha Z, op;
 int v;

 /* Pilha de operadores */
 op = CriaPilha();
 /* Pilha de inteiros*/
 Z = CriaPilha();

 /* Separa os dados da expressao em duas pilhas para que seja possivel calcular corretamente */
 EmpilhaPre(pre, Z, op);
 
 /* Processa os dados empilhados*/
 while(!PilhaVazia(op))
  Calcular(Desempilha(Z), Z, op);
 
 /* Salva o resultado */
 v = Desempilha(Z);

 /* Libera a memoria */
 LiberaPilha(op);
 LiberaPilha(Z);

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
