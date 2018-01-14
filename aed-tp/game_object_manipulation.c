#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "game_typedefs.h"
#include "game_constants.h"
#include "game_globals.h"
#include "game_utils.h"
#include "game_information_output.h"
#include "game_object_creation.h"

/*
Funcoes para manipular objectos e informacao do jogo
*/

/*
Adiciona o jogador no plantel.
Return 0: fail
Return 1: sucess
*/
int adicionarJogadorAPlantel(Plantel* plantel, Jogador* jogador) {

	// verificar se plantel está cheio:
	if (plantel->numeroActualJogadores == NUMERO_JOGADORES_PLANTEL) {

		return 0;

	}

	// nesta fase, podemos adicionar o jogador ao ultimo indice disponivel:

	int indice = plantel->numeroActualJogadores;

	plantel->jogadores[indice] = jogador;
	plantel->numeroActualJogadores++;  // passo muito importante.

	return 1;

};

/*
Retorna a equipa por nome.
NULL caso não seja encontrada
*/
Equipa* obterEquipaPorNome(Equipa* EQUIPAS[], char string[]) {

	int i;

	for (i = 0; i < NUMERO_EQUIPAS; i++) {

		if (strcmp(string, EQUIPAS[i]->nome) == 0) {

			return EQUIPAS[i];

		}

	}

	// caso a equipa não seja encontrada:
	return NULL;

};

/*
Retorna a equipa por letra do sorteio.
NULL caso não seja encontrada
*/
Equipa* obterEquipaPorLetraSorteio(Equipa* EQUIPAS[], char letra) {

	int i;

	for (i = 0; i < NUMERO_EQUIPAS; i++) {

		if (letra == EQUIPAS[i]->letraSorteio) {

			return EQUIPAS[i];

		}

	}

	// caso a equipa não seja encontrada:
	return NULL;

};

/*
Troca dois jogadores um por outro
Equipa 1 é a equipa que paga
*/
void trocaJogadores(Equipa* equipa1, Equipa* equipa2, int indice1, int indice2, float valorTransf) {

	// guardar jogador1 num buffer
	Jogador* bufferJogador1 = equipa1->plantel->jogadores[indice1];
	//printf("jogador no buffer:%s\n", bufferJogador1->nome);

	// colocar jogador2 na equipa1
	equipa1->plantel->jogadores[indice1] = equipa2->plantel->jogadores[indice2];
	//printf("jogador no posto na equipa1:%s\n", equipa1->plantel->jogadores[indice1]->nome);

	// colocar buffer na equipa2
	equipa2->plantel->jogadores[indice2] = bufferJogador1;
	//printf("jogador no posto na equipa2:%s\n", equipa2->plantel->jogadores[indice2]->nome);

	//actualizar o vencimento do jogador transferido
	equipa1->plantel->jogadores[indice1]->vencimentoMensal *= 1.5;

	// subtrair aos fundos da equipa a compra
	equipa1->fundos -= valorTransf;

	// adicionar aos fundos da equipa que vende
	equipa2->fundos += valorTransf;

	nTransferencias++;

};

/*
Retorna o valor da transferencia de um jogador
*/
float obterValorTransferencia(Jogador* j) {

	// a formula para o valor da transferencia é dado por:
	// Salário * 5 * número de meses de contrato que faltam cumprir

	float valor;

	// calcular o numero de meses que faltam
	// mktime devolve o tempo em ms desde 1970 (unix epoch)
	// talvez não esteja totalmente correcto porque nao sabemos
	// se o sistema que estamos a correr usa o unix epoch...

	time_t dataContractoMs = mktime(j->dataContracto);
	time_t dataFimContractoMs = mktime(j->dataFimContracto);

	time_t diffms = difftime(dataFimContractoMs, dataContractoMs);

	struct tm *diff = gmtime(&diffms);
	diff->tm_year -= 70; // subtrair 70 por causa do unix epoch

	int mesesDeContractoEmFalta = diff->tm_year * 12 + diff->tm_mon + 1;  // ignoramos os dias

	// calcular valor final
	valor = j->vencimentoMensal * 5 * mesesDeContractoEmFalta;

	return valor;

};

