#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

int prazoValidade(char data[]){
	return converterData(data)-diaAtual();
}

void main (){
	char data[10] = "06/04/2017";
    printf("%i\n\n", converterData(data));
}
