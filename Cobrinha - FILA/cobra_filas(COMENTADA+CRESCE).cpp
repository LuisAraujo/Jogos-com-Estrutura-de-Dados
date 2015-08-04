/*
  
  Implementação do jogo Snakc pelo Professor Alexandre Fanco (do IFBA Campus Santo Amaro)  
  para a disciplina ESTRUTURA DE DADOS 
  
  */
  
  
  
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

#define QUEUESIZE 1600
#define COBRASIZE 2

//IMPLEMENTADA POR LUIS GUSTAVO

#define FOOD 20

int _comida=0;
long _speed=40;
int _dirL=1, _dirJ=0, _dirI=0, _dirK=0,_x=0,_jogar=1;

//____________________________fim_________________________________________



//_________________________________ESTRUTURAS______________________________

struct corpo {
       //coordenadas do corpo;
       int x, y; 
       // 0 - se é corpo  1 - se é cabeça
       int cabeca; 
};

struct queue {
       int start, end;
       struct corpo items[QUEUESIZE];
};


struct comida{
       
       struct corpo items[FOOD];
};

//Declarando a estutura cobra (Global)
struct queue cobra;

struct comida comida;

//____________________________________FIM___________________________________




//___________________________OPERAÇÕES DA FILA_______________________________


//INCIALIZA A FILA
void inicializa_queue(struct queue *fila){
     fila->start = QUEUESIZE - 1;
     fila->end = QUEUESIZE - 1;
}


//VERIFICA SE FILA VAZIA
int empty(struct queue fila) {
    return fila.start == fila.end;
}

//RETIRA NA FILA
struct corpo dequeue(struct queue *fila){
    if (empty(*fila)){
       printf("Fila vazia");
    } else {
       if (fila->start == QUEUESIZE - 1)
          fila->start = 0;
       else
          fila->start++;
       return fila->items[fila->start];
    }
}


//INSERE NA FILA
void enqueue(struct queue *fila, struct corpo elem){
    
    int endtemp = fila->end;

    if (fila->end == QUEUESIZE - 1)
       fila->end = 0;
    else
       fila->end++;

    if (fila->start == fila->end){
       printf("Fila cheia");
       fila->end = endtemp;
    } else
       fila->items[fila->end] = elem;
}

//____________________________FIM_________________________________





//_______________________FUNÇÔES ESPECIFICAS DO JOGO______________



