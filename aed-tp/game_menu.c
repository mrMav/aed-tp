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

	printf("\nObrigado por jogares FUTASTIC\n Volta sempre....\n");

	Sleep(3000);

	exit(0);
}

void iniciarMenuInicial() {

	system("cls");

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

	imprimirOpcao("%i: Novo jogo\n", MENU_INICIAL_OPCAO_NOVO_JOGO);
	imprimirOpcao("%i: Sair do jogo\n", MENU_INICIAL_OPCAO_SAIR);

	imprimirSeparador();
	imprimirCursor();

}

void iniciarMenuNovoJogo() {

	int opcao = 0;
	int exit = 1;

	system("cls");

	imprimirTitulo("Come�ar Novo Jogo");
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

			// vou guardar tamb�m uma referencia � equipa
			equipaJogador = EQUIPAS[INDICE_EQUIPA_JOGADOR];
			fazerOnzeAleatorio(equipaJogador);

			exit = 0;

		}
		else {

			printf("Op��o n�o v�lida. Escolha de novo.\n");
			imprimirInstrucao("Escolha a sua equipa:\n");
			listarEquipas();

		}

	}

	system("cls");

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

			system("cls");

			if (nTransferencias < NUMERO_TRANSFERENCIAS) {

				iniciarMenuCompraEVenda(equipasSeleciondasTransferencias);

			}
			else {

				printf("Total de transfer�ncias feitas!\n");

			}

			break;
		case MENU_PREPARACAO_EPOCA_OPCAO_INFORMACAO:

			iniciarMenuInformacao();

			break;
		case MENU_PREPARACAO_EPOCA_INICIAR_EPOCA:
			// INICIAR a �poca!
			epocaIniciada = 1;
			fazerOnzeAleatorio(equipaJogador);
			iniciarMenuDecorrerEpoca();

			break;
		}

	}

	sairJogo();

}

