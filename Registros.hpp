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
	list<IndiceP>::iterator registro;				// Ponteiro para próximo elemento referente ao índice secundário
}IndiceP;

typedef struct RegistroS{
	char curso[2];
	list<IndiceP>::iterator registroP;				// Ponteiro para a lista de indice primario
}IndiceS;
class ArquivoDeIndice{
private:
	list<IndiceP> primario;
	list<IndiceS> secundario;
public:
	void incluir(list<IndiceP>&, list<IndiceS>&, IndiceP, IndiceS);
	void criar(list<IndiceP>&, list<IndiceS>&, string);
	void excluir(list<IndiceP>&, list<IndiceS>&);
	void atualizar(list<IndiceP>&, list<IndiceS>&);
	void visualizar(list<IndiceP>&, list<IndiceS>&);
	ArquivoDeIndice();
	~ArquivoDeIndice();
	
};