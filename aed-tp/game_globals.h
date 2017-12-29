#pragma once

#include "game_constants.h"
#include "game_typedefs.h"

// extern keyword makes variables available for compilation
// see this:
// https://stackoverflow.com/a/27796066

// array para guardar todas as EQUIPAS
extern Equipa *EQUIPAS[NUMERO_EQUIPAS];  

// indice da equipa escolhida pelo jogador
extern int INDICE_EQUIPA_JOGADOR;

// nome do jogador
extern char *NOME_JOGADOR[100];