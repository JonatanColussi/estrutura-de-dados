/***********************************************/ 
/* Lista Encadeada                             */
/* objetivo: cadastro de pessoas               */
/* programador: Jonatan Colussi               */
/***********************************************/ 

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/***********************************************/ 
/* Definição dos Registros                     */
/***********************************************/ 
typedef struct {// registro para uma pessoa
       int  codigo;
       char nome[30];
} INFORMACAO;
       
typedef struct LISTA {
       INFORMACAO info;// dados do registro
       LISTA* prox; // ponteiro para o próximo registro
}; 

/***********************************************/ 
/* Definição das Funções                       */
/***********************************************/ 
void    entrada_dados  ( LISTA* aux ); // leitura dos dados de entrada
void    imprime_lista  ( LISTA* aux ); // visualizacao da lista em tela
void    cria_lista     ( LISTA** l );  // inicializa lista com NULL
void    inclui_fim     ( LISTA** l );  // inclui um novo registro no final da lista
void    inclui_inicio  ( LISTA** l );  // inclui um novo registro no inicio da lista
LISTA*  procura_nodo   ( LISTA* l, int cod ); // procura na lista por uma codigo
void    exclui_nodo    ( LISTA** l );  // exclui um regitro por codigo 
void    ordena_lista   ( LISTA** l );  // ordena lista por codigo
void    inclui_ordenado( LISTA** l );  // inclui registro na lista ordenado por codigo
void    inverte        ( LISTA** l );  // inverte referencia dos registros
void    consulta_nome  ( LISTA* l );   // consulta por um nome
void    inserir_antes  ( LISTA** l );  // inserir um registro antes de uma codigo de referencia
void    inserir_depois ( LISTA** l );  // inserir um registro depois de uma codigo de referencia
void    conta_nodo     ( LISTA** l );  // contar o numero de registros existentes na lista
void    ordena_selecao ( LISTA** l );  // ordena lista por codigo


