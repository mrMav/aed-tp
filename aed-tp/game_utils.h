#pragma once

#include <time.h>

#include "game_typedefs.h"

/*

Funcoes uteis:

*/

float randomFloat();

int randomInt(int, int);

struct tm* novaData(char string[]);

int VerificaTatica(char Tatica[]);

void iniciarPrimirParaContinuar();