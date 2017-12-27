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

	int opcao = 0;

	Equipa* equipaSelecionada = equipas[0];

	while (opcao != SAIR_JOGO) {

		imprimirMenu();

		scanf("%i", &opcao);

		switch (opcao) {

		case VER_RESULTADOS:



			imprimeResultados(equipaSelecionada->resultados);

			break;
		case VER_EQUIPA:

			imprimeEquipa(equipaSelecionada);

			break;
		case VER_PLANTEL:

			imprimePlantel(equipaSelecionada->plantel);

			break;
		}



	}

	printf("\nExiting game....\n");
	Sleep(1000);

}

void imprimirMenu() {

	printf("---- Futebol Game ----\n");

	printf("-1: SAIR DO JOGO\n");
	printf(" 0: VER RESULTADOS\n");
	printf(" 1: VER EQUIPA\n");
	printf(" 2: VER PLANTEL\n");

	printf("-----------------------\n");
	
}