#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_typedefs.h"
#include "game_constants.h"
#include "game_globals.h"
#include "game_utils.h"
#include "game_information_output.h"

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
NULL caso não seja encontrada
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
Retorna a equipa por letra do sorteio.
NULL caso não seja encontrada
*/
Equipa* obterEquipaPorLetraSorteio(Equipa* EQUIPAS[], char letra) {

	int i;

	for (i = 0; i < NUMERO_EQUIPAS; i++) {

		if (letra == EQUIPAS[i]->letraSorteio) {

			return EQUIPAS[i];

		}

	}

	// caso a equipa não seja encontrada:
	return NULL;

};

/*
Troca dois jogadores um por outro
Equipa 1 é a equipa que paga
*/
void trocaJogadores(Equipa* equipa1, Equipa* equipa2, int indice1, int indice2, float valorTransf) {

	// guardar jogador1 num buffer
	Jogador* bufferJogador1 = equipa1->plantel->jogadores[indice1];
	//printf("jogador no buffer:%s\n", bufferJogador1->nome);

	// colocar jogador2 na equipa1
	equipa1->plantel->jogadores[indice1] = equipa2->plantel->jogadores[indice2];
	//printf("jogador no posto na equipa1:%s\n", equipa1->plantel->jogadores[indice1]->nome);

	// colocar buffer na equipa2
	equipa2->plantel->jogadores[indice2] = bufferJogador1;
	//printf("jogador no posto na equipa2:%s\n", equipa2->plantel->jogadores[indice2]->nome);

	//actualizar o vencimento do jogador transferido
	equipa1->plantel->jogadores[indice1]->vencimentoMensal *= 1.5;

	// subtrair aos fundos da equipa a compra
	equipa1->fundos -= valorTransf;

	// adicionar aos fundos da equipa que vende
	equipa2->fundos += valorTransf;

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

	time_t dataContractoMs = mktime(j->dataContracto);
	time_t dataFimContractoMs = mktime(j->dataFimContracto);

	time_t diffms = difftime(dataFimContractoMs, dataContractoMs);

	struct tm *diff = gmtime(&diffms);
	diff->tm_year -= 70; // subtrair 70 por causa do unix epoch

	int mesesDeContractoEmFalta = diff->tm_year * 12 + diff->tm_mon + 1;  // ignoramos os dias

	// calcular valor final
	valor = j->vencimentoMensal * 5 * mesesDeContractoEmFalta;

	return valor;

};

void atribuirLetrasSorteio() {

	// letras necessárias
	char alfabeto[] = "ABCDEFGHIJKLMNOPQR";

	// baralhar
	for (int i = 0; i < (int)strlen(alfabeto); i++) {

		int rnd = randomInt(0, strlen(alfabeto) - 1);

		char tmp = alfabeto[i];

		alfabeto[i] = alfabeto[rnd];
		alfabeto[rnd] = tmp;

	}

	// alfabeto está agora baralhado
	// vamos atribuir uma letra a cada equipa
	for (int j = 0; j < NUMERO_EQUIPAS; j++) {

		EQUIPAS[j]->letraSorteio = alfabeto[j];

	}

}

Jogador* escolherJogador(Equipa* e) {

	int exit = 1, option;
	
	imprimirInstrucao("Escolha o jogador:\n\n");

	while (exit) {

		imprimirCursor();
		scanf("%i", &option);
		getchar();

		if (option > 0 && option < NUMERO_JOGADORES_PLANTEL + 1) {

			option = option - 1;

			exit = 0;


		}
		else {

			printf("Opcao não válida. Não existe jogador número %i.\n", option);

		}

	}

	return e->plantel->jogadores[option];

}

void resetEstadoJogo(Equipa* e) {

	for (int i = 0; i < NUMERO_JOGADORES_PLANTEL; i++) {

		EQUIPAS[INDICE_EQUIPA_JOGADOR]->plantel->jogadores[i]->estadoEmJogo[0] = 0;
		EQUIPAS[INDICE_EQUIPA_JOGADOR]->plantel->jogadores[i]->estadoEmJogo[1] = 0;

	}

};

