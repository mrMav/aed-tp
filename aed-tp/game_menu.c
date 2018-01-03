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
	imprimirCursor();
	gets(NOME_JOGADOR);
	
	imprimirInstrucao("Escolha a sua equipa:\n");
	listarEquipas();

	while (exit) {

		imprimirCursor();
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

	strcpy(EQUIPAS[INDICE_EQUIPA_JOGADOR]->plantel->treinador->nome, NOME_JOGADOR);

	imprimirInicioDoJogo();
	iniciarMenuPreparacaoEpoca();

}


void iniciarMenuPreparacaoEpoca() {

	enum MENU_INICIAL opcao = MENU_INICIAL_OPCAO_NULA;
	
	while (opcao != MENU_INICIAL_OPCAO_SAIR) {

		imprimirMenuPreparacaoEpoca(nTransferencias);

		scanf("%i", &opcao);
		getchar();

		switch (opcao) {

		case MENU_PREPARACAO_EPOCA_OPCAO_TRANSFERENCIA_JOGADORES:

			if (nTransferencias < NUMERO_TRANSFERENCIAS) {
				
				iniciarMenuCompraEVenda();

			}
			else {

				printf("Total de transferencias feitas!\n");

			}

			break;
		case MENU_PREPARACAO_EPOCA_OPCAO_INFORMACAO:

			imprimeEquipa(EQUIPAS[INDICE_EQUIPA_JOGADOR]);
			imprimePlantel(EQUIPAS[INDICE_EQUIPA_JOGADOR]->plantel);
			imprimeEstadio(EQUIPAS[INDICE_EQUIPA_JOGADOR]->estadio);

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
	imprimirOpcao("%i: COMPRA E VENDA DE JOGADORES", MENU_PREPARACAO_EPOCA_OPCAO_TRANSFERENCIA_JOGADORES);
	printf(" (%i/%i)\n", nTransferencias, NUMERO_TRANSFERENCIAS);
	imprimirOpcao("%i: VER EQUIPA, JOGADORES, ETC\n", MENU_PREPARACAO_EPOCA_OPCAO_INFORMACAO);
	imprimirOpcao("%i: INICIAR ÉPOCA\n", MENU_PREPARACAO_EPOCA_INICIAR_EPOCA);

	imprimirSeparador();
	imprimirCursor();

}

void iniciarMenuCompraEVenda() {

	int equipaEscolhida = 0;
	int jogadorEscolhido = 0;
	int jogadorATrocar = 0;
	int exit = 1;

	imprimirTitulo("Compra e venda de jogadores");
	imprimirInstrucao("Para efectuar uma transferencia deve trocar sempre um jogador por outro.\nComece por escolher a equipa a que pretende ir buscar o novo jogador:\n");
	listarEquipas();
	
	while (exit) {

		imprimirCursor();
		scanf("%i", &equipaEscolhida);
		getchar();

		if (equipaEscolhida != INDICE_EQUIPA_JOGADOR + 1 && equipaEscolhida > 0 && equipaEscolhida < NUMERO_EQUIPAS + 1) {
			
			equipaEscolhida = equipaEscolhida - 1;

			exit = 0;

		} else {

			printf("Opcao nao valida. Escolha de novo.\n");

		}

	}

	imprimirInstrucao("Escolha o jogador:\n");
	listarJogadores(EQUIPAS[equipaEscolhida]);

	exit = 1;
	while (exit) {

		imprimirCursor();
		scanf("%i", &jogadorEscolhido);
		getchar();

		if (jogadorEscolhido > 0 && jogadorEscolhido < NUMERO_JOGADORES_PLANTEL + 1) {
			
			jogadorEscolhido = jogadorEscolhido - 1;

			exit = 0;

		}
		else {

			printf("Opcao nao valida. Escolha de novo.\n");

		}

	}

	imprimirInstrucao("Escolha o jogador da SUA equipa para TROCAR:\n");
	listarJogadores(EQUIPAS[INDICE_EQUIPA_JOGADOR]);

	exit = 1;
	while (exit) {

		imprimirCursor();
		scanf("%i", &jogadorATrocar);
		getchar();

		if (jogadorATrocar > 0 && jogadorATrocar < NUMERO_JOGADORES_PLANTEL + 1) {
			
			jogadorATrocar = jogadorATrocar - 1;

			exit = 0;

		}
		else {

			printf("Opcao nao valida. Escolha de novo.\n");

		}

	}
	
	// TODO: verificar se a equipa tem fundos para este jogador
	// TODO: imprimir valor do jogador
	// ATENCAO: com o metodo de  troca sempre possivel, é possivel retirar todos os 
	// guarda redes de uma equipa por exemplo
	trocaJogadores(EQUIPAS[INDICE_EQUIPA_JOGADOR], EQUIPAS[equipaEscolhida], jogadorATrocar, jogadorEscolhido);
	
}