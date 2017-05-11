/***********************************************/ 
/*                                             */
/* objetivo: trabalho Daniela                  */
/* programador: Rene Danni                     */
/* programador: Marcus Medeiros                */
/* programador: Filipe Cemin                   */
/* programador: Jonatan Colussi                */
/* programador: Felipe Santos da Silva         */
/* criado em: 09/05/2017                       */
/* data da ultima alteracao: 09/05/2017        */
/***********************************************/ 

#include <stdio.h>
//#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
    int  codigo;
	char nome[30];
	char endereco[30];
	char telefone[30];
	char zona[1];
} ENTIDADE;
       
typedef struct LISTA {
    ENTIDADE info;
    struct LISTA* prox;
} LISTA; 

void entrada_dados(LISTA* aux);
void imprime_lista(LISTA* aux);
void criar_lista(LISTA** p);
void ordena_lista(LISTA** p);
void inserir_registro(LISTA** p);
LISTA* procura_nodo(LISTA* p, int codigo);
void remover_registro(LISTA** p);

main( void ){
    char op;                            
    LISTA* p;
    
    while(1){
         printf( "\n /---------------------------------------------------/" ); 
         printf( "\n Programa de cadastro de entidades                    " );
         printf( "\n [1] Cria lista                                       " );
         printf( "\n [2] Inserir registro                                 " );
         printf( "\n [3] Remover registro                                 " );
         printf( "\n [4] Imprime lista                                    " );
         printf( "\n [5] Odenar lista                                     " );
         printf( "\n [0] Para sair do programa                            " );
         printf( "\n /---------------------------------------------------/" );      
         printf( "\n Opcao: " );
         op = getche();

         switch( op ) {
           case '1':
                criar_lista(&p);
                break;
                                
           case '2':
                inserir_registro(&p);    
                break;
           
           case '3':
                //remover_registro(&p);
                break;
                                                                            
           case '4':               
                //imprime_lista(p); 
                break;
                
            case '5':
                //ordena_lista(&p);
                break;
                                
           case '0':                                           
                exit( 1 ); 
                break;
                
           default : 
                printf( "\n Digite uma opcao!" );
                break;
        }

       
        fflush(stdin);
        getchar();
        
        printf( "\n" );
    }
}
	
void entrada_dados(LISTA* aux){
	printf("\n\n Digite o código: "); 
    fflush( stdin );// limpa buffer do teclado
    scanf("%d", &aux->info.codigo);

    printf("\n Digite o nome da entidade: ");
    fflush(stdin);// limpa buffer do teclado
    gets(aux->info.nome);
    
    printf("\n Digite o endereço da entidade: ");
    fflush(stdin);// limpa buffer do teclado
    gets(aux->info.endereco);
    
    printf("\n Digite o telefone da entidade: ");
    fflush(stdin);// limpa buffer do teclado
    gets(aux->info.telefone);
    
    printf("\n Informa a zona [N, S, L, O]: ");
    do{
	    fflush(stdin);// limpa buffer do teclado
	    gets(aux->info.zona);
	    
	    if(aux->info.zona[0] != 'N' || aux->info.zona[0] != 'S' || aux->info.zona[0] != 'L' || aux->info.zona[0] != 'O')
	    	printf("\n\t ZONA INVÁLIDA!");
	}while(aux->info.zona[0] != 'N' || aux->info.zona[0] != 'S' || aux->info.zona[0] != 'L' || aux->info.zona[0] != 'O');
  
    aux->prox= NULL;     // não aponta
}
//void imprime_lista(LISTA* aux){}
void criar_lista(LISTA** p){
	*p = NULL;
}
//void ordena_lista(LISTA** p){}
void inserir_registro(LISTA** p){
	LISTA *no = (LISTA *) malloc(sizeof(LISTA));
    
    if(no != NULL){
    	entrada_dados(no);
    	if(p == NULL)
    		*p = no;
    	else{
    		no->prox = *p;
    		*p = no;
		}
		printf("\n Registro inserido\n");
	}else
		printf("\n Lista Cheia \n");
}
//LISTA* procura_nodo(LISTA* p, int codigo){}
//void remover_registro(LISTA** p){}