void atribuirLetrasSorteio() {

	// letras necessárias
	char alfabeto[] = "ABCDEFGHIJKLMNOPQR";

	// baralhar
	for (int i = 0; i < (int)strlen(alfabeto); i++) {

		int rnd = randomInt(0, strlen(alfabeto) - 1);

		char tmp = alfabeto[i];

		alfabeto[i] = alfabeto[rnd];
		alfabeto[rnd] = tmp;

	}

	// alfabeto está agora baralhado
	// vamos atribuir uma letra a cada equipa
	for (int j = 0; j < NUMERO_EQUIPAS; j++) {

		EQUIPAS[j]->letraSorteio = alfabeto[j];

	}

}

Jogador* escolherJogador(Equipa* e) {

	int exit = 1, option;

	imprimirInstrucao("Escolha o jogador:\n\n");

	while (exit) {

		imprimirCursor();
		scanf("%i", &option);
		getchar();

		if (option > 0 && option < NUMERO_JOGADORES_PLANTEL + 1) {

			option = option - 1;

			exit = 0;


		}
		else {

			printf("Opcao não válida. Não existe jogador número %i.\n", option);

		}

	}

	return e->plantel->jogadores[option];

}

void resetEstadoJogo(Equipa* e) {

	for (int i = 0; i < NUMERO_JOGADORES_PLANTEL; i++) {

		e->plantel->jogadores[i]->estadoEmJogo[0] = 0;
		e->plantel->jogadores[i]->estadoEmJogo[1] = 0;

	}

};

/*
Retorna o jogo em que o jogador participa, na jornada actual
*/
Jogo* obterJogoJogadorNaJornada(int nJornada) {

	// vamos correr todos os jogos da jornada
	for (int i = 0; i < (sizeof(JORNADAS[0]) / sizeof(JORNADAS[0][0])); i++) {

		if (JORNADAS[nJornada][i]->equipaA == EQUIPAS[INDICE_EQUIPA_JOGADOR]->letraSorteio ||
			JORNADAS[nJornada][i]->equipaB == EQUIPAS[INDICE_EQUIPA_JOGADOR]->letraSorteio) {

			return JORNADAS[nJornada][i];

		}

	}

	// if it comes to this, we are in deep shit
	return NULL;

}

/*
Obter array com jogadores de uma certa posição
*/
void obterJogadoresComPosição(Jogador* jogadores[], Equipa* equipa, char posicao[]) {

	int count = 0;

	for (int i = 0; i < NUMERO_JOGADORES_PLANTEL; i++) {

		if (strstr(equipa->plantel->jogadores[i]->posicao, posicao) != NULL) {  // strstr procura uma substring noutra

			jogadores[count] = equipa->plantel->jogadores[i];
			count++;

		}

	}

	jogadores[count] = NULL;

};

/*
Obter jogador aleatorio de array
*/
Jogador* obterJogadorAleatorioDeArray(Jogador* jogadores[]) {

	int count = 0;

	while (jogadores[count] != NULL) {

		count++;

	}

	return jogadores[randomInt(0, count - 1)];

};

/*
Baralha uma array de jogares
*/
void baralharArrayJogadores(Jogador* jogadores[]) {

	int count = 0;

	while (jogadores[count] != NULL) {

		count++;

	}

	for (int i = 0; i < count; i++) {

		int rnd = randomInt(0, count - 1);

		Jogador* tmp = jogadores[i];

		jogadores[i] = jogadores[rnd];
		jogadores[rnd] = tmp;

	}

};

