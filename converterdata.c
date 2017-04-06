#include <stdio.h>
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
    int i, soma, j = 0; //Inicializando as variaveis
    char *p = strtok (data, "/"); //Iniciando a separação da data por barras
    char *array[3]; //Vetor que receberá os valores separados

    while (p != NULL){ //Separando a data por barras
        array[i++] = p;
        p = strtok (NULL, "/");
    }
	
	//array[0] = dia
	//array[1] = mes
	//array[2] = ano
	
	soma += atoi(array[0]); //Soma os dias
	
	for(j = 1; j < atoi(array[1]); j++) //Percorre os meses
		soma += quantidadeDiasMes(i); //soma os dias referentes à cada mês
	
	soma += (atoi(array[2])*365); // soma os anos
	
	return soma; //retorna a soma de dias
}

int diaAtual(){
	char dateStr[9];
    _strdate(dateStr); //pegando a data atual no formato MM/DD/YY
    
    int i = 0;
    char *p = strtok (dateStr, "/"); //Iniciando a separação da data por barras
    char *array[3]; //Vetor que receberá os valores separados
	char data[10] = "";
	
    while (p != NULL){ //Separando a data por barras
        array[i++] = p;
        p = strtok (NULL, "/");
    }
    
	//array[0] = mes
    //array[] = dia
	//array[2] = ano
    
    //Montando a data no formato DD/MM/YYYY
    strcat(data, array[1]);
    strcat(data, "/");
    strcat(data, array[0]);
    strcat(data, "/20");
    strcat(data, array[2]);
    printf("\n\n%i\n\n", converterData(data));
    //Retorna a data em dias
//    return converterData(data);
	return 0;
}

void main (){
	char data[10] = "05/04/2017";
    printf("%i", converterData(data));
    printf("%\n");
    printf("%i", diaAtual());
}
