#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>


typedef struct{   //estrutura para cadastrar produtos
	char nome[20];
	char descricao[40];
	int dataValidade;
	int codProduto;
}cadastro;

typedef struct{   //estrutura para controlar o numero de produtos cadastrados e suas posicoes.
	cadastro dados[1000];
	int qtde;
}base;

int pegarAno();
void cadastraProduto(base *listaCadastro, int *ano);//Prototipando as funcoes
void sair(); 
void excluiProduto(base *listaCadastro);
void relatorioProduto(base *listaCadastro, int *ano);
void ordenaProduto(base *listaCadastro);

int main(void){
	setlocale(LC_ALL,"portuguese");
	base listaCadastro;
	listaCadastro.qtde=0;
	int codCadastro=0;
	char op;
	int ano = pegarAno();
	fflush(stdin);
	do{
		system("cls");
		printf("\n Ano atual: %i", ano);
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
				 cadastraProduto(&listaCadastro, &ano);
				break;
			case '2':
				if (listaCadastro.qtde==0){
						system("cls");
						printf (" - Não há produtos cadastrados! \n\n");
						system("pause");
					}else{		
						excluiProduto(&listaCadastro);
						}
					
					break;
				break;
			case '3':
				if (listaCadastro.qtde==0){
						system("cls");
						printf (" - Não há produtos cadastrados! \n\n");
						system("pause");
					}else{
							
						relatorioProduto(&listaCadastro, &ano);
						}				
				break;
			case '4':
				if (listaCadastro.qtde==0){
						system("cls");
						printf (" - Não há produtos cadastrados! \n\n");
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
					printf (" - Digito inválido! \n\n");
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

	printf("\t| Descrição: ");
	gets(auxprod.descricao);
	fflush(stdin);

	printf("\t| Data de validade: ");
	scanf("%i",&auxprod.dataValidade);
	fflush(stdin);
	printf("\t ------------------");
	/*printf("\nCodigo do produto: ");
	scanf("%i",&auxprod.codProduto);
	fflush(stdin);*/
	
	if(auxprod.dataValidade<*ano){
		
		printf("\n\n - Produto nao pode ser cadastrado pois está fora da validade!!!\n\n");
		system("pause");
	}else{
	
	//Criando o codigo, ele nao pode ser 0, portando somamos sempre +1, assim ele nao será 0 e nem se repetirá.
	auxprod.codProduto = listaCadastro->qtde+1;

	//armazenando os dados cadastrados na variável "dados", do tipo "cliente".
	listaCadastro->dados[listaCadastro->qtde]=auxprod;

	//Aumenta o número de clientes cadastrados.
	listaCadastro->qtde++;
		printf("\n\n - Produto cadastrado com sucesso!!\n\n");
		system("pause");
	}
			/*if(listaCadastro->dados.dataValidade<ano){
				for (cont = pos; cont < listaCadastro->qtde; cont++ )
				{ // DELETANDO
					listaCadastro->dados[cont] = listaCadastro->dados[cont+1];
					listaCadastro->qtde--;
				}
				printf("\n\t Produto fora da validade excluido com sucesso!\n");
			}
			
			printf("\n\n\tCadastro Realizado com sucesso!!!\n\n");
		*/
	
}
void excluiProduto(base *listaCadastro){
	int cod,pf=0,x;
	int pos = 0;
	int achou = 0;
	int cont = 0;
	system("cls");
	printf("\n\t| Exclui produto\n\n");
	
	for(int i=0; i<listaCadastro->qtde;i++){
		printf("\n\tnome: %s codigo: %i\n",listaCadastro->dados[i].nome,listaCadastro->dados[i].codProduto);		
	
	}
	
	printf("\n\t Informe o codigo que deseja excluir:");
	fflush(stdin);
	scanf("%i",&cod);
	fflush(stdin);
	
	// Encontra a posição do produto no vetor que tenha o código igual ao informado pelo usuário
	for (cont = 0; cont < listaCadastro->qtde; cont++)
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
		for (cont = pos; cont < listaCadastro->qtde; cont++ )
		{ // DELETANDO
			listaCadastro->dados[cont] = listaCadastro->dados[cont+1];
			listaCadastro->qtde--;
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
void relatorioProduto(base *listaCadastro, int *ano){
	for(int i=0; i<listaCadastro->qtde;i++){
		if(listaCadastro->dados[i].dataValidade== *ano){
		printf("| nome: %s | codigo: %i | descrição:%s | data de Validade: %i |Alerta:Produto vence esse ano!",listaCadastro->dados[i].nome,listaCadastro->dados[i].codProduto,listaCadastro->dados[i].descricao,listaCadastro->dados[i].dataValidade);		
		printf("\n|----------------------------------------------------------------\n");
	
	}else if(listaCadastro->dados[i].dataValidade==*ano+1){
		printf("| nome: %s | codigo: %i | descrição:%s | data de Validade: %i |Alerta:Produto vence ano que vem!",listaCadastro->dados[i].nome,listaCadastro->dados[i].codProduto,listaCadastro->dados[i].descricao,listaCadastro->dados[i].dataValidade);		
		printf("\n|----------------------------------------------------------------\n");
	
	
	}else{
		printf("| nome: %s | codigo: %i | descrição:%s | data de Validade: %i |",listaCadastro->dados[i].nome,listaCadastro->dados[i].codProduto,listaCadastro->dados[i].descricao,listaCadastro->dados[i].dataValidade);		
		printf("\n|----------------------------------------------------------------\n");
		
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
			for (cont1 = 0; cont1 < listaCadastro->qtde; cont1++){
				for (cont2 = cont1+1; cont2 < listaCadastro->qtde; cont2++){
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
				for (cont1 = 0; cont1 < listaCadastro->qtde; cont1++){
					for (cont2 = cont1+1; cont2 < listaCadastro->qtde; cont2++){
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
			for (cont1 = 0; cont1 < listaCadastro->qtde; cont1++){
					for (cont2 = cont1+1; cont2 < listaCadastro->qtde; cont2++){
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
int pegarAno(){
	time_t current_time;
	struct tm *time_info;
	char year[5];
	int ano;
	current_time = time(NULL);
	time_info = localtime(&current_time);
	strftime(year, 5, "%Y", time_info);
	ano = atoi(year);
	return ano;
}
