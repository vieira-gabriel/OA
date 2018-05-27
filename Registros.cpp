#include "Registros.hpp"

void ArquivoDeIndice::incluir(list<IndiceP>& primario, list<IndiceS>& secundario, IndiceP Chave1, IndiceS Chave2){
	list<IndiceP>::iterator ponteiroSP;
	list<IndiceP>::iterator ponteiroP;
	list<IndiceS>::iterator ponteiroS;

	// Incerindo a chave na lista secundária
	ponteiroS = secundario.begin();									// Ponteiro aponta pro primeiro elemento da lista secundaria
	while(*ponteiroS != Chave2 || ponteiroS != secundario.end()){	// Laço de repetição para verificar se a chave ja n existe na lista até que o ponteiro chegue no final da mesma
		if (*ponteiroS == Chave2) break; 							// Caso ja exista a chave, sai do laço e o ponteiro é salvo para mais tarde
		ponteiroS++;												// Aponta para proximo elemento
	}
	if(ponteiroS == secundario.end()) secundario.incert(ponteiroS, Chave2);	// Incere chave no ultimo elemento da lista se ele ja não existir nela

	// Incerindo a chave na lista primária
	ponteiroSP = *ponteiroS.registroP;
	if(ponteiroSP != NULL){				// Se a chave secundária não aponta para nenhum elemento na lista primária
		ponteiroP = ponterioSP;
		while(ponteiroP != NULL || *ponteiroP != Chave1) ponteiroP = *ponteiroP.registro;	// Verifica se a chave não existe na lista
		if (*ponteiroP == Chave1) break;			// Caso já exista a chave, não realiza mais nada;
		ponteiroP = ponteiroSP;
		while(ponteiroP != NULL){		// Enquanto não chegar no ultimo elemento referente à chave secundária na lista primária
			// Compara se a chave 1 é maior ou menor para ja incerir na ordem certa
			ponteiroP = *ponteiroP.registro;
		}
	}
	else{									// Se a chave secundária aponta para nenhum elemento na lista primária, a chave primaria sera incerida no final da lista
		ponteiroP = primario.end();
		primario.incert(ponteiroP, Chave1);
		Chave2.registro = ponteiroP;
	}

	//Aqui entra algoritmo de ordenação lista secundária
}

void ArquivoDeIndice::criar(list<IndiceP>& primario, list<IndiceS>& secundario, stirng arquivo){
	ifstream File;
	string matricula, nome, curso, chaveP, aux, turma;
	IndiceP Chave1;
	IndiceS Chave2;

	File.open(arquivo);
	if(!File.is_open()){
		cout << "Arquivo não encontrado" << endl;
		exit(EXIT_FAILURE);
	}

	while(File.good()){						// laço de repetição para executar enquanto o arquivo não acaba
		File >> matricula;
		chaveP = matricula;
		do{
			File >> nome;
			if(nome[0] < '0' || nome[0] > '9'){
				aux = nome[0];
				chaveP = chaveP + aux;
			}
		}while(nome[0] < '0' || nome[0] > '9');

		Chave1.identificador = chaveP;
		File >> curso;
		Chave2.curso = curso;
		File >> turma;

		ArquivoDeIndice::incluir(primario, secundario, Chave1, Chave2);
	}
	cout << endl;
	File.close();
}