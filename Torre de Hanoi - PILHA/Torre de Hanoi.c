#include <stdio.h>
#include <stdlib.h>
#include "gotoxy.c"

#define MAXSIZE  3

typedef struct pilha{
 
 int discos[MAXSIZE];      
 int top;
 
} Pilha;

Pilha hannoi[MAXSIZE];


//Inicializando
void inicializa (Pilha *pilha){
 
 (*pilha).top=-1;    // OU   pilha->top=-1;
     
}   

//Empilhando
void push(Pilha *pilha, int disco){
     
  (*pilha).discos[++(*pilha).top]=disco;
}


//Desempilhando
int pop(Pilha *pilha){
     
  return (*pilha).discos[ ((*pilha).top)-- ];

}

//Verifica topo
int stacktop(Pilha pilha){
               
   return pilha.discos[pilha.top];        
}

//Retorna se cheia
int underflow(Pilha pilha){
  return pilha.top == MAXSIZE-1;  
}

int empty(Pilha pilha){
    
   return pilha.top==-1; 
}

//Funcoes do Jogo 
start(Pilha hannoi[MAXSIZE]){

int i,j;  
  
  //Empilhando....          
  push(hannoi,3);
  push(hannoi,2);
  push(hannoi,1);
  
  for(j=1;j<3;j++){
    for(i=0;i<3;i++){
       hannoi[j].discos[i]=0; 
       }
    }         
}

end(Pilha hannoi[MAXSIZE]){
   
   if ( (hannoi[2].discos[0]==3) && (hannoi[2].discos[1]==2) && (hannoi[2].discos[2]==1) ){
       return 1;
   }else{
       return 0;
   }

}


imprime(Pilha hannoi[MAXSIZE]){
     
    char bloco=-37;
    int i,j=0;
    int cord=4;
     gotoxy(30,0);
    printf("TORRE DE HANOI \n \n ");
  

  gotoxy(0,2); 
    printf("PILHA 1");       
   gotoxy(0,cord++);  
    for (j=hannoi[0].top; j>=0; j--){ 
           
      
        if ( hannoi[0].discos[j]== 1){
         printf("   %c%c%c ",bloco, bloco, bloco);
          gotoxy(0,cord++);
        }else
        if( hannoi[0].discos[j]== 2){
           printf("  %c%c%c%c%c",bloco, bloco, bloco, bloco, bloco);  
            gotoxy(0,cord++);  
        } else  
        if ( hannoi[0].discos[j]== 3){
         printf(" %c%c%c%c%c%c%c",bloco, bloco, bloco, bloco, bloco, bloco, bloco);
          gotoxy(0,++cord);       
        }
        
    }  

    gotoxy(25,2);     
        
   printf("PILHA 2");
   cord=4;
   gotoxy(25,cord++);  
          
      for (j=hannoi[1].top; j>=0; j--){ 
            
        if(hannoi[1].discos[j]== 1){
          printf("   %c%c%c    ",bloco, bloco, bloco);
            gotoxy(25,cord++);
        }else
        if( hannoi[1].discos[j]== 2){
            printf("  %c%c%c%c%c",bloco, bloco, bloco, bloco, bloco);       
              gotoxy(25,cord++);
        }else        
        if ( hannoi[1].discos[j]== 3){
         printf(" %c%c%c%c%c%c%c ",bloco, bloco, bloco, bloco, bloco, bloco, bloco);           
           gotoxy(25,++cord);
        
        }
        
      }
      
      gotoxy(50,2);
        
      printf("PILHA 3 ");
      cord=4;   
        gotoxy(50,cord++);
      for (j=hannoi[2].top; j>=0; j--){ 
             
        if (hannoi[2].discos[j]== 1){
            printf("   %c%c%c ",bloco, bloco, bloco);
              gotoxy(50,cord++);
        }else
         
        if( hannoi[2].discos[j]== 2){
            printf("  %c%c%c%c%c  ",bloco, bloco, bloco, bloco, bloco);
              gotoxy(50,cord++); 
        }else
                
        if ( hannoi[2].discos[j]== 3){
            printf(" %c%c%c%c%c%c%c ",bloco, bloco, bloco, bloco, bloco, bloco, bloco); 
              gotoxy(50,++cord);      
        }    
     
     }
  
  }





main () {    
   
int i=0,pilhaRetira,pilhaInsere,jogadas=0;
  
      //Inicializa as pilhas
      for(i=0;i<3;i++){
            
             inicializa(hannoi+i);
      }
      
            
      //Coloca os discos na primeira pilha
      start(hannoi);
       

while(end(hannoi)!=1){
                    
 
  imprime(hannoi);
  gotoxy(0,10);
  printf("INFORME SUA JOGADA:");
    gotoxy(0,11);
  printf("Disco da pilha:");
  scanf("%d",&pilhaRetira);

  gotoxy(0,13);
  if( (pilhaRetira!=1)&&(pilhaRetira!=2)&&(pilhaRetira!=3) ){
     
     printf("jogada Invalida: Esta pilha não existe!");
     system("pause");
     system("cls");
     continue;
   }
  printf("para a pilha:");
  scanf("%d",&pilhaInsere);
  
  if( (pilhaInsere!=1)&&(pilhaInsere!=2)&&(pilhaInsere!=3) ){
     printf("jogada Invalida: Esta pilha não existe! \n");
     system("pause");
     system("cls");
     continue;
   }
   
  jogadas++; 

  if ( empty(hannoi[pilhaRetira-1]) ) {
      
      printf("Jogada Invalida: Pilha Vazia");
      system("pause");
  
  }else if(underflow(hannoi[pilhaInsere-1])){
  
     printf("Jogada Invalida: Pilha cheia!!! \n"); 
     system("pause");
   
  }else if(hannoi[pilhaInsere-1].top == -1){
        
    push(hannoi+(pilhaInsere-1),pop( hannoi+(pilhaRetira-1) ) );
  
  }else if (hannoi[pilhaRetira-1].discos[  hannoi[pilhaRetira-1].top]  > hannoi[pilhaInsere-1].discos[ hannoi[pilhaInsere-1].top ] ) {
   
           printf("Jogada Invalida: Disco maior que o topo \n");
     
         system("pause");    
    
  }else{
      
      push(hannoi+(pilhaInsere-1),pop( hannoi+(pilhaRetira-1)  ) );
    
   }
      
system("cls"); 


}

printf("FIM DE JOGO \n");

if(jogadas==7){
  printf("   Parabens!!! \n");
}else if( (jogadas>7) && (jogadas<=10) ){
  printf("   Muito Bom!!! \n");     
}else if (jogadas > 10){
  printf("   Precisa Melhorar!!! \n");
}
  printf("Voce realizou %d jogadas",jogadas);


system("pause");
}
