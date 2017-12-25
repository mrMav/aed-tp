#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game_constants.h"
#include "game_typedefs.h"
#include "game_functions_prototypes.h"

int main(void) {

	int i = 0;

	// seed para numeros aleatorios
	srand(time(NULL));   // should only be called once

	Atributos* a = novoAtributos();

	time_t curtime;
	time(&curtime);

	Jogador* j[NUMERO_JOGADORES_PLANTEL];
	for (i = 0; i < NUMERO_JOGADORES_PLANTEL; i++) {

		j[i] = novoJogadorVazio();

	}

	j[0] = novoJogador("Jorge Noro", 20, 2000.0, &curtime, 4, "GR ", a);
	j[1] = novoJogador("Carlos Silva", 15, 3000.0, &curtime, 4, "DEF", a);
	j[2] = novoJogador("Nelson Mendes", 7, 5000.0, &curtime, 4, "AV", a);
	
	Treinador* t = novoTreinador("Miguel Arezes");

	Plantel* p = novoPlantel(t, j);
	
	imprimePlantel(p);

	// System pause
	scanf("%i", &i);

	return 0;

}
