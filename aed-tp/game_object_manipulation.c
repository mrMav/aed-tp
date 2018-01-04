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

/*
Retorna o valor da transferencia de um jogador
*/
float obterValorTransferencia(Jogador* j) {

	// a formula para o valor da transferencia é dado por:
	// Salário * 5 * número de meses de contrato que faltam cumprir

	float valor;

	// calcular o numero de meses que faltam
	// mktime devolve o tempo em ms desde 1970 (unix epoch)
	// talvez não esteja totalmente correcto porque nao sabemos
	// se o sistema que estamos a correr usa o unix epoch...

	time_t dataContractoMs    = mktime(j->dataContracto);
	time_t dataFimContractoMs = mktime(j->dataFimContracto);

	time_t diffms = difftime(dataFimContractoMs, dataContractoMs);

	struct tm *diff = gmtime(&diffms);
	diff->tm_year -= 70; // subtrair 70 por causa do unix epoch

	int mesesDeContractoEmFalta = diff->tm_year * 12 + diff->tm_mon + 1;  // ignoramos os dias

	printf("%i\n", mesesDeContractoEmFalta);

	// calcular valor final
	valor = j->vencimentoMensal * 5 * mesesDeContractoEmFalta;

	return valor;

};