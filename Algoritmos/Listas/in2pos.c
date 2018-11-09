bool Precedencia(char c){


}

void In2Pos(char expr[]){
 Pilha P;
 int i;
 char c;

 P = CriaPilha();

 i = 0;
 Empilha(P,'(');
 do{
 
  c = expr[i];
  i++;

  switch(c){
   case: '('
    Empilha(P, c)
    break;
   case: ')'
    break;
   case: '\0'
    break;
   case: '+'
   case: '-'
   case: '*'
   case: '/'
   case: '^'
    t = Desempilha(P);
    if(Precedencia(t, c){
     printf("%c", t);
     Empilha
    }
    else{
     Empilha(t);
     Empilha(c);
    }
    break;
   default:
    printf("%c", c);
  }
 
 }while(c != '\0');

 LiberaPilha(P);
}

int main(){

 char expr[]="a*(b+c)*(d-g)*h";
 
 In2Pos(expr);
 
 return 0;
}