//Posiciona o cursor na tela, diacordo com as cordenadas X,Y
void gotoxy(int x, int y) { 
   
   //Esse tipo e varável
   COORD c;

   //X e Y são "atributos" do Tipo COORD
   c.X = x;
   c.Y = y;
   
   //Posiciona o curso diacordo com c.x e c.y  
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


//IMPREME A ESTRUTURA passada por parametro  (ESSA FUNÇÂO E CHAMADA PELA FUNÇÂO ANDA_COBRA)
void imprime_cobra(struct queue cobra){
     
     //Atribuia a i o valor do inicio da estrutura
     int i = cobra.start;
     
     //Enquando i for diferente do fim (Com isso pecorremos toda a estrutura)
     while (i != cobra.end){
         
         //Incrementa (Já que no inicio não temos dados)  
         i++;
         
         //Se i maior que tamanho da fila - 1
         if (i > QUEUESIZE - 1)
            /*Então i será 0 (Nesse caso se o i chegar no fim e ainda não for igual 
             ao end é porque temos que ler os dados que estão no incio da fila, já
             que a fila é ciclica
            */
            i = 0;
         
         //Passa as cordenadas do elemento para a função que posiciona o cursor para a impressão   
         gotoxy(cobra.items[i].x, cobra.items[i].y);
         //se a variavel cabelça do itens for 1
         if (cobra.items[i].cabeca)
         //impima a carinha, pela tabela ASCII '1'
            printf("%c",1);
         else
         //Se não, imprima o quadrado, pela TABELA ASCII 256
            printf("%c",254);
     }
}



//INICIALIZA A COBRA (coloca a cabeça e o corpo)
void inicializa_cobra(struct queue *cobra){
    
    struct corpo elems[COBRASIZE];
    int i;
    
    for (i = 0; i<COBRASIZE; i++){
       gotoxy(i, 0);
       
       if (i == COBRASIZE - 1)
          elems[i].cabeca = 1;
       else
          elems[i].cabeca = 0;
       
       
       // Coloa o curso no canto esquerdo superior 
       elems[i].x = i;
       //Y = 0 , logo elas está "deitada"
       elems[i].y = 0;
       
       //Empilhando o elems na pilha;
       enqueue(cobra, elems[i]);       
    }
    //Imprimindo a cobra
    imprime_cobra(*cobra);
}







//IMPLEMENTADA POR LUIS GUSTAVO


//Essa função coloca randomicamente as cordenadas das comida
void inicializa_comida(struct comida *comida){
           
int i;

  for (i=0;i<FOOD;i++){
    
    
   //recebe valor de 0 a 79 
   comida->items[i].x=rand()%80;
   //recebe valor de 0 a 23;
   comida->items[i].y=rand()%24;
   //atribui o valor 1(comida = true)
   comida->items[i].cabeca=1;

 }
           
           
}


//Imprime as comidas na tela
void imprime_comida(struct comida comida){

int i;

   //Pecorre toda a estrutura
   for (i=0;i<FOOD;i++){
  
      //pocisiona o cursor de acordo com os numero sorteado 
      gotoxy(comida.items[i].x, comida.items[i].y);

      //imprime a comida
      printf("*");
   }


}



//verifica se a cabeça da cobra tocou no corpo
int verifica_jogo(struct queue *cobra){

  int i,retorno=0;
    
  for(i=cobra->start+1;i<cobra->end;i++){

 
    if (  (cobra->items[i].x == cobra->items[cobra->end].x ) && (cobra->items[i].y == cobra->items[cobra->end].y) ){  
            
               retorno=1;       
       } 
    }
  
  
   return retorno; 
}



//verifica se acabou a comida, logo o jogador venceu
int verifica_comida(struct comida comida){
                  
int i,retorno=1;
 
  for (i=0; i<FOOD;i++)
    if(comida.items[i].cabeca == 1)
       retorno=0;
       
     return retorno;     
    
}


//Verifica se a posição que a cobra está é de uma comida, se sim a cobra cresce
void cobra_come(struct queue *cobra, struct comida *comida, struct corpo elem){
     
        int i;
          //De i=0 até quantidade de comidas
          for (i=0;i<FOOD;i++){
               
            //Se a cordenada x e y é iguala a cordenada de alguma comida 
              if( ( cobra->items[cobra->end].x == comida->items[i].x) && 
              ( cobra->items[cobra->end].y == comida->items[i].y) && (comida->items[i].cabeca)){
                       
                      //apaga a cabeça, pois o elem já veio incrementado
                      cobra->items[cobra->end].cabeca=0;
                      //colocar o elem cabeça na pilha
                      enqueue(cobra,elem);  
                      //atribui 0(false) ao alimento que já foi comido
                      comida->items[i].cabeca=0;
                      //incrementa a quantidade de alimento comido
                      _comida++;
              }
           }
        
        
        
       //se a quantidade de alimento comido está ente 1/5 e 1/2, velocidade igual a 30 
       if (  (_comida > FOOD/5) && (_comida < FOOD/2) )
                    _speed=30;
        //Se maior que 1/2  e menor que quantidade da comida -1, velocidade iguala 20         
       else if (   (_comida >= FOOD/2) && (_comida < FOOD-1) )
                  _speed=20;
        //se temos apenas uma comida na tela, velocidade de 10;          
       else if ( (_comida == FOOD-1) )
                  _speed=10; 
        
    


}



//função para a tela fiinal do jogo
void tela_fim(int num){
  
  //se a msg estiver no canto, inicia novamente   
  if(_x>79)
    _x=0; 
  
  //apaga tela para escrever em outra cord  
 system("cls");
 
 //seta o curso (incrementando o x)
 gotoxy(++_x,10);        
 
 
 //se o parametro num = 1 venceu
 if(num==1){      
       printf("FIM DE JOGO: VOCE GANHOU");    

//se igual a 2 perdeu
}else if(num==2){                      
        printf("FIM DE JOGO VOCE PERDEU");     
}   
 
 //delay
 _sleep(50); 

//recusividade
tela_fim(num);
 
}
//____________________________________Fim____________________________________



//FUNÇÃO PARA A COBRA ANDAR, recebe a estrutura e a direção (a varaiável c na main)
void anda_cobra(struct queue *cobra, char dir){
        

//IMPLEMENTADA POR LUIS GUSTAVO

// esse trecho do codigo permite que a cobra não volte de onde veio, se sobrepondo

 if(dir=='l') {
   
      _dirL=1;
      _dirI=0;
      _dirK=0;
      
 }
 else if (dir=='j') {
      
      _dirJ=1;
      _dirI=0;
      _dirK=0;
       
}
 else if(dir=='i') {
      
      _dirI=1;
      _dirL=0;
      _dirJ=0;
}     
 else if(dir=='k') {
      
      _dirK=1;
      _dirL=0;
      _dirJ=0;
}     
  
  if( (dir=='j') && (_dirL==1)  )
     dir='l';      
  else if ( (dir=='l') && (_dirJ==1) )
     dir='j';      
  else if((dir=='k') && (_dirI==1))
     dir='i';
  else if((dir=='i') && (_dirK==1))
       dir='k';
          
    
    
    
//___________________________Fim__________________________________
    
    
    
    
    
    
    
    
    
     /*Declara uma fila do tipo CORPO, as manipulações de inserção na fila
     serão feitas nessa estrutura e posteriormente inseridas na estrutura da COBRA
     passada por parametro     
     */
     struct corpo elem, elem2, rastro;
     
     //Variável do tipo interio, mas que simula uma boolean (1=verdade, 0=falso);
     int andou = 0;

     //Coloca o valor 1 (verdadeiro), na variavel cabeça da estrutura elem (tipo CORPO)
     elem.cabeca = 1;
     
     //insere no final da estrutura na variavel cabeça o valor 0 (falso) 
     cobra->items[cobra->end].cabeca = 0;
     
     //Essa sequência de ifs usa o parameto dir (variável c na main) 
     
    //SE DIR IGUALA A l
    if (dir == 'l'){
        
        //andou igual a 1(verdade);     
        andou = 1;
        
        //Atribui o valor de x na estutura elem (tipo CORPO) INCEMENTADO, logo ele vai para a direira
        elem.x = cobra->items[cobra->end].x + 1;
        elem2.x =elem.x+1;
        
        //Atribui o valor de y na estrutura elem (tipo CORPO), logo ele vai permanecer com o mesmo y
        elem.y = cobra->items[cobra->end].y;
        
        elem2.y=elem.y;
        
        
        //Se elem.x (que acabamos que atribuir) for maior que 79 (limite a direita da tela)
        if (elem.x > 79)
        
        //Então ele será iguala a 0 (do outro lado da tela)
           elem.x = 0;
           
     
     //SE DIR IGUAL A j
     } else if (dir == 'j') {
        
        //andou igual a 1(verdade);     
        andou = 1;
        
        //Atribui o valor de x na estutura elem (tipo CORPO) DECEMENTADO, logo ele vai para a esquerda
        elem.x = cobra->items[cobra->end].x - 1;
        
        // essa variável é incrementada ou decrementada durante esse trecho, pois é justamente a proxima posição que a cobra deve estar se comer
        elem2.x =elem.x-1;
        //Atribui o valor de y na estrutura elem (tipo CORPO), logo ele vai permanecer com o mesmo y 
        
        elem.y = cobra->items[cobra->end].y;
        
        elem2.y=elem.y;
        //Se elem.x for menor que 0 (limite a esquerda da tela)
        if (elem.x < 0)
        
           //Ele será iguala a 79 (do outro lado da tela) 
           elem.x = 79;
     
     //SE DIR IGUALA A i
     } else if (dir == 'i') {
         
         //andou igual a 1(verdade);     
        andou = 1;
        
         //Atribui o valor de x na estrutura elem (tipo CORPO), logo ele vai permanecer com o mesmo x
        elem.x = cobra->items[cobra->end].x;
        
        elem2.x =elem.x;
        //Atribui o valor de y na estrutura elem (tipo CORPO) DECREMENTADO, logo ele vai subir 
        elem.y = cobra->items[cobra->end].y - 1;
        
        elem2.y=elem.y-1;
        //Se elem.y menor que 0 (limite superior da tela)
        if (elem.y < 0)
        
          //ele será igual a  23 (outro lado da tela)
           elem.y = 23;
     
     } else if (dir == 'k') {
        
        //andou igual a 1(verdade);     
        andou = 1;
        
        //Atribui o valor de x na estrutura elem (tipo CORPO), logo ele vai permanecer com o mesmo x 
        elem.x = cobra->items[cobra->end].x;
        elem2.x=elem.x;
        //Atribui o valor de y na estrutura elem (tipo CORPO) DECREMENTADO, logo ele vai descer
        elem.y = cobra->items[cobra->end].y + 1;
        elem2.y=elem.y+1;
        //Se elem.y maior que 23 (limite inferior da tela)
        if (elem.y > 23)
        
        //Ele será iguala a 0 (Outro lado da tela)
           elem.y = 0;
     }



//Observe que se foi presionada uma tecla válida(j,i,k,l) andou é 1(verdade) senão ele é 0(falso)
     if (andou){
        
        //Inserindo na fila o elem       
        enqueue(cobra, elem);
        
        //Atribuindo na variável rasto o que é retirado da fila
        rastro = dequeue(cobra);
        
        //Posiciona o curso do mouse na rasto (ultimo elemento da cobra- o rabo -)
        gotoxy(rastro.x, rastro.y);
        
        //Apaga o rasto remanecente na tela
        printf(" ");
       
       //passando elem2 e não elem, caso a cobra a cabeça tem que está na proxima cord de acordo a direção. 
       cobra_come(cobra,&comida,elem2); 
   
        
        
        //Imprimindo cobra
        imprime_cobra(*cobra);
     }



      



}











int main(){
    
//Imprementado por LUIS GUSTAVO
    
    //Funcão da biblioteca <time.h> permite a implatação do ramdom usado na inicializa_comida
    srand(time(NULL));
    
     inicializa_comida(&comida);
     imprime_comida(comida);
    
//________________fim____________


    
    //Variável do tipo char receberá a direção da função getchar();
    char c;
    //Essa variável é do tipo long para suportar o número "10.000.000" 
    long i;
    
    //Inicializa a fila (Ou seja a coloca em situação vazia)
    inicializa_queue(&cobra);
    //Insere os elementos da cobra (corpo e cabeça) na fila
    inicializa_cobra(&cobra);
    
    do {
        
       //kbhit é uma função da biblioteca conio.h, retorna não 0 se foi pressionada uma tecla, e 0 se não
       if (kbhit()) // Alocandi um caracter em c 
          c = getch();
       
       // Faz a fila (cobra) andar de acordo com a direção(c)   
       anda_cobra(&cobra,c);      
      
     
      //Imprementado por Luis Gustavo
      
      if(verifica_jogo(&cobra)==1){
          tela_fim(2);
                    
      }else if(verifica_comida(comida)==1){
         tela_fim(1); 
              
      }
      //_________________Fim_________________     
      
      
      
      //Essa estrutura de repetição serve para dar um delay a cada interação
      _sleep(_speed);
    
    //Essas instruções se repetiram até que c seja igual a "27"
    } while (1);
    
    
    
    
    
    
    
}
