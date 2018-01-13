#pragma once

#include "game_constants.h"
#include "game_typedefs.h"

// array para guardar todas as EQUIPAS
Equipa *EQUIPAS[NUMERO_EQUIPAS];

// indice da equipa escolhida pelo jogador
int INDICE_EQUIPA_JOGADOR = -1;

// nome do jogador
char *NOME_JOGADOR[100];

// estrutura de dados de jornada
Jogo *JORNADAS[(NUMERO_EQUIPAS - 1) * 2][NUMERO_EQUIPAS / 2];

// numero de transferencias reslizadas pelo jogador
int nTransferencias = 0;

// jornada actual
int nJornada = 0;

// epoca iniciada
int epocaIniciada = 0;

// arte do titulo
char titleArt[2048];


