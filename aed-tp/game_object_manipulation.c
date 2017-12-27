#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_typedefs.h"
#include "game_constants.h"

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
Equipa* obterEquipaPorNome(Equipa* equipas[], char string[]) {

	int i;

	for (i = 0; i < NUMERO_EQUIPAS; i++) {

		if (strcmp(string, equipas[i]->nome) == 0) {

			return equipas[i];

		}

	}

	// caso a equipa não seja encontrada:
	return NULL;

};