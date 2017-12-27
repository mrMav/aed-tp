#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_typedefs.h"
#include "game_constants.h"
#include "game_functions_prototypes.h"

/*

	Data load

*/
void carregarEquipas(Equipa *equipas[]) {

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
					bufferEquipa = novaEquipa(clube, bufferEstadio, atoi(nsocios), NULL, novoResultado(), atof(fundos));

					equipas[j] = bufferEquipa;
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

void carregarPlanteis(Equipa *equipas[]) {

	char nomeFicheiro[] = "planteis2.txt";

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

					imprimeJogador(jogador);
					printf("%i\n", ++nJogadores);

					/*
					equipas[j] = bufferEquipa;
					j++;
					*/

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