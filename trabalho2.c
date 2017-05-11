
/***********************************************/ 
/*                                             */
/* objetivo: trabalho Daniela                  */
/* programador: Rene Danni                     */
/* programador: Marcus Medeiros                */
/* programador: Filipe Cemin                   */
/* programador: Jonatan Colussi                */
/* programador: Felipe Santos da Silva         */
/* criado em: 09/05/2017                       */
/* data da ultima alteracao: 11/05/2017        */
/***********************************************/ 

#include <stdio.h>
//#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/***********************************************/ 
/* Definição dos Registros                     */
/***********************************************/ 
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


/***********************************************/ 
/* Definiçãoo das Funções                       */
/***********************************************/ 
void entrada_dados(LISTA* aux); // leitura dos dados de entrada
void imprime_lista(LISTA* aux); // visualizacao da lista em tela
void criar_lista(LISTA** p); // inicializa lista com NULL
void ordena_lista(LISTA** p); // ordena lista por campo a ser escolhido
void inserir_registro(LISTA** p); // inclui um novo registro no inicio da lista
LISTA*  procura_nodo( LISTA* p, int cod ); // procura na lista por uma codigo
void remover_registro(LISTA** l); // exclui um regitro por codigo 


/***********************************************/ 
/* Programa Principal                          */
/***********************************************/ 
int main ( void ){
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
                remover_registro(&p);
                break;
                                                                            
           case '4':               
                imprime_lista(p); 
                break;
                
            case '5':
                ordena_lista(&p);
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

/************************************************ 
 * entrada_dados                                *
 * objetivo: rotina para ler dados              *
 * entrada : nodo (ponteiro para o novo espaco) *
 * saida   : nodo com dados                     *
 ************************************************/
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
    //do{
	    fflush(stdin);// limpa buffer do teclado
	    gets(aux->info.zona);
	    
	/*    if(aux->info.zona[0] != 'N' || aux->info.zona[0] != 'S' || aux->info.zona[0] != 'L' || aux->info.zona[0] != 'O')
	    	printf("\n\t ZONA INVÁLIDA!");
	}while(aux->info.zona[0] != 'N' || aux->info.zona[0] != 'S' || aux->info.zona[0] != 'L' || aux->info.zona[0] != 'O');
  */
    aux->prox= NULL;     // não aponta
}

/************************************************
 * cria_lista                                   *
 * objetivo: rotina para inicializar a lista    *
 * entrada : lista                              *
 * saída   : NULL (inicializa lista)            *
 ************************************************/ 
void criar_lista(LISTA** p){
	*p = NULL;
}

/*************************************************** 
 * inserir_registro                                   *
 * objetivo: rotina para inserir no inicio da lista*
 * entrada : referencia de lista                   *
 * saída   : referencia lista com novo registro    *
 ***************************************************/ 
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

/************************************************ 
 * procura_nodo                                 *
 * objetivo: achar um registro por codigo       *
 * entrada : lista e codigo a ser procurado     *
 * saída   : posicao ou NULL (não encontrou)    *
 ************************************************/ 


/*************************************************
 * imprime_lista                                 *
 * objetivo: rotina para imprimir dados          *
 * entrada : lista                               *
 * saida   : nenhuma                             *
 *************************************************/ 
void imprime_lista( LISTA* aux )
{
	 if( aux == NULL )
	     printf("\n Lista vazia");
	 else{
	     LISTA *p = aux; //iniciliza o ponteiro auxiliar p
	     while( p != NULL ){ //p percorre a lista até o fim
	     	    printf("\n Nome: %s", p->info.nome);
	     	    printf("\n Codigo: %i", p->info.codigo);
                printf("\n Endereço: %s", p->info.endereco);
                printf("\n Telefone: %s", p->info.telefone);
                printf("\n Zona: %s", p->info.zona);

	     	    p= p->prox; //anda pela lista
		 }    
	          
	 }

}

/*************************************************** 
 * ordena_lista                                    *
 * objetivo: rotina para ordenar a lista           *
 * entrada : lista                                 *
 * saida   : lista ordenada por codigo             *
 ***************************************************/ 
