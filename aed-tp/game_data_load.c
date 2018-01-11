#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_typedefs.h"
#include "game_constants.h"
#include "game_object_creation.h"
#include "game_object_manipulation.h"
#include "game_information_output.h"
#include "game_globals.h"

/*

	Data load

*/
void carregarEquipas() {

	char nomeFicheiro[] = "clubes.txt";

	FILE *f = fopen(nomeFicheiro, "r");

	int i = 0, j = 0, tabs = 0, c;

	char string[100];
	char clube[100];
	char estadio[100];
	char lotacao[100];
	char nsocios[100];
	char fundos[100];
	char despesasEstadio[100];
	char treinador[100];

	Equipa  *bufferEquipa = NULL;
	Estadio *bufferEstadio = NULL;

	if (f == NULL) {

		printf("\nErro ao abrir ficheiro %s\n", nomeFicheiro);

	}
	else {

		while ((c = fgetc(f)) != EOF) {

			if (c != '\t' && c != '\n') {

				// collect all chars until a tab is found
				string[i] = c;
				i++;

			}
			else {

				// when found, store a terminator in the end
				string[i] = '\0';

				switch (tabs) {

				case 0:
					strcpy(clube, string);
					break;
				case 1:
					strcpy(estadio, string);
					break;
				case 2:
					strcpy(lotacao, string);
					break;
				case 3:
					strcpy(nsocios, string);
					break;
				case 4:
					strcpy(fundos, string);
					break;
				case 5:
					strcpy(despesasEstadio, string);
					break;
				case 6:
					strcpy(treinador, string);
					break;
				}

				// this resets all the stuff so they are ready for the next
				// chunk of data.
				// if we have a new line in hands, we need to set the tabs to 0
				if (c == '\n') {

					bufferEstadio = novoEstadio(estadio, atoi(lotacao), atof(despesasEstadio));
					bufferEquipa = novaEquipa(clube, bufferEstadio, atoi(nsocios), novoPlantelVazio(), novoResultado(), atof(fundos));
					
					bufferEquipa->plantel->treinador = novoTreinador(treinador);
					
					EQUIPAS[j] = bufferEquipa;
					j++;

					bufferEstadio = NULL;
					bufferEquipa = NULL;

					tabs = 0;

				}
				else {

					tabs++;

				}

				i = 0;

			}

		}

		fclose(f);

	}

}

void carregarPlanteis() {

	char nomeFicheiro[] = "planteis.txt";

	FILE *f = fopen(nomeFicheiro, "r");

	int i = 0, j = 0, tabs = 0, c;
	int nJogadores = 0;

	char string[100]; // buffer
	char clube[100];
	char nome[100];
	char posicao[100];
	char numero[100];
	char valorMercado[100];
	char vencimentoMensal[100];
	char dataInicioNoClube[100];
	char dataFimNoClube[100];
	char anosConstrato[100];
	char atribGR[100];
	char atribDEF[100];
	char atribMED[100];
	char atribAV[100];

	Jogador  *jogador = NULL;

	if (f == NULL) {

		printf("\nErro ao abrir ficheiro %s\n", nomeFicheiro);

	}
	else {

		while ((c = fgetc(f)) != EOF) {

			if (c != '\t' && c != '\n') {

				// collect all chars until a tab is found
				string[i] = c;
				i++;

			}
			else {

				// when found, store a terminator in the end
				string[i] = '\0';

				switch (tabs) {

				case 0:
					strcpy(clube, string);
					break;
				case 1:
					strcpy(nome, string);
					break;
				case 2:
					strcpy(posicao, string);
					break;
				case 3:
					strcpy(numero, string);
					break;
				case 4:
					strcpy(valorMercado, string);
					break;
				case 5:
					strcpy(vencimentoMensal, string);
					break;
				case 6:
					strcpy(dataInicioNoClube, string);
					break;
				case 7:
					strcpy(dataFimNoClube, string);
					break;
				case 8:
					strcpy(anosConstrato, string);
					break;
				case 9:
					strcpy(atribGR, string);
					break;
				case 10:
					strcpy(atribDEF, string);
					break;
				case 11:
					strcpy(atribMED, string);
					break;
				case 12:
					strcpy(atribAV, string);
					break;
				}

				// this resets all the stuff so they are ready for the next
				// chunk of data.
				// if we have a new line in hands, we need to set the tabs to 0
				if (c == '\n') {

					struct tm* dataInicio = novaData(dataInicioNoClube);
					struct tm* dataFim = novaData(dataFimNoClube);

					Atributos* atrib = novoAtributos(
						atof(atribGR),
						atof(atribDEF),
						atof(atribMED),
						atof(atribAV)
					);
					
					jogador = novoJogador(
						nome,
						atoi(numero),
						atof(vencimentoMensal),
						dataInicio,
						dataFim,
						atoi(anosConstrato),
						posicao,
						atrib
					);
					
					//adicionar jogador a plantel da sua equipa:
					int sucess = adicionarJogadorAPlantel(obterEquipaPorNome(EQUIPAS, clube)->plantel, jogador);
					
					nJogadores += sucess;
					jogador = NULL;					
					tabs = 0;

				}
				else {

					tabs++;

				}

				i = 0;

			}

		}

		//printf("Numero total de jogadores carregados: %i\n", nJogadores);

		fclose(f);

	}

}

void carregarJornadas() {

	char nomeFicheiro[] = "jornadas.txt";

	FILE *f = fopen(nomeFicheiro, "r");

	int i = 0, c, tab = 0, line = 0;

	char string[4]; // buffer

	if (f == NULL) {

		printf("\nErro ao abrir ficheiro %s\n", nomeFicheiro);

	}
	else {

		while ((c = fgetc(f)) != EOF) {

			if (c != '\t' && c != '\n') {

				// collect all chars until a tab is found
				string[i] = c;
				i++;

			}
			else {

				// when found, store a terminator in the end
				string[i] = '\0';

				if (c == '\t') {

					tab++;

				}
				else if (c == '\n') {

					line++;
					tab = 0;

				}

				// linhas representam jornadas
				JORNADAS[line][tab] = 

				// reset
				i = 0;

			}

		}

		fclose(f);

	}

}