/*
Organiza aleatoriamente o 11 da equipa do argumento
*/
void fazerOnzeAleatorio(Equipa* equipa) {

	resetEstadoJogo(equipa);

	// agora, escolher uma estratégia
	char *taticas[5];
	taticas[0] = "3-4-3";
	taticas[1] = "4-4-2";
	taticas[2] = "4-3-3";
	taticas[3] = "4-5-1";
	taticas[4] = "5-3-2";

	char tatica[6];
	strcpy(tatica, taticas[randomInt(0, 4)]);

	// criar buffer para pesquisa de jogadores
	Jogador* bufferDeJogadores[20];
	obterJogadoresComPosição(bufferDeJogadores, equipa, "GR");

	// posicao 0 é o GR principal... vá, não vamos deixar ninguém em desvantagem
	bufferDeJogadores[0]->estadoEmJogo[0] = POSICAO_GR;

	// escolher defesas
	Jogador* bufferDeJogadoresDEF[20];
	obterJogadoresComPosição(bufferDeJogadoresDEF, equipa, "DEF");
	baralharArrayJogadores(bufferDeJogadoresDEF);

	for (int i = 0; i < (int)(tatica[0] - '0'); i++) {

		bufferDeJogadoresDEF[i]->estadoEmJogo[0] = POSICAO_DEF;

	}

	// escolher medios
	Jogador* bufferDeJogadoresMED[20];
	obterJogadoresComPosição(bufferDeJogadoresMED, equipa, "MED");
	baralharArrayJogadores(bufferDeJogadoresMED);

	for (int i = 0; i < (int)(tatica[2] - '0'); i++) {

		bufferDeJogadoresMED[i]->estadoEmJogo[0] = POSICAO_MED;

	}

	// escolher avancados
	Jogador* bufferDeJogadoresAV[20];
	obterJogadoresComPosição(bufferDeJogadoresAV, equipa, "AV");
	baralharArrayJogadores(bufferDeJogadoresAV);

	for (int i = 0; i < (int)(tatica[4] - '0'); i++) {

		bufferDeJogadoresAV[i]->estadoEmJogo[0] = POSICAO_AV;

	}

	// imprimirOnzeDefinido(equipa);

};

/*
Calcula o poder de defesa de uma equipa
*/
void obterPoderesDeOnze(Equipa* equipa, int parteDoJogo, float poderes[]) {

	float poderDefesa = 0.0;
	float poderAtaque = 0.0;
	float contribuicaoDef = 0.0;
	float contribuicaoAta = 0.0;

	// somar contribuicao guarda redes
	for (int i = 0; i < NUMERO_JOGADORES_PLANTEL; i++) {

		Jogador* j = equipa->plantel->jogadores[i];

		if (j->estadoEmJogo[parteDoJogo] == POSICAO_GR) {

			contribuicaoDef += j->atributos->gr;
			contribuicaoAta += j->atributos->av;

		}

	}

	poderDefesa += contribuicaoDef * CONTRIBUICOES_POSICOES[POSICAO_GR][0];
	poderAtaque += contribuicaoAta * CONTRIBUICOES_POSICOES[POSICAO_GR][1];
	contribuicaoDef = 0.0;
	contribuicaoAta = 0.0;

	// somar contribuicao defesas
	for (int i = 0; i < NUMERO_JOGADORES_PLANTEL; i++) {

		Jogador* j = equipa->plantel->jogadores[i];

		if (j->estadoEmJogo[parteDoJogo] == POSICAO_DEF) {

			contribuicaoDef += j->atributos->df;
			contribuicaoAta += j->atributos->av;

		}

	}

	poderDefesa += contribuicaoDef * CONTRIBUICOES_POSICOES[POSICAO_DEF][0];
	poderAtaque += contribuicaoAta * CONTRIBUICOES_POSICOES[POSICAO_DEF][1];
	contribuicaoDef = 0.0;
	contribuicaoAta = 0.0;

	// somar contribuicao medios
	for (int i = 0; i < NUMERO_JOGADORES_PLANTEL; i++) {

		Jogador* j = equipa->plantel->jogadores[i];

		if (j->estadoEmJogo[parteDoJogo] == POSICAO_MED) {

			contribuicaoDef += j->atributos->md;
			contribuicaoAta += j->atributos->md;

		}

	}

	poderDefesa += contribuicaoDef * CONTRIBUICOES_POSICOES[POSICAO_MED][0];
	poderAtaque += contribuicaoAta * CONTRIBUICOES_POSICOES[POSICAO_MED][1];
	contribuicaoDef = 0.0;
	contribuicaoAta = 0.0;

	// somar contribuicao avancados
	for (int i = 0; i < NUMERO_JOGADORES_PLANTEL; i++) {

		Jogador* j = equipa->plantel->jogadores[i];

		if (j->estadoEmJogo[parteDoJogo] == POSICAO_AV) {

			contribuicaoDef += j->atributos->df;
			contribuicaoAta += j->atributos->av;

		}

	}

	poderDefesa += contribuicaoDef * CONTRIBUICOES_POSICOES[POSICAO_AV][0];
	poderAtaque += contribuicaoAta * CONTRIBUICOES_POSICOES[POSICAO_AV][1];
	contribuicaoDef = 0.0;
	contribuicaoAta = 0.0;


	poderes[0] = poderDefesa;
	poderes[1] = poderAtaque;

}


