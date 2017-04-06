#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stddef.h>
#include <wchar.h>
#define QTD 10

typedef struct{   //estrutura para cadastrar produtos
	char nome[20];
	char descricao[40];
	char dataValidade[9];
	float valor;
	int quantidade;
	int codProduto;
}cadastro;

typedef struct{   //estrutura para controlar o numero de produtos cadastrados e suas posicoes.
	cadastro dados[QTD];
	int f;
	int diaAtual;
}base;

int diaAtual();
int quantidadeDiasMes(int mes);
int converterData(char data[]);
int prazoValidade(char data[], base *listaCadastro);

void cria_lista(base *listaCadastro);       // inicializa a lista
void cadastraProduto(base *listaCadastro);//Prototipando as funcoes
int procura_nodo(base *listaCadastro);
void sair(); 
void excluiProduto(base *listaCadastro);
void relatorioProduto(base *listaCadastro);
void ordenaProduto(base *listaCadastro);

int main(void){
	setlocale(LC_ALL,"portuguese");
	base listaCadastro;
	char op;
	fflush(stdin);
	
	cria_lista(&listaCadastro);
	do{
		system("cls");
		printf("\n\t ----> AgroTEC <----  ");
		printf("\n Escolha uma opção abaixo: ");
		printf("\n\t 1- Cadastrar produto        |");
		printf("\n\t 2- Excluir produto          |");
		printf("\n\t 3- Relatorio dos produtos   |");
		printf("\n\t 4- Ordenar os produtos      |");
		printf("\n\t s- Sair                     |");
		printf("\nDigite: ");
		scanf("%c", &op);
		fflush(stdin);
		
		switch(op){
			case '1':
				cadastraProduto(&listaCadastro);
				break;
			case '2':
			    excluiProduto(&listaCadastro);
				break;
			case '3':
			    relatorioProduto(&listaCadastro);				
				break;
			case '4':					
                ordenaProduto(&listaCadastro);
                break;
			case 's':
				sair();
				break;
			default:
                system("cls");
			    printf (" - Digito inválido! \n\n");
                system("pause");
		}
	}while(toupper(op)!='S');
}

void cria_lista(base *listaCadastro){
    listaCadastro->f = 0;
    listaCadastro->diaAtual = diaAtual();
}

void cadastraProduto(base *listaCadastro){
	cadastro auxprod;
	char confirmarData;
	int i;
	if(listaCadastro->f <= QTD){
		system("cls");
		printf("\t ------------------");
		printf("\n\t| Cadastro de Produtos ");
		printf("\n\t|");
		printf("\n\t| Código do produto: ");
		scanf("%i", &auxprod.codProduto);
		fflush(stdin);
		
		printf("\t| Nome: ");
		gets(auxprod.nome);
		fflush(stdin);
	
		printf("\t| Descrição: ");
		gets(auxprod.descricao);
		fflush(stdin);
		
		printf("\n\t| Valor unitário R$: ");
		scanf("%f", &auxprod.valor);
		fflush(stdin);
		
		printf("\n\t| Quantidade: ");
		scanf("%i", &auxprod.valor);
		fflush(stdin);
	
		do{
			printf("\t| Data de validade: ");
			for(i=0; i <= 9; i++){
				if(i == 2 || i == 5){
					auxprod.dataValidade[i] = '/';
					printf("/");
				}else
					auxprod.dataValidade[i] = getche();
				fflush(stdin);
			}
			
			printf("\n\t|");
			printf("\n\t|\t Data dadosrmada: %s", auxprod.dataValidade);
			printf("\n\t|\t Confirma a data dadosrmada? [S/N] ");
			scanf("%c", &confirmarData);
			fflush(stdin);
		}while(toupper(confirmarData) !='S');
		
		printf("\t|");
		printf("\n\t|");
	
		//armazenando os dados cadastrados na variável "dados"
		listaCadastro->dados[listaCadastro->f] = auxprod;
	
		//Aumenta o número de produtos cadastrados.
		listaCadastro->f++;
			
		printf("\t- Produto cadastrado com sucesso!!\n\n");
		ordenaProduto(listaCadastro);
		system("pause");
	}else{
		system("cls");
		printf("\t- A lista está cheia!!!\n\n");
		system("pause");
	}
}
int procura_nodo(base *listaCadastro){
	int posicao = -1;
	int codigo, i;
	printf("\n Digite o código do registro que deseja excluir: ");
    scanf("%i", &codigo);
    
   	for(i=0; i < listaCadastro->f; i++)
   		if(listaCadastro->dados[i].codProduto == codigo)
   			posicao = i;
   	
   	return posicao;
}
void excluiProduto(base *listaCadastro){
	int codigo, i, posicao;
    relatorioProduto(listaCadastro);
    posicao = procura_nodo(listaCadastro);
    
   	if(posicao >= 0){
	   	for(i=posicao; i < listaCadastro->f; i++)
	    	listaCadastro->dados[i] = listaCadastro->dados[i+1];
		listaCadastro->f--;
   		printf("\n Registro excluído com sucesso \n");
	}else{
   		printf("\n Código não encontrado \n");
	}
}

