#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_typedefs.h"
#include "game_constants.h"

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

	data->tm_year = atoi(ano);
	data->tm_mon = atoi(mes) - 1;  // reparem no -1
	data->tm_mday = atoi(dia);

	return data;

};