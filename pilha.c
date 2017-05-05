/***********************************************/ 
/* Pilha Encadeada                             */
/* objetivo: cadastro academico                */
/* programador: Jonatan Colussi               */
/***********************************************/ 

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>


/***********************************************/ 
/* Definição dos Registros                     */
/***********************************************/ 
typedef struct {           // registro para uma pessoa
       int  matr;
       char nome[30];
} INFORMACAO;
       
typedef struct pilha {
       INFORMACAO info;    // dados do registro
       struct pilha* prox; // ponteiro para o próximo registro
} PILHA; 



/***********************************************/ 
/* Definição das Funções                       */
/***********************************************/ 
void    entrada_dados ( PILHA* aux );
void    imprime_pilha ( PILHA* aux );
void    cria_pilha    ( PILHA** p );
void    empilha       ( PILHA** p );
PILHA*  procura_nodo  ( PILHA* p, int matricula );
void    desempilha    ( PILHA** p );
       
       

/***********************************************/ 
/* Programa Principal                          */
/***********************************************/ 
int main( void ){
    char op;  // opcao do menu                               
    PILHA* p; // declaracao da pilha // variavel do tipo pilha = pilha de ponteiros


    while( 1 ){
         printf( "\n /---------------------------------------------------/" ); 
         printf( "\n Programa de cadastro academico - Menu                " );
         printf( "\n [1] Cria pilha                                       " );
         printf( "\n [2] Empilha                                          " );
         printf( "\n [3] Desempilha                                       " );
         printf( "\n [4] Imprime pilha                                    " );
         printf( "\n [5] Para sair do programa                            " );
         printf( "\n /---------------------------------------------------/" );      
         printf( "\n Opcao: " );
         op = getche();// tecla de opcao do menu

         switch( op ) {
           case '1':  // rotina cria pilha
                cria_pilha( &p );
                break;
                                
           case '2':  // rotina empilha
                empilha( &p );    
                break;
           
           case '3':   // rotina desempilha
                desempilha( &p );
                break;
                                                                            
           case '4':   // rotina imprime pilha                 
                imprime_pilha( p ); 
                break;
                                
           case '5':  // término do programa                                                 
                exit( 1 ); 
                break;
                
           default : 
                printf( "\n Digite uma opcao!" );
                break;
        } // switch( op )

       
        fflush( stdin ); // limpa buffer do teclado, funciona junto com entrada de dados
        getchar();       // parada da tela
        
        printf( "\n" );
     } // fim do while( 1 )
     
 return 0;
} // fim do programa principal



/************************************************ 
 * entrada_dados                                *
 * objetivo: rotina para ler dados              *
 * entrada : nodo (ponteiro para o novo espaco) *
 * saida   : nodo com dados                     *
 ************************************************/
void entrada_dados( PILHA* aux ){ 
    printf( "\n\n Digite a matricula: " ); 
    fflush( stdin );     // limpa buffer do teclado, funciona junto com entrada de dados
    scanf("%d", &aux->info.matr);

    printf( "\n Digite o nome: " );
    fflush( stdin );     // limpa buffer do teclado, funciona junto com entrada de dados
    gets( aux->info.nome );
  
    aux->prox= NULL;     // não aponta

}



/*************************************************
 * imprime_pilha                                 *
 * objetivo: rotina para imprimir dados          *
 * entrada : pilha                               *
 * saída   : nenhuma                             *
 *************************************************/ 
void imprime_pilha( PILHA* aux ){

    if( aux == NULL )
        printf( "\n Underflow - Pilha vazia!" );
    else {
         printf("\n\n ---- Relatorio Geral ---- ");    
         while( aux != NULL ){  // ponteiro auxiliar para a lista
                printf( "\n Nome.....: %s", aux->info.nome );
                printf( "\n Matricula: %d", aux->info.matr );
                aux = aux->prox;// aponta para o proximo registro da lista
         } // fim while( aux != NULL )
    } // fim if( aux == NULL )  
}



/************************************************
 * cria_pilha                                   *
 * objetivo: rotina para inicializar a pilha    *
 * entrada : pilha                              *
 * saida   : NULL (inicializa pilha)            *
 ************************************************/ 
void cria_pilha( PILHA** topo ){
    *topo = NULL; // pilha criada, topo nao aponta
}



/************************************************ 
 * empilha                                      *
 * objetivo: rotina para inserir na pilha       *
 * entrada : pilha                              *
 * saida   : pilha com registro inserido no topo*
 ************************************************/ 
void empilha( PILHA** p ){
    PILHA *no = (PILHA *) malloc(sizeof(PILHA));
    
    if(no != NULL){
    	entrada_dados(no);
    	if(p == NULL)
    		*p = no;
    	else{
    		no->prox = *p;
    		*p = no;
		}
		printf("\n Registro inserido\n");
	}else{
		printf("\n Pilha Cheia \n");
	}
 
}



/*************************************************** 
 * exclui_nodo                                     *
 * objetivo: rotina para excluir registro da pilha *
 * entrada : pilha                                 *
 * saida   : pilha com o registro removido do topo *
 ***************************************************/ 
void desempilha( PILHA** p ){
	if(*p != NULL){
		PILHA *aux;
		aux = *p;
		
		*p = aux->prox;
		free(aux);
		printf("\n Registro removido com sucesso \n");
	}else{
		printf("\n Pilha Vazia \n");
	}
}

