#pragma once

#include "game_constants.h"
#include "game_typedefs.h"

/*

Funcoes para representar objectos no ecra:

*/

void imprimeJogador(Jogador* j);

void imprimeTreinador(Treinador* t);

void imprimeAtributos(Atributos* a);

void imprimePlantel(Plantel* p);

void imprimeEquipa(Equipa* e);

void imprimeEstadio(Estadio* e);

void imprimeResultados(Resultado* r);

void imprimirCabecalho(char* string);

void imprimirOpcao(char* string, int opcao);

void imprimirInstrucao(char* string);

void imprimirTitulo(char* string);

void imprimirSeparador();

void imprimirCursor();

void imprimirInicioDoJogo();

void listarEquipas();