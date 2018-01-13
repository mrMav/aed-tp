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

	printf("\nA sair do jogo....\n");

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

	system("cls");

	printf(titleArt);

	imprimirOpcao("%i: Sair do jogo\n", MENU_INICIAL_OPCAO_SAIR);
	imprimirOpcao("%i: Novo jogo\n", MENU_INICIAL_OPCAO_NOVO_JOGO);

	imprimirSeparador();
	imprimirCursor();

}

void iniciarMenuNovoJogo() {

	system("cls");

	int opcao = 0;
	int exit = 1;

	imprimirTitulo("Começar Novo Jogo");
	imprimirInstrucao("Escreva o seu nome:\n");
	imprimirCursor();
	gets(NOME_JOGADOR);

	system("cls");

	imprimirInstrucao("Escolha a sua equipa:\n\n");
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

			printf("Opção não válida. Escolha de novo.\n");
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

				printf("Total de transferências feitas!\n");

			}

			break;
		case MENU_PREPARACAO_EPOCA_OPCAO_INFORMACAO:

			iniciarMenuInformacao();

			break;
		case MENU_PREPARACAO_EPOCA_INICIAR_EPOCA:
			// INICIAR a época!
			epocaIniciada = 1;

			iniciarMenuDecorrerEpoca();

			break;
		}

	}

	sairJogo();

}

void imprimirMenuPreparacaoEpoca() {

	system("cls");

	char buffer[60];
	// guarda a string formatada no buffer
	snprintf(buffer, sizeof(buffer), "Preparação para a Época - %s - %s", EQUIPAS[INDICE_EQUIPA_JOGADOR]->nome, EQUIPAS[INDICE_EQUIPA_JOGADOR]->plantel->treinador->nome);

	imprimirTitulo(buffer);

	imprimirOpcao("%i: Sair do jogo\n", MENU_PREPARACAO_EPOCA_OPCAO_SAIR);
	imprimirOpcao("%i: Compra e venda de jogadores", MENU_PREPARACAO_EPOCA_OPCAO_TRANSFERENCIA_JOGADORES);
	printf(" (%i/%i)\n", nTransferencias, NUMERO_TRANSFERENCIAS);
	imprimirOpcao("%i: Ver equipas\n", MENU_PREPARACAO_EPOCA_OPCAO_INFORMACAO);
	imprimirOpcao("%i: Iniciar época\n", MENU_PREPARACAO_EPOCA_INICIAR_EPOCA);

	imprimirSeparador();
	imprimirCursor();

}

void iniciarMenuCompraEVenda(int *equipasSelecionadas) {

	system("cls");

	int equipaEscolhida = 0;
	int jogadorEscolhido = 0;
	int jogadorATrocar = 0;
	int exit = 1;

	imprimirTitulo("Compra e venda de jogadores");
	imprimirInstrucao("Para efectuar uma transferência, deve trocar um jogador por outro.\nComece por escolher a equipa a que pretende ir buscar o novo jogador:\n\n");
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

					printf("Opção inválida! Já comprou jogadores à equipa %s.\n", EQUIPAS[equipaEscolhida - 1]->nome);

				}

			}
			else {

				printf("Opção inválida! Não existe equipa número %i.\n", equipaEscolhida);

			}

		}
		else {

			printf("Opção inválida! Não pode comprar jogadores à sua própria equipa.\n");

		}

	}

	imprimirInstrucao("Escolha o jogador:\n\n");
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

			printf("Opção inválida. Não existe jogador número %i.\n", jogadorEscolhido);

		}

	}

	imprimirInstrucao("Escolha o jogador da SUA equipa para TROCAR:\n\n");
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

			printf("Opão inválida. Escolha de novo.\n");

		}

	}

	// ATENCAO: com este modelo é possivel trocar entre posicoes diferentes
	// talvez fazer com que so de para trocar jogadores entre as mesmas posicoes?

	// agora que temos todos os inputs do utilizador
	// vamos calcular o valor da transferencia e pedir 
	// confirmação ao utilizador

	float valorTransf = obterValorTransferencia(EQUIPAS[equipaEscolhida]->plantel->jogadores[jogadorEscolhido]);

	printf("Valor da transferência: %.2f%s\n", valorTransf, SIMBOLO_EURO);
	printf("Os seus fundos: %.2f%s\n", EQUIPAS[INDICE_EQUIPA_JOGADOR]->fundos, SIMBOLO_EURO);

	if (EQUIPAS[INDICE_EQUIPA_JOGADOR]->fundos >= valorTransf) {

		printf("Realizar transferência?\n0:NÃO\n1:SIM\n");

		int exit = 1, opcao = -1;

		while (exit) {

			imprimirCursor();
			scanf("%i", &opcao);
			getchar();

			switch (opcao) {

			case 1:

				trocaJogadores(EQUIPAS[INDICE_EQUIPA_JOGADOR], EQUIPAS[equipaEscolhida], jogadorATrocar, jogadorEscolhido, valorTransf);

				system("cls");

				imprimirCabecalho("PARABÉNS!");
				printf("%s faz agora parte da sua equipa!\n", EQUIPAS[INDICE_EQUIPA_JOGADOR]->plantel->jogadores[jogadorATrocar]->nome);

				Sleep(3000);

				exit = 0;

				break;

			}

		}

	}
	else {

		printf("Não possui os fundos necessários para efectuar esta transferência.\nTransferência foi cancelada.\n");
		iniciarPrimirParaContinuar();
		

	}

}

