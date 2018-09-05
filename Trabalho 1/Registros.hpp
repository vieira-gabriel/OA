#define REGISTROS_H

#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <iterator>

using namespace std;

bool troca(string, string);
//void CriaInd(ArquivoDeIndice);

typedef struct RegistroP{
	string completo;
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
	void atualizar(char);
	void criaInd(char);
	list<IndiceS>::iterator comecoS(){
		return this->secundario.begin();
	}
	list<IndiceS>::iterator fimS(){
		return this->secundario.end();
	}
	list<IndiceP>::iterator comecoP(){
		return this->primario.begin();
	}
	list<IndiceP>::iterator fimP(){
		return this->primario.end();
	}
};

void ordena(list<IndiceP>::iterator, IndiceP);
ArquivoDeIndice merge(ArquivoDeIndice &L1, ArquivoDeIndice &L2);