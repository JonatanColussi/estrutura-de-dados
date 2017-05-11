
/***********************************************/ 
/*                                             */
/* objetivo: trabalho Daniela                  */
/* programador: Rene Danni                     */
/* programador: Marcus Medeiros                */
/* programador: Filipe Cemin                   */
/* programador: Jonatan Colussi                */
/* programador: Felipe Santos da Silva         */
/* criado em: 09/05/2017                       */
/* data da ultima alteração: 11/05/2017        */
/***********************************************/ 

#include <stdio.h>
//#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <ctype.h>


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
/* Definiçãoo das Funções                      */
/***********************************************/ 
void entrada_dados(LISTA* aux); // leitura dos dados de entrada
void imprime_lista(LISTA* aux); // visualização da lista em tela
void criar_lista(LISTA** p); // inicializa lista com NULL
void ordena_lista(LISTA** p); // ordena lista por campo a ser escolhido
void inserir_registro(LISTA** p); // inclui um novo registro no inicio da lista
LISTA* procura_nodo( LISTA* p, int cod ); // procura na lista por código
void remover_registro(LISTA** l); // exclui um regitro por código 
int validarZona(char zona[1]); // valida se a zona é válida


/***********************************************/ 
/* Programa Principal                          */
/***********************************************/ 
main(){
    char op;                            
    LISTA* p;
    criar_lista(&p);
    setlocale (LC_ALL, "Portuguese");
    while(1){
		printf( "\n /---------------------------------------------------/" ); 
		printf( "\n Programa de cadastro de entidades                    " );
		printf( "\n [1] Criar lista                                       " );
		printf( "\n [2] Inserir registro                                 " );
		printf( "\n [3] Remover registro                                 " );
		printf( "\n [4] Imprimir lista                                    " );
		printf( "\n [5] Odenar lista                                     " );
		printf( "\n [0] Para sair do programa                            " );
		printf( "\n /---------------------------------------------------/" );      
		printf( "\n Opcao: " );
		op = getche();

        switch(op) {
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
                printf( "\n Digite uma opção!" );
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
 * entrada : nodo (ponteiro para o novo espaço) *
 * saida   : nenhuma                            *
 ************************************************/
void entrada_dados(LISTA* aux){
	int error = 0;
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
    
    printf("\n Informe a zona [N, S, L, O]: ");
    do{//obriga o usuário a escolher uma das zonas
	    fflush(stdin);// limpa buffer do teclado
	    gets(aux->info.zona);
	    //Converte a entrada em letra maiuscula
	    aux->info.zona[0] = toupper(aux->info.zona[0]);
	    //verifica se a zona digitada está certa
	    error = validarZona(aux->info.zona);
	    //Caso esteja errado, repete o processo
		if(error){
	    	printf("\n\t ZONA INVÁLIDA!");
   			printf("\n Informe a zona [N, S, L, O]: ");
			fflush(stdin);// limpa buffer do teclado
	    	gets(aux->info.zona);
	    	//Converte a entrada em letra maiuscula
		    aux->info.zona[0] = toupper(aux->info.zona[0]);
		    //verifica se a zona digitada está certa
		    error = validarZona(aux->info.zona);
		}
	}while(error);//repete até enquanto houverem erros
    
	aux->prox= NULL;
}

/************************************************
 * cria_lista                                   *
 * objetivo: rotina para inicializar a lista    *
 * entrada : lista                              *
 * saÃ­da   : NULL (inicializa lista)            *
 ************************************************/ 
void criar_lista(LISTA** p){
	*p = NULL; //aponta a lista para NULL
}

/*************************************************** 
 * inserir_registro                                   *
 * objetivo: rotina para inserir no inicio da lista*
 * entrada : referencia de lista                   *
 * saÃ­da   : referencia lista com novo registro    *
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

/*************************************************
 * imprime_lista                                 *
 * objetivo: rotina para imprimir dados          *
 * entrada : lista                               *
 * saida   : nenhuma                             *
 *************************************************/ 
void imprime_lista( LISTA* aux ){
	if( aux == NULL )
	    printf("\n Lista vazia");
	else{
	    LISTA *p = aux; //iniciliza o ponteiro auxiliar p
	    while( p != NULL ){ //p percorre a lista até o fim
     	    printf("\n Nome: %s", p->info.nome);
     	    printf("\n Codigo: %i", p->info.codigo);
            printf("\n Endereço: %s", p->info.endereco);
            printf("\n Telefone: %s", p->info.telefone);
            printf("\n Zona ");
            switch(p->info.zona[0]){
            	case 'N':
            		printf("Norte");
            		break;
            	case 'S':
            		printf("Sul");
            		break;
            	case 'L':
            		printf("Leste");
            		break;
            	case 'O':
            		printf("Oeste");
            		break;
			}
			printf("\n---------------------\n");
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
void ordena_lista( LISTA** l ){
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
	        printf( "\n Selecione o Campo de Oredenação                    " );
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
	
	        switch(ord){ // Escolhe o campo a ser ordenado
	           case '1':
		            while(ant->prox != NULL) {
		                while (p != NULL){
		                    if(p->info.codigo < ant->info.codigo){
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
		            while(ant->prox != NULL){
		                while (p != NULL){
		                    if(strcmp(p->info.nome,ant->info.nome) < 0){ // Compara strings -1 menor, 0 igual, 1 maior
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
		            while(ant->prox != NULL) {
		                while (p != NULL){
		                    if(p->info.telefone < ant->info.telefone){
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
		            while(ant->prox != NULL) {
		                while (p != NULL){
		                    if(strcmp(p->info.endereco, ant->info.endereco) < 0){
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
		            while(ant->prox != NULL) {
		                while (p != NULL){
		                    if(strcmp(p->info.zona, ant->info.zona) < 0){
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

/************************************************ 
 * procura_nodo                                 *
 * objetivo: achar um registro por codigo       *
 * entrada : lista e codigo a ser procurado     *
 * saÃ­da   : posicao ou NULL (nÃ£o encontrou)    *
 ************************************************/ 

LISTA* procura_nodo( LISTA *p, int cod ){
	while(p->info.codigo != cod){ // repete ate encontrar o cod desejado
		p=p->prox;	// percorre lista
		if(p==NULL) // toda lista percorrida e nao encontrou
			return NULL;
	}
	return p; 		// encontrou, retorna o endereco do cod desejado
}

/*************************************************** 
 * remover_registro                                *
 * objetivo: rotina para excluir registro da lista *
 * entrada : lista                                 *
 * saida   : lista                                 *
 ***************************************************/ 

void remover_registro(LISTA** l){
	int cod;      // codigo a ser excluido 
    LISTA* p;     // ponteiro auxiliar para percorrer a lista 
    LISTA* no;    // ponteiro auxiliar para a codigo de referencia

    printf("\n codigo de referencia: ");
    fflush( stdin );                        // limpa buffer do teclado e faz a entrada de dados
    scanf( "%d", &cod );              
    
    if(*l != NULL){                       // verifica se a lista esta vazia 
        no = procura_nodo(*l, cod);       // procura codigo de referencia, a ser excluida
        if((cod == no->info.codigo) && (no != NULL)){ // verifica se encontrou a codigo na lista
            p = *l;                         // ponteiro auxiliar aponta para o inicio da lista
            if(p == no)                   // verifica se o registro apontado pelo auxiliar e o registro que sera excluido
                *l = p->prox;               // faz o inicio da lista apontar para o proximo registro, visto que o primeiro sera excluido
            else{
                while(p->prox != no)     // procura registro anterior ao que sera excluido
                    p = p->prox;
                p->prox = no->prox;        // faz o registro anterior apontar para um registro após o excluido - para onde este esta apontando
            }

            free(no); // libera o espaco de memoria que estava sendo ocupado pelo registro que foi excluido
            printf("\n Registro excluido!");
        }else
             printf("\n Nodo nao encontrado!");
    }else
        printf("\n Lista vazia!");
}

/***************************************************************** 
 * validarZona                                                   *
 * objetivo: função para validar se a zona digitada está correta *
 * entrada : char[1]                                             *
 * saida   : int                                                 *
 *****************************************************************/ 
int validarZona(char zona[1]){
	switch(zona[0]){
    	case 'N':
    	case 'S':
    	case 'L':
    	case 'O':
    		//se a zona digitada está ná lista, retorna 0, ou seja false. Esse retorno será usado como erro
    		return 0;
    	default:
    		//se a zona digitada não está ná lista, retorna 1, ou seja true. Esse retorno será usado como erro
    		return 1;
	}
}
