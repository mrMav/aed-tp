#pragma once
#include <time.h>

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
	Atributos* atributos;

} Jogador;

typedef struct {

	char nome[40];

} Treinador;

typedef struct {

	Treinador* treinador;
	Jogador* jogadores[20];

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