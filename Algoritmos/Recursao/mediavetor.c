#include<stdio.h>

float CalculaMedia(float V[], int n){
 
 float r;

 r = V[n-1];

 if(n > 1)
  r = (r + (n-1)*CalculaMedia(V, n-1))/n;

 return r;

}


int main(){

 float V[5], r, num;
 int n = 5, i;

 for(i = 0; i < n; i++){
  scanf("%f", &num);
  V[i] = num;
 }
 r = CalculaMedia(V, n);
 printf("%f\n", r);

 return 0;

}
