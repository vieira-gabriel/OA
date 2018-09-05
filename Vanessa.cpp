void ArquivoDeIndice::incluir(IndiceP Chave1, IndiceS Chave2){
	list<IndiceP>::iterator ponteiroP, ponteiroSP, ponteiroAuxP, anterior;
	list<IndiceS>::iterator ponteiroS, ponteiroAuxS ,fim;
	IndiceP AuxP;
	IndiceS AuxS;
	int pos = 1, trocouS = 0, trocouP = 0, Prox;
	string id;
	list<IndiceP>::iterator temp;

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
		if(!trocouS) Chave2.posicaoP = pos;
		this->primario.insert(primario.end(), Chave1);
	}
	ponteiroP = this->primario.begin();
	while(ponteiroP->identificador != Chave1.identificador && ponteiroP != this->primario.end()){
		++ponteiroP;
	}
	if(Chave2.posicaoP == -1){
		if(trocouS){
			ponteiroAuxS->posicaoP = pos;
			ponteiroAuxS->registroP = ponteiroP;
		}
		else{
			Chave2.posicaoP = pos;
			Chave2.registroP = ponteiroP;
		}
	}
	if(ponteiroS == this->secundario.end()) this->secundario.insert(ponteiroS, Chave2);	// Insere chave no ultimo elemento da lista se ele ja não existir nela
	//Aqui entra algoritmo de ordenação lista secundária
}