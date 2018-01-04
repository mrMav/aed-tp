#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#include "game_typedefs.h"
#include "game_constants.h"
#include "game_globals.h"
#include "game_data_load.h"
#include "game_menu.h"
#include "game_information_output.h"
#include "game_object_creation.h"
#include "game_object_manipulation.h"
#include "game_utils.h"

int main(void) {
	
	// ATENCAO: definir a regiao pode fazer com que as funcoes
	// atof() ou strtof() n�o funcionem devido ao separador das decimas
	// ser diferente de idioma a idioma
	setlocale(LC_ALL, "pt_PT");

	// seed para numeros aleatorios
	srand(time(NULL));   // should only be called once
	
	// carrega todos os dados necessarios
	carregarEquipas();
	carregarPlanteis();
	
	// comeca o loop infinito do jogo
	iniciarJogo();

	// funcao de fecho do jogo
	// (saving, memory clean up, etc...)
	sairJogo();

	return 0;

}
