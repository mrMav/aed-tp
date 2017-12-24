#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_typedefs.h"

/*
Retorna float entre 0 e 1
*/
float randomFloat()
{
	float r = (float)rand() / (float)RAND_MAX;
	return r;
}

/*
Cria e retorna um Atributos.
*/
Atributos* novoAtributos() {

	Atributos* a = malloc(sizeof(Atributos));

	a->gr = randomFloat();
	a->df = randomFloat();
	a->md = randomFloat();
	a->av = randomFloat();
	
	return a;

};


/*
Cria e retorna um Jogador.
*/
Jogador* novoJogador(char n[], int num, float vM, time_t* dC, int aC, Atributos *a) {

	Jogador* j = malloc(sizeof(Jogador));

	strcpy(j->nome, n);	
	j->numero = num;
	j->vencimentoMensal = vM;
	j->dataContracto = dC;
	j->anosContracto = aC;
	j->atributos = a;
	
	return j;

};

/*
Imprime atributos do argumento
*/
void imprimeAtributos(Atributos* a) {
	
	printf("+ GuardaRedes: %.2f\n", a->gr);
	printf("+ Defesa: %.2f\n", a->df);
	printf("+ Medio: %.2f\n", a->md);
	printf("+ Avancado: %.2f\n", a->av);

};

/*
Imprime a informação do jogador no argumento
*/
void imprimeJogador(Jogador* j) {

	printf("--------\n");

	printf("Cartao do jogador: %s\n", j->nome);

	printf("Numero: %i\n", j->numero);
	printf("Vencimento: %f\n", j->vencimentoMensal);
	printf("Data do contracto: %s", ctime(j->dataContracto));  // reparar na funcao ctime()
	printf("Anos de contracto: %i\n", j->anosContracto);
	printf("Atributos do jogador:\n");

	imprimeAtributos(j->atributos);

	printf("--------\n");
};
