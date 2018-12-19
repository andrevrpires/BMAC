#include <stdio.h>
#include <stdlib.h>

struct Termo{
  float coef;
  int expo;
  struct Termo *prox;
};
 
typedef struct Termo* Polinomio;

struct Termo *AlocaTermo(){
  struct Termo *p;
  p = (struct Termo*)malloc(sizeof(struct Termo));
  if(p == NULL)
    exit(1);
  return p;
}

Polinomio CriaPolinomioNulo(){
  Polinomio p;
  p = AlocaTermo();
  p->coef = 0.0;
  p->expo = -1;
  p->prox = p;
  return p;
}

void InsereTermo(Polinomio p, float coef, int expo){
  struct Termo *t, *at,*q;
  /* Aloca memória para o novo termo: */
  q = AlocaTermo();
  q->coef = coef;
  q->expo = expo;
  /* Busca a posição correta para inserir o novo termo,
     O novo termo será inserido entre os termos apontados 
     por at e t.
  */
  at = p;
  t = p->prox;
  while(expo < t->expo){
    at = t;
    t = t->prox;
  }
  q->prox = t;
  at->prox = q;
}

void ImprimePolinomio(Polinomio p){
  struct Termo *t;
   
  t = p->prox;
  if(t == p){
   
   printf("%.2f*x^%d",0.00,0);
  }
  while(t != p){
    printf("%.2f*x^%d",t->coef,t->expo);
    t = t->prox;
    if(t != p){
      if(t->coef >= 0.0)
        printf("+");
    }
  }
  printf("\n");
}

Polinomio CriaPolinomio(char expr[]){
  Polinomio p;
  int expo,r,n,nn;
  float coef,sinal = 1.0;
  char c;
 
  nn = 0;
  p = CriaPolinomioNulo();
  while(1){
    r = sscanf(expr+nn," %f * x ^ %d %n",&coef, &expo,&n);
    if(r == 0 || r == EOF) 
      break;
    nn += n;
 
    InsereTermo(p, sinal*coef, expo);
     
    r = sscanf(expr+nn,"%c %n",&c,&n);
    if(r == EOF || r == 0)
      break;
    nn += n;
 
    if(c == '-')
      sinal = -1.0;
    else
      sinal = 1.0;
  }
  return p;
}

Polinomio SomaPolinomios(Polinomio p,
                         Polinomio q){
  Polinomio r;
  struct Termo *pp, *qq, *rr;
  float cf;
 
  r = CriaPolinomioNulo();
  rr = r;
  pp = p->prox;
  qq = q->prox;
  while(pp->expo > -1 || qq->expo > -1){
    if(pp->expo < qq->expo){
      InsereTermo(rr, qq->coef, qq->expo);
      rr = rr->prox;
      qq = qq->prox;
    }
    else if(qq->expo < pp->expo){
      InsereTermo(rr, pp->coef, pp->expo);
      rr = rr->prox;
      pp = pp->prox;
    }
    else{ /* pp->expo == qq->expo */
      cf = pp->coef + qq->coef;
      if(cf != 0.0){
        InsereTermo(rr, cf, pp->expo);
        rr = rr->prox;
      }
      pp = pp->prox;
      qq = qq->prox;
    }
 
  }
  return r;
}

float Valor(Polinomio p, float x){

 struct Termo *t;
 float r, pot;
 int exp;

 r = 0.0; 

 /*Testa se o Polinomio eh nulo (apenas noh cabeca)*/
 t = p->prox;
 if(t->expo == -1)
  return r;

 /*Comeca o laco*/
 while(t->expo > 0){
  
  /*Calcula a potencia*/
  exp = t->expo;
  pot = x;
  while(exp > 1){   
   pot = pot*x;
   exp--;
  }

  /*Soma no acumulador*/
  r = r + t->coef*(pot);

  /*Segue para o proximo termo*/
  t = t->prox;
 }

 /*Soma o termo independente, se houver*/
 if (t->expo == 0)
  r = r + t->coef;

 return r;
}

void LiberaPolinomio(Polinomio p){
 
 struct Termo *t, *ta;

 /*Posiciono os ponteiros nos dois primeiros nohs*/
 ta = p;
 t = p->prox;

 while(t->expo != -1){
  /*enquanto nao volto ao sentinela, sigo + apago o anterior*/
  ta = t;
  t = t->prox;
  free(ta); 
 }

 /*apago o noh kbca*/
 free(t);

}

Polinomio Derivada(Polinomio p){

 struct Termo *t, *tt, *dd;
 Polinomio d;

 /*Cria o polinomio da derivada e checa se vai dar nulo*/
 d = CriaPolinomioNulo(); 
 t = p->prox;
 if(t->expo < 1)
  return d;

 dd = d;
 while(t->expo > 0){
  /*Aloca novo noh, preenche os valores e adiciona aah derivada*/
  tt = AlocaTermo();
  tt->coef = (t->coef)*(t->expo);
  tt->expo = (t->expo) - 1;
  dd->prox = tt;
  dd = tt;
  t = t->prox;
 }

 dd->prox = d;
 return d;

}

Polinomio DerivadaSegunda(Polinomio p){

 struct Termo *t, *tt, *dd;
 Polinomio d;

 /*Cria o polinomio da derivada e checa se vai dar nulo*/
 d = CriaPolinomioNulo(); 
 t = p->prox;
 if(t->expo < 2)
  return d;

 dd = d;
 while(t->expo > 1){
  /*Aloca novo noh, preenche os valores e adiciona aah derivada*/
  tt = AlocaTermo();
  tt->coef = (t->coef)*(t->expo)*((t->expo) - 1);
  tt->expo = (t->expo) - 2;
  dd->prox = tt;
  dd = tt;
  t = t->prox;
 }

 dd->prox = d;
 return d;

}

int main(){

 char expr[500];
 float x,r;
 Polinomio p, dp, ds;

 /*Leh a entrada*/
 scanf(" %f %[^\n]", &x, expr);

 /*Leh a string*/
 p = CriaPolinomio(expr);
 
 /*Calcula o valor e printa*/
 r = Valor(p, x);
 printf("%.2f\n", r);

 /*Calcula as derivadas e printa*/
 dp = Derivada(p);
 ImprimePolinomio(dp);
 ds = DerivadaSegunda(p);
 ImprimePolinomio(ds);

 /*Libera memoria*/
 LiberaPolinomio(p);
 LiberaPolinomio(dp);
 LiberaPolinomio(ds);

 return 0;

}
