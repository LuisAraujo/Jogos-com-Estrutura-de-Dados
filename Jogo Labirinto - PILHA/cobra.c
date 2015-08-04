#include <stdio.h>
#include <stdlib.h>

//Criando estrutura
typedef struct est{    
    
    int topo;
    char caminho[50];   

}Pilha;

//Declarando a estrutura do tipo Pilha
Pilha pilha;

//Inicializando
void inicializa (Pilha *pilha){
 
 (*pilha).topo=-1;    // OU   pilha->top=-1;
     
}   

//Empilhando
void push(Pilha *pilha, char c){
     
     (*pilha).caminho[++(*pilha).topo]=c;
}


//Desempilhando
char pop(Pilha *pilha){
     
   return (*pilha).caminho[ ((*pilha).topo)-- ];

}


main(){

       
char caminho, tabuleiro[10][9];  
//Coordenadas inicial da seta (0,2)
int x=0,y=2,i,j;

//Preenche o labirinto
preenche(tabuleiro);

//inicializa a pilha
inicializa(&pilha);


printf("<- JOGO DA SETINHA -> \n");
printf("Desenvolvido por: Luis Gustavo Araujon\n");
printf("Obs.: Pressione qualquer tecla para cada interacao");


//Enquanto alguma coisa
while(tabuleiro[5][8]!=26){

         getchar();
         system("cls");
         imprime(tabuleiro); 
         printf("Cornedadas x,y: %d %d",x,y);
         if(tabuleiro[y][x+1]==-37){
          
              tabuleiro[y][x]=000;
              tabuleiro[y][++x]=26;
              push(&pilha,'d');
              //empilha a letra d (direita)                             
         
         }else if(tabuleiro[y+1][x]==-37){
             
               tabuleiro[y][x]=000;
               tabuleiro[++y][x]=25;
               push(&pilha,'b');
               //empilha a letra b (baixo)
                                       
         }else if (tabuleiro[y][x-1]==-37){
         
             tabuleiro[y][x]=000;
             tabuleiro[y][--x]=27;
             push(&pilha,'e');
             //empilha a letra e  (esquerda) 
         
         }else if(tabuleiro[y-1][x]==-37){
             
             tabuleiro[y][x]=000;
             tabuleiro[--y][x]=24;
             push(&pilha,'c');
             //empilha a letra c (cima)
         
         }else{              
              caminho=pop(&pilha);
              
              if(caminho=='d'){   
                                 
                  tabuleiro[y][x]=000;
                  tabuleiro[y][--x]=27;
                              
              }else if (caminho=='b'){
                
                 tabuleiro[y][x]=000;
                 tabuleiro[--y][x]=24;  
              
              }else if (caminho=='e'){
                    
                    tabuleiro[y][x]=000;
                    tabuleiro[y][++x]=26;
              
              }else if(caminho=='c'){
                    
                    tabuleiro[y][x]=000;
                    tabuleiro[++y][x]=25;
                    
              }      
         
         
         
         
         } 
   
   } 
 
 system("cls");
imprime(tabuleiro); 
printf("\\o/  Voce Saiu do Labirinto!!! \\o/ \n");


system("pause");
}



preenche(char tabuleiro[10][9]){
              
              int i,j,aberto=-37;
                 
                 for(i=0;i<10;i++){
                    for(j=0; j<9;j++){              
                       tabuleiro[i][j]=178;  
                       }
                    } 
                     
                     //inicio 
                     tabuleiro[2][0]=26;
                     
                     
                    tabuleiro[1][2]=aberto;tabuleiro[1][3]=aberto;tabuleiro[1][4]=aberto;
                    tabuleiro[1][5]=aberto;tabuleiro[2][1]=aberto;tabuleiro[2][2]=aberto;
                    tabuleiro[2][5]=aberto;tabuleiro[3][2]=aberto;tabuleiro[3][4]=aberto;
                    tabuleiro[3][5]=aberto;tabuleiro[4][3]=aberto;tabuleiro[4][4]=aberto;
                    tabuleiro[4][7]=aberto;tabuleiro[5][1]=aberto;tabuleiro[5][2]=aberto;
                    tabuleiro[5][3]=aberto;tabuleiro[5][7]=aberto;tabuleiro[5][8]=aberto;
                    tabuleiro[6][1]=aberto;tabuleiro[6][3]=aberto;tabuleiro[6][4]=aberto;
                    tabuleiro[6][6]=aberto;tabuleiro[6][7]=aberto;tabuleiro[7][1]=aberto;
                    tabuleiro[7][6]=aberto;tabuleiro[8][1]=aberto;tabuleiro[8][2]=aberto;
                    tabuleiro[8][3]=aberto;tabuleiro[8][4]=aberto;tabuleiro[8][5]=aberto;
                    tabuleiro[8][6]=aberto;tabuleiro[8][7]=aberto;


}


imprime(char tabuleiro[10][9]){

             int i,j;
             
                 for(i=0;i<10;i++){ 
                   for(j=0; j<9;j++){              
                       printf("%c",tabuleiro[i][j]);
                   } 
                       printf("\n");
                  } 
            
}