/*
Retorna o jogo em que o jogador participa, na jornada actual
*/
Jogo* obterJogoJogadorNaJornada(int nJornada) {

	// vamos correr todos os jogos da jornada
	for (int i = 0; i < (sizeof(JORNADAS[0]) / sizeof(JORNADAS[0][0])); i++) {

		if (JORNADAS[nJornada][i]->equipaA == EQUIPAS[INDICE_EQUIPA_JOGADOR]->letraSorteio ||
			JORNADAS[nJornada][i]->equipaB == EQUIPAS[INDICE_EQUIPA_JOGADOR]->letraSorteio) {

			return JORNADAS[nJornada][i];

		}

	}

	// if it comes to this, we are in deep shit
	return NULL;

}

/*
Obter array com jogadores de uma certa posição
*/
void obterJogadoresComPosição(Jogador* jogadores[], Equipa* equipa, char posicao[]) {
	
	int count = 0;

	for (int i = 0; i < NUMERO_JOGADORES_PLANTEL; i++) {

		if (strstr(equipa->plantel->jogadores[i]->posicao, posicao) != NULL) {  // strstr procura uma substring noutra

			jogadores[count] = equipa->plantel->jogadores[i];
			count++;

		}

	}

	jogadores[count] = NULL;

};

/*
Obter jogador aleatorio de array
*/
Jogador* obterJogadorAleatorioDeArray(Jogador* jogadores[]) {

	int count = 0;

	while (jogadores[count] != NULL) {

		count++;

	}

	return jogadores[randomInt(0, count - 1)];

};

/*
Baralha uma array de jogares
*/
void baralharArrayJogadores(Jogador* jogadores[]) {

	int count = 0;

	while (jogadores[count] != NULL) {

		count++;

	}

	for (int i = 0; i < count; i++) {

		int rnd = randomInt(0, count - 1);

		Jogador* tmp = jogadores[i];
		
		jogadores[i] = jogadores[rnd];
		jogadores[rnd] = tmp;

	}

};

/*
Organiza aleatoriamente o 11 da equipa do argumento
*/
void fazerOnzeAleatorio(Equipa* equipa) {

	// antes de mais, fazer reset a tudo
	for (int i = 0; i < NUMERO_JOGADORES_PLANTEL; i++) {

		equipa->plantel->jogadores[i]->estadoEmJogo[0] = 0;
		equipa->plantel->jogadores[i]->estadoEmJogo[1] = 0;

	}

	// agora, escolher uma estratégia
	char *taticas[5];
	taticas[0] = "3-4-3";
	taticas[1] = "4-4-2";
	taticas[2] = "4-3-3";
	taticas[3] = "4-5-1";
	taticas[4] = "5-3-2";

	char tatica[5];
	strcpy(tatica, taticas[randomInt(0, 4)]);

	// criar buffer para pesquisa de jogadores
	Jogador* bufferDeJogadores[20];
	obterJogadoresComPosição(bufferDeJogadores, equipa, "GR");

	// posicao 0 é o GR principal... vá, não vamos deixar ninguém em desvantagem
	bufferDeJogadores[0]->estadoEmJogo[0] = POSICAO_GR;

	// escolher defesas
	Jogador* bufferDeJogadoresDEF[20];
	obterJogadoresComPosição(bufferDeJogadoresDEF, equipa, "DEF");
	baralharArrayJogadores(bufferDeJogadoresDEF);

	for (int i = 0; i < (int)(tatica[0] - '0'); i++) {

		bufferDeJogadoresDEF[i]->estadoEmJogo[0] = POSICAO_DEF;

	}

	// escolher medios
	Jogador* bufferDeJogadoresMED[20];
	obterJogadoresComPosição(bufferDeJogadoresMED, equipa, "MED");
	baralharArrayJogadores(bufferDeJogadoresMED);

	for (int i = 0; i < (int)(tatica[2] - '0'); i++) {

		bufferDeJogadoresMED[i]->estadoEmJogo[0] = POSICAO_MED;

	}
	
	// escolher avancados
	Jogador* bufferDeJogadoresAV[20];
	obterJogadoresComPosição(bufferDeJogadoresAV, equipa, "AV");
	baralharArrayJogadores(bufferDeJogadoresAV);

	for (int i = 0; i < (int)(tatica[4] - '0'); i++) {

		bufferDeJogadoresAV[i]->estadoEmJogo[0] = POSICAO_AV;

	}

	imprimirOnzeDefinido(equipa);

};

/*
Realiza o jogo do argumento
*/
void realizarJogo(Jogo* jogo) {

	

}
