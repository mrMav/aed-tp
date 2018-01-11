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

Acho que quando estou a carregar a informa��o de ficheiros, estou a usar o dobro da memoria necess�ria.
Acho isto porque quando declaro um array de um certo tipo, vamos supor Jogador*, esse array j� � uma lista
de apontadores para vari�veis do tipo Jogador*.

Agora vamos ver o que eu fa�o ao carregar os jogadores:
EQUIPAS[x]->plantel->jogadores[y] = novoJogador();  //novo jogador retorn Jogador*
(n�o � exactamemte esta linha de c�digo, mas � a l�gica aplicada)

O que � que isto nos diz? Que este elemento y do array, que j� aponta para uma variavel do tipo Jogador*, vai
apontar para uma nova vari�vel do tipo Jogador*. O que � feito ao primeiro apontador original no elemento do array?

� necess�rio rever isto.

*/


// teste jorge

int main(void) {
	
	// ATENCAO: definir a regiao pode fazer com que as funcoes
	// atof() ou strtof() n�o funcionem devido ao separador das decimas
	// ser diferente de idioma a idioma
	// neste caso, os nossos atributos usam virgulas, por isso est� ok
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

