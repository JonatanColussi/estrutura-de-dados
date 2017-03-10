#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define QTD 20

typedef struct{
	char modelo[50];
	float valor;
	char vendido;
	int ano;
}carro;

typedef struct{
	int cont;
	carro dados[QTD]; 
}ficha;

void cadastrarCarro(ficha *controle);
void listarCarros(ficha *controle);
void venderCarro(ficha *controle);

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
				listarCarros(&controle);
				system("pause");
				break;
			case 3: 
				printf("Vender carros\n");
				venderCarro(&controle);
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
		scanf("%f",&auxiliar.valor);
		auxiliar.vendido = 'N';
		
		controle->dados[controle->cont] = auxiliar;
		controle->cont++;	
	}else{
		printf("\t\n Sistema cheio");
	}
}

void listarCarros(ficha *controle){
	char vendido[3];
	printf("Código \t|\t Modelo \t|\t Ano \t|\t Valor \t|\t Vendido\n");
	for(int i=0; i< controle->cont; i++){
		printf("%i", i);
		printf("\t|\t");
		printf("%s", controle->dados[i].modelo);
		printf("\t|\t");
		printf("%i", controle->dados[i].ano);
		printf("\t|\t");
		printf("%.2f", controle->dados[i].valor);
		printf("\t|\t");	
		strcpy(vendido, (controle->dados[i].vendido == 'S') ? "Sim" : "Não");
		printf("%s", vendido);
		printf("\n");
	}
}

void venderCarro(ficha *controle){
	int opt;
	carro auxiliar;
	listarCarros(controle);
	printf("\n\n\tDigite o código do carro que deseja vender: ");
	scanf("%i",&opt);
	if(opt < controle->cont){
		controle->dados[opt].vendido = 'S';
	}else{
		venderCarro(controle);
	}
}

