#ifndef REGISTROS_H
#define REGISTROS_H

#include<stdio.h>
#include <stdbool.h>
#include<stdlib.h>
#include <string>
#include <cstring>
#include <stdexcept>
#include <string.h>
#include <iostream>
#include <fstream>
#include <list>
#include <iterator>

using namespace std;

bool troca(string, string);

void CriaInd(ArquivoDeIndice);

typedef struct RegistroP{
	string 	identificador;							// Esse identificador vai ser a matricula mais as iniciais do nome
	int ProxRegistro, posicao;
	list<RegistroP>::iterator registro;				// Ponteiro para próximo elemento referente ao índice secundário
	//struct RegistroP * registro;
}IndiceP;

typedef struct RegistroS{
	string curso;
	int posicaoP, posicao;
	list<IndiceP>::iterator registroP;				// Ponteiro para a lista de indice primario
	//IndiceP *registroP;
}IndiceS;


class ArquivoDeIndice{
private:
	list<IndiceP> primario;
	list<IndiceS> secundario;
public:
	void visualizar();
	void incluir(IndiceP, IndiceS);
	void criar(char*);
	void excluir();
	void atualizar();
};

#endif