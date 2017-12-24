#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game_typedefs.h"
#include "game_functions_prototypes.h"

int main(void) {

	int i = 0;

	// seed para numeros aleatorios
	srand(time(NULL));   // should only be called once

	Atributos* a = novoAtributos();

	time_t curtime;
	time(&curtime);

	Jogador* jn = novoJogador("Jorge Noro", 20, 2000.0, &curtime, 4, a);

	imprimeJogador(jn);

	// System pause
	scanf("%i", &i);

	return 0;

}
