#pragma once
#include <time.h>
#include "game_typedefs.h"

/*

Funcoes para criar os objectos:

*/

/*
Cria e retorna Equipa;
*/
Equipa* novaEquipa(char n[], Estadio *e, int s, Plantel *p, Resultado *r);

/*
Cria e retorna um Plantel.
*/
Plantel* novoPlantel(Treinador *t, Jogador *j[]);

/*
Cria e retorna um Estadio.
*/
Estadio* novoEstadio(char n[], int l, float dM);

/*
Cria e retorna um Resultado.
*/
Resultado* novoResultado();

/*
Cria e retorna um Atributos.
*/
Atributos* novoAtributos();
Atributos* novoAtributosVazio();

/*
Cria e retorna um Treinador.
*/
Treinador* novoTreinador(char n[]);

/*
Cria e retorna um Jogador.
*/
Jogador* novoJogador(char n[], int num, float vM, time_t* dC, int aC, char p[], Atributos *a);
Jogador* novoJogadorVazio();


/*

Funcoes para lidar com os objectos:

*/


// representacao da informacao:

void imprimeJogador(Jogador* j);

void imprimeTreinador(Treinador* t);

void imprimeAtributos(Atributos* a);

void imprimePlantel(Plantel* p);

/*

Funcoes uteis:

*/

float randomFloat();