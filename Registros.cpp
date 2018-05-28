#include "Registros.hpp"

bool troca(string atual, string incere){
	int j = 0;
	while(atual[j] == incere[j])++j;
	if (atual[j] > incere[j]) return 1;
	return 0;
}

void ArquivoDeIndice::visualizar(){

	if(this->primario.empty()){
		cout << "\tLista nao foi criada" << endl;
		return;
	}
	cout << "\t\tIndices secundarios" << endl << endl;
	for(list<IndiceS>::iterator ponteiroS = this->secundario.begin(); ponteiroS != this->secundario.end(); ++ponteiroS){
    	cout << ponteiroS->posicao << '\t' << ponteiroS->curso << '\t' << ponteiroS->posicaoP << endl;
	}


    cout << endl << "\t\tIndices primarios" << endl << endl;
	for(list<IndiceP>::iterator ponteiroP = this->primario.begin(); ponteiroP != this->primario.end(); ++ponteiroP){
    	cout << '\t'  << ponteiroP->posicao << '\t' << ponteiroP->identificador << '\t' << ponteiroP->ProxRegistro << endl;
	}

    cout << endl;
}

void ArquivoDeIndice::incluir(IndiceP Chave1, IndiceS Chave2){
	list<IndiceP>::iterator ponteiroP, ponteiroSP, ponteiroAuxP, anterior;
	list<IndiceS>::iterator ponteiroS, ponteiroAuxS ,fim;
	IndiceP * regist;
	IndiceP AuxP;
	IndiceS AuxS;
	int pos = 1, trocouS = 0, trocouP = 0, Prox;
	string id;
	list<IndiceP>::iterator temp;

//-----------------  Incerindo a chave na lista secundária -----------------------------------------------------------

	pos = 1;
	if(this->secundario.empty()){										// Incere no começo se a lista esiver vazia
		Chave2.posicao = pos;
		ponteiroS = this->secundario.begin();
	}
	else{
		ponteiroS = this->secundario.begin();							// Ponteiro aponta pro primeiro elemento da lista secundaria
		fim  = this->secundario.end();
		while(ponteiroS != fim){	// Laço de repetição para verificar se a chave ja n existe na lista até que o ponteiro chegue no final da mesma
			if (Chave2.curso == ponteiroS->curso){ 				// Caso ja exista a chave, sai do laço e o ponteiro é salvo para mais tarde
				Chave2.registroP = ponteiroS->registroP;
				Chave2.posicaoP = ponteiroS->posicaoP;
				break;
			}
			if ((ponteiroS->curso[0] > Chave2.curso[0]) || (ponteiroS->curso[0] < Chave2.curso[0] && ponteiroS->curso[1] > Chave2.curso[1])){
				AuxS = *ponteiroS;
				ponteiroS->curso = Chave2.curso;
				ponteiroS->registroP = Chave2.registroP;
				ponteiroS->posicaoP = Chave2.posicaoP;
				Chave2 = AuxS;
				ponteiroAuxS = ponteiroS;
				AuxS = *ponteiroS;
				trocouS = 1;
			}
			pos++;
			ponteiroS++;															// Aponta para proximo elemento
			if(trocouS) ++Chave2.posicao;
		}
		if(trocouS && ponteiroS == this->secundario.end()) this->secundario.insert(ponteiroS, Chave2); 
	}
	Chave2.posicao = pos;

//----------------- Incerindo a chave na lista primária -----------------------------------------------------------------

	pos = 1;
	if(trocouS){
		Chave2 = AuxS;
		ponteiroS = ponteiroAuxS;
	}
	if(Chave2.posicaoP != -1){				// Se a chave secundária não aponta para nenhum elemento na lista primária
		Prox = Chave2.posicaoP;

		do{
			ponteiroP = this->primario.begin();
			for (int i = 1; i < Prox; ++i){
				ponteiroP++;
			}
			Prox = ponteiroP->ProxRegistro;
	    	if (ponteiroP->identificador == Chave1.identificador) break;      // Caso já exista a chave, não realiza mais nada;
			if (troca(ponteiroP->identificador, Chave1.identificador)){
				AuxP = *ponteiroP;
				ponteiroP->identificador = Chave1.identificador;
				ponteiroP->ProxRegistro = Chave1.ProxRegistro;
				ponteiroP->registro = Chave1.registro;
				Chave1 = AuxP;
				ponteiroAuxP = ponteiroP;
				AuxP = *ponteiroP;
				trocouP = 1;
				break;
			}
		}while(Prox != -1 || ponteiroP->registro != primario.end());

		if(trocouP && ponteiroP->identificador != Chave1.identificador){
			anterior = this->primario.begin();
			while(anterior != this->primario.end()){
				anterior++;
				pos++;
			}
			Chave1.posicao = pos;
			this->primario.insert(this->primario.end(), Chave1);
			anterior = this->primario.end();
			Chave1 = AuxP;
			ponteiroP = ponteiroAuxP;
			pos = 0;
		}
		Chave1.ProxRegistro = -1;
		ponteiroAuxP = this->primario.begin();
		while(ponteiroAuxP != this->primario.end()){
			ponteiroAuxP++;
			pos++;
		}
		Chave1.posicao = pos;
		Chave1.registro = primario.end();
		ponteiroP->ProxRegistro = pos;

		if (ponteiroP->identificador != Chave1.identificador) this->primario.insert(this->primario.end(), Chave1);
	}
	else{									// Se a chave secundária aponta para nenhum elemento na lista primária, a chave primaria sera incerida no final da lista
		ponteiroP = this->primario.begin();
		while(ponteiroP != this->primario.end()){
			pos++;
			ponteiroP++;
		}
		Chave1.posicao = pos;
		Chave1.registro = primario.end();
		Chave1.ProxRegistro = -1;
		Chave2.registroP = ponteiroP;
		if(trocouS) ponteiroAuxS->posicaoP = pos;
		else Chave2.posicaoP = pos;
		this->primario.insert(ponteiroP, Chave1);
	}

	if(ponteiroS == this->secundario.end()) this->secundario.insert(ponteiroS, Chave2);	// Incere chave no ultimo elemento da lista se ele ja não existir nela

	//Aqui entra algoritmo de ordenação lista secundária
}

