#define REGISTROS_H

#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <iterator>

using namespace std;

typedef struct Registro{
	string completo;
	string 	chave;							// Esse identificador vai ser a matricula mais as iniciais do nome
	//struct RegistroP * registro;
}RegistroP;

class No{
	RegistroP *chaves;
	No **filhos;
	int numero;							//numero de chaves
	bool EhFolha;
	int ordem;							//ordem da arvore

public:
	No(int ordem, bool EhFolha);
	No* procura(RegistroP);
	int procuraChave(RegistroP);
	void incerirNaoCheio(RegistroP);
	void dividirFilho(int NumFilho, No*);
	void remover(RegistroP);
	void removeDaFolha(int pos);			// Remove a chave desse nó na posição pos se ela for folha
	void removeDaNaoFolha(int pos);			// Remove a chave desse nó na posição pos se ela não for folha
	RegistroP getAnterior(int pos);
	RegistroP getSucessor(int pos);
	void fill(int pos);
	void pegaDoAnterior(int pos);
	void pegaDoProximo(int pos);
	void merge(int pos);
	friend class ArvoreB;
};


class ArvoreB{
	No *caminho;
public:
	ArvoreB(){
		caminho = NULL;
	}
	void visualizar();
	void incerir(RegistroP);
	void remover(RegistroP);
	void criar(char*);
};

bool EhMaior(RegistroP, RegistroP);