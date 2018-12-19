#include<stdio.h>

void ImprimePiramide(int n){

 int i;

 if(n > 1)
  ImprimePiramide(n - 1);

 for(i = 1; i <= n; i++)
  printf("%d ", i);
 printf("\n");

}

int main(){

 ImprimePiramide(10);

 return 0;
}
