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

	char nome[100];
	int numero;
	float vencimentoMensal;
	struct tm* dataContracto;
	struct tm* dataFimContracto;
	int anosContracto;
	char posicao[3];
	int estadoEmJogo[2];
	Atributos* atributos;

} Jogador;

typedef struct {

	char nome[100];

} Treinador;

typedef struct {

	Treinador* treinador;
	Jogador* jogadores[NUMERO_JOGADORES_PLANTEL];
	int numeroActualJogadores;

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

	char nome[100];
	int lugares;
	float despesaMensal;

} Estadio;

typedef struct {

	char nome[100];
	Estadio* estadio;
	int socios;
	float fundos;
	Resultado* resultados;
	Plantel* plantel;
	char letraSorteio;

} Equipa;

typedef struct {

	Equipa *vencedor;
	Equipa *derrotado;

	int golosVencedor;
	int golosDerrotado;

} ResultadosJogo;

typedef struct {

	char equipaA;
	char equipaB;

	int realizado;

	ResultadosJogo *resultados;

} Jogo;