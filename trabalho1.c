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


//Prototipando as funcoes
int diaAtual(); //retorna a data atual, em numero de dias
int quantidadeDiasMes(int mes); //quantidade de dias de cada mes
int converterData(char data[]); //converte uma data DD/MM/YYYY em numero de dias
int prazoValidade(char data[], base *listaCadastro); //retorna o número de dias que falta para o produto vencer (baseado na data informada e no dia atual)
void cria_lista(base *listaCadastro); // inicializa a lista
void cadastraProduto(base *listaCadastro); //cadastra o produto
int procura_nodo(base *listaCadastro); //procura a posição de um registro pelo código
void sair(); //sai do programa
void excluiProduto(base *listaCadastro); //exclui um produto
void relatorioProduto(base *listaCadastro); //exibe o relatorio de produtos
void ordenaProduto(base *listaCadastro); //ordena os produtos por data de vencimento
void venderProduto(base *listaCadastro); //vende um produto

int main(void){
	setlocale(LC_ALL,"portuguese");
	base listaCadastro;
	char op;
	fflush(stdin);
	
	cria_lista(&listaCadastro);
	do{
		//menu
		system("cls");
		printf("\n\t ----> AgroTEC <----  ");
		printf("\n Escolha uma opção abaixo: ");
		printf("\n\t 1- Cadastrar produto        |");
		printf("\n\t 2- Excluir produto          |");
		printf("\n\t 3- Relatorio dos produtos   |");
		printf("\n\t 4- Vender produtos          |");
		printf("\n\t s- Sair                     |");
		printf("\nDigite: ");
		scanf("%c", &op);
		fflush(stdin);
		
		//opçoes do menu
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
			    venderProduto(&listaCadastro);				
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

//inicializa a lista
void cria_lista(base *listaCadastro){
    listaCadastro->f = 0; //define o primeiro elemento como 0
    listaCadastro->diaAtual = diaAtual(); //define a data atual em quantidade de dias
}

//cadastra um rpoduto
void cadastraProduto(base *listaCadastro){
	cadastro auxprod;
	char confirmarData;
	int i;
	//verifica se tem espaços disponívei na lista
	if(listaCadastro->f <= QTD){
		system("cls");
		//colhe informações
		printf("\n\t Cadastro de Produtos ");
		printf("\n\t");
		printf("\n\t Código do produto: ");
		scanf("%i", &auxprod.codProduto);
		fflush(stdin);
		
		printf("\t Nome: ");
		gets(auxprod.nome);
		fflush(stdin);
	
		printf("\t Descrição: ");
		gets(auxprod.descricao);
		fflush(stdin);
		
		printf("\t Valor unitário R$: ");
		scanf("%f", &auxprod.valor);
		fflush(stdin);
		
		printf("\t Quantidade: ");
		scanf("%i", &auxprod.quantidade);
		fflush(stdin);
		//[end]colhe informações
		do{//formata a data
			printf("\t Data de validade: ");
			for(i=0; i <= 9; i++){
				if(i == 2 || i == 5){
					auxprod.dataValidade[i] = '/';
					printf("/");
				}else
					auxprod.dataValidade[i] = getche();
				fflush(stdin);
			}
			
			printf("\n\n\t Data digitada: %s", auxprod.dataValidade);
			printf("\n\t Confirma a data digitada? [S/N] ");
			scanf("%c", &confirmarData);
			fflush(stdin);
		}while(toupper(confirmarData) !='S');
		
		
	
		//armazenando os dados cadastrados na variável "dados"
		listaCadastro->dados[listaCadastro->f] = auxprod;
	
		//Aumenta o número de produtos cadastrados.
		listaCadastro->f++;
			
		printf("\t- Produto cadastrado com sucesso!!\n\n");
		system("pause");
		ordenaProduto(listaCadastro);//ordena a lista por data
	}else{
		system("cls");
		printf("\t- A lista está cheia!!!\n\n");
		system("pause");
	}
}

//procura um registro por codigo
int procura_nodo(base *listaCadastro){
	int posicao = -1;
	int codigo, i;
	printf("\n Digite o código do registro: ");
    scanf("%i", &codigo);
    fflush(stdin);
   	for(i=0; i < listaCadastro->f; i++)
   		if(listaCadastro->dados[i].codProduto == codigo)
   			posicao = i;
   	
   	return posicao;
}

//exclui um produto
void excluiProduto(base *listaCadastro){
	int codigo, i, posicao;
	printf("\n Excluir registro \n");
	printf("--------------------- \n");
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
	system("pause");
}

//encerra o programa
void sair(){
	printf("\n\n Sistema finalizado com sucesso! \n\n");
	system("pause");
}
//exibe o relatorio
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
		printf("Valor total: %.2f \n", (listaCadastro->dados[i].valor)*(listaCadastro->dados[i].quantidade));
		printf("Data de Validade: %s \n", listaCadastro->dados[i].dataValidade);
		//verifica quantos dias faltam para vencer o produto
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

//ordena os produtos com a data de vencimento
void ordenaProduto(base *listaCadastro){
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

//realiza a venda de produtos
void venderProduto(base *listaCadastro){
	int codigo, i, posicao, qtd;
	printf("\n vender produto \n");
	printf("--------------------- \n");
    relatorioProduto(listaCadastro);
    posicao = procura_nodo(listaCadastro);
    
    //se foi encontrado pelo codigo
   	if(posicao >= 0){
   		//se esta dentro do prazo de validade
   		if(prazoValidade(listaCadastro->dados[posicao].dataValidade, listaCadastro) >= 0){
		    do{
		    	//se a quantidade requirida está disponivel
			    printf("\n Digite a quantidade que deseja vender: ");
			    scanf("%i", &qtd);
			    fflush(stdin);
				if(qtd > listaCadastro->dados[posicao].quantidade){
					printf("\nQuantidade Inválida!");
				}
			}while(qtd > listaCadastro->dados[posicao].quantidade);
			//diminui a quantidade do registro
		    listaCadastro->dados[posicao].quantidade = listaCadastro->dados[posicao].quantidade-qtd;
	   		printf("\n Itens vendidos com sucesso \n");
	   }else
	   		printf("\n Produto fora do prazo de validade \n");
	   	system("pause");
	}else{
   		printf("\n Código não encontrado \n");
   		system("pause");
	}
}

// quantidade de dias de acordo com o mês
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
	
	//define que os dois primeiros digitos da data são o dia
	array[0][0] = data[0];
	array[0][1] = data[1];
	
	//define que o quarto e o quinto digitos da data são o mês
	array[1][0] = data[3];
	array[1][1] = data[4];
	
	//define que os quatro ultimos dias da data são o ano
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

//retorna a data atual, em quantidade de dias
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

//retorna a quantidade de dias restantes para o vencimento do produto
int prazoValidade(char data[], base *listaCadastro){
	return converterData(data) - (listaCadastro->diaAtual);
}
