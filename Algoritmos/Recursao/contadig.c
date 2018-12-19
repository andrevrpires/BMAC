#include<stdio.h>

void Conta(char str[], int n){

 if(str[n + 1] != '\0')
  Conta(str, n+1);
 else
  printf("%d", n+1);

}

void ContaDigitos(int n){

 char str[10];
 
 sprintf(str, "%d", n); 
 Conta(str, 0);

}

int main(){

 ContaDigitos(333222111);
 printf("\n");
 return 0;

}
