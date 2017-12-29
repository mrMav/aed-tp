#pragma once

#include "game_typedefs.h"

/*
Funcoes para manipular objectos e informacao do jogo
*/

/*
Adiciona o jogador no plantel.
Return 0: fail
Return 1: sucess
*/
int adicionarJogadorAPlantel(Plantel* plantel, Jogador* jogador);


Equipa* obterEquipaPorNome(Equipa* EQUIPAS[], char string[]);
