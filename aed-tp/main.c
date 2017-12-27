#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#include "game_constants.h"
#include "game_typedefs.h"
#include "game_data_load.h"
#include "game_functions_prototypes.h"

int main(void) {
	
	setlocale(LC_ALL, "");

	// seed para numeros aleatorios
	srand(time(NULL));   // should only be called once

	// int for system pause
	int i = 0;
	int j = 0;
	
	// array para guardar todas as equipas
	Equipa *equipas[NUMERO_EQUIPAS];
	carregarEquipas(equipas);
	carregarPlanteis(equipas); // TODO: sort players into teams
	
	// System pause
	scanf("%i", &i);

	return 0;

}
