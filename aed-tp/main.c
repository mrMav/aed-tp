#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#include "game_constants.h"
#include "game_typedefs.h"
#include "game_data_load.h"
#include "game_menu.h"
#include "game_information_output.h"
#include "game_object_creation.h"
#include "game_object_manipulation.h"
#include "game_utils.h"

int main(void) {

	setlocale(LC_ALL, "");

	// seed para numeros aleatorios
	srand(time(NULL));   // should only be called once

	// array para guardar todas as equipas
	Equipa *equipas[NUMERO_EQUIPAS];
	carregarEquipas(equipas);
	carregarPlanteis(equipas);
	
	// comeca o loop infinito do jogo
	iniciarJogo(equipas);

	return 0;

}