void iniciarMenuInformacao() {

	enum MENU_INFORMACAO opcao = MENU_INFORMACAO_OPCAO_NULA;

	while (opcao != MENU_INFORMACAO_OPCAO_SAIR) {

		int equipaEscolhida;
		int exit = 1;

		system("cls");
		imprimirCabecalho("Informação");
		imprimirOpcao("%i: Voltar\n", MENU_INFORMACAO_OPCAO_SAIR);
		imprimirOpcao("%i: Ver equipas\n", MENU_INFORMACAO_VER_EQUIPAS);
		imprimirOpcao("%i: Ver jornada\n", MENU_INFORMACAO_VER_JORNADA);
		imprimirOpcao("%i: Ver sorteio\n", MENU_INFORMACAO_VER_SORTEIO);

		imprimirCursor();

		scanf("%i", &opcao);
		getchar();

		switch (opcao) {

		case MENU_INFORMACAO_VER_EQUIPAS:

			while (exit) {

				imprimirInstrucao("Selecione uma equipa para ver mais informações:\n");
				listarEquipas();

				imprimirCursor();
				scanf("%i", &equipaEscolhida);
				getchar();

				if (equipaEscolhida > 0 && equipaEscolhida < NUMERO_EQUIPAS + 1) {

					equipaEscolhida = equipaEscolhida - 1;

					exit = 0;

				}
				else {

					printf("Opção inválida. Escolha de novo.\n");

				}

			}

			imprimeEquipa(EQUIPAS[equipaEscolhida]);
			imprimePlantel(EQUIPAS[equipaEscolhida]->plantel);
			imprimeEstadio(EQUIPAS[equipaEscolhida]->estadio);

			iniciarPrimirParaContinuar();

			break;

		case MENU_INFORMACAO_VER_JORNADA:

			imprimirJornada(nJornada);

			break;

		case MENU_INFORMACAO_VER_SORTEIO:

			imprimirTabelaSorteios();

			break;

		}

	}


}

void imprimirTabelaSorteios() {

	system("cls");

	imprimirTitulo("Sorteio dos Jogos");

	imprimirEpoca();

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
			printf("Opção inválida.\n");
			break;
		}
	}
}

void imprimirMenuDecorrerEpoca() {

	system("cls");

	imprimirTitulo("Decorrer da Época");

	imprimirOpcao("%i: Sair do jogo\n", MENU_DECORRER_EPOCA_OPCAO_SAIR);
	imprimirOpcao("%i: Ver equipas\n", MENU_DECORRER_EPOCA_OPCAO_VER_EQUIPA);

	char buffer[50];
	snprintf(buffer, sizeof(buffer), "%i: Iniciar jornada %i\n", MENU_DECORRER_EPOCA_OPCAO_PROXIMA_JORNADA, nJornada + 1);
	imprimirOpcao(buffer, 0);

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

			iniciarMenuEscolhaDeTatica();

			break;
		case MENU_PREPARACAO_JOGO_OPCAO_VOLTAR:
			//voltar atrás
			break;
		default:
			printf("Opção inválida.");
			break;
		}
	}

}

