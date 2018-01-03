#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_typedefs.h"
#include "game_constants.h"
#include "game_utils.h"
#include "game_globals.h"

/*

Funcoes para representar objectos no ecra:

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
		if (p->jogadores[i]) {

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

void imprimeResultados(Resultado* r) {

	printf("--------\n");

	printf("Vitorias: %i\n", r->vitorias);
	printf("Empates: %i\n", r->empates);
	printf("Derrotas: %i\n", r->derrotas);
	printf("Golos Marcados: %i\n", r->golosMarcados);
	printf("Golos Sofridos: %i\n", r->golosSofridos);
	printf("Jogos Realizados: %i\n", r->jogosRealizados);

	printf("--------\n");
};

void imprimirTitulo(char* string) {

	int length = strlen(string);
	int i;

	for (i = 0; i < length + 4; i++) {

		printf("-");

	};

	printf("\n| %s |\n", string);
	
	for (i = 0; i < length + 4; i++) {

		printf("-");

	};

	printf("\n");

};

void imprimirCabecalho(char* string) {

	int length = strlen(string);
	int i;

	for (i = 0; i < length + 6; i++) {

		printf("#");

	};

	printf("\n## %s ##\n", string);

	for (i = 0; i < length + 6; i++) {

		printf("#");

	};

	printf("\n");

};

void imprimirOpcao(char* string, int opcao) {

	printf(string, opcao);

};

void imprimirSeparador() {

	printf("--------\n");

}

void imprimirCursor() {

	printf("-> ");

}

void imprimirInstrucao(char* string) {

	imprimirCursor();
	printf("%s", string);

};

void imprimirInicioDoJogo() {

	int jogadorAleatorio = randomInt(0, NUMERO_JOGADORES_PLANTEL - 1);
	
	printf("--------\n");
	printf("Novo treinador do %s começa hoje a treinar a equipa!\nO jogador %s mostra-se confiante relativamente a %s.\n",
		EQUIPAS[INDICE_EQUIPA_JOGADOR]->nome,		
		EQUIPAS[INDICE_EQUIPA_JOGADOR]->plantel->jogadores[jogadorAleatorio],
		NOME_JOGADOR
	);

};

void listarEquipas() {

	int i;
	for (i = 0; i < NUMERO_EQUIPAS; i++) {

		printf("%02i | %s\n", i + 1, EQUIPAS[i]->nome);

	}
	
}

void listarJogadores(Equipa* e) {

	int espacoReservadoParaNomeDoJogador = 30;

	int i;
	for (i = 0; i < NUMERO_JOGADORES_PLANTEL; i++) {
		
		printf("%02i | %s | %s", i + 1, e->plantel->jogadores[i]->posicao, e->plantel->jogadores[i]->nome);

		int j;
		for (j = strlen(e->plantel->jogadores[i]->nome); j < espacoReservadoParaNomeDoJogador; j++) {
			printf(" ");
		}

		printf("| GR: %.2f\% | DEF: %.2f\% | MED: %.2f\% | AV: %.2f\% | \n",
			e->plantel->jogadores[i]->atributos->gr,
			e->plantel->jogadores[i]->atributos->df,
			e->plantel->jogadores[i]->atributos->md,
			e->plantel->jogadores[i]->atributos->av
		);
		
	}

}