void imprimirMenuPreparacaoEpoca() {


	char buffer[60];
	// guarda a string formatada no buffer
	snprintf(buffer, sizeof(buffer), "Prepara��o para a �poca - %s - %s", EQUIPAS[INDICE_EQUIPA_JOGADOR]->nome, EQUIPAS[INDICE_EQUIPA_JOGADOR]->plantel->treinador->nome);

	imprimirTitulo(buffer);

	imprimirOpcao("%i: Compra e venda de jogadores", MENU_PREPARACAO_EPOCA_OPCAO_TRANSFERENCIA_JOGADORES);
	printf(" (%i/%i)\n", nTransferencias, NUMERO_TRANSFERENCIAS);
	imprimirOpcao("%i: Ver equipas\n", MENU_PREPARACAO_EPOCA_OPCAO_INFORMACAO);
	imprimirOpcao("%i: Iniciar �poca\n", MENU_PREPARACAO_EPOCA_INICIAR_EPOCA);
	imprimirOpcao("%i: Sair do jogo\n", MENU_PREPARACAO_EPOCA_OPCAO_SAIR);


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
	imprimirInstrucao("Para efectuar uma transfer�ncia, deve trocar um jogador por outro.\nComece por escolher a equipa a que pretende ir buscar o novo jogador:\n\n");
	listarEquipas();

	while (exit) {

		imprimirCursor();
		scanf("%i", &equipaEscolhida);
		getchar();

		if (equipaEscolhida != INDICE_EQUIPA_JOGADOR + 1) {

			if (equipaEscolhida > 0 && equipaEscolhida < NUMERO_EQUIPAS + 1) {

				int transValida = 1;

				// verificar se o utilizador j� n�o comprou a esta equipa
				int i;
				for (i = 0; i < NUMERO_TRANSFERENCIAS; i++) {

					if (equipaEscolhida - 1 == equipasSelecionadas[i]) {

						transValida = 0;

					}

				}

				if (transValida) {

					equipaEscolhida = equipaEscolhida - 1;

					// guardar indice da equipa escolhida neste array
					// este array � verificado para s� ser possivel escolher um jogador de cada equipa
					equipasSelecionadas[nTransferencias] = equipaEscolhida;

					exit = 0;

				}
				else {

					printf("Op��o inv�lida! J� comprou jogadores � equipa %s.\n", EQUIPAS[equipaEscolhida - 1]->nome);

				}

			}
			else {

				printf("Op��o inv�lida! N�o existe equipa n�mero %i.\n", equipaEscolhida);

			}

		}
		else {

			printf("Op��o inv�lida! N�o pode comprar jogadores � sua pr�pria equipa.\n");

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

			printf("Op��o inv�lida. N�o existe jogador n�mero %i.\n", jogadorEscolhido);

		}

	}

	system("cls");

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

			printf("Op�o inv�lida. Escolha de novo.\n");

		}

	}

	// ATENCAO: com este modelo � possivel trocar entre posicoes diferentes
	// talvez fazer com que so de para trocar jogadores entre as mesmas posicoes?

	// agora que temos todos os inputs do utilizador
	// vamos calcular o valor da transferencia e pedir 
	// confirma��o ao utilizador

	float valorTransf = obterValorTransferencia(EQUIPAS[equipaEscolhida]->plantel->jogadores[jogadorEscolhido]);

	printf("Pretende trocar %s por %s\n", EQUIPAS[INDICE_EQUIPA_JOGADOR]->plantel->jogadores[jogadorATrocar], EQUIPAS[equipaEscolhida]->plantel->jogadores[jogadorEscolhido]);
	printf("Valor da transfer�ncia: %.2f%s\n", valorTransf, SIMBOLO_EURO);
	printf("Os seus fundos: %.2f%s\n", EQUIPAS[INDICE_EQUIPA_JOGADOR]->fundos, SIMBOLO_EURO);

	if (EQUIPAS[INDICE_EQUIPA_JOGADOR]->fundos >= valorTransf) {

		printf("Realizar transfer�ncia?\n0:N�O\n1:SIM\n");

		int exit = 1, opcao = -1;

		while (exit) {

			imprimirCursor();
			scanf("%i", &opcao);
			getchar();

			switch (opcao) {
			case 0:
				// FALTA INSERIR AQUI QUALQUER COISA PARA VOLTAR AO MenuPreparacaoEpoca() SEM ACRESCENTAR AO NUMERO DAS TRANSFER�NCIAS

				break;

			case 1:

				trocaJogadores(EQUIPAS[INDICE_EQUIPA_JOGADOR], EQUIPAS[equipaEscolhida], jogadorATrocar, jogadorEscolhido, valorTransf);

				system("cls");

				imprimirCabecalho("PARAB�NS!");
				printf("%s faz agora parte da sua equipa!\n", EQUIPAS[INDICE_EQUIPA_JOGADOR]->plantel->jogadores[jogadorATrocar]->nome);

				exit = 0;

				break;

			}

		}

	}
	else {

		printf("N�o possui os fundos necess�rios para efectuar esta transfer�ncia.\nTransfer�ncia foi cancelada.\n");
		iniciarPrimirParaContinuar();


	}

}

void iniciarMenuInformacao() {

	enum MENU_INFORMACAO opcao = MENU_INFORMACAO_OPCAO_NULA;

	while (opcao != MENU_INFORMACAO_OPCAO_SAIR) {

		int equipaEscolhida;
		int exit = 1;

		system("cls");
		imprimirCabecalho("Informa��o");
		imprimirOpcao("%i: Ver equipas\n", MENU_INFORMACAO_VER_EQUIPAS);
		imprimirOpcao("%i: Ver jornada\n", MENU_INFORMACAO_VER_JORNADA);
		imprimirOpcao("%i: Ver sorteio\n", MENU_INFORMACAO_VER_SORTEIO);
		imprimirOpcao("%i: Voltar\n", MENU_INFORMACAO_OPCAO_SAIR);

		imprimirCursor();

		scanf("%i", &opcao);
		getchar();

		switch (opcao) {

		case MENU_INFORMACAO_VER_EQUIPAS:

			while (exit) {

				imprimirInstrucao("Selecione uma equipa para ver mais informa��es:\n");
				listarEquipas();

				imprimirCursor();
				scanf("%i", &equipaEscolhida);
				getchar();

				if (equipaEscolhida > 0 && equipaEscolhida < NUMERO_EQUIPAS + 1) {

					equipaEscolhida = equipaEscolhida - 1;

					exit = 0;

				}
				else {

					printf("Op��o inv�lida. Escolha de novo.\n");

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
			printf("Op��o inv�lida.\n");
			break;
		}
	}
}

void imprimirMenuDecorrerEpoca() {

	system("cls");

	imprimirTitulo("Decorrer da �poca");

	imprimirOpcao("%i: Ver equipas\n", MENU_DECORRER_EPOCA_OPCAO_VER_EQUIPA);
	imprimirOpcao("%i: Sair do jogo\n", MENU_DECORRER_EPOCA_OPCAO_SAIR);

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
			iniciarMenuJogo();

			break;
		case MENU_PREPARACAO_JOGO_OPCAO_VOLTAR:
			//voltar atr�s
			break;
		default:
			printf("Op��o inv�lida.");
			break;
		}
	}

}