void iniciarMenuEscolhaDeTatica() {

	system("cls");

	imprimirTitulo("Escolha de tática");

	int checkTatica = 0;
	char Tatica[6];
	int opcao;
	Jogador* j;
	char buffer[50];

	while (checkTatica == 0) {

		imprimirInstrucao("Inserir tática (formato x-x-x):\n");
		imprimirCursor();
		scanf("%s", Tatica);

		checkTatica = VerificaTatica(Tatica);

	}

	/*

	Cada jogador tem uma array[2] chamado estado de jogo.
	Esse array guarda as posições em que os jogadores estão a jogar.
	Abaixo é pedido ao jogador para colocar jogadores nas posições
	que escolheu acima.

	As opções válidas são:
	1 - Guarda-Redes
	2 - Desefa
	3 - Médio
	4 - Avançado

	O array é de duas dimensões, pois cada array[0] é usado na primeira
	parte, e array[1] é usado na segunda parte do confronto.

	*/

	// ESCOLHER UMA NOVA TÁTICA, FAZ RESET À ANTERIOR
	resetEstadoJogo(EQUIPAS[INDICE_EQUIPA_JOGADOR]);

	//escolher gr
	imprimirInstrucao("Escolher 1 Guarda-Redes:\n\n");

	listarJogadoresAindaNaoEscolhidosParaJogo(0);  // zero é a primeira parte  
	j = escolherJogador(EQUIPAS[INDICE_EQUIPA_JOGADOR]);
	// marcar este jogador como guarda redes:
	j->estadoEmJogo[0] = POSICAO_GR;

	// escolher defesas
	snprintf(buffer, sizeof(buffer), "Escolher %c Defesas:\n\n", Tatica[0]);
	imprimirInstrucao(buffer);
	listarJogadoresAindaNaoEscolhidosParaJogo(0);  // zero é a primeira parte
	int n = Tatica[0] - '0';
	for (int i = 0; i < n; i++) {

		j = escolherJogador(EQUIPAS[INDICE_EQUIPA_JOGADOR]);
		j->estadoEmJogo[0] = POSICAO_DEF;

	}

	snprintf(buffer, sizeof(buffer), "Escolher %c Médios:\n\n", Tatica[2]);
	imprimirInstrucao(buffer);
	listarJogadoresAindaNaoEscolhidosParaJogo(0);  // zero é a primeira parte
	n = Tatica[2] - '0';
	for (int i = 0; i < n; i++) {

		j = escolherJogador(EQUIPAS[INDICE_EQUIPA_JOGADOR]);
		j->estadoEmJogo[0] = POSICAO_MED;

	}

	snprintf(buffer, sizeof(buffer), "Escolher %c Avançados:\n\n", Tatica[4]);
	imprimirInstrucao(buffer);
	listarJogadoresAindaNaoEscolhidosParaJogo(0);  // zero é a primeira parte
	n = Tatica[4] - '0';
	for (int i = 0; i < n; i++) {

		j = escolherJogador(EQUIPAS[INDICE_EQUIPA_JOGADOR]);
		j->estadoEmJogo[0] = POSICAO_AV;

	}

	listarJogadoresEscolhidosAJogo();
	iniciarPrimirParaContinuar();

}

void imprimirMenuPreparacaoJogo() {

	system("cls");

	imprimirTitulo("Preparação para o Jogo");
	
	imprimirOpcao("%i: Escolher tática\n", MENU_PREPARACAO_JOGO_OPCAO_TATICA);
	imprimirOpcao("%i: Voltar\n", MENU_PREPARACAO_JOGO_OPCAO_VOLTAR);

	imprimirSeparador();
	imprimirCursor();
}

void iniciarMenuIntervaloJogo() {
	enum MENU_INTERVALO_JOGO opcao = MENU_INTERVALO_JOGO_OPCAO_NULA;

	while (opcao != MENU_INTERVALO_JOGO_OPCAO_JOGAR_2PARTE) {
		imprimirMenuIntervaloJogo();
		scanf("%i", &opcao);
		getchar();

		switch (opcao) {
		case MENU_INTERVALO_JOGO_OPCAO_ALTERAR_TATICA:
			//MENU TATICA
			break;
		case MENU_INTERVALO_JOGO_OPCAO_SUBSTITUICOES:
			//SUBSTITUICOES
			break;
		case MENU_INTERVALO_JOGO_OPCAO_JOGAR_2PARTE:
			//JOGAR 2º PARTE
			break;
		default:
			printf("Opção inválida.");
			break;
		}
	}

}

void imprimirMenuIntervaloJogo() {
	imprimirTitulo("Intervalo");

	imprimirOpcao("%i: Alterar tática\n", MENU_INTERVALO_JOGO_OPCAO_ALTERAR_TATICA);
	imprimirOpcao("%i: Substituições\n", MENU_INTERVALO_JOGO_OPCAO_SUBSTITUICOES);
	imprimirOpcao("%i: Jogar 2ª parte.\n", MENU_INTERVALO_JOGO_OPCAO_JOGAR_2PARTE);

	imprimirSeparador();
	imprimirCursor();
}

void iniciarMenuFinalJogo() {
	enum MENU_FINAL_JOGO opcao = MENU_FINAL_JOGO_OPCAO_NULA;

	printf("AQUI FICA O RESULTADO FINAL DO JOGO");
	while (opcao != MENU_FINAL_JOGO_OPCAO_CONTINUAR) {
		scanf("%i", &opcao);
		getchar();

		switch (opcao) {
		case MENU_FINAL_JOGO_OPCAO_CONTINUAR:
			iniciarMenuResumoJornada();
			break;
		default:
			printf("Opção inválida.");
			break;
		}
	}
}

void iniciarMenuResumoJornada() {
	enum MENU_RESUMO_JORNADA opcao = MENU_RESUMO_JORNADA_OPCAO_NULA;

	printf("RESULTADOS DOS JOGOS");
	printf("TABELA DE CLASSIFICAÇÃO");
	while (opcao != MENU_RESUMO_JORNADA_OPCAO_CONTINUAR) {
		scanf("%i", &opcao);
		getchar();

		switch (opcao) {
		case MENU_RESUMO_JORNADA_OPCAO_CONTINUAR:
			//CONTINUAR
			break;
		default:
			printf("Opção inválida.");
			break;
		}
	}
}