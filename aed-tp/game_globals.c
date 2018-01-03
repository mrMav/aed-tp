#pragma once

#include "game_constants.h"
#include "game_typedefs.h"

// array para guardar todas as EQUIPAS
Equipa *EQUIPAS[NUMERO_EQUIPAS];

// indice da equipa escolhida pelo jogador
int INDICE_EQUIPA_JOGADOR = -1;

// nome do jogador
char *NOME_JOGADOR[100];

int nTransferencias = 0;