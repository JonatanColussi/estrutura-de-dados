
/*************************************************/ 
/*         Desafio de Programação 3              */
/* objetivo: Listas Encadeadas                   */
/* programador: Rene Danni                       */
/* programador: Marcus Medeiros                  */
/* programador: Filipe Cemim                     */
/* programador: Jonatan Colussi                  */
/* programador: Felipe Santos da Silva           */
/* criado em: 09/05/2017                         */
/* data da ultima alteração: 11/05/2017          */
/*************************************************/ 

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


/**********************************************/ 
/* Definição das Funções                      */
/**********************************************/ 
void entrada_dados(LISTA* aux, int inserirCodigo); // leitura dos dados de entrada
void imprime_lista(LISTA* aux); // visualização da lista em tela
void criar_lista(LISTA** p); // inicializa lista com NULL
void ordena_lista(LISTA** p); // ordena lista por campo a ser escolhido
void inserir_registro(LISTA** p); // inclui um novo registro no inicio da lista
LISTA* procura_nodo( LISTA* p, int cod ); // procura na lista por código
void remover_registro(LISTA** l); // exclui um regitro por código 
void altera_lista(LISTA** l); // Altera dados da lista
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
         printf( "\n [1] Criar lista                                      " );
         printf( "\n [2] Inserir registro                                 " );
         printf( "\n [3] Remover registro                                 " );
         printf( "\n [4] Imprimir lista                                   " );
         printf( "\n [5] Odenar lista                                     " );
         printf( "\n [6] Altera dados de entidade                         " );         
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
                
            case '6':
                altera_lista(&p);
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
 * saída   : nenhuma                            *
 ************************************************/
