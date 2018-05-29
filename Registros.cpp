#include "Registros.hpp"

bool troca(string atual, string incere){
	int j = 0;
	while(atual[j] == incere[j])++j;
	if (atual[j] > incere[j]) return 1;
	return 0;
}

void ordena(list<IndiceP>::iterator anterior, IndiceP *Chave1){
	Chave1->ProxRegistro = anterior->ProxRegistro;
	Chave1->registro = anterior->registro;
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

	Chave2.registroP = primario.end();
	Chave2.posicaoP = -1;
	Chave1.registro = primario.end();
	Chave1.ProxRegistro = -1;

//-----------------  Inserindo a chave na lista secundária -----------------------------------------------------------

	pos = 1;
	if(this->secundario.empty()){										// Insere no começo se a lista esiver vazia
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

//----------------- Inserindo a chave na lista primária -----------------------------------------------------------------

	pos = 1;
	if(trocouS){
		Chave2 = AuxS;
		ponteiroS = ponteiroAuxS;
	}
	ponteiroP = this->primario.begin();
	while(ponteiroP != this->primario.end()){
		pos++;
		ponteiroP++;
	}
	Chave1.posicao = pos;

	if(Chave2.posicaoP == -1){
		Chave1.registro = primario.end();
		Chave1.ProxRegistro = -1;
		Chave2.registroP = primario.end();
		if(trocouS) ponteiroAuxS->posicaoP = pos;
		else Chave2.posicaoP = pos;
		this->primario.insert(primario.end(), Chave1);
	}
	else{
		Prox = Chave2.posicaoP;
		do{
			ponteiroP = this->primario.begin();
			for (int i = 1; i < Prox; ++i){
				anterior = ponteiroP;
				ponteiroP++;
			}

			Prox = ponteiroP->ProxRegistro;
	    	if (ponteiroP->identificador == Chave1.identificador) break;      // Caso já exista a chave, não realiza mais nada;
			if (troca(ponteiroP->identificador, Chave1.identificador)){
				trocouP = 1;
				ordena(anterior, &Chave1);
			}
		}while(Prox != -1 || ponteiroP->registro != primario.end());
		if(!trocouP){
			ponteiroP->ProxRegistro = Chave1.posicao;
			ponteiroAuxP = this->primario.begin();
			while(ponteiroAuxP->registro != this->primario.end()) ponteiroAuxP++;
			ponteiroP->registro = ponteiroAuxP;
			Chave1.ProxRegistro = -1;
			Chave1.registro = primario.end();
		}
		pos = 1;
		if(trocouP && ponteiroP->identificador != Chave1.identificador){
			anterior->ProxRegistro = Chave1.posicao;
			anterior = this->primario.begin();
			while(anterior != this->primario.end()){
				anterior++;
				pos++;
			}
			Chave1.posicao = pos;
		}
		Chave2.registroP = ponteiroP;
		if(!trocouS) Chave2.posicaoP = pos;
		this->primario.insert(primario.end(), Chave1);
	}

	if(ponteiroS == this->secundario.end()) this->secundario.insert(ponteiroS, Chave2);	// Insere chave no ultimo elemento da lista se ele ja não existir nela
	//Aqui entra algoritmo de ordenação lista secundária
}

void ArquivoDeIndice::criar(char arquivo[]){
	ifstream File;
	string matricula, nome, curso, chaveP, aux, turma;
	IndiceP Chave1;
	IndiceS Chave2;

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
	string nome, curso, chave, temp;
	int flag;
	char resp, turma;
	list<IndiceP>::iterator ponteiroP,anterior;
	list<IndiceS>::iterator ponteiroS;
	cout << "Informe os dados do registro cadastrado:" << endl;		//Informacoes do registro que deve ser excluido.
	cout << "Matricula: ";
	cin >> chave;
	cout << "Nome: ";
	getline (cin, nome);
	getline (cin, nome);
	chave = chave + nome[0];
	for(int i = 1; nome[i] != '\0'; ++i){				// Pegar iniciais do nome.
		if(nome[i-1] == ' ') 
			chave = chave + nome[i];
	}
	do{
		cout << "Curso:(Entre com as duas iniciais em maiusculo) ";
		cin >> curso;
		if(curso.size() > 2)
			cout << "Entre com apenas as duas iniciais em maiusculo." << endl;
		else if((curso[0] < 'A' && curso[1] < 'A') || (curso[0] > 'Z' && curso[1] > 'Z'))
			cout << "Entrada inválida." << endl;
	}while((curso[0] < 'A' && curso[1] < 'A') || (curso[0] > 'Z' && curso[1] > 'Z') || curso.size() > 2);

		//Procura no indice secundario.
	cout<<"AQUIHEUHEUHUEHUE!!"<<endl;
	ponteiroS = this->secundario.begin();
	flag = 0;
	while(flag != 1 && ponteiroS != this->secundario.end()){
		if(ponteiroS->curso == curso){									//Verifica se eh o curso desejado.
			flag = 1;
		}else{
			ponteiroS++;
		}
	}
	if(flag == 1){
		//Procura no indice primario.

		ponteiroP = ponteiroS->registroP;

		if(ponteiroP->registro != this->primario.end()){
			while(ponteiroP->identificador != chave && ponteiroP->registro != this->primario.end()){

				cout << "chave: " << ponteiroP->identificador << endl;

				anterior = ponteiroP;						//Guarda a referencia do anterior.
				ponteiroP = ponteiroP->registro;			//Passa pro proximo.
			}
			cout << "to aquiiii" <<endl;
			if(ponteiroP->identificador == chave){			//Se for o registro desejado, apaga e coloca '*'.
				cout << "Achou a chave" << endl;
				ponteiroP->identificador = "*";
				anterior->registro = ponteiroP->registro;
				anterior->ProxRegistro = ponteiroP->ProxRegistro;
				ponteiroP = anterior;
				while(ponteiroP->registro != this->primario.end()){
					ponteiroP = ponteiroP->registro;
					--ponteiroP->posicao;
				}
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
		getchar();
		cin >> resp;
		if(resp != 's' || resp != 'S' || resp != 'n' || resp != 'N')
			cout << "Resposta invalida." << endl;
	}while(resp != 's' && resp != 'S' && resp != 'n' && resp != 'N');
	if(resp == 's' || resp == 'S')
		this->excluir();						//Chama a funcao de novo se o usuario quiser excluir outro registro.
	//atualiza o arq.ind 
}


void ArquivoDeIndice::atualizar(){
	string curso, matricula, nome, chave, aux;
	IndiceP Chave1;
	IndiceS Chave2;

	this->excluir();					// Exclui o registro.
	cout << "Informe os dados do registro com sua alteracao incluida:" << endl;
	cout << "Curso: ";
	cin >> curso;
	cout << endl << "Matricula: ";
	cin >> matricula;
	cout << endl << "Nome: ";
	cin >> nome;
	chave = matricula + nome[0];
	for(int i = 1; nome[i] != '\0'; ++i){		// Pega as inicias do Nome.
		if (nome[i] = ' ') chave += nome[i-1];
	}

	Chave1.identificador = chave;
	Chave2.curso = curso;
	this->incluir(Chave1, Chave2);			// Inclui o registro com as alterãcoes nas listas.

}


ArquivoDeIndice merge(char lista1[], char lista2[]){
	ArquivoDeIndice Junto;
	ifstream File1, File2;
	ofstream FileM;
	string nome1, nome2, matricula;
	list<string> registro1, registro2;

	File1.open(lista1);
	if(!File1.is_open()){
		cout << "Arquivo nao encontrado" << endl;
		exit(EXIT_FAILURE);
	}
	File2.open(lista2);
	if(!File2.is_open()){
		cout << "Arquivo nao encontrado" << endl;
		exit(EXIT_FAILURE);
	}
	FileM.open("lista12.txt", std::ofstream::out | std::ofstream::trunc); // Se o arquivo existia anteriormente, ele apaga o que estava dentro
	//getline(File1, registro1);	//salvar nome todo em uma string e depois pegar as iniciais para chave primária;
	while(File1.good()){
		
	}
	

	//getline(File2, registro2);




	File1.close();
	File2.close();
	FileM.close();

	return Junto;
}