void ArquivoDeIndice::criar(char arquivo[]){
	ifstream File;
	string matricula, nome, curso, chaveP, aux, turma;
	IndiceP Chave1;
	IndiceS Chave2;

	Chave2.registroP = primario.end();
	Chave2.posicaoP = -1;
	Chave1.registro = primario.end();

	if(!this->primario.empty()){
		cout << "Lista ja existente" << endl;
		return;
	}

	File.open(arquivo);
	if(!File.is_open()){
		cout << "Arquivo nao encontrado" << endl;
		exit(EXIT_FAILURE);
	}
	File >> matricula;
	while(File.good()){						// laço de repetição para executar enquanto o arquivo não acaba
		chaveP = matricula;
		do{
			File >> nome;
			if(nome[0] < '0' || nome[0] > '9'){
				aux = nome[0];
				chaveP = chaveP + aux;
			}
			else break;
		}while((nome[0] < '0' || nome[0] > '9'));

		Chave1.identificador = chaveP;
		File >> curso;
		Chave2.curso = curso;
		File >> turma;

		this->incluir(Chave1, Chave2);
		File >> matricula;
	}
	cout << endl;
	File.close();
}

void ArquivoDeIndice::excluir(){ 
	string matricula, nome, curso, chave, temp;
	int flag=0;
	char resp;
	list<IndiceP>::iterator ponteiroP;
	list<IndiceP>::iterator anterior;
	list<IndiceS>::iterator ponteiroS;

	cout << "Informe os dados do registro a ser excluído:" << endl;		//Informacoes do registro que deve ser excluido.
	cout << "Qual eh a matricula? ";
	cin >> matricula;
	cout << "Qual eh o nome? ";		//colocar loop para pegar as iniciais
	cin >> nome;
	chave = matricula + nome[0];
	for(int i = 1; nome[i] != '\0', ++i){
		if (nome[i] = ' ') chave += nome[i-1];
	}
	//concatenar na variavel 'chave'
	cout << "Qual eh o curso? ";
	cin >> curso;
	
	while(flag == 1 || ponteiroS != this->secundario.end()){				//procura no indice secundario.
		ponteiroS = this->secundario.begin();
		temp = ponteiroS->curso;
		if(strcmp(curso, temp))											//Verifica se eh igual.
			flag++;
		ponteiroS++;
	}
	if(flag == 1){
		ponteiroP = ponteiroS->registroP;
		if(ponteiroP != primario.end()){
			while(ponteiroP->identificador != chave || ponteiroP != NULL){		//procura no indice primario.
				anterior = ponteiroP;											//guarda a referencia do anterior.
				ponteiroP = ponteiroP->registro;								//passa pro proximo.
			}
			if(ponteiroP->identificador == chave){			//Se for o registro, retira e apaga.
				anterior->registro = *ponteiroP->registro;
				anterior->ProxRegistro = ponteiroP->ProxRegistro;	//Tem '*'?
				free(ponteiroP);							//Exclui registro e libera a memória.
			}else{
				cout << "Registro inexistente." << endl;
			}
		} else{
			cout << "Registro inexistente." << endl;
		}
	}else{
		cout << "Registro inexistente, nao ha o curso informado." << endl;
	}
	
	do{
		cout << "Quer retirar outro? (S/N)" << endl;
		cin >> resp;
		if(resp != 's' || resp != 'S' || resp != 'n' || resp != 'N')
			cout << "Resposta invalida." << endl;
	}while(resp != 's' || resp != 'S' || resp != 'n' || resp != 'N')
	if(resp == 's' || resp == 'S')
		this->excluir();						//Chama a funcao de novo se o usuario quiser excluir outro registro.
	//atualiza o arq.ind 
	this->visualizar();
}