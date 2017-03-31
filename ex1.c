/***********************************************/
/* Exercício para Lista Sequencial             */
/* objetivo: controle de pacientes             */
/* programador: Daniela Bagatini               */
/* criado em: 24/08/2016                       */
/* data da Última alteração: 24/08/2016        */
/***********************************************/

#include <stdio.h>  // printf e scanf 
#include <conio.h>  // getche
#include <stdlib.h> // exit
#include <string.h> // strcmp
#include <ctype.h>  // toupper
#include <locale.h> // português



#define N_MAX   4  // número máximo de registros na lista


/***********************************************/
/* Definição dos Registros                     */
/***********************************************/
typedef struct {       // registro para uma pessoa
       int codigo;
       char nome[ 30 ];
       //char cpf[ 11 ];
       //char endereco[40];
       //char email[40];
} NODO;


typedef struct {       // registro para uma pessoa
        NODO info[ N_MAX ];
        int  f;        // indica o final da lista válida (próxima posição a incluir)
} LISTASEQ;



/***********************************************/
/* Definição das Funções                       */
/***********************************************/
void cria_lista       (int *fim );       // inicializa a lista
void entrada_dados    (NODO *aux);       // lê dados de entrada do registro
void imprime_lista    (LISTASEQ *lista); // visualização da lista em tela            
void inclui_fim       (LISTASEQ *lista); // inclui um novo registro no final da lista (posição f)
void inclui_inicio    (LISTASEQ *lista); // inclui um novo registro no início da lista (posição 0)
void exclui_nodo      (LISTASEQ *lista); // exclui um regitro por código
int  procura_nodo     (LISTASEQ *lista); // procura na lista por um código
void inclui_antes     (LISTASEQ *lista); // inclui um novo registro antes de um código de referência
void inclui_depois    (LISTASEQ *lista); // inclui um novo registro depois de um código de referência
void ordena_lista     (LISTASEQ *lista); // ordena por código em ordem crescente
void altera_nodo      (LISTASEQ *lista); // altera um regitro por código
//void inclui_ordenado(LISTASEQ *lista); // inlcui ordenado por código
void posicionar_inicio(LISTASEQ *lista, int posicao);


/***********************************************/
/* Programa Principal                          */
/***********************************************/
int main(void){
   	char op;// opção do menu
    LISTASEQ lista;     
    setlocale(LC_ALL, "Portuguese");

    cria_lista(&lista.f); // inicializa a lista
    while(1){
        printf("\n /-------------------------------------------------------/");
        printf("\n Programa de cadastro de pessoas - Menu                   ");
        printf("\n [1] Inclui registro no final                             ");
        printf("\n [2] Inclui registro no início                            ");
        printf("\n [3] Exclui registro                                      ");              
        printf("\n [4] Imprime lista                                        ");
        printf("\n [5] Incluir depois                                       ");
        printf("\n [6] Incluir antes                                        ");
        printf("\n [7] Altera nodo                                          ");
        printf("\n [8] Ordenar lista                                        ");
        printf("\n [s] Para sair do programa                                ");
        printf("\n /-------------------------------------------------------/");
        printf("\n Opção: ");
        op = toupper(getche());// tecla de opção do menu
         
        switch(op) {
        	case '1':  // rotina inclui no fim da lista (posição f)
        		system("cls");
                inclui_fim(&lista);
                break;        
            case '2':  // rotina inclui no início da lista (posição 0)
            	system("cls");
				inclui_inicio(&lista);
                break;    
            case '3':  // rotina exclui registro conforme código
            	system("cls");
				exclui_nodo(&lista);
                break;
            case '4': // rotina imprime registros
            	system("cls");
				imprime_lista(&lista);
                break;
            case '5': // rotina imprime registros
            	system("cls");
				inclui_depois(&lista);
                break;
            case '6': // rotina imprime registros
            	system("cls");
				inclui_antes(&lista);
                break;
            case '7': // rotina imprime registros
            	system("cls");
				altera_nodo(&lista);
                break;
            case '8': // rotina imprime registros
            	system("cls");
				ordena_lista(&lista);
                break;
            case 'S': // término do programa
                exit(1);
                break;
            default :
                printf("\n Digite uma opção!");
                break;
        } // switch(op)
        printf("\n");
     } // fim do while(1)

 return 0;
} // fim do programa principal



/*************************************************
 * cria_lista                                    *
 * objetivo: rotina para incializar o controle   *
 * entrada : f                                 *
 *************************************************/
void cria_lista (int *fim){
    *fim = 0;
}


/*************************************************
 * entrada_dados                                 *
 * objetivo: rotina para ler dados novo registro *
 * entrada : aux                                 *
 *************************************************/
void entrada_dados (NODO *aux){
	printf("\n Informe código: ");
	fflush(stdin);
	scanf("%i", &aux->codigo);
	
	printf("\n Informe nome: ");
	fflush(stdin);
	gets(aux->nome);
}


/*************************************************
 * imprime_lista                                 *
 * objetivo: rotina para imprimir dados          *
 * entrada : lista                               *
 *************************************************/
