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

		if (opcao > 0 && opcao <= NUMERO_EQUIPAS) {

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
	
	int equipasSeleciondasTransferencias[NUMERO_TRANSFERENCIAS];
	// init array
	int i;
	for (i = 0; i < NUMERO_TRANSFERENCIAS; i++) {
		equipasSeleciondasTransferencias[i] = -1;
	}

	while (opcao != MENU_INICIAL_OPCAO_SAIR) {

		imprimirMenuPreparacaoEpoca(nTransferencias);

		scanf("%i", &opcao);
		getchar();

		switch (opcao) {

		case MENU_PREPARACAO_EPOCA_OPCAO_TRANSFERENCIA_JOGADORES:

			if (nTransferencias < NUMERO_TRANSFERENCIAS) {
				
				iniciarMenuCompraEVenda(equipasSeleciondasTransferencias);

			}
			else {

				printf("Total de transferencias feitas!\n");

			}

			break;
		case MENU_PREPARACAO_EPOCA_OPCAO_INFORMACAO:

			iniciarMenuInformacao();

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

void iniciarMenuCompraEVenda(int *equipasSelecionadas) {

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

		if (equipaEscolhida != INDICE_EQUIPA_JOGADOR + 1) {

			if (equipaEscolhida > 0 && equipaEscolhida < NUMERO_EQUIPAS + 1) {

				int transValida = 1;

				// verificar se o utilizador já não comprou a esta equipa
				int i;
				for (i = 0; i < NUMERO_TRANSFERENCIAS; i++) {

					if (equipaEscolhida - 1 == equipasSelecionadas[i]) {

						transValida = 0;

					}

				}

				if (transValida) {

					equipaEscolhida = equipaEscolhida - 1;

					// guardar indice da equipa escolhida neste array
					// este array é verificado para só ser possivel escolher um jogador de cada equipa
					equipasSelecionadas[nTransferencias] = equipaEscolhida;

					exit = 0;

				}
				else {

					printf("Opção não válida! Já comprou jogadores à equipa %s.\n", EQUIPAS[equipaEscolhida-1]->nome);
					
				}
				
			}
			else {

				printf("Opção não válida! Não existe equipa número %i.\n", equipaEscolhida);

			}

		} else {

			printf("Opção não válida! Não pode comprar jogadores à sua própria equipa.\n");

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

			printf("Opcao nao valida. Não existe jogador número %i.\n", jogadorEscolhido);

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

	// ATENCAO: com este modelo é possivel trocar entre posicoes diferentes
	// talvez fazer com que so de para trocar jogadores entre as mesmas posicoes?

	// agora que temos todos os inputs do utilizador
	// vamos calcular o valor da transferencia e pedir 
	// confirmação ao utilizador
		
	float valorTransf = obterValorTransferencia(EQUIPAS[equipaEscolhida]->plantel->jogadores[jogadorEscolhido]);

	printf("Valor da transferencia: %.2f%s\n", valorTransf, SIMBOLO_EURO);
	printf("Os seus fundos: %.2f%s\n", EQUIPAS[INDICE_EQUIPA_JOGADOR]->fundos, SIMBOLO_EURO);

	if (EQUIPAS[INDICE_EQUIPA_JOGADOR]->fundos >= valorTransf) {

		printf("Realizar transferencia?\n0.NÃO\n1.SIM\n");

		int exit = 1, opcao = -1;

		while (exit) {

			imprimirCursor();
			scanf("%i", &opcao);
			getchar();

			switch (opcao) {

			case 1:

				trocaJogadores(EQUIPAS[INDICE_EQUIPA_JOGADOR], EQUIPAS[equipaEscolhida], jogadorATrocar, jogadorEscolhido, valorTransf);
				
				imprimirCabecalho("PARABÉNS!");
				printf("%s faz agora parte da sua equipa!\n", EQUIPAS[INDICE_EQUIPA_JOGADOR]->plantel->jogadores[jogadorATrocar]->nome);

				exit = 0;

				break;

			}

		}

	}
	else {

		printf("Não possui os fundos necessários para efectuar esta transferencia.\nTransferencia cancelada.\n");

	}
	
}

void iniciarMenuInformacao() {

	enum MENU_INFORMACAO opcao = MENU_INFORMACAO_OPCAO_NULA;
	
	imprimirCabecalho("INFORMACAO");

	while (opcao != MENU_INFORMACAO_OPCAO_SAIR) {
		
		int equipaEscolhida;
		int exit = 1;

		imprimirOpcao("%i: VOLTAR\n", MENU_INFORMACAO_OPCAO_SAIR);
		imprimirOpcao("%i: VER EQUIPAS\n", MENU_INFORMACAO_VER_OUTRAS);

		scanf("%i", &opcao);
		getchar();

		switch (opcao) {

		case MENU_INFORMACAO_VER_OUTRAS:

			while (exit) {

				imprimirInstrucao("Selecione uma equipa para ver mais informação:\n");
				listarEquipas();

				imprimirCursor();
				scanf("%i", &equipaEscolhida);
				getchar();

				if (equipaEscolhida > 0 && equipaEscolhida < NUMERO_EQUIPAS + 1) {

					equipaEscolhida = equipaEscolhida - 1;

					exit = 0;

				}
				else {

					printf("Opcao nao valida. Escolha de novo.\n");

				}

			}

			imprimeEquipa(EQUIPAS[equipaEscolhida]);
			imprimePlantel(EQUIPAS[equipaEscolhida]->plantel);
			imprimeEstadio(EQUIPAS[equipaEscolhida]->estadio);

			break;

		}

	}


}

void iniciarMenuSorteio() {
	enum MENU_SORTEIO opcao = MENU_SORTEIO_OPCAO_NULA;

	printf("AQUI FICA A TABELA DO RESULTADO DO SORTEIO");
	while (opcao != MENU_SORTEIO_OPCAO_SAIR) {
		imprimirTabelaSorteios();
		scanf("%i", &opcao);
		getchar();

		switch (opcao) {
		case MENU_SORTEIO_OPCAO_CONTINUAR:
			iniciarMenuDecorrerEpoca();
			break;
		case MENU_SORTEIO_OPCAO_SAIR:
			sairJogo();
			break;
		default:
			printf("OPÇÃO INVÁLIDA.");
			break;
		}
	}
}

void imprimirTabelaSorteios() {
	imprimirTitulo("Sorteio dos Jogos");

	imprimirOpcao("%i: CONTINUAR\n", MENU_SORTEIO_OPCAO_CONTINUAR);
	imprimirOpcao("%i: SAIR DO JOGO\n", MENU_SORTEIO_OPCAO_SAIR);

	imprimirSeparador();
	imprimirCursor();
}

void iniciarMenuDecorrerEpoca() {
	enum MENU_DECORRER_EPOCA opcao = MENU_DECORRER_EPOCA_OPCAO_NULA;

	while (opcao != MENU_DECORRER_EPOCA_OPCAO_SAIR) {
		imprimirMenuDecorrerEpoca();
		scanf("%i", &opcao);
		getchar();

		switch (opcao) {
		case MENU_DECORRER_EPOCA_OPCAO_VER_EQUIPA:
			iniciarMenuInformacao();
			break;
		case MENU_DECORRER_EPOCA_OPCAO_PROXIMA_JORNADA:
			iniciarMenuPreparacaoJogo();
			break;

		case MENU_DECORRER_EPOCA_OPCAO_SAIR:
			sairJogo();
			break;
		default:
			printf("OPÇÃO INVÁLIDA.");
			break;
		}
	}
}
void imprimirMenuDecorrerEpoca() {
	imprimirTitulo("Decorrer da Época");
	
	imprimirOpcao("%i: VER EQUIPAS E ESTATÍSTICAS\n", MENU_DECORRER_EPOCA_OPCAO_VER_EQUIPA);
	imprimirOpcao("%i: PRÓXIMA JORNADA\n", MENU_DECORRER_EPOCA_OPCAO_PROXIMA_JORNADA);
	imprimirOpcao("%i: SAIR DO JOGO\n", MENU_DECORRER_EPOCA_OPCAO_SAIR);

	imprimirSeparador();
	imprimirCursor();
}

void iniciarMenuPreparacaoJogo() {
	enum MENU_PREPARACAO_JOGO opcao = MENU_PREPARACAO_JOGO_OPCAO_NULA;

	while (opcao != MENU_PREPARACAO_JOGO_OPCAO_VOLTAR) {
		imprimirMenuPreparacaoJogo();
		scanf("%i", &opcao);
		getchar();

		switch (opcao) {
		case MENU_PREPARACAO_JOGO_OPCAO_TATICA:
			printf("ESCOLHA DE TATICA:");
			int checkTatica;
			char Tatica[6];
			do {
				printf("Inserir Tática (formato x-x-x):");
				scanf("%s", Tatica);
				checkTatica = VerificaTatica(Tatica);
			} while (checkTatica = 0);

			break;
		case MENU_PREPARACAO_JOGO_OPCAO_VOLTAR:
			//voltar atrás
			break;
		default:
			printf("OPÇÃO INVÁLIDA.");
			break;
		}
	}

}
void imprimirMenuPreparacaoJogo() {
	imprimirTitulo("Preparação para o Jogo");

	imprimirOpcao("%i: ESCOLHER TÁTICA\n", MENU_PREPARACAO_JOGO_OPCAO_TATICA);
	imprimirOpcao("%i: VOLTAR\n", MENU_PREPARACAO_JOGO_OPCAO_VOLTAR);

	imprimirSeparador();
	imprimirCursor();

}