/*
Realiza o parte do jogo do argumento
*/
void realizarParteDeJogo(Jogo* jogo, int parte) {

	Equipa *equipaA = obterEquipaPorLetraSorteio(EQUIPAS, jogo->equipaA);
	Equipa *equipaB = obterEquipaPorLetraSorteio(EQUIPAS, jogo->equipaB);
	/*
	0 é o poder de defesa
	1 é o poder de ataque
	*/
	float poderesEquipaA[2] = { 0.0, 0.0 };
	obterPoderesDeOnze(equipaA, parte, poderesEquipaA);

	// adicionar o factor casa
	// a equipaA joga sempre em casa
	float factorCasa = randomFloat() * 0.2;
	// factor posicao
	float factorPosicaoA = 0.008 * pow(((double)obterPossicaoEquipa(equipaA) - 11.0), 2) + 1.0;	
	poderesEquipaA[0] += factorCasa;
	poderesEquipaA[1] += factorCasa;

	float poderesEquipaB[2];
	obterPoderesDeOnze(equipaB, parte, poderesEquipaB);
	
	// se já há posicoes
	if (nJornada >= 2) {

		// factor posicao
		float factorPosicaoA = 0.008 * pow(((double)obterPossicaoEquipa(equipaA) - 11.0), 2) + 1.0;
		poderesEquipaA[0] += factorPosicaoA;
		poderesEquipaA[1] += factorPosicaoA;

		// factor posicao
		float factorPosicaoB = 0.008 * pow(((double)obterPossicaoEquipa(equipaB) - 11.0), 2) + 1.0;
		poderesEquipaB[0] += factorPosicaoB;
		poderesEquipaB[1] += factorPosicaoB;

	}

	/*
	Calcular os golos.
	Os golos são a diferença entre poderes de ataque e defesa
	*/


	int golosA = poderesEquipaA[1] - poderesEquipaB[0];
	int golosB = poderesEquipaB[1] - poderesEquipaA[0];

	printf("Equipa A:\n");
	printf("%.2f\n", poderesEquipaA[0]);
	printf("%.2f\n", poderesEquipaA[1]);
	printf("%i\n", golosA);

	printf("Equipa B:\n");
	printf("%.2f\n", poderesEquipaB[0]);
	printf("%.2f\n", poderesEquipaB[1]);
	printf("%i\n", golosB);

	jogo->resultados->golosEquipaA += golosA >= 0 ? golosA : 0;
	jogo->resultados->golosEquipaB += golosB >= 0 ? golosB : 0;

	if (parte == 0) {

		jogo->resultados->poderDefesaEquipaAPrimeiraParte = poderesEquipaA[0];
		jogo->resultados->poderAtaqueEquipaAPrimeiraParte = poderesEquipaA[1];

		jogo->resultados->poderDefesaEquipaBPrimeiraParte = poderesEquipaB[0];
		jogo->resultados->poderAtaqueEquipaBPrimeiraParte = poderesEquipaB[1];

	}
	else if (parte == 2) {

		jogo->resultados->poderDefesaEquipaASegundaParte = poderesEquipaA[0];
		jogo->resultados->poderAtaqueEquipaASegundaParte = poderesEquipaA[1];

		jogo->resultados->poderDefesaEquipaBSegundaParte = poderesEquipaB[0];
		jogo->resultados->poderAtaqueEquipaBSegundaParte = poderesEquipaB[1];

	}

}

