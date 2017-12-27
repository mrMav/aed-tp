#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_typedefs.h"
#include "game_constants.h"
#include "game_functions_prototypes.h"


/*

Funcoes para criar os objectos :

*/

/*
Cria e retorna um Atributos.
*/
Atributos* novoAtributos(float gr, float df, float md, float av) {

	Atributos* a = malloc(sizeof(Atributos));

	a->gr = gr;
	a->df = df;
	a->md = md;
	a->av = av;
	
	return a;

};

/*
Cria e retorna um Atributos Vazio.
*/
Atributos* novoAtributosVazio() {

	Atributos* a = malloc(sizeof(Atributos));

	a->gr = 0.0;
	a->df = 0.0;
	a->md = 0.0;
	a->av = 0.0;

	return a;

};

/*
Cria e retorna um Jogador.
*/
Jogador* novoJogador(char n[], int num, float vM, struct tm* dC, struct tm* dF, int aC, char p[], Atributos *a) {

	Jogador* j = malloc(sizeof(Jogador));

	strcpy(j->nome, n);	
	j->numero = num;
	j->vencimentoMensal = vM;
	j->dataContracto = dC;
	j->dataFimContracto = dF;
	j->anosContracto = aC;
	strcpy(j->posicao, p);
	j->atributos = a;
	
	return j;

};
/*
Cria e retorna um Jogador vazio.
*/
Jogador* novoJogadorVazio() {

	Jogador* j = malloc(sizeof(Jogador));

	j->nome[0] = '\0';
	j->numero = -1;
	j->vencimentoMensal = -1.0;
	j->dataContracto = NULL;
	j->dataFimContracto = NULL;
	j->anosContracto = -1;
	strcpy(j->posicao, "AAA");
	j->atributos = novoAtributosVazio();

	return j;

};

/*
Cria e retorna um Treinador.
*/
Treinador* novoTreinador(char n[]) {

	Treinador* t = malloc(sizeof(Treinador));

	strcpy(t->nome, n);

	return t;

};

/*
Cria e retorna um Plantel.
*/
Plantel* novoPlantel(Treinador *t, Jogador *j[]) {

	Plantel* p = malloc(sizeof(Plantel));

	p->treinador = t;
	
	int i;
	for (i = 0; i < NUMERO_JOGADORES_PLANTEL; i++) {

		p->jogadores[i] = j[i];

	};

	return p;

};

/*
Cria e retorna um Estadio
*/
Estadio* novoEstadio(char n[], int l, float dM) {

	Estadio *e = malloc(sizeof(Estadio));

	strcpy(e->nome, n);
	e->lugares = l;
	e->despesaMensal = dM;

	return e;

};

/*
Cria e retorna uma Equipa
*/
Equipa* novaEquipa(char n[], Estadio *e, int s, Plantel *p, Resultado *r, float f) {

	Equipa *equipa = malloc(sizeof(Equipa));

	strcpy(equipa->nome, n);
	equipa->estadio = e;
	equipa->socios = s;
	equipa->plantel = p;
	equipa->resultados = r;
	equipa->fundos = f;

	return equipa;

};

/*
Cria e retorna um Resultado.
*/
Resultado* novoResultado() {

	Resultado *r = malloc(sizeof(Resultado));

	r->jogosRealizados = 0;
	r->vitorias = 0;
	r->empates = 0;
	r->derrotas = 0;
	r->golosMarcados = 0;
	r->golosSofridos = 0;

	return r;

};


/*

Funcoes para lidar com os objectos:

*/


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
	printf("Vencimento: %.2f\n", j->vencimentoMensal);
	printf("Data de inicio do contracto: %i/%i/%i\n", j->dataContracto->tm_mday, j->dataContracto->tm_mon + 1, j->dataContracto->tm_year);
	printf("Data de finm do contracto: %i/%i/%i\n", j->dataFimContracto->tm_mday, j->dataFimContracto->tm_mon + 1, j->dataFimContracto->tm_year);
	printf("Anos de contracto: %i\n", j->anosContracto);
	printf("Posicao:%s\n", j->posicao);
	printf("Atributos:\n");

	imprimeAtributos(j->atributos);

	printf("--------\n");
};

/*
Imprime a informação do treinador no argumento
*/
void imprimeTreinador(Treinador* t) {

	printf("--------\n");

	printf("Cartao do Treinador: %s\n", t->nome);
	
	printf("--------\n");
};

/*
Imprime plantel
*/
void imprimePlantel(Plantel* p) {

	printf("--------\n");

	printf("Treinador: %s\n", p->treinador->nome);
	printf("Jogadores:\n");

	int i;
	for (i = 0; i < NUMERO_JOGADORES_PLANTEL; i++) {

		// apenas imprime se o jogador estiver definido!
		// (apontador não é nulo)
		if (p->jogadores[i]->nome[0] != '\0') {

			printf("+ %s | %s\n", p->jogadores[i]->posicao, p->jogadores[i]->nome);

		}
	
	}

	printf("--------\n");
};

void imprimeEquipa(Equipa* e) {

	printf("--------\n");
	
	printf("Nome: %s\n", e->nome);
	printf("Estadio: %s\n", e->estadio->nome);
	printf("Socios: %i\n", e->socios);
	printf("Fundos: %0.2f\n", e->fundos);
	
	printf("--------\n");
};

void imprimeEstadio(Estadio* e) {

	printf("--------\n");

	printf("Nome: %s\n", e->nome);
	printf("Lugares: %i\n", e->lugares);
	printf("Despesa Mensal: %0.2f\n", e->despesaMensal);

	printf("--------\n");
};

/*

Funcoes uteis:

*/

/*
Retorna float entre 0 e 1
*/
float randomFloat()
{
	float r = (float)rand() / (float)RAND_MAX;
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
	data->tm_mon  = atoi(mes) - 1;  // reparem no -1
	data->tm_mday = atoi(dia);

	return data;

};