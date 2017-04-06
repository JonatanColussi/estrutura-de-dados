#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

#DEFINE QTD 10

typedef struct{   //estrutura para cadastrar produtos
	char nome[20];
	char descricao[40];
	char dataValidade[10];
	int codProduto;
}cadastro;

typedef struct{   //estrutura para controlar o numero de produtos cadastrados e suas posicoes.
	cadastro dados[QTD];
	int f;
}base;

void cadastraProduto(base *listaCadastro, int *ano);//Prototipando as funcoes
void sair(); 
void excluiProduto(base *listaCadastro);
void relatorioProduto(base *listaCadastro, int *ano);
void ordenaProduto(base *listaCadastro);
int prazoValidade(char data[]);

int main(void){
	setlocale(LC_ALL,"portuguese");
	base listaCadastro;
	listaCadastro.f=0;
	int codCadastro=0;
	char op;
	int ano = pegarAno();
	fflush(stdin);
	do{
		system("cls");
		printf("\n Ano atual: %i", ano);
		printf("\n\t ----> AgroTEC <----  ");
		printf("\n Escolha uma op��o abaixo: ");
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
				 cadastraProduto(&listaCadastro, &ano);
				break;
			case '2':
				if (listaCadastro.f==0){
						system("cls");
						printf (" - N�o h� produtos cadastrados! \n\n");
						system("pause");
					}else{		
						excluiProduto(&listaCadastro);
						}
					
					break;
				break;
			case '3':
				if (listaCadastro.f==0){
						system("cls");
						printf (" - N�o h� produtos cadastrados! \n\n");
						system("pause");
					}else{
							
						relatorioProduto(&listaCadastro, &ano);
						}				
				break;
			case '4':
				if (listaCadastro.f==0){
						system("cls");
						printf (" - N�o h� produtos cadastrados! \n\n");
						system("pause");
					}else{						
						ordenaProduto(&listaCadastro);
						}
				
				
				break;
			case 's':
				 sair();
				break;
				default:
					system("cls");
					printf (" - Digito inv�lido! \n\n");
					system("pause");
		}
		
		
		
	}while(toupper(op)!='S');
	
	
}
void cadastraProduto(base *listaCadastro,int *ano){

	cadastro auxprod;

	printf("\t ------------------");
	printf("\n\t| Cadastra Produto ");
	printf("\n\t|                  ");
	printf("\n\t| Nome: ");
	gets(auxprod.nome);
	fflush(stdin);

	printf("\t| Descri��o: ");
	gets(auxprod.descricao);
	fflush(stdin);

	printf("\t| Data de validade: ");
	gets(auxprod.dataValidade);
	fflush(stdin);
	
	printf("\t ------------------");
	printf("\nCodigo do produto: ");
	scanf("%i", &auxprod.codProduto);
	fflush(stdin);

	if(prazoValidade(auxprod.dataValidade) < 0){
		printf("\n\n - Produto n�o pode ser cadastrado pois est� fora da validade!!!\n\n");
		system("pause");
	}else{
		//armazenando os dados cadastrados na vari�vel "dados", do tipo "cliente".
		listaCadastro->dados[listaCadastro->f]=auxprod;

		//Aumenta o n�mero de produtos cadastrados.
		listaCadastro->f++;
		printf("\n\n - Produto cadastrado com sucesso!!\n\n");
		system("pause");
	}
}
void excluiProduto(base *listaCadastro){
	int cod,pf=0,x;
	int pos = 0;
	int achou = 0;
	int cont = 0;
	system("cls");
	printf("\n\t| Exclui produto\n\n");
	
	for(int i=0; i<listaCadastro->f;i++){
		printf("\n\tnome: %s codigo: %i\n",listaCadastro->dados[i].nome,listaCadastro->dados[i].codProduto);		
	
	}
	
	printf("\n\t Informe o codigo que deseja excluir:");
	fflush(stdin);
	scanf("%i",&cod);
	fflush(stdin);
	
	// Encontra a posi��o do produto no vetor que tenha o c�digo igual ao informado pelo usu�rio
	for (cont = 0; cont < listaCadastro->f; cont++)
	{
		if (cod == listaCadastro->dados[cont].codProduto)
		{
			pos = cont;
			achou++;
		}
	}
	
	// Deleta o produto passando os da frente pra tras
	if ( achou != 0) // come�a a deletar
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
			printf (" N�o foram encontrados produtos com este c�digo! \n\n");
			system("pause");
		}
	
	
}
void sair(){
	
	printf("\n\n Sistema finalizado com sucesso! \n\n");
	
}
void relatorioProduto(base *listaCadastro, int *ano){
	for(int i=0; i<listaCadastro->f;i++){
		if(listaCadastro->dados[i].dataValidade== *ano){
		printf("| nome: %s | codigo: %i | descri��o:%s | data de Validade: %i |Alerta:Produto vence esse ano!",listaCadastro->dados[i].nome,listaCadastro->dados[i].codProduto,listaCadastro->dados[i].descricao,listaCadastro->dados[i].dataValidade);		
		printf("\n|----------------------------------------------------------------\n");
	
	}else if(listaCadastro->dados[i].dataValidade==*ano+1){
		printf("| nome: %s | codigo: %i | descri��o:%s | data de Validade: %i |Alerta:Produto vence ano que vem!",listaCadastro->dados[i].nome,listaCadastro->dados[i].codProduto,listaCadastro->dados[i].descricao,listaCadastro->dados[i].dataValidade);		
		printf("\n|----------------------------------------------------------------\n");
	
	
	}else{
		printf("| nome: %s | codigo: %i | descri��o:%s | data de Validade: %i |",listaCadastro->dados[i].nome,listaCadastro->dados[i].codProduto,listaCadastro->dados[i].descricao,listaCadastro->dados[i].dataValidade);		
		printf("\n|----------------------------------------------------------------\n");
		
	}
	}
	system("pause");
}
void ordenaProduto(base *listaCadastro){
	
	char escolha;
	system("cls");
	printf("\n\nVoce deseja ordenar de que forma? \n");
	printf (" 1 - C�digo \n");
	printf (" 2 - Validade \n");
	printf (" 3 - Nome \n");
	
	fflush(stdin);
	scanf ("%c", &escolha);
	fflush(stdin);
	
	int cont1 = 0, cont2 = 0;
	cadastro aux;
	
	switch (tolower(escolha)){
		case '1': // Ordenar por c�digo
			// Ordena��o BOLHA
			for (cont1 = 0; cont1 < listaCadastro->f; cont1++){
				for (cont2 = cont1+1; cont2 < listaCadastro->f; cont2++){
					if (listaCadastro->dados[cont1].codProduto > listaCadastro->dados[cont2].codProduto){ // Caso seja menor entrar� aqui e trocar� a posi��o
						aux = listaCadastro->dados[cont1]; // mem�ria
						// troca as posi��es
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
						if (listaCadastro->dados[cont1].dataValidade > listaCadastro->dados[cont2].dataValidade){ // Caso seja menor entrar� aqui e trocar� a posi��o
							aux = listaCadastro->dados[cont1]; // mem�ria
							// troca as posi��es
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
						if (strcmpi(listaCadastro->dados[cont1].nome,listaCadastro->dados[cont2].nome) > 0 ){ // Caso seja menor entrar� aqui e trocar� a posi��o
							aux = listaCadastro->dados[cont1]; // mem�ria
							// troca as posi��es
							listaCadastro->dados[cont1] = listaCadastro->dados[cont2];
							listaCadastro->dados[cont2] = aux;
						}
				}
			}
			printf("\n Alterado com sucesso!!!\n\n");
			system("pause");
			break;
			default:
				printf("\n Op��o invalida!!!\n\n");
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
    int i, soma, j = 0; //Inicializando as variaveis
    char *p = strtok (data, "/"); //Iniciando a separa��o da data por barras
    char *array[3]; //Vetor que receber� os valores separados

    while (p != NULL){ //Separando a data por barras
        array[i++] = p;
        p = strtok (NULL, "/");
    }
	
	//array[0] = dia
	//array[1] = mes
	//array[2] = ano

	soma = atoi(array[0]); //Soma os dias
	
	for(j = 1; j < atoi(array[1]); j++) //Percorre os meses
		soma += quantidadeDiasMes(j); //soma os dias referentes � cada m�s
	
	soma += (atoi(array[2])*365); // soma os anos
	
	return soma; //retorna a soma de dias
}

int diaAtual(){
	char dateStr[9];
    _strdate(dateStr); //pegando a data atual no formato MM/DD/YY
    
    int i = 0;
    char *p = strtok (dateStr, "/"); //Iniciando a separa��o da data por barras
    char *array[3]; //Vetor que receber� os valores separados
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

int prazoValidade(char data[]){
	return converterData(data)-diaAtual();
}
