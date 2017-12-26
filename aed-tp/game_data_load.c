#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
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

	Equipa  *bufferEquipa  = NULL;
	Estadio *bufferEstadio = NULL;

	if (f == NULL) {

		printf("\nErro ao abrir ficheiro %s\n", nomeFicheiro);

	} else {
		
		while ((c = fgetc(f)) != EOF) {
			
			if (c != '\t' && c != '\n') {

				// collect all chars until a tab is found
				string[i] = c;
				i++;
				
			} else {

				// when found, store a terminator in the end
				string[i] = '\0';

				// Clube	Estádio	lotação	n.º de sócios	fundos do clube	despesas mensais da manutenção do estádio	Treinador
				
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
				// bit of data.
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

		//printf("Clube: %s\nEstadio: %s\nLotacao: %s\nNumero de socios: %s\nFundos: %s\nDespesas: %s\nTreinador: %s",
		//	clube, estadio, lotacao, nsocios, fundos, despesasEstadio, treinador);
		
		fclose(f);

	}

}
