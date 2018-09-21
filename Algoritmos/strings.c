# include <stdio.h>


int TamanhoStr(char str[]){
	
 int i=0;

 while (str[i] != '\0'){
  i++;
 }

 return i;

}


void InverteStr(char str[]){

 char tmp;
 int i, j;

 i = 0;
 j = TamanhoStr(str) - 1;

 while ( i < j ) {
  
  tmp = str[i];
  str[i] = str[j];
  str[j] = tmp;
  j--;
  i++;

 }

}

 
void InverteSubstr(char str[], int i, int j){

 char tmp;

 while ( i < j ) {
  
  tmp = str[i];
  str[i] = str[j];
  str[j] = tmp;
  j--;
  i++;  

 }

}


void InvertePalavra(char str[]){

 int i, j;

 i = 0;
 
 do{
 
 while (str[i] == ' ') i++;

 j = i;
 while (str[j] != '\0' && str[j] != ' ') j++;

 j--;
 if ( j > i) InverteSubstr(str, i, j);
 
 i = j + 1;
 
 } while(str[i] !='\0');

}


void ReduzEspacos(char str[], char strreduz[]){

 char t;
 int i,j;
	
 i = 0;
 j = 0;

 while(str[i] != '\0'){

  if(str[i] == ' '){
   
   t = str[i];
   while(str[i] == ' ') i++;

  }

  else{
   
   t = str[i];
   i++;
  
  }

  strreduz[j] = t;
  j++;
 
 }

 strreduz[j] = '\0';

}


int ProcuraSubstr(char str[], int i, int j, char substr[]){

 if(TamanhoStr(substr) != (j - i + 1)) return 0;

 else {
  while ( i <= j ) {
   if(str[i] != substr[i]) return 0;
   i++;  
  }
 }

 return 1;

}


int ProcuraCharSubstr(char str[], int i, int j, char p){

 while ( i <= j ) {
  
  if(str[i] == p || str[j] == p) return 1;
  j--;
  i++;  

 }

 return 0;

}


void CopiaSubstr(char str[], char strcopia[], int inic, int fim){

 int i, j;

 j = 0;
 for(i = inic; i <= fim; i++){

  strcopia[j] = str[i];
  j++;

 }

 strcopia[j] = '\0';

}

void ProcuraEmail(char str[], char email[]){

 int i, j;

 /*Encontra o índice do '@'*/
 while(str[i] != '\0'){
  if(str[i] == '@') break;
  i++;
 }

 /*'@' não encontrado*/
 if(str[i] == '\0'){
  email[0] = '\0';
  return;
 }
 
 /*'@' encontrado*/
 else {
  j = i;
  
  do{
   j++;
  }while(str[j] != ' ' || str[j] != '\0');

  while(i > 0){
   if(str[i - 1] == ' ') break;
   i--;
  }
  CopiaSubstr(str, email, i, j);
 }
}

void ProcuraEmailMeu(char str[], char email[]){ 

 int i, j;

 i = 0;
 
 do{
 
 while (str[i] == ' ') i++;

 j = i;
 while (str[j] != '\0' && str[j] != ' ') j++;

 j--;
 if ( j > i){
  if(ProcuraCharSubstr(str, i, j, '@')){
   CopiaSubstr(str, email, i, j);   
  }
 }
 
 i = j + 1;
 
 } while(str[i] !='\0');
 
}




int main(){

 char teste[] = "pamela anderson";
 char espacos[] = "   varios   espacos  a mais  ";
 char semespacos[200];
 char tememail[] = " eu uso o andrevrpires@hotmail.com direto";
 char resultemail[50];

 InverteStr(teste);
 printf("%s.\n", teste);
 InvertePalavra(teste);
 printf("%s.\n", teste);
 ReduzEspacos(espacos, semespacos);
 printf("%s.\n", semespacos);
 ProcuraEmail(tememail, resultemail);
 printf("%s.\n", resultemail);
 ProcuraEmailMeu(tememail, resultemail);
 printf("%s.\n", resultemail);

 return 0;

}
