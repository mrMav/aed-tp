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

Equipa* obterEquipaPorLetraSorteio(Equipa* EQUIPAS[], char letra);

/*
Troca dois jogadores um por outro
*/
void trocaJogadores(Equipa* equipa1, Equipa* equipa2, int indice1, int indice2, float valorTransf);

/*
Retorna o valor da transferencia de um jogador
*/
float obterValorTransferencia(Jogador* j);

/*
Atribuir letra aleatoria a equipas
*/
void atribuirLetrasSorteio();

/*
Lista jogadores de uma equipa e devolve jogador escolhido
*/
Jogador* escolherJogador(Equipa* e);

/*
Reset do estado de jogo dos jogadores da equipa
*/
void resetEstadoJogo(Equipa* e);

/*
Retorna o jogo em que o jogador participa, na jornada actual
*/
Jogo* obterJogoJogadorNaJornada(int nJornada);

/*
Realiza o jogo do argumento
*/
void realizarJogo(Jogo* jogo);

/*
Organiza aleatoriamente o 11 da equipa do argumento
*/
void fazerOnzeAleatorio(Equipa* equipa);

/*
Obter array com jogadores de uma certa posição
*/
void obterJogadoresComPosição(Jogador* jogadores[], Equipa* equipa, char posicao[]);

/*
Obter jogador aleatorio de array
*/
Jogador* obterJogadorAleatorioDeArray(Jogador* jogadores[]);

/*
Baralha uma array de jogares
*/
void baralharArrayJogadores(Jogador* jogadores[]);