void iniciarMenuEscolhaDeTatica() {


	system("cls");

	imprimirTitulo("Escolha de t�tica");

	int rndOrNot = -1;
	int exit = 1;

	printf("\n Manter o seu onze actual, escolher aleat�riamente, ou fazer 11 manualmente?\n");
	printf("\n0.Manter\n1.Aleat�riamente\n2.Manualmente\n");
	while (exit) {

		imprimirCursor();

		scanf("%i", &rndOrNot);

		switch (rndOrNot) {
		case 0:
			exit = 0;
			break;
		case 1:
			exit = 0;
			break;
		case 2:
			exit = 0;
			break;

		}
	}

	if (rndOrNot == 0) {

		return;

	}
	else if (rndOrNot == 1) {

		fazerOnzeAleatorio(equipaJogador);

	}
	else if(rndOrNot == 2){

		// permite ao jogador fazer o seu onze

		int checkTatica = 0;
		char Tatica[6];
		int opcao;
		Jogador* j;
		char buffer[50];

		while (checkTatica == 0) {

			imprimirInstrucao("Inserir t�tica (formato x-x-x):\n");
			imprimirCursor();
			scanf("%s", Tatica);

			checkTatica = VerificaTatica(Tatica);

		}

		/*

		Cada jogador tem uma array[2] chamado estado de jogo.
		Esse array guarda as posi��es em que os jogadores est�o a jogar.
		Abaixo � pedido ao jogador para colocar jogadores nas posi��es
		que escolheu acima.

		As op��es v�lidas s�o:
		1 - Guarda-Redes
		2 - Desefa
		3 - M�dio
		4 - Avan�ado

		O array � de duas dimens�es, pois cada array[0] � usado na primeira
		parte, e array[1] � usado na segunda parte do confronto.

		*/

		// ESCOLHER UMA NOVA T�TICA, FAZ RESET � ANTERIOR
		resetEstadoJogo(equipaJogador);

		//escolher gr
		imprimirInstrucao("Escolher 1 Guarda-Redes:\n\n");

		listarJogadoresAindaNaoEscolhidosParaJogo(0);  // zero � a primeira parte  
		j = escolherJogador(EQUIPAS[INDICE_EQUIPA_JOGADOR]);
		// marcar este jogador como guarda redes:
		j->estadoEmJogo[0] = POSICAO_GR;

		// escolher defesas
		snprintf(buffer, sizeof(buffer), "Escolher %c Defesas:\n\n", Tatica[0]);
		imprimirInstrucao(buffer);
		listarJogadoresAindaNaoEscolhidosParaJogo(0);  // zero � a primeira parte
		int n = Tatica[0] - '0';
		for (int i = 0; i < n; i++) {

			j = escolherJogador(EQUIPAS[INDICE_EQUIPA_JOGADOR]);
			j->estadoEmJogo[0] = POSICAO_DEF;

		}

		snprintf(buffer, sizeof(buffer), "Escolher %c M�dios:\n\n", Tatica[2]);
		imprimirInstrucao(buffer);
		listarJogadoresAindaNaoEscolhidosParaJogo(0);  // zero � a primeira parte
		n = Tatica[2] - '0';
		for (int i = 0; i < n; i++) {

			j = escolherJogador(EQUIPAS[INDICE_EQUIPA_JOGADOR]);
			j->estadoEmJogo[0] = POSICAO_MED;

		}

		snprintf(buffer, sizeof(buffer), "Escolher %c Avan�ados:\n\n", Tatica[4]);
		imprimirInstrucao(buffer);
		listarJogadoresAindaNaoEscolhidosParaJogo(0);  // zero � a primeira parte
		n = Tatica[4] - '0';
		for (int i = 0; i < n; i++) {

			j = escolherJogador(EQUIPAS[INDICE_EQUIPA_JOGADOR]);
			j->estadoEmJogo[0] = POSICAO_AV;

		}

	}

}

