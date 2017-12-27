#pragma once
#include <time.h>
#include "game_typedefs.h"

/*

Funcoes para criar os objectos:

*/

/*
Cria e retorna Equipa;
*/
Equipa* novaEquipa(char n[], Estadio *e, int s, Plantel *p, Resultado *r, float f);

/*
Cria e retorna um Plantel.
*/
Plantel* novoPlantel(Treinador *t, Jogador *j[]);

Plantel* novoPlantelVazio();

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
Atributos* novoAtributos(float gr, float df, float md, float av);
Atributos* novoAtributosVazio();

/*
Cria e retorna um Treinador.
*/
Treinador* novoTreinador(char n[]);

/*
Cria e retorna um Jogador.
*/
Jogador* novoJogador(char n[], int num, float vM, struct tm* dC, struct tm* dF, int aC, char p[], Atributos *a);
Jogador* novoJogadorVazio();


// TODO: Criar funcoes para libertar memoria

/*

Funcoes para lidar com os objectos:

*/

// representacao da informacao:

void imprimeJogador(Jogador* j);

void imprimeTreinador(Treinador* t);

void imprimeAtributos(Atributos* a);

void imprimePlantel(Plantel* p);

void imprimeEquipa(Equipa* e);

void imprimeEstadio(Estadio* e);

// manipulação da informação:

int adicionarJogadorAPlantel(Plantel* plantel, Jogador* jogador);


/*

Funcoes uteis:

*/

float randomFloat();

struct tm* novaData(char string[]);

Equipa* obterEquipaPorNome(Equipa* equipas[], char string[]);