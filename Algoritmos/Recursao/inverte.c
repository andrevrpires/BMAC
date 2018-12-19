#include<stdio.h>

void Inverte(char str[], int n){

 if(str[n + 1] != '\0')
  Inverte(str, n+1);
 printf("%c", str[n]);

}

void DigitosInvertidos(int n){

 char str[10];
 
 sprintf(str, "%d", n); 
 Inverte(str, 0);

}

int main(){

 DigitosInvertidos(333222111);
 printf("\n");
 return 0;

}
