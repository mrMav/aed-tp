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

	printf("\nExiting game....\n");
	Sleep(1000);

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
	
}

void imprimirMenuInicial() {

	imprimirCabecalho(" F-TASTIC ");

	//printf("%i: SAIR DO JOGO\n", MENU_INICIAL_OPCAO_SAIR);
	imprimirOpcao("%i: SAIR DO JOGO\n", MENU_INICIAL_OPCAO_SAIR);
	imprimirOpcao("%i: CONTINUAR\n", MENU_INICIAL_OPCAO_CONTINUAR);
	imprimirOpcao("%i: NOVO JOGO\n", MENU_INICIAL_OPCAO_NOVO_JOGO);

	printf("-----------------------\n");
	printf("-> ");

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

	imprimirInicioDoJogo();

}

void imprimirMenuNovoJogo() {

	printf("\n---- Novo Jogo ----\n");

	printf("%i: VOLTAR\n", MENU_NOVO_JOGO_OPCAO_SAIR);
	printf("%i: INSERIR NOME\n", MENU_NOVO_JOGO_OPCAO_INSERIR_NOME);
	printf("%i: ESCOLHER EQUIPA\n", MENU_NOVO_JOGO_OPCAO_ESCOLHER_EQUIPA);

	printf("-----------------------\n");

}