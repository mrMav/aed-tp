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
#include "game_object_manipulation.h"

/*

Funcoes para representar objectos no ecra:

*/

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

	printf("\n-> ");

}

void imprimirInstrucao(char* string) {

	imprimirCursor();
	printf("%s", string);

};


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

	imprimirSeparador();

	printf("Cartao do jogador: %s\n", j->nome);

	printf("Numero: %i\n", j->numero);
	printf("Vencimento: %.2f\n", j->vencimentoMensal);
	printf("Data de inicio do contracto: %i/%i/%i\n", j->dataContracto->tm_mday, j->dataContracto->tm_mon + 1, j->dataContracto->tm_year);
	printf("Data de finm do contracto: %i/%i/%i\n", j->dataFimContracto->tm_mday, j->dataFimContracto->tm_mon + 1, j->dataFimContracto->tm_year);
	printf("Anos de contracto: %i\n", j->anosContracto);
	printf("Posicao:%s\n", j->posicao);
	printf("Atributos:\n");

	imprimeAtributos(j->atributos);

	imprimirSeparador();
};

void imprimeJogadorFormaDeLista(Jogador* j) {

	int espacoReservadoParaNomeDoJogador = 30;

	printf("%s | %s", j->posicao, j->nome);

	int i;
	for (i = strlen(j->nome); i < espacoReservadoParaNomeDoJogador; i++) {
		printf(" ");
	}

	printf("| GR: %.2f | DEF: %.2f | MED: %.2f | AV: %.2f | \n",
		j->atributos->gr,
		j->atributos->df,
		j->atributos->md,
		j->atributos->av
	);
};

/*
Imprime a informação do treinador no argumento
*/
void imprimeTreinador(Treinador* t) {

	imprimirSeparador();

	printf("Cartao do Treinador: %s\n", t->nome);

	imprimirSeparador();
};

/*
Imprime plantel
*/
void imprimePlantel(Plantel* p) {

	imprimirSeparador();

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

	imprimirSeparador();
};

void imprimeEquipa(Equipa* e) {

	imprimirSeparador();

	printf("Nome: %s\n", e->nome);
	printf("Estadio: %s\n", e->estadio->nome);
	printf("Socios: %i\n", e->socios);
	printf("Fundos: %0.2f\n", e->fundos);
	printf("Letra Sorteio: %c\n", e->letraSorteio);

	imprimirSeparador();
};

void imprimeEstadio(Estadio* e) {

	imprimirSeparador();

	printf("Nome: %s\n", e->nome);
	printf("Lugares: %i\n", e->lugares);
	printf("Despesa Mensal: %0.2f\n", e->despesaMensal);

	imprimirSeparador();
};

void imprimeResultados(Resultado* r) {

	imprimirSeparador();

	printf("Vitorias: %i\n", r->vitorias);
	printf("Empates: %i\n", r->empates);
	printf("Derrotas: %i\n", r->derrotas);
	printf("Golos Marcados: %i\n", r->golosMarcados);
	printf("Golos Sofridos: %i\n", r->golosSofridos);
	printf("Jogos Realizados: %i\n", r->jogosRealizados);

	imprimirSeparador();
};

void imprimirInicioDoJogo() {

	int jogadorAleatorio = randomInt(0, NUMERO_JOGADORES_PLANTEL - 1);

	imprimirSeparador();
	printf("Novo treinador do %s começa hoje a treinar a equipa!\nO jogador %s mostra-se confiante relativamente a %s.\n",
		EQUIPAS[INDICE_EQUIPA_JOGADOR]->nome,
		EQUIPAS[INDICE_EQUIPA_JOGADOR]->plantel->jogadores[jogadorAleatorio]->nome,
		NOME_JOGADOR
	);

};

void listarEquipas() {

	int espacoReservadoParaNomeDaEquipa = 30;

	int i;
	for (i = 0; i < NUMERO_EQUIPAS; i++) {

		printf("%02i | %s", i + 1, EQUIPAS[i]->nome);

		int j;
		for (j = strlen(EQUIPAS[i]->nome); j < espacoReservadoParaNomeDaEquipa; j++) {
			printf(" ");
		}

		printf("| Fundos: %.2f%s\n", EQUIPAS[i]->fundos, SIMBOLO_EURO);


	}

}

void listarJogadores(Equipa* e) {

	int espacoReservadoParaNomeDoJogador = 30;

	int i;
	for (i = 0; i < NUMERO_JOGADORES_PLANTEL; i++) {

		printf("%02i |", i + 1);

		imprimeJogadorFormaDeLista(e->plantel->jogadores[i]);

	}

}