void ordena_lista( LISTA** l )
{
    if(*l == NULL)
        printf("\n Lista vazia!");
    else{
        if( (*l)->prox == NULL)
            printf("\n Lista com apenas 1 elemento!");
        else{
            ENTIDADE aux;
            LISTA *ant = *l;
            LISTA *p = ant->prox;
        
        char ord;

         printf( "\n /---------------------------------------------------/" ); 
         printf( "\n Selecione o Campo de Oredenação                      " );
         printf( "\n [1] Código                                           " );
         printf( "\n [2] Nome                                             " );
         printf( "\n [3] Telefone                                         " );
         printf( "\n [4] Endereço                                         " );
         printf( "\n [5] Zona                                             " );
         printf( "\n [0] Cancelar                                         " );
         printf( "\n /---------------------------------------------------/" );      
         printf( "\n Opcao: " );
         fflush(stdin);
         ord = getchar();

         switch( ord ) { // Escolhe o campo a ser ordenado
           case '1':
            
            while( ant->prox != NULL) {
                while (p != NULL){
                    if(p->info.codigo < ant->info.codigo)
                    {
                        aux = p->info;
                        p->info = ant->info;
                        ant->info = aux;
                    }
                    p = p->prox;
                }
                ant= ant->prox;
                p = ant->prox;
            }
            
                break;
                                
           case '2':
           
             while( ant->prox != NULL) {
                while (p != NULL){
                    if(strcmp(p->info.nome,ant->info.nome) < 0) // Compara strings -1 menor, 0 igual, 1 maior
                    {
                        aux = p->info;
                        p->info = ant->info;
                        ant->info = aux;
                    }
                    p = p->prox;
                }
                ant= ant->prox;
                p = ant->prox;
            }
           
                break;
           
           case '3':
                
            while( ant->prox != NULL) {
                while (p != NULL){
                    if(p->info.telefone < ant->info.telefone)
                    {
                        aux = p->info;
                        p->info = ant->info;
                        ant->info = aux;
                    }
                    p = p->prox;
                }
                ant= ant->prox;
                p = ant->prox;
            }

                break;
                                                                            
           case '4':               
                
            while( ant->prox != NULL) {
                while (p != NULL){
                    if(strcmp(p->info.endereco, ant->info.endereco) < 0)
                    {
                        aux = p->info;
                        p->info = ant->info;
                        ant->info = aux;
                    }
                    p = p->prox;
                }
                ant= ant->prox;
                p = ant->prox;
            }

                break;
                
            case '5':
                
            while( ant->prox != NULL) {
                while (p != NULL){
                    if(strcmp(p->info.zona, ant->info.zona) < 0 )
                    {
                        aux = p->info;
                        p->info = ant->info;
                        ant->info = aux;
                    }
                    p = p->prox;
                }
                ant= ant->prox;
                p = ant->prox;
            }

                break;
                                
           case '0':                                           
                break;
                
           default : 
                printf( "\n Opção inválida!" );
                break;
        }


    }

}
}

LISTA* procura_nodo( LISTA *p, int cod ){
	while(p->info.codigo != cod){ // repete ate encontrar o cod desejado
		p=p->prox;	// percorre lista
		if(p==NULL) // toda lista percorrida e nao encontrou
			return NULL;
	}
	return p; 		// encontrou, retorna o endereco do cod desejado
}



void remover_registro(LISTA** l){
	if(*l != NULL){
		int cod = 0;
		LISTA *p = *l;
		LISTA *pc = p;
		printf("\n\n  Digite o codigo do registro para exclusao: ");
		fflush(stdin);
		scanf("%d",&cod);
		p = procura_nodo(p, cod);
		
		if(p != NULL){
			if(pc==p){
				*l=p->prox;
				pc->prox=p->prox;
				free(p);
				printf("funcionou");
			}else{
				while(pc->prox!=p){
					pc=pc->prox;
					pc->prox=p->prox;
					free(p);
					p=NULL;
				printf("Aqui tambem ");
				}
			}
		}else{
			printf(" Codigo n�o encontado");
		}	
		
	}else{
		printf(" Lista Vazia");
	}
}