void imprimirMenuPreparacaoJogo() {

	system("cls");

	imprimirTitulo("Prepara��o para o Jogo");

	imprimirOpcao("%i: Escolher t�tica\n", MENU_PREPARACAO_JOGO_OPCAO_TATICA);
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
			//JOGAR 2� PARTE
			break;
		default:
			printf("Op��o inv�lida.");
			break;
		}
	}

}

void imprimirMenuIntervaloJogo() {
	imprimirTitulo("Intervalo");

	imprimirOpcao("%i: Alterar t�tica\n", MENU_INTERVALO_JOGO_OPCAO_ALTERAR_TATICA);
	imprimirOpcao("%i: Substitui��es\n", MENU_INTERVALO_JOGO_OPCAO_SUBSTITUICOES);
	imprimirOpcao("%i: Jogar 2� parte\n", MENU_INTERVALO_JOGO_OPCAO_JOGAR_2PARTE);
	imprimirOpcao("%i: Sair\n", MENU_INTERVALO_JOGO_OPCAO_SAIR);

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
			printf("Op��o inv�lida.");
			break;
		}
	}
}

void iniciarMenuResumoJornada() {
	enum MENU_RESUMO_JORNADA opcao = MENU_RESUMO_JORNADA_OPCAO_NULA;

	printf("RESULTADOS DOS JOGOS");
	printf("TABELA DE CLASSIFICA��O");
	while (opcao != MENU_RESUMO_JORNADA_OPCAO_CONTINUAR) {
		scanf("%i", &opcao);
		getchar();

		switch (opcao) {
		case MENU_RESUMO_JORNADA_OPCAO_CONTINUAR:
			//CONTINUAR
			break;
		default:
			printf("Op��o inv�lida.");
			break;
		}
	}
}

void iniciarMenuJogo() {

	enum MENU_INICIAR_JOGO opcao = MENU_INICIAR_JOGO_OPCAO_NULA;

	// obter o jogo do jogador correspondente a esta jornada
	Jogo* jogo = obterJogoJogadorNaJornada(nJornada);

	// obter referencia � equipa do jogador e � oponente
	Equipa *oponente;

	// basicamente vou ver qual das equipas do jogo � a oponente ao jogador
	// estou a comparar as letras do sorteio
	if (jogo->equipaA == equipaJogador->letraSorteio)
		oponente = obterEquipaPorLetraSorteio(EQUIPAS, jogo->equipaB);
	else
		oponente = obterEquipaPorLetraSorteio(EQUIPAS, jogo->equipaA);

	// agora o oponente vai escolher um onze
	fazerOnzeAleatorio(oponente);

	while (1) {

		system("cls");

		imprimirAnteJogo(jogo);
		imprimirMenuAnteJogo();

		scanf("%i", &opcao);
		getchar();

		switch (opcao) {
		case MENU_INICIAR_JOGO_OPCAO_VER_MEU_ONZE:

			system("cls");
			imprimirOnzeDefinido(equipaJogador);
			iniciarPrimirParaContinuar();

			break;
		case MENU_INICIAR_JOGO_OPCAO_VER_ONZE_OPONENTE:

			system("cls");
			imprimirOnzeDefinido(oponente);
			iniciarPrimirParaContinuar();

			break;
		case MENU_INICIAR_JOGO_OPCAO_JOGAR_PARTIDA:

			break;

		}

	}

}

void imprimirMenuAnteJogo() {
	
	printf("\n\n");

	imprimirOpcao("%i: Ver o meu onze\n", MENU_INICIAR_JOGO_OPCAO_VER_MEU_ONZE);
	imprimirOpcao("%i: Ver o onze oponente\n", MENU_INICIAR_JOGO_OPCAO_VER_ONZE_OPONENTE);
	imprimirOpcao("%i: Jogar a 1� parte\n", MENU_INICIAR_JOGO_OPCAO_JOGAR_PARTIDA);
	imprimirOpcao("%i: Sair\n", MENU_INICIAR_JOGO_OPCAO_SAIR);

	imprimirSeparador();
	imprimirCursor();

};