void listarJogadoresAindaNaoEscolhidosParaJogo(int parteDoJogo) {

	int espacoReservadoParaNomeDoJogador = 30;

	Equipa* e = EQUIPAS[INDICE_EQUIPA_JOGADOR];

	int i;
	for (i = 0; i < NUMERO_JOGADORES_PLANTEL; i++) {

		Jogador* j = e->plantel->jogadores[i];

		if (j->estadoEmJogo[parteDoJogo] == 0) {

			printf("%02i | ", i + 1);

			imprimeJogadorFormaDeLista(e->plantel->jogadores[i]);

		}

	}

}

void imprimirResultadosJogo(ResultadosJogo* rj) {

	if (rj->golosVencedor != rj->golosDerrotado) {

		printf("Equipa vencedora: %s(%c)\n", rj->vencedor->nome, rj->vencedor->letraSorteio);
		printf("Equipa derrotada: %s(%c)\n", rj->derrotado->nome, rj->derrotado->letraSorteio);
		printf("Resultado: %i-%i", rj->golosVencedor, rj->golosDerrotado);

	}
	else {

		printf("Empate.");
		printf("%s(%c) - %s(%c)", rj->vencedor->nome, rj->vencedor->letraSorteio, rj->derrotado->nome, rj->derrotado->letraSorteio);
		printf("Resultado: %i-%i", rj->golosVencedor, rj->golosDerrotado);

	}


};

void imprimirJogo(Jogo* j) {

	printf("Equipa %c vs Equipa %c\n", j->equipaA, j->equipaB);
	if (j->realizado) {

		printf("Jogo realizado!\n");
		imprimirResultadosJogo(j->resultados);

	}
	else {

		printf("Jogo não realizado.\n\n");

	}

};

void imprimirJornada(int n) {

	if (epocaIniciada) {

		char buffer[30];
		int reservaEspaçoNomeEquipa = 20;

		// guarda a string formatada no buffer
		snprintf(buffer, sizeof(buffer), "JORNADA %02i", n + 1);

		imprimirTitulo(buffer);
		printf("\n");

		// imprimir a tabela com os jogos da jornada
		for (int i = 0; i < (sizeof(JORNADAS[0]) / sizeof(JORNADAS[0][0])); i++) {  // aquela coisa feia é uma forma de saber o tamanho do array, neste caso, 9

			Equipa* a = obterEquipaPorLetraSorteio(EQUIPAS, JORNADAS[n][i]->equipaA);
			Equipa* b = obterEquipaPorLetraSorteio(EQUIPAS, JORNADAS[n][i]->equipaB);

			for (int i = 0; i < reservaEspaçoNomeEquipa - strlen(a->nome); i++) {

				printf(" ");

			}

			printf("%s vs %s\n", a->nome, b->nome);

		}

	}
	else {

		printf("Ainda não iniciou a época!\n");

	}

	iniciarPrimirParaContinuar();

}

void imprimirEpoca() {

	if (epocaIniciada) {

		imprimirCabecalho("Calendário da época");
		printf("\n");

		for (int i = 0; i < (sizeof(JORNADAS) / sizeof(JORNADAS[0])); i++) {

			imprimirJornada(i);

		}

	}
	else {

		printf("Ainda não iniciou a época!\n");

	}
	
	iniciarPrimirParaContinuar();

};

void imprimirOnzeDefinido(Equipa* equipa) {

	printf("Guarda-Redes:\n");
	for (int i = 0; i < NUMERO_JOGADORES_PLANTEL; i++) {

		Jogador* j = equipa->plantel->jogadores[i];

		if (j->estadoEmJogo[0] == POSICAO_GR) {

			imprimeJogadorFormaDeLista(j);

		}

	}

	printf("Defesas:\n");
	for (int i = 0; i < NUMERO_JOGADORES_PLANTEL; i++) {

		Jogador* j = equipa->plantel->jogadores[i];

		if (j->estadoEmJogo[0] == POSICAO_DEF) {

			imprimeJogadorFormaDeLista(j);

		}

	}

	printf("Médios:\n");
	for (int i = 0; i < NUMERO_JOGADORES_PLANTEL; i++) {

		Jogador* j = equipa->plantel->jogadores[i];

		if (j->estadoEmJogo[0] == POSICAO_MED) {

			imprimeJogadorFormaDeLista(j);

		}

	}

	printf("Avançados:\n");
	for (int i = 0; i < NUMERO_JOGADORES_PLANTEL; i++) {

		Jogador* j = equipa->plantel->jogadores[i];

		if (j->estadoEmJogo[0] == POSICAO_AV) {

			imprimeJogadorFormaDeLista(j);

		}

	}

};

void listarJogadoresEscolhidosAJogo() {

	system("cls");

	imprimirTitulo("O seu 11:");

	imprimirOnzeDefinido(EQUIPAS[INDICE_EQUIPA_JOGADOR]);

}