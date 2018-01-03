#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_typedefs.h"
#include "game_constants.h"
#include "game_globals.h"

/*
Funcoes para manipular objectos e informacao do jogo
*/

/*
Adiciona o jogador no plantel.
Return 0: fail
Return 1: sucess
*/
int adicionarJogadorAPlantel(Plantel* plantel, Jogador* jogador) {

	// verificar se plantel está cheio:
	if (plantel->numeroActualJogadores == NUMERO_JOGADORES_PLANTEL) {

		return 0;

	}

	// nesta fase, podemos adicionar o jogador ao ultimo indice disponivel:

	int indice = plantel->numeroActualJogadores;

	plantel->jogadores[indice] = jogador;
	plantel->numeroActualJogadores++;  // passo muito importante.

	return 1;

};

/*
Retorna a equipa por nome.
*/
Equipa* obterEquipaPorNome(Equipa* EQUIPAS[], char string[]) {

	int i;

	for (i = 0; i < NUMERO_EQUIPAS; i++) {

		if (strcmp(string, EQUIPAS[i]->nome) == 0) {

			return EQUIPAS[i];

		}

	}

	// caso a equipa não seja encontrada:
	return NULL;

};

/*
Troca dois jogadores um por outro
*/
void trocaJogadores(Equipa* equipa1, Equipa* equipa2, int indice1, int indice2) {

	// guardar jogador1 num buffer
	Jogador* bufferJogador1 = equipa1->plantel->jogadores[indice1];
	//printf("jogador no buffer:%s\n", bufferJogador1->nome);

	// colocar jogador2 na equipa1
	equipa1->plantel->jogadores[indice1] = equipa2->plantel->jogadores[indice2];
	//printf("jogador no posto na equipa1:%s\n", equipa1->plantel->jogadores[indice1]->nome);

	// colocar buffer na equipa2
	equipa2->plantel->jogadores[indice2] = bufferJogador1;
	//printf("jogador no posto na equipa2:%s\n", equipa2->plantel->jogadores[indice2]->nome);

	nTransferencias++;

};