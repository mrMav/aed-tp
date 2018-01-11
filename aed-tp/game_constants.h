#pragma once

#define NUMERO_JOGADORES_PLANTEL 20
#define NUMERO_EQUIPAS 18
#define NUMERO_TRANSFERENCIAS 3

#define SIMBOLO_EURO "Euro"

// Menu constants

enum MENU_INICIAL {

	MENU_INICIAL_OPCAO_NULA = -1,
	MENU_INICIAL_OPCAO_SAIR,
	MENU_INICIAL_OPCAO_CONTINUAR,
	MENU_INICIAL_OPCAO_NOVO_JOGO

};

enum MENU_NOVO_JOGO {

	MENU_NOVO_JOGO_OPCAO_NULA = -1,
	MENU_NOVO_JOGO_OPCAO_SAIR,
	MENU_NOVO_JOGO_OPCAO_INSERIR_NOME,
	MENU_NOVO_JOGO_OPCAO_ESCOLHER_EQUIPA

};

enum MENU_PREPARACAO_EPOCA {

	MENU_PREPARACAO_EPOCA_OPCAO_NULA = -1,
	MENU_PREPARACAO_EPOCA_OPCAO_SAIR,
	MENU_PREPARACAO_EPOCA_OPCAO_TRANSFERENCIA_JOGADORES,
	MENU_PREPARACAO_EPOCA_OPCAO_INFORMACAO,
	MENU_PREPARACAO_EPOCA_INICIAR_EPOCA

};

enum MENU_INFORMACAO {

	MENU_INFORMACAO_OPCAO_NULA = -1,
	MENU_INFORMACAO_OPCAO_SAIR,
	MENU_INFORMACAO_VER_OUTRAS

};

enum MENU_SORTEIO {
	MENU_SORTEIO_OPCAO_NULA = -1,
	MENU_SORTEIO_OPCAO_CONTINUAR,
	MENU_SORTEIO_OPCAO_SAIR
};

enum MENU_DECORRER_EPOCA {
	MENU_DECORRER_EPOCA_OPCAO_NULA = -1,
	MENU_DECORRER_EPOCA_OPCAO_VER_EQUIPA,
	MENU_DECORRER_EPOCA_OPCAO_PROXIMA_JORNADA,
	MENU_DECORRER_EPOCA_OPCAO_SAIR
};

enum MENU_PREPARACAO {
	MENU_PREPARACAO_JOGO_OPCAO_NULA = -1,
	MENU_PREPARACAO_JOGO_OPCAO_TATICA,
	MENU_PREPARACAO_JOGO_OPCAO_SAIR
};
