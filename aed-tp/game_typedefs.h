#pragma once
#include <time.h>

#include "game_constants.h"

typedef struct {

	// Forca posicao de guardaredes
	float gr;
	
	// Forca posicao defesa
	float df;
	
	// Forca posicao medio
	float md;
	
	// Forca posicao avancado
	float av;

} Atributos;

typedef struct {

	char nome[40];
	int numero;
	float vencimentoMensal;
	time_t* dataContracto;
	int anosContracto;
	char posicao[3];
	Atributos* atributos;

} Jogador;

typedef struct {

	char nome[40];

} Treinador;

typedef struct {

	Treinador* treinador;
	Jogador* jogadores[NUMERO_JOGADORES_PLANTEL];

} Plantel;

typedef struct {

	int jogosRealizados;
	int vitorias;
	int empates;
	int derrotas;
	int golosMarcados;
	int golosSofridos;

} Resultado;

typedef struct {

	char nome[40];
	int lugares;
	float despesaMensal;

} Estadio;

typedef struct {

	char nome[40];
	Estadio estadio;
	int socios;
	Resultado resultados;
	Plantel plantel;

} Equipa;