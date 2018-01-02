#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#include "game_typedefs.h"
#include "game_constants.h"
#include "game_data_load.h"
#include "game_menu.h"
#include "game_information_output.h"
#include "game_object_creation.h"
#include "game_object_manipulation.h"
#include "game_utils.h"
#include "game_globals.h"


void iniciarJogo() {

	iniciarMenuInicial();
	
}

void sairJogo() {
	
	printf("\nExiting game....\n");
	
	Sleep(1000);

	exit(0);
}

void iniciarMenuInicial() {
	
	enum MENU_INICIAL opcao = MENU_INICIAL_OPCAO_NULA;
	
	while (opcao != MENU_INICIAL_OPCAO_SAIR) {

		imprimirMenuInicial();

		scanf("%i", &opcao);
		getchar();

		switch (opcao) {

		case MENU_INICIAL_OPCAO_CONTINUAR:

			printf("\nNot working yet...\n");

			break;
		case MENU_INICIAL_OPCAO_NOVO_JOGO:

			iniciarMenuNovoJogo();

			break;
		}

	}

	sairJogo();
	
}

void imprimirMenuInicial() {

	imprimirCabecalho(" F-TASTIC ");

	imprimirOpcao("%i: SAIR DO JOGO\n", MENU_INICIAL_OPCAO_SAIR);
	imprimirOpcao("%i: CONTINUAR\n", MENU_INICIAL_OPCAO_CONTINUAR);
	imprimirOpcao("%i: NOVO JOGO\n", MENU_INICIAL_OPCAO_NOVO_JOGO);

	imprimirSeparador();
	imprimirCursor();

}

void iniciarMenuNovoJogo() {

	int opcao = 0;
	int exit = 1;

	imprimirTitulo("Começar Novo Jogo");
	imprimirInstrucao("Escreva o seu nome:\n");
	
	gets(NOME_JOGADOR);

	imprimirInstrucao("Escolha a sua equipa:\n");
	listarEquipas();

	while (exit) {
		
		scanf("%i", &opcao);
		getchar();

		if (opcao > 0 && opcao < NUMERO_EQUIPAS) {

			INDICE_EQUIPA_JOGADOR = opcao - 1;

			exit = 0;

		}
		else {

			printf("Opcao nao valida. Escolha de novo.\n");
			imprimirInstrucao("Escolha a sua equipa:\n");
			listarEquipas();

		}

	}

	iniciarMenuPreparacaoEpoca();

}


void iniciarMenuPreparacaoEpoca() {

	enum MENU_INICIAL opcao = MENU_INICIAL_OPCAO_NULA;

	while (opcao != MENU_INICIAL_OPCAO_SAIR) {

		imprimirMenuPreparacaoEpoca();

		scanf("%i", &opcao);
		getchar();

		switch (opcao) {

		case MENU_PREPARACAO_EPOCA_OPCAO_TRANSFERENCIA_JOGADORES:

			printf("\nNot working yet...\n");

			break;
		case MENU_PREPARACAO_EPOCA_OPCAO_INFORMACAO:

			printf("\nNot working yet...\n");

			break;
		case MENU_PREPARACAO_EPOCA_INICIAR_EPOCA:

			printf("\nNot working yet...\n");

			break;
		}

	}

	sairJogo();

}

void imprimirMenuPreparacaoEpoca() {

	imprimirTitulo("Começar a Época");

	imprimirOpcao("%i: SAIR DO JOGO\n", MENU_PREPARACAO_EPOCA_OPCAO_SAIR);
	imprimirOpcao("%i: TRANSFERENCIA DE JOGADORES\n", MENU_PREPARACAO_EPOCA_OPCAO_TRANSFERENCIA_JOGADORES);
	imprimirOpcao("%i: INFORMACAO\n", MENU_PREPARACAO_EPOCA_OPCAO_INFORMACAO);
	imprimirOpcao("%i: INICIAR ÉPOCA\n", MENU_PREPARACAO_EPOCA_INICIAR_EPOCA);

	imprimirSeparador();
	imprimirCursor();

}