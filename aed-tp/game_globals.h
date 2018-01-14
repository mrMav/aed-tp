#pragma once

#include "game_constants.h"
#include "game_typedefs.h"


// extern keyword makes variables available for compilation
// see this:
// https://stackoverflow.com/a/27796066

// array para guardar todas as EQUIPAS
extern Equipa *EQUIPAS[NUMERO_EQUIPAS]; 

// referencia da equipa escolhida pelo jogador
extern Equipa *equipaJogador;

// indice da equipa escolhida pelo jogador
extern int INDICE_EQUIPA_JOGADOR;

// nome do jogador
extern char *NOME_JOGADOR[100];

// estrutura de dados de jornada
extern Jogo *JORNADAS[(NUMERO_EQUIPAS - 1) * 2][NUMERO_EQUIPAS / 2];

// numero de transferencias reslizadas pelo jogador
extern int nTransferencias;

// jornada actual
extern int nJornada;

// epoca iniciada
extern int epocaIniciada;

// arte do titulo
extern char titleArt[1024];