/***********************************************/ 
/* Programa Principal                          */
/***********************************************/ 
main(){
    int op;   // opcao do menu                               
    LISTA *l; // declaracao da lista // variavel do tipo lista = lista de ponteiros

    cria_lista( &l );
    while( 1 ){
         printf( "\n /------------------------------------------------------/" ); 
         printf( "\n Programa de cadastro - Menu                             " );
         printf( "\n [ 1]   Cria lista                                       " );
         printf( "\n [ 2]   Inclui registro no final da lista                " );
         printf( "\n [ 3]   Inclui registro no inicio da lista               " );
         printf( "\n [ 4]   Exclui registro                                  " );
         printf( "\n [ 5]   Ordena lista                                     " );
         printf( "\n [ 6]   Inlcui ordenado                                  " );
         printf( "\n [ 7]   Inverte lista                                    " );         
         printf( "\n [ 8]   Consulta nome                                    " );         
         printf( "\n [ 9]   Inserir antes                                    " );           
         printf( "\n [10]  Inserir depois                                    " );     
         printf( "\n [11]  Conta registros                                   " );           
         printf( "\n [12]  Ordena selecao                                    " );  
         printf( "\n [13]  Imprime lista                                     " );         
         printf( "\n [ 0]   Para sair do programa                            " );
         printf( "\n /------------------------------------------------------/" );      
         printf( "\n Opcao: " );
         scanf("%d", &op); // tecla de opcao do menu
         

         switch( op ) {
            case 1: // rotina cria lista       
                cria_lista( &l );
                break;
                                
            case 2:  // rotina inclui registro no final da lista
                inclui_fim( &l );    
                break;
          
            case 3:  // rotina inclui registro no inicio da lista
                inclui_inicio( &l );
                break;
                
            case 4:  // rotina exclui registro da lista
                //exclui_nodo( &l );
                break;
                  
            case 5:  // rotina ordena lista
                ordena_lista( &l );
                break;

            case 6:  // rotina inclui ordenado
                //inclui_ordenado( &l );
                break;
                                                                                   
            case 7:  // rotina inverte o sentido dos ponteiros da lista (aponta da direita para a esquerda, mudando o início e fim)                
                //inverte( &l ); 
                break;                                
                    
            case 8: // rotina consultar por um nome                 
                //consulta_nome( l ); 
                break;             

            case 9: // rotina inserir antes de um codigo                 
                //inserir_antes( &l ); 
                break; 

            case 10: // rotina inserir depois de um codigo                 
                //inserir_depois( &l ); 
                break; 
                                                                               
            case 11: // rotina contar o numero de registros na lista                 
                conta_nodo( &l ); 
                break; 

            case 12: // rotina imprime lista                 
                //ordena_selecao( &l ); 
                break;

            case 13: // rotina imprime lista                 
                imprime_lista( l ); 
                break;                    
                    
            case 0: // término do programa                                                 
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
     

} // fim do programa principal

/*************************************************
 * imprime_lista                                 *
 * objetivo: rotina para imprimir dados          *
 * entrada : lista                               *
 * saida   : nenhuma                             *
 *************************************************/ 
void imprime_lista( LISTA* aux ){
	system("cls");
	if( aux == NULL )
    	printf("\n Lista vazia");
	else{
		LISTA *tmp = aux;
		while(tmp != NULL){
			printf("\nCódigo: %i", tmp->info.codigo);
			printf("\nNome: %s", tmp->info.nome);
			printf("\n-----------------------");
			tmp = tmp->prox;
		}
	}
}



/************************************************
 * cria_lista                                   *
 * objetivo: rotina para inicializar a lista    *
 * entrada : lista                              *
 * saída   : NULL (inicializa lista)            *
 ************************************************/ 
void cria_lista( LISTA** l ){
  *l = NULL;
}


/************************************************ 
 * entrada_dados                                *
 * objetivo: rotina para ler dados              *
 * entrada : nodo (ponteiro para o novo espaco) *
 * saida   : nodo com dados                     *
 ************************************************/
void entrada_dados( LISTA *aux ){ 
	printf("\nDigite o código: ");
	fflush(stdin);
	scanf("%i", &aux->info.codigo);
	
	printf("\nInsira o nome: ");
	fflush(stdin);
	gets(aux->info.nome);
	
	aux->prox = NULL;
}


/************************************************ 
 * inclui_fim                                   *
 * objetivo: rotina para inserir no fim da lista*
 * entrada : lista                              *
 * saida   : lista com novo registro            *
 ************************************************/ 
void inclui_fim( LISTA** l ){
	LISTA *no = (LISTA *) malloc(sizeof(LISTA));
	
	if(no != NULL){
		entrada_dados(no);
		if(*l == NULL)
			*l = no;
		else{
			LISTA *p = *l;
			while(p->prox != NULL)
				p = p->prox;
				
			p->prox = no;
		}
		printf("Registro inserido!");
	}else
		printf("\n Lista cheia!");
 
}



/*************************************************** 
 * inclui_inicio                                   *
 * objetivo: rotina para inserir no inicio da lista*
 * entrada : referencia de lista                   *
 * saída   : referencia lista com novo registro    *
 ***************************************************/ 
void inclui_inicio( LISTA** l ){
	LISTA *no = (LISTA *) malloc(sizeof(LISTA));
	
	if(no != NULL){
	    entrada_dados(no);
	    if(*l == NULL)
			*l = no;
		else{
			no->prox = *l;
			*l = no;
		}
		printf("Registro inserido!");
	}else
		printf("\n Lista cheia!");
}

/*************************************************** 
 * conta_nodo                                      *
 * objetivo: rotina para contar numero de registros*
 * entrada : lista                                 *
 * saida   : nenhuma                               *
 **************************************************/ 
void conta_nodo( LISTA** l ){
	int i = 0;
	LISTA *p = *l;
	if(p != NULL){
		while(p->prox != NULL){
			i++;
			p = p->prox;
		}
		i++;
	}
	printf("\nTemos %i registros inseridos!\n", i);
}




/************************************************ 
 * procura_nodo                                 *
 * objetivo: achar um registro por codigo       *
 * entrada : lista e codigo a ser procurado     *
 * saída   : posicao ou NULL (não encontrou)    *
 ************************************************/ 
LISTA* procura_nodo( LISTA* l, int cod )
{ 
    while( ( l->info.codigo != cod ) && ( l->prox != NULL ))// anda pela lista até o final ou até encontrar codigo desejado
             l = l->prox;                                   // passa para o proximo   
             
    return p; // nodo de referencia
}



/*************************************************** 
 * exclui_nodo                                     *
 * objetivo: rotina para excluir nodo da lista     *
 * entrada : lista                                 *
 * saida   : lista                                 *
 ***************************************************/ 
void exclui_nodo(LISTA** l){
    int cod;      // codigo a ser excluido 
    LISTA* p;     // ponteiro auxiliar para percorrer a lista 
    LISTA* no;    // ponteiro auxiliar para a codigo de referencia

    printf("\n codigo de referencia: ");
    fflush( stdin );                        // limpa buffer do teclado e faz a entrada de dados
    scanf( "%d", &cod );              
    
    if(*l != NULL)
	{                       // verifica se a lista esta vazia 
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

void ordena_lista(LISTA** l){
	LISTA* atual;
	LISTA* proximo;
	INFORMACAO aux;
	
	atual = *l; //atual aponta pro primeiro
	proximo = atual->prox; //proximo aponta pro proximo do atual, que é o primeiro, que é o segundo
	
	while(atual->prox != NULL){ //varre o array começando pelo primeiro
		while(proximo != NULL){ //varre o array começando sempre no proximo
			if(proximo->info.codigo < atual->info.codigo){//verifica se o codigo do próximo é maior que o do primeiro
				//Troca default
				aux = atual->info;
				atual->info = proximo->info;
				proximo->info = aux;	
			}
			proximo = proximo->prox; //Incrementa o proximo para continuarmos com o while interno até o fim
		}
		
		atual = atual->prox; //move a variavel atual pro proximo
		proximo = atual->prox; //move a variavel próximo pro próximo do próximo
	}
}
