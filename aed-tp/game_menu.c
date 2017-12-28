#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#include "game_constants.h"
#include "game_typedefs.h"
#include "game_data_load.h"
#include "game_menu.h"
#include "game_information_output.h"
#include "game_object_creation.h"
#include "game_object_manipulation.h"
#include "game_utils.h"


void iniciarJogo(Equipa *equipas[]) {

	iniciarMenuInicial(equipas);

	printf("\nExiting game....\n");
	Sleep(1000);

}

void iniciarMenuInicial(Equipa * equipas[]) {
	
	enum MENU_INICIAL opcao = MENU_INICIAL_OPCAO_NULA;

	Equipa* equipaSelecionada = equipas[0];

	while (opcao != MENU_INICIAL_OPCAO_SAIR) {

		imprimirMenuInicial();

		scanf("%i", &opcao);

		switch (opcao) {

		case MENU_INICIAL_OPCAO_CONTINUAR:

			//iniciarMenuNovoJogo(equipas);

			break;
		case MENU_INICIAL_OPCAO_NOVO_JOGO:

			iniciarMenuNovoJogo(equipas);

			break;
		}

	}
	
}

void imprimirMenuInicial() {

	printf("\n---- Futebol Game ----\n");

	printf("%i: SAIR DO JOGO\n", MENU_INICIAL_OPCAO_SAIR);
	printf("%i: CONTINUAR\n", MENU_INICIAL_OPCAO_CONTINUAR);
	printf("%i: NOVO JOGO\n", MENU_INICIAL_OPCAO_NOVO_JOGO);

	printf("-----------------------\n");

}


void iniciarMenuNovoJogo(Equipa * equipas[]) {

	enum MENU_NOVO_JOGO opcao = MENU_NOVO_JOGO_OPCAO_NULA;

	Equipa* equipaSelecionada = equipas[0];

	while (opcao != MENU_NOVO_JOGO_OPCAO_SAIR) {

		imprimirMenuNovoJogo();

		scanf("%i", &opcao);

		switch (opcao) {

		case MENU_NOVO_JOGO_OPCAO_INSERIR_NOME:

			//iniciarMenuInicial(equipas);

			break;
		
		case MENU_NOVO_JOGO_OPCAO_ESCOLHER_EQUIPA:

			//iniciarMenuInicial(equipas);

			break;
		}

	}

}

void imprimirMenuNovoJogo() {

	printf("\n---- Novo Jogo ----\n");

	printf("%i: VOLTAR\n", MENU_NOVO_JOGO_OPCAO_SAIR);
	printf("%i: INSERIR NOME\n", MENU_NOVO_JOGO_OPCAO_INSERIR_NOME);
	printf("%i: ESCOLHER EQUIPA\n", MENU_NOVO_JOGO_OPCAO_ESCOLHER_EQUIPA);

	printf("-----------------------\n");

}