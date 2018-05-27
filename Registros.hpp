#ifndef REGISTROS_H
#define REGISTROS_H

#include<stdio.h>
#include<stdlib.h>
#include <string>
#include <cstring>
#include <stdexcept>
#include<string.h>
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

typedef struct RegistroP{
	string 	identificador;							// Esse identificador vai ser a matricula mais as iniciais do nome
	list<RegistroP>::iterator registro;				// Ponteiro para próximo elemento referente ao índice secundário
}IndiceP;

typedef struct RegistroS{
	string curso;
	list<IndiceP>::iterator registroP;				// Ponteiro para a lista de indice primario
}IndiceS;


class ArquivoDeIndice{
private:
	list<IndiceP> primario;
	list<IndiceS> secundario;
public:
	void visualizar(list<IndiceP>&, list<IndiceS>&);
	void incluir(list<IndiceP>&, list<IndiceS>&, IndiceP, IndiceS);
	void criar(list<IndiceP>&, list<IndiceS>&, char*);
	void excluir(list<IndiceP>&, list<IndiceS>&);
	void atualizar(list<IndiceP>&, list<IndiceS>&);
	
};

#endif