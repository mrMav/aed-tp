#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_typedefs.h"
#include "game_constants.h"
#include "game_information_output.h"

/*
Retorna float entre 0 e 1
*/
float randomFloat()
{
	float r = (float)rand() / (float)RAND_MAX;
	return r;
}

/*
Retorna int entre min e max
*/
int randomInt(int min, int max)
{
	int r = (rand() % max) + min;
	return r;
}

/*
Retorna estrutura com a data da string
o formato da string tem de ser yyyy/mm/dd
*/
struct tm* novaData(char string[]) {

	struct tm* data = malloc(sizeof(struct tm));

	char ano[4];
	char mes[2];
	char dia[2];

	ano[0] = string[0];
	ano[1] = string[1];
	ano[2] = string[2];
	ano[3] = string[3];

	mes[0] = string[5];
	mes[1] = string[6];

	dia[0] = string[8];
	dia[1] = string[9];

	data->tm_year = atoi(ano) - 1900;  // reparem no - 1900;
	data->tm_mon = atoi(mes) - 1;      // reparem no - 1
	data->tm_mday = atoi(dia);

	// inicializar resto dos componentes do struct
	data->tm_hour = 0;
	data->tm_min = 0;
	data->tm_sec = 0;
	data->tm_isdst = -1;

	return data;

}

/*
Função VerificaTatica Retorna 1 se for válida 0 se inválida
*/
int VerificaTatica(char Tatica[]) {
	int Verifica_Tatica = 0;
	char ndefesas[2]="\0";
	char nmedios[2] = "\0";
	char navancados[2] = "\0";
	ndefesas[0] = Tatica[0];
	nmedios[0] = Tatica[2];
	navancados[0] = Tatica[4];
	if (strlen(Tatica) != 5) {
		printf("Tática inválida\n");
	}
	else {
		if (atoi(ndefesas) + atoi(nmedios) + atoi(navancados) != 10) {
			printf("Tática inválida\n");
		}
		else {
			Verifica_Tatica = 1;
			printf("Tatica validada.\n");
		}
	}
	return Verifica_Tatica;
}

void iniciarPrimirParaContinuar() {

	int exit = -1;

	imprimirInstrucao("01: Continuar...\n");
		
	while (exit != 1) {

		imprimirCursor();

		scanf("%i", &exit);
		
	}

}