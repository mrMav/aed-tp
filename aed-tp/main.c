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

/*

ATENCAO:

Acho que quando estou a carregar a informação de ficheiros, estou a usar o dobro da memoria necessária.
Acho isto porque quando declaro um array de um certo tipo, vamos supor Jogador*, esse array já é uma lista
de apontadores para variáveis do tipo Jogador*.

Agora vamos ver o que eu faço ao carregar os jogadores:
EQUIPAS[x]->plantel->jogadores[y] = novoJogador();  //novo jogador retorn Jogador*
(não é exactamemte esta linha de código, mas é a lógica aplicada)

O que é que isto nos diz? Que este elemento y do array, que já aponta para uma variavel do tipo Jogador*, vai
apontar para uma nova variável do tipo Jogador*. O que é feito ao primeiro apontador original no elemento do array?

É necessário rever isto.

*/


// teste jorge

int main(void) {
	
	// ATENCAO: definir a regiao pode fazer com que as funcoes
	// atof() ou strtof() não funcionem devido ao separador das decimas
	// ser diferente de idioma a idioma
	// neste caso, os nossos atributos usam virgulas, por isso está ok
	setlocale(LC_ALL, "pt-PT");

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