void imprime_lista(LISTASEQ *lista){
	int i;
	
	if(lista->f == 0){
		printf("\n Lista vazia!");
	}
	else
		for(i= 0; i < lista->f; i++){
			printf("\n Nome..: %s", lista->info[i].nome);
			printf("\n Código: %i", lista->info[i].codigo);
		}
}


/************************************************
 * inclui_inicio                                *
 * objetivo: rotina para inserir no início lista*
 * entrada : lista                              *
 * saída   : lista com novo elemento            *
 ************************************************/
void inclui_inicio(LISTASEQ *lista){
	int i;
	NODO aux; // auxiliar para a leitura de dados
	
	if(lista->f < N_MAX){    // verifica se a lista não está cheia
		entrada_dados(&aux); // lê dados
		for(i= lista->f; i > 0; i--) 
		    lista->info[i]= lista->info[i-1]; // deslocamento dos registros na lista
		lista->info[0]= aux; // insere novo registro na posição zero
		lista->f++; // incrementa número de registros
		printf("\n Registro inserido!");    
	}
	else
		printf("\n Lista cheia!");
}


/************************************************
 * inclui_fim                                   *
 * objetivo: rotina para inserir no fim da lista*
 * entrada : lista                              *
 * saída   : lista com novo elemento            *
 ************************************************/
void inclui_fim(LISTASEQ *lista){
	NODO aux; // auxiliar para a leitura de dados
	
	if(lista->f < N_MAX){    // verifica se a lista não está cheia
		entrada_dados(&aux); // lê dados
		lista->info[lista->f]= aux; // insere na lista na posição indicada por f (primeira posição vaga)
		lista->f++; // incrementa f com mais um registro
		printf("\n Registro inserido!");
	}
	else
		printf("\n Lista cheia!");
}


/************************************************
 * exclui_nodo                                  *
 * objetivo: rotina para excluir no fim da lista*
 * entrada : lista                              *
 * saída   : lista com um elemento removido     *
 ************************************************/
void exclui_nodo(LISTASEQ *lista){
	int codigo, i, posicao;
    imprime_lista(lista);
    posicao = procura_nodo(lista);
    
   	if(posicao >= 0){
	   	for(i=posicao; i < lista->f; i++)
	    	lista->info[i] = lista->info[i+1];
		lista->f--;
   		printf("\n Registro excluído com sucesso \n");
	}else{
   		printf("\n Código não encontrado \n");
	}
}

int procura_nodo(LISTASEQ *lista){
	int posicao = -1;
	int codigo, i;
	imprime_lista(lista);
	printf("\n Digite o código do registro que deseja excluir: ");
    scanf("%i", &codigo);
    
   	for(i=0; i < lista->f; i++)
   		if(lista->info[i].codigo == codigo)
   			posicao = i;
   	
   	return posicao;
}

void inclui_depois(LISTASEQ *lista){
	NODO aux; // auxiliar para a leitura de dados
	int posicao = -1;
	int i;
	
	if(lista->f < N_MAX){    // verifica se a lista não está cheia
		posicao = procura_nodo(lista);
		if(posicao >= 0){
			entrada_dados(&aux); // lê dados
			for(i = lista->f; i >= posicao; i--){
				lista->info[i+1] = lista->info[i];
			}
			lista->info[posicao+1]= aux;
			lista->f++; // incrementa f com mais um registro
			printf("\n Registro inserido!");
		}else{
			printf("\n Código não encontrado \n");
		}
	}
	else
		printf("\n Lista cheia!");
}

void inclui_antes(LISTASEQ *lista){
	NODO aux; // auxiliar para a leitura de dados
	int posicao = -1;
	int i;
	
	if(lista->f < N_MAX){    // verifica se a lista não está cheia
		posicao = procura_nodo(lista);
		if(posicao >= 0){
			entrada_dados(&aux); // lê dados
			for(i = lista->f; i > posicao; i--){
				lista->info[i] = lista->info[i-1];
			}
			lista->info[posicao]= aux;
			lista->f++; // incrementa f com mais um registro
			printf("\n Registro inserido!");
		}else{
			printf("\n Código não encontrado \n");
		}
	}
	else
		printf("\n Lista cheia!");
}

void altera_nodo(LISTASEQ *lista){
	NODO aux; // auxiliar para a leitura de dados
	int posicao = -1;
	int i;

	posicao = procura_nodo(lista);
	if(posicao >= 0){
		entrada_dados(&aux); // lê dados
		lista->info[posicao]= aux;
		printf("\n Registro alterado!");
	}else{
		printf("\n Código não encontrado \n");
	}
}

void ordena_lista(LISTASEQ *lista){
	int i;
	for(i=0; i < lista->f; i++)
		if(lista->info[i].codigo < lista->info[0].codigo)
			posicionar_inicio(lista, 1);
}

void posicionar_inicio(LISTASEQ *lista, int posicao){
	int i;
	for(i= lista->f; i > 0; i--) 
	    lista->info[i] = lista->info[i-1];
	lista->info[0] = lista->info[posicao];
	lista->f++;
	
	
	for(i=posicao; i < lista->f; i++)
    	lista->info[i] = lista->info[i+1];
	lista->f--;
}