/*
Realiza o jogo do jogaodr no argumento
*/
void realizarJogoDoJogador(Jogo* jogo) {

	Equipa *equipaA = obterEquipaPorLetraSorteio(EQUIPAS, jogo->equipaA);
	Equipa *equipaB = obterEquipaPorLetraSorteio(EQUIPAS, jogo->equipaB);

	int parteDoJogo = 0;

	realizarParteDeJogo(jogo, parteDoJogo);

	printf("Resultados 1ª parte:\n\n");

	printf("%s: %i\n",
		equipaA->nome,
		jogo->resultados->golosEquipaA
	);

	printf("%s: %i\n",
		equipaB->nome,
		jogo->resultados->golosEquipaB
	);

	iniciarPrimirParaContinuar();

	int mudarTaticaOuNao = -1;
	int exit = 1;

	printf("\nPretende alterar a sua tática?\n");
	printf("\n1.Não\n2.Sim\n");
	while (exit) {

		imprimirCursor();

		scanf("%i", &mudarTaticaOuNao);

		switch (mudarTaticaOuNao) {
		case 1:
			exit = 0;
			break;
		case 2:
			exit = 0;
			break;
		}

	}

	if (mudarTaticaOuNao == 2) {

		iniciarMenuEscolhaDeTatica();

	}
	
	parteDoJogo = 1;

	realizarParteDeJogo(jogo, parteDoJogo);

	printf("Resultados finais do encontro:\n\n");

	printf("%s: %i\n",
		equipaA->nome,
		jogo->resultados->golosEquipaA
	);

	printf("%s: %i\n",
		equipaB->nome,
		jogo->resultados->golosEquipaB
	);

	iniciarPrimirParaContinuar();

	jogo->realizado = 1;

	// quem ganhou?
	// actalizar stats e assim
	if (jogo->resultados->golosEquipaA > jogo->resultados->golosEquipaB) {

		// ganha equipa A

		jogo->resultados->vencedor  = equipaA;
		jogo->resultados->derrotado = equipaB;

		equipaA->resultados->vitorias++;
		equipaB->resultados->derrotas++;

		equipaA->resultados->pontos += 3;

	}
	else if (jogo->resultados->golosEquipaB > jogo->resultados->golosEquipaA) {

		// ganha equipa B

		jogo->resultados->vencedor = equipaB;
		jogo->resultados->derrotado = equipaA;

		equipaA->resultados->derrotas++;
		equipaB->resultados->vitorias++;

		equipaB->resultados->pontos += 3;

	}
	else {

		jogo->resultados->vencedor = NULL;
		jogo->resultados->derrotado = NULL;
		jogo->resultados->empate = 1;

		equipaA->resultados->empates++;
		equipaB->resultados->empates++;

		equipaA->resultados->pontos += 1;
		equipaB->resultados->pontos += 1;

	}

	equipaA->resultados->golosMarcados += jogo->resultados->golosEquipaA;
	equipaB->resultados->golosMarcados += jogo->resultados->golosEquipaB;

	equipaA->resultados->golosSofridos += jogo->resultados->golosEquipaB;
	equipaB->resultados->golosSofridos += jogo->resultados->golosEquipaA;

}