void sair(){
	
	printf("\n\n Sistema finalizado com sucesso! \n\n");
	
}
void relatorioProduto(base *listaCadastro){
	int i;
	int dias;
	for(i = 0; i < listaCadastro->f; i++){
		printf("-------------------------------------------------------------------\n");
		printf("Codigo: %i\n ", listaCadastro->dados[i].codProduto);
		printf("Nome: %s\n ", listaCadastro->dados[i].nome);
		printf("Descrição: %s \n", listaCadastro->dados[i].descricao);
		printf("Quantidade: %i \n", listaCadastro->dados[i].quantidade);
		printf("Valor unitário: %.2f \n", listaCadastro->dados[i].valor);
		printf("Valor total: %s \n", listaCadastro->dados[i].valor*listaCadastro->dados[i].quantidade);
		printf("Data de Validade: %s \n", listaCadastro->dados[i].dataValidade);
		dias = prazoValidade(listaCadastro->dados[i].dataValidade, listaCadastro);
		if(dias == 0)
			printf("O produto vence hoje!");
		else if(dias > 0)
			printf("O produto vence em %i dias!", dias);
		else{
			dias *= -1;			
			printf("O produto venceu há %i dias!", dias);
		}
		printf("\n-------------------------------------------------------------------\n");	
	}
	system("pause");
}
void ordenaProduto(base *listaCadastro){
	system("cls");
	
	int cont1 = 0, cont2 = 0;
	cadastro aux;

	for (cont1 = 0; cont1 < listaCadastro->f; cont1++){
		for (cont2 = cont1+1; cont2 < listaCadastro->f; cont2++){
			if (prazoValidade(listaCadastro->dados[cont1].dataValidade, listaCadastro) > prazoValidade(listaCadastro->dados[cont2].dataValidade, listaCadastro)){ // Caso seja menor entrará aqui e trocará a posição
				aux = listaCadastro->dados[cont1]; // memória
				// troca as posições
				listaCadastro->dados[cont1] = listaCadastro->dados[cont2];
				listaCadastro->dados[cont2] = aux;
			}
		}
	}
}
int quantidadeDiasMes(int mes){
	switch(mes){
		case 1:
			return 31;
			break;
		case 2:
			return 28;
			break;
		case 3:
			return 31;
			break;
		case 4:
			return 30;
			break;
		case 5:
			return 31;
			break;
		case 6:
			return 30;
			break;
		case 7:
			return 31;
			break;
		case 8:
			return 31;
			break;
		case 9:
			return 30;
			break;
		case 10:
			return 31;
			break;
		case 11:
			return 30;
			break;
		case 12:
			return 31;
			break;
	}
}
int converterData(char data[]){
    int soma, j= 0; //Inicializando as variaveis
    char array[3][3]; //Vetor que receberá os valores separados
	

	array[0][0] = data[0];
	array[0][1] = data[1];
	
	array[1][0] = data[3];
	array[1][1] = data[4];
	
	array[2][0] = data[6];
	array[2][1] = data[7];
	array[2][2] = data[8];
	array[2][3] = data[9];
		
		
	//array[0] = dia
	//array[1] = mes
	//array[2] = ano

	soma = atoi(array[0]); //Soma os dias
	
	for(j = 1; j < atoi(array[1]); j++) //Percorre os meses
		soma += quantidadeDiasMes(j); //soma os dias referentes à cada mês
	
	soma += (atoi(array[2])*365); // soma os anos
	

	return soma; //retorna a soma de dias
}

int diaAtual(){
	char dateStr[9];
    _strdate(dateStr); //pegando a data atual no formato MM/DD/YY
    
    int i = 0;
    char *p = strtok (dateStr, "/"); //Iniciando a separação da data por barras
    char *array[3]; //Vetor que receberá os valores separados
	char dataAtual[10] = "";
	char *data;
	
    while (p != NULL){ //Separando a data por barras
        array[i++] = p;
        p = strtok (NULL, "/");
    }
    
	//array[0] = mes
    //array[1] = dia
	//array[2] = ano
    
    //Montando a data no formato DD/MM/YYYY
    strcpy(dataAtual, array[1]);
    strcat(dataAtual, "/");
    strcat(dataAtual, array[0]);
    strcat(dataAtual, "/20");
    strcat(dataAtual, array[2]);
    
    data = malloc(sizeof(dataAtual));
    strcpy(data, dataAtual);
    //Retorna a data em dias
    return converterData(data);
}

int prazoValidade(char data[], base *listaCadastro){
	return converterData(data) - (listaCadastro->diaAtual);
}
