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
#define QTD 2

typedef struct{   //estrutura para cadastrar produtos
	char nome[20];
	char descricao[40];
	char dataValidade[9];
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
		printf("\n\t| Codigo do produto: ");
		scanf("%i", &auxprod.codProduto);
		fflush(stdin);
		
		printf("\t| Nome: ");
		gets(auxprod.nome);
		fflush(stdin);
	
		printf("\t| Descrição: ");
		gets(auxprod.descricao);
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
			printf("\n\t|\t Data informada: %s", auxprod.dataValidade);
			printf("\n\t|\t Confirma a data informada? [S/N] ");
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
		system("pause");
	}else{
		system("cls");
		printf("\t- A lista está cheia!!!\n\n");
		system("pause");
	}
}
void excluiProduto(base *listaCadastro){
	int x;
	int pos, achou,cont, i, cod, pf = 0;
	system("cls");
	printf("\n\t| Exclui produto\n\n");
	
	for(i=0; i<listaCadastro->f;i++){
		printf("\n\tnome: %s codigo: %i\n",listaCadastro->dados[i].nome,listaCadastro->dados[i].codProduto);		
	
	}
	
	printf("\n\t Informe o codigo que deseja excluir:");
	fflush(stdin);
	scanf("%i",&cod);
	fflush(stdin);
	
	// Encontra a posição do produto no vetor que tenha o código igual ao informado pelo usuário
	for (cont = 0; cont < listaCadastro->f; cont++)
	{
		if (cod == listaCadastro->dados[cont].codProduto)
		{
			pos = cont;
			achou++;
		}
	}
	
	// Deleta o produto passando os da frente pra tras
	if ( achou != 0) // começa a deletar
	{
		for (cont = pos; cont < listaCadastro->f; cont++ )
		{ // DELETANDO
			listaCadastro->dados[cont] = listaCadastro->dados[cont+1];
			listaCadastro->f--;
		}
		printf("\n\t Produto excluido com sucesso!\n\n");
		system("pause");
	}
		else // caso nao tenha achado
		{
			printf (" Não foram encontrados produtos com este código! \n\n");
			system("pause");
		}
	
	
}
void sair(){
	
	printf("\n\n Sistema finalizado com sucesso! \n\n");
	
}
void relatorioProduto(base *listaCadastro){
	int i;
	int dias;
	for(i = 0; i < listaCadastro->f; i++){
		printf("Codigo: %i\n ", listaCadastro->dados[i].codProduto);
		printf("Nome: %s\n ", listaCadastro->dados[i].nome);
		printf("Descrição: %s \n", listaCadastro->dados[i].descricao);
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
		
	}
	system("pause");
}
void ordenaProduto(base *listaCadastro){
	
	char escolha;
	system("cls");
	printf("\n\nVoce deseja ordenar de que forma? \n");
	printf (" 1 - Código \n");
	printf (" 2 - Validade \n");
	printf (" 3 - Nome \n");
	
	fflush(stdin);
	scanf ("%c", &escolha);
	fflush(stdin);
	
	int cont1 = 0, cont2 = 0;
	cadastro aux;
	
	switch (tolower(escolha)){
		case '1': // Ordenar por código
			// Ordenação BOLHA
			for (cont1 = 0; cont1 < listaCadastro->f; cont1++){
				for (cont2 = cont1+1; cont2 < listaCadastro->f; cont2++){
					if (listaCadastro->dados[cont1].codProduto > listaCadastro->dados[cont2].codProduto){ // Caso seja menor entrará aqui e trocará a posição
						aux = listaCadastro->dados[cont1]; // memória
						// troca as posições
						listaCadastro->dados[cont1] = listaCadastro->dados[cont2];
						listaCadastro->dados[cont2] = aux;
					}
				}
			}
			printf("\n Alterado com sucesso!!!\n\n");
			system("pause");
			break;
		case '2': // Ordenar por validade
				for (cont1 = 0; cont1 < listaCadastro->f; cont1++){
					for (cont2 = cont1+1; cont2 < listaCadastro->f; cont2++){
						if (listaCadastro->dados[cont1].dataValidade > listaCadastro->dados[cont2].dataValidade){ // Caso seja menor entrará aqui e trocará a posição
							aux = listaCadastro->dados[cont1]; // memória
							// troca as posições
							listaCadastro->dados[cont1] = listaCadastro->dados[cont2];
							listaCadastro->dados[cont2] = aux;
						}
				}
			}
			printf("\n Alterado com sucesso!!!\n\n");
			system("pause");
			break;
		case '3':
			for (cont1 = 0; cont1 < listaCadastro->f; cont1++){
					for (cont2 = cont1+1; cont2 < listaCadastro->f; cont2++){
						if (strcmpi(listaCadastro->dados[cont1].nome,listaCadastro->dados[cont2].nome) > 0 ){ // Caso seja menor entrará aqui e trocará a posição
							aux = listaCadastro->dados[cont1]; // memória
							// troca as posições
							listaCadastro->dados[cont1] = listaCadastro->dados[cont2];
							listaCadastro->dados[cont2] = aux;
						}
				}
			}
			printf("\n Alterado com sucesso!!!\n\n");
			system("pause");
			break;
			default:
				printf("\n Opção invalida!!!\n\n");
				system("pause");
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
