#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define QTD 20

typedef struct{
	char modelo[50];
	float preco;
	char vendido;
	int ano;
}carro;

typedef struct{
	int cont;
	carro dados[QTD]; 
}ficha;

void cadastrarCarro(ficha *controle);

main(){
	setlocale(LC_ALL,"Portuguese");
	int opt;
	ficha controle;
	do{	
		system("cls");
		printf("\n\n Bem vindo ao CarroTec\n\n");
		printf("\t 1  - Cadastrar Carro");
		printf("\n\t 2  - Listar Carro");
		printf("\n\t 3  - Vender Carro");	
		printf("\n\t 0 - Sair\n\n");
		printf("\n\n Digite: \n\n\t");
		scanf("%i",&opt);
		
		system("cls");
		switch(opt){
			case 1:
				printf("Cadastrando carros\n");
				system("pause");
				cadastrarCarro(&controle);
				break;
			case 2:
				printf("Listando carros\n");
				system("pause");
				break;
			case 3: 
				printf("Vender carros\n");
				system("pause");
				break;
			case 0:
				printf("Saindo..\n");
				break;
			default:
				system("cls");
				printf("Digito inválido\n");
				system("pause");
		}
	
	}while(opt != 0);
}
void cadastrarCarro(ficha *controle){
	carro auxiliar;
		
	if(controle->cont < QTD){
		printf("\t\n Modelo: ");
		fflush(stdin);
		gets(auxiliar.modelo);
		printf("\t\n Ano:");
		scanf("%i",&auxiliar.ano);
		printf("\t\n Valor:");
		scanf("%f",&auxiliar.preco);
		auxiliar.vendido = 'n';
		
		controle->dados[controle->cont] = auxiliar;
		controle->cont++;	
	}else{
		printf("\t\n Sistema cheio");
	}
}