void entrada_dados(LISTA* aux, int inserirCodigo){
	int error = 0;
	if(inserirCodigo){
		printf("\n\n Digite o código: "); 
    	fflush( stdin );// limpa buffer do teclado
    	scanf("%d", &aux->info.codigo);
	}

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
 * saída   : NULL (inicializa lista)            *
 ************************************************/ 
void criar_lista(LISTA** p){
	*p = NULL; //aponta a lista para NULL
}

/*************************************************** 
 * inserir_registro                                *
 * objetivo: rotina para inserir no inicio da lista*
 * entrada : referencia de lista                   *
 * saída   : referencia lista com novo registro    *
 ***************************************************/ 
void inserir_registro(LISTA** p){
	LISTA *no = (LISTA *) malloc(sizeof(LISTA));
    
    if(no != NULL){
    	entrada_dados(no, 1);
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
 * saída   : nenhuma                             *
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
 * saída   : lista ordenada por codigo             *
 ***************************************************/ 
void ordena_lista( LISTA** l ){// Função para ordenar lista
	time_t tempoInicial, tempoFinal; //cria as variaveis para pegar o tempo inicial e o tempo final
  float tempoGasto; // cria a variavel que vai receber o tempo total gasto em execução
         
	tempoInicial = time(NULL); // captura o tempo que iniciou a função
  if(*l == NULL)                            //Testa se a lista está vazia
    printf("\n Lista vazia!");
  else{
    if( (*l)->prox == NULL)              //Testa se a lista tem mais de um registro
      printf("\n Lista com apenas 1 elemento!");
    else{
      LISTA *p = *l; //Ponteiro auxiliar
      LISTA *b = *l; //Ponteiro auxiliar
      LISTA *menor = *l; //Ponteiro auxiliar
      //todos acima apontam para o início da lista

     	LISTA *a = p->prox; //Ponteiro auxiliar que aponta pro proximo em relação ao primeiro
      char ord;// cria variável de seleção do menu

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

      switch(ord){// Escolhe o campo a ser ordenado
        case '1':
          while(p->prox != NULL){//percorre a lista até que o proximo seja nulo
            while(a != NULL){//percorre a lista com o auxiliar 'a' até que o proximo seja nulo
				      if(a->info.codigo < menor->info.codigo){ // verifica se o código da Posição 'a' é menor que o 'menor'
                menor = a; // se o código da Posição 'a' for menor que o 'menor', entao o menor é 'a'
				        while(b->prox != menor)//percorrre a lista procurando a posição anterior ao menor
						      b = b->prox; // 'b' se posiciona na posição anterior ao menor
		          }
		          a = a->prox; // 'a' se posiciona uma posição após ele mesmo
		        }
		        if(p == *l){ // se 'p' estiver na primeira Posição, alteramos a primeira posição
              if(menor == p){ // se o p for o menor
                p = p->prox; // passamos o p para a próxima posição
              }else{
		            *l = menor; // 'l' aponta para o 'menor', ou seja, o primeiro vai ser o menor ;)
                b->prox = menor->prox; // 'b' aponta para o mesmo lugar que o 'menor' estava appontando
                menor->prox = p; // 'menor' agora aponta para 'p'
				      }
            }else{
              if(menor == p){ // se o p for o menor
                p=p->prox; // passamos o p para a próxima posição
              }else{
                a = *l; // posicionamos 'a' no inicio
                while(a->prox != p) //percorrre a lista procurando a posição anterior ao p
                  a = a->prox; // 'a' se posiciona na posição próxima a ele mesmo
                a->prox = menor;  // prox de a aponta para o menor
                b->prox = menor->prox; // prox de b aponta para o mesmo lugar que aponta o prox do menor
                menor->prox = p; // prox de menor aponta para p
				      }
            }
            menor = p; 	//menor recebe p
            b = p;		// a ordenação continua a partir de 'p'
            a = p->prox; // 'a' aponta para o próximo de 'p', novamente...
          }
        break;                        
        case '2':
          while(p->prox != NULL){//percorre a lista até que o proximo seja nulo
            while(a != NULL){//percorre a lista com o auxiliar 'a' até que o proximo seja nulo
              if(strcmp(a->info.nome, menor->info.nome) < 0){ // Compara strings -1 menor, 0 igual, 1 maior
                menor = a; // se o código da Posição 'a' for menor que o 'menor', entao o menor é 'a'
                while(b->prox != menor)//percorrre a lista procurando a posição anterior ao menor
                  b = b->prox; // 'b' se posiciona na posição anterior ao menor
              }
              a = a->prox; // 'a' se posiciona uma posição após ele mesmo
            }
            if(p == *l){ // se 'p' estiver na primeira Posição, alteramos a primeira posição
              if(menor == p){ // se o p for o menor
                p = p->prox; // passamos o p para a próxima posição
              }else{
                *l = menor; // 'l' aponta para o 'menor', ou seja, o primeiro vai ser o menor ;)
                b->prox = menor->prox; // 'b' aponta para o mesmo lugar que o 'menor' estava appontando
                menor->prox = p; // 'menor' agora aponta para 'p'
              }
            }else{
              if(menor == p){ // se o p for o menor
                p=p->prox; // passamos o p para a próxima posição
              }else{
                a = *l; // posicionamos 'a' no inicio
                while(a->prox != p) //percorrre a lista procurando a posição anterior ao p
                  a = a->prox; // 'a' se posiciona na posição próxima a ele mesmo
                a->prox = menor;  // prox de a aponta para o menor
                b->prox = menor->prox; // prox de b aponta para o mesmo lugar que aponta o prox do menor
                menor->prox = p; // prox de menor aponta para p
              }
            }
            menor = p;  //menor recebe p
            b = p;    // a ordenação continua a partir de 'p'
            a = p->prox; // 'a' aponta para o próximo de 'p', novamente...
          }
        break;
        case '3':   
          while(p->prox != NULL){//percorre a lista até que o proximo seja nulo
            while(a != NULL){//percorre a lista com o auxiliar 'a' até que o proximo seja nulo
              if(strcmp(a->info.telefone, menor->info.telefone) < 0){ // Compara strings -1 menor, 0 igual, 1 maior
                menor = a; // se o código da Posição 'a' for menor que o 'menor', entao o menor é 'a'
                while(b->prox != menor)//percorrre a lista procurando a posição anterior ao menor
                  b = b->prox; // 'b' se posiciona na posição anterior ao menor
              }
              a = a->prox; // 'a' se posiciona uma posição após ele mesmo
            }
            if(p == *l){ // se 'p' estiver na primeira Posição, alteramos a primeira posição
              if(menor == p){ // se o p for o menor
                p = p->prox; // passamos o p para a próxima posição
              }else{
                *l = menor; // 'l' aponta para o 'menor', ou seja, o primeiro vai ser o menor ;)
                b->prox = menor->prox; // 'b' aponta para o mesmo lugar que o 'menor' estava appontando
                menor->prox = p; // 'menor' agora aponta para 'p'
              }
            }else{
              if(menor == p){ // se o p for o menor
                p=p->prox; // passamos o p para a próxima posição
              }else{
                a = *l; // posicionamos 'a' no inicio
                while(a->prox != p) //percorrre a lista procurando a posição anterior ao p
                  a = a->prox; // 'a' se posiciona na posição próxima a ele mesmo
                a->prox = menor;  // prox de a aponta para o menor
                b->prox = menor->prox; // prox de b aponta para o mesmo lugar que aponta o prox do menor
                menor->prox = p; // prox de menor aponta para p
              }
            }
            menor = p;  //menor recebe p
            b = p;    // a ordenação continua a partir de 'p'
            a = p->prox; // 'a' aponta para o próximo de 'p', novamente...
          }
        break;                                                                    
        case '4':                       
          while(p->prox != NULL){//percorre a lista até que o proximo seja nulo
            while(a != NULL){//percorre a lista com o auxiliar 'a' até que o proximo seja nulo
              if(strcmp(a->info.endereco, menor->info.endereco) < 0){ // Compara strings -1 menor, 0 igual, 1 maior
                menor = a; // se o código da Posição 'a' for menor que o 'menor', entao o menor é 'a'
                while(b->prox != menor)//percorrre a lista procurando a posição anterior ao menor
                  b = b->prox; // 'b' se posiciona na posição anterior ao menor
              }
              a = a->prox; // 'a' se posiciona uma posição após ele mesmo
            }
            if(p == *l){ // se 'p' estiver na primeira Posição, alteramos a primeira posição
              if(menor == p){ // se o p for o menor
                p = p->prox; // passamos o p para a próxima posição
              }else{
                *l = menor; // 'l' aponta para o 'menor', ou seja, o primeiro vai ser o menor ;)
                b->prox = menor->prox; // 'b' aponta para o mesmo lugar que o 'menor' estava appontando
                menor->prox = p; // 'menor' agora aponta para 'p'
              }
            }else{
              if(menor == p){ // se o p for o menor
                p=p->prox; // passamos o p para a próxima posição
              }else{
                a = *l; // posicionamos 'a' no inicio
                while(a->prox != p) //percorrre a lista procurando a posição anterior ao p
                  a = a->prox; // 'a' se posiciona na posição próxima a ele mesmo
                a->prox = menor;  // prox de a aponta para o menor
                b->prox = menor->prox; // prox de b aponta para o mesmo lugar que aponta o prox do menor
                menor->prox = p; // prox de menor aponta para p
              }
            }
            menor = p;  //menor recebe p
            b = p;    // a ordenação continua a partir de 'p'
            a = p->prox; // 'a' aponta para o próximo de 'p', novamente...
          }
        break;        
        case '5':        
          while(p->prox != NULL){//percorre a lista até que o proximo seja nulo
            while(a != NULL){//percorre a lista com o auxiliar 'a' até que o proximo seja nulo
              if(strcmp(a->info.zona, menor->info.zona) < 0){ // Compara strings -1 menor, 0 igual, 1 maior
                menor = a; // se o código da Posição 'a' for menor que o 'menor', entao o menor é 'a'
                while(b->prox != menor)//percorrre a lista procurando a posição anterior ao menor
                  b = b->prox; // 'b' se posiciona na posição anterior ao menor
              }
              a = a->prox; // 'a' se posiciona uma posição após ele mesmo
            }
            if(p == *l){ // se 'p' estiver na primeira Posição, alteramos a primeira posição
              if(menor == p){ // se o p for o menor
                p = p->prox; // passamos o p para a próxima posição
              }else{
                *l = menor; // 'l' aponta para o 'menor', ou seja, o primeiro vai ser o menor ;)
                b->prox = menor->prox; // 'b' aponta para o mesmo lugar que o 'menor' estava appontando
                menor->prox = p; // 'menor' agora aponta para 'p'
              }
            }else{
              if(menor == p){ // se o p for o menor
                p=p->prox; // passamos o p para a próxima posição
              }else{
                a = *l; // posicionamos 'a' no inicio
                while(a->prox != p) //percorrre a lista procurando a posição anterior ao p
                  a = a->prox; // 'a' se posiciona na posição próxima a ele mesmo
                a->prox = menor;  // prox de a aponta para o menor
                b->prox = menor->prox; // prox de b aponta para o mesmo lugar que aponta o prox do menor
                menor->prox = p; // prox de menor aponta para p
              }
            }
            menor = p;  //menor recebe p
            b = p;    // a ordenação continua a partir de 'p'
            a = p->prox; // 'a' aponta para o próximo de 'p', novamente...
          }
        break;                        
        case '0':     // opção de saída                                      
        break;              
        default : 
          printf( "\n Opção inválida!" );
        break;
      }
		  _sleep(5000); // da uma pausa em Milissegundo
		  tempoFinal = time(NULL); // captura o tempo final da execução
      tempoGasto= difftime(tempoFinal, tempoInicial); // retorna a diferença entre o tempo final e tempo inicial
        
      printf("Ordenado com sucesso! \n");
		  printf("Tempo de execucao %f",tempoGasto); // mostra o tempo de execução 
    }
  }
}

/************************************************ 
 * procura_nodo                                 *
 * objetivo: achar um registro por codigo       *
 * entrada : lista e codigo a ser procurado     *
 * saída   : Posição ou NULL (Não encontrou)    *
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
 * saída   : nenhum                                *
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
 * saída   : int                                                 *
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

/*************************************************
 * altera_lista                                 *
 * objetivo: rotina para alterar dados          *
 * entrada : lista                               *
 * saída   : nenhuma                             *
 *************************************************/ 
void altera_lista( LISTA** aux ){
	int codigo;// Recebe código do item que será alterado
	LISTA* no;
	
	if( aux == NULL )
	    printf("\n Lista vazia");
	else{
		printf("\n Código do item: ");
		scanf("%i", &codigo);
		printf("\n");
		no = procura_nodo(*aux, codigo);
		entrada_dados(no, 0);
		printf("\n Registro alterado com sucesso! \n");
	}
}
