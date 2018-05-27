#include "Registros.hpp"

void ArquivoDeIndice::visualizar(list<IndiceP>& primario, list<IndiceS>& secundario){
	list<IndiceP>::iterator temp1;

	cout << "\tChaves secunárias" << endl << endl;
	for(list<IndiceS>::iterator ponteiroS = secundario.begin(); ponteiroS != secundario.end(); ++ponteiroS){
		temp1 = ponteiroS->registroP;
    	cout << ponteiroS->curso << ' ' << &temp1 << endl;
	}


    cout << "\tChaves primárias" << endl << endl;
	for(list<IndiceP>::iterator ponteiroP = primario.begin(); ponteiroP != primario.end(); ++ponteiroP){
		temp1 = ponteiroP->registro;
    	cout << &ponteiroP << ' ' << ponteiroP->identificador << ' ' << &temp1 << endl;
	}

    cout << endl;
}

void ArquivoDeIndice::incluir(list<IndiceP>& primario, list<IndiceS>& secundario, IndiceP Chave1, IndiceS Chave2){
	list<IndiceP>::iterator ponteiroSP;
	list<IndiceP>::iterator ponteiroP;
	list<IndiceS>::iterator ponteiroS;

	// Incerindo a chave na lista secundária
	ponteiroS = secundario.begin();									// Ponteiro aponta pro primeiro elemento da lista secundaria
	while(ponteiroS->curso != Chave2.curso || ponteiroS != secundario.end()){	// Laço de repetição para verificar se a chave ja n existe na lista até que o ponteiro chegue no final da mesma
		if (ponteiroS->curso == Chave2.curso) break; 							// Caso ja exista a chave, sai do laço e o ponteiro é salvo para mais tarde
		ponteiroS++;												// Aponta para proximo elemento
	}
	if(ponteiroS == secundario.end()) secundario.insert(ponteiroS, Chave2);	// Incere chave no ultimo elemento da lista se ele ja não existir nela

	// Incerindo a chave na lista primária
	ponteiroSP = ponteiroS->registroP;
	if(ponteiroSP != primario.end()){				// Se a chave secundária não aponta para nenhum elemento na lista primária
		ponteiroP = ponteiroSP;
		while(ponteiroP != primario.end() || ponteiroP->identificador != Chave1.identificador) ponteiroP = ponteiroP->registro;	// Verifica se a chave não existe na lista
		if (ponteiroP->identificador == Chave1.identificador);			// Caso já exista a chave, não realiza mais nada;
		else{
			ponteiroP = ponteiroSP;
			while(ponteiroP != primario.end()){		// Enquanto não chegar no ultimo elemento referente à chave secundária na lista primária
				// Compara se a chave 1 é maior ou menor para ja incerir na ordem certa
				ponteiroP = ponteiroP->registro;
			}
		}
	}
	else{									// Se a chave secundária aponta para nenhum elemento na lista primária, a chave primaria sera incerida no final da lista
		ponteiroP = primario.end();
		primario.insert(ponteiroP, Chave1);
		Chave2.registroP = ponteiroP;
	}

	//Aqui entra algoritmo de ordenação lista secundária
}

void ArquivoDeIndice::criar(list<IndiceP>& primario, list<IndiceS>& secundario, char arquivo[]){
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