/*
Realiza o jogo CPU no argumento
*/
void realizarJogoCPU(Jogo* jogo) {

	Equipa *equipaA = obterEquipaPorLetraSorteio(EQUIPAS, jogo->equipaA);
	Equipa *equipaB = obterEquipaPorLetraSorteio(EQUIPAS, jogo->equipaB);

	int parteDoJogo = 0;

	realizarParteDeJogo(jogo, parteDoJogo);

	parteDoJogo = 1;

	realizarParteDeJogo(jogo, parteDoJogo);

	jogo->realizado = 1;

	// ISTO PODIA ESTAR NUMA FUNÇÃO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! :(
	// quem ganhou?
	// actalizar stats e assim
	if (jogo->resultados->golosEquipaA > jogo->resultados->golosEquipaB) {

		// ganha equipa A

		jogo->resultados->vencedor = equipaA;
		jogo->resultados->derrotado = equipaB;

		equipaA->resultados->vitorias++;
		equipaB->resultados->derrotas++;

		equipaA->resultados->pontos += 3;

	}
	else if (jogo->resultados->golosEquipaB > jogo->resultados->golosEquipaA) {

		// ganha equipa B

		jogo->resultados->vencedor = equipaB;
		jogo->resultados->derrotado = equipaA;

		equipaA->resultados->derrotas++;
		equipaB->resultados->vitorias++;

		equipaB->resultados->pontos += 3;

	}
	else {

		jogo->resultados->vencedor = NULL;
		jogo->resultados->derrotado = NULL;
		jogo->resultados->empate = 1;

		equipaA->resultados->empates++;
		equipaB->resultados->empates++;

		equipaA->resultados->pontos += 1;
		equipaB->resultados->pontos += 1;

	}

	equipaA->resultados->golosMarcados += jogo->resultados->golosEquipaA;
	equipaB->resultados->golosMarcados += jogo->resultados->golosEquipaB;

	equipaA->resultados->golosSofridos += jogo->resultados->golosEquipaB;
	equipaB->resultados->golosSofridos += jogo->resultados->golosEquipaA;

}

/*
compara duas equipas pelos seus pontos
https://stackoverflow.com/a/23689916
*/
int comparaPontosEquipas(const void *v1, const void *v2)
{

	Equipa *ptr_to_left_struct = *(Equipa**)v1;
	Equipa *ptr_to_right_struct = *(Equipa**)v2;

	if (ptr_to_left_struct->resultados->pontos > ptr_to_right_struct->resultados->pontos)
		return -1;
	else if (ptr_to_left_struct->resultados->pontos < ptr_to_right_struct->resultados->pontos)
		return 1;
	else
		return 0;
}

/*
Ordena por pontos a tabela classificativa
*/
void ordenarTabelaClassificativa() {

	qsort(tabelaClassificacoes, NUMERO_EQUIPAS, sizeof(int), comparaPontosEquipas);

}

void subtrairDespesasClubes() {
	
	for (int i = 0; i < NUMERO_EQUIPAS; i++) {

		Equipa *e = EQUIPAS[i];

		float total = 0.0;

		// subtrair despesas do estadio
		total += e->estadio->despesaMensal;

		// subtrair salarios
		for (int j = 0; j < NUMERO_JOGADORES_PLANTEL; j++) {

			total += e->plantel->jogadores[j]->vencimentoMensal;
		}

		// notificar
		if (e == equipaJogador) {

			system("cls");

			imprimirTitulo("Hora das contas!");
			printf("Iram ser retirados dos fundos da equipa %.2f euros!\nIsto mantém os seus jogadores contentes e o seu estadio em condições.\n", total);
			iniciarPrimirParaContinuar();

		}

		e->fundos -= total;
		
	}

}

void avancarEpoca() {

	// era bom fazer reset da epoca quando esta acaba...

	nJornada++;

	ordenarTabelaClassificativa();

	// subtrair despesas de 4 em 4 jornadas
	if (nJornada % 4 == 0) {

		subtrairDespesasClubes();
		
	}

}

int obterPossicaoEquipa(Equipa *e) {

	for (int i = 0; i < NUMERO_EQUIPAS; i++) {

		if (tabelaClassificacoes[i] == e)
			return i;

	}

}