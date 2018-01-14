#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_typedefs.h"
#include "game_constants.h"
#include "game_object_creation.h"


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

	p->numeroActualJogadores = NUMERO_JOGADORES_PLANTEL;

	return p;

};
Plantel* novoPlantelVazio() {

	Plantel* p = malloc(sizeof(Plantel));

	p->treinador = NULL;

	int i;
	for (i = 0; i < NUMERO_JOGADORES_PLANTEL; i++) {

		p->jogadores[i] = NULL;

	};

	p->numeroActualJogadores = 0;

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
	r->pontos = 0;

	return r;

};

/*
Novo resultados jogo
*/
ResultadosJogo* novoResultadosJogo() {

	ResultadosJogo *rj = malloc(sizeof(ResultadosJogo));

	rj->derrotado = NULL;
	rj->vencedor  = NULL;

	rj->empate = 0;

	rj->golosEquipaA = 0;
	rj->golosEquipaB = 0;

	rj->poderAtaqueEquipaAPrimeiraParte = 0.0;
	rj->poderAtaqueEquipaBPrimeiraParte = 0.0;

	rj->poderDefesaEquipaAPrimeiraParte = 0.0;
	rj->poderDefesaEquipaBPrimeiraParte = 0.0;

	rj->poderAtaqueEquipaASegundaParte = 0.0;
	rj->poderAtaqueEquipaBSegundaParte = 0.0;

	rj->poderDefesaEquipaASegundaParte = 0.0;
	rj->poderDefesaEquipaBSegundaParte = 0.0;


	return rj;


};

/*
Novo jogo(confronto)
*/
Jogo* novoJogo(char eA, char eB) {

	Jogo *j = malloc(sizeof(Jogo));

	j->equipaA = eA;
	j->equipaB = eB;
	
	j->realizado = 0;
	j->resultados = novoResultadosJogo();

	return j;


};