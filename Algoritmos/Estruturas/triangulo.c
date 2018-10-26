#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Vertice{
 float x;
 float y;
};

struct Triangulo{
 struct Vertice A;
 struct Vertice B;
 struct Vertice C;
};

float Distancia(struct Vertice A, struct Vertice B){
 float dx, dy, d;
 dx = B.x - A.x;
 dy = B.y - A.y;
 d = sqrtf(dx*dx + dy*dy);
 return d;
}

float Perimetro(struct Triangulo T){
 float p = 0.0;
 p += Distancia(T.A, T.B);
 p += Distancia(T.B, T.C);
 p += Distancia(T.C, T.A);
 return p;
}

int main(){

 struct Triangulo T;
 float p;

 printf("Entre com as coordenadas do ponto A: ");
 scanf("%f %f", &T.A.x, &T.A.y);

 printf("Entre com as coordenadas do ponto B: ");
 scanf("%f %f", &T.B.x, &T.B.y);
 
 printf("Entre com as coordenadas do ponto C: ");
 scanf("%f %f", &T.C.x, &T.C.y);
 
 p = Perimetro(T);
 printf("O perimetro deste triangulo eh %.2f\n", p);

 return 0;
}
