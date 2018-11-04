#include<stdio.h>
#include<stdlib.h>

typedef int TipoDado;

#include "./pilhas_lig.c"

int ValorExpressao(char exp[]){
 
 int v, i;
 char c;
 i = 0;
 while(c != '\0'){
  c = exp[i];
  if(c){}

 }


 return v;
}

int main(){ 
  char pos[] = "123+*45+*6*"; 
  int v; 
  v = ValorExpressao(pos); 
  printf("v: %d\n",v);  /* Imprime v: 270 */ 
  return 0;
}
