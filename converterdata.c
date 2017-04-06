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
    int i, dias, meses, anos = 0;
    char *p = strtok (data, "/");
    char *array[3];

    while (p != NULL){
        array[i++] = p;
        p = strtok (NULL, "/");
    }
	
	dias = atoi(array[0]);
	meses = atoi(array[1])*quantidadeDiasMes(atoi(array[1]));
	anos = atoi(array[2])*365;
	
    return dias+meses+anos;
}

int diaAtutal(){
	char dateStr[9];
    _strdate(dateStr);
    int i = 0;
    char *p = strtok (dateStr, "/");
    char *array[3];
	char data[10] = "";
	
    while (p != NULL){
        array[i++] = p;
        p = strtok (NULL, "/");
    }
    
    
    strcat(data, array[1]);
    strcat(data, "/");
    strcat(data, array[0]);
    strcat(data, "/20");
    strcat(data, array[2]);
    
    return converterData(data);
}

void main (){
	char data[10] = "05/04/2017";
    printf("%i", converterData(data));
    printf("%\n");
    printf("%i", diaAtutal());
}
