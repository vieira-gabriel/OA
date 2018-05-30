/*
	Universidade de Brasilia - Departamento de Ciência da Computacao
	Organizacao de Arquivos - Turma C
	Gabriel Vieira Arimatea - 15/0126956
	Vanessa Rodrigues Galeno - 16/0147069
*/

#include "Registros.hpp"

using namespace std;

string EscolherArquivo(){
	char resp;
	const char *arq;

	cout << endl << "\tEscolha qual turma você deseja abrir:" << endl;
	do{
		cout << " A" << endl << " B" << endl;
		cout << endl << ">> ";
		cin >> resp;
		if(resp != 'a' && resp != 'A' && resp != 'b' && resp != 'B')
			cout << endl << "Opcao inválida, escolha uma das opções abaixo:" << endl;
	}while(resp != 'a' && resp != 'A' && resp != 'b' && resp != 'B');
	if(resp == 'a' || resp == 'A') arq = "lista1.txt";
	else arq = "lista2.txt";
	return arq;
}

int menu(ArquivoDeIndice &L1, ArquivoDeIndice &L2, ArquivoDeIndice &L3){
	char lista1[] = "lista1.txt", lista2[] = "lista2.txt";
	char resp;
	string arquivo;
	IndiceP Chave1;
	IndiceS Chave2;
	string nome, curso;

	cout << endl << "\tEscolha uma das opcoes e digite o numero correspondente:" << endl;
	do{
		cout << "1) Incluir registros." << endl << "2) Excluir registros." << endl << "3) Atualizar registros." << endl << "4) Intercalar as duas turmas." << endl;
		cout << "5) Sair." << endl;
		cout << endl << ">> ";
		cin >> resp;
		if(resp<'1' || resp>'5')
			cout << endl << "Opcao inválida, escolha uma das opções abaixo:" << endl << endl;
	}while(resp<'1' || resp>'5');

	switch(resp){
		case('1'):
			
			arquivo = EscolherArquivo();
			cout << endl << endl << "\tInforme os dados do registro que deseja incluir:" << endl;		//Informacoes do registro que deve ser excluido.
			cout << "Qual eh a matricula? ";
			cin >> Chave1.identificador;
			Chave1.completo = Chave1.identificador + '\t';
			cout << "Qual eh o nome? ";
			getline (cin, nome);
			getline (cin, nome);
			Chave1.identificador = Chave1.identificador + nome[0];
			Chave1.completo += nome + '\t';
			for(int i = 1; nome[i] != '\0'; ++i){
					if(nome[i-1] == ' ') Chave1.identificador = Chave1.identificador + nome[i];
			}
			Chave1.completo += "32\t";
			do{
				cout << "Qual eh seu curso?(Entre com as duas iniciais em maiusculo) ";
				cin>>curso;
				cout<<"CURSO DIGITADO: "<<curso<<endl;
				if(curso.size() > 2)
					cout << "Entre com apenas as duas iniciais em maiusculo" << endl;
				else if((curso[0] < 'A' && curso[1] < 'A') || (curso[0] > 'Z' && curso[1] > 'Z'))
					cout << "Entrada inválida" << endl;
			}while((curso[0] < 'A' && curso[1] < 'A') || (curso[0] > 'Z' && curso[1] > 'Z') || curso.size() > 2);
			Chave2.curso = curso;
			Chave1.completo += curso + '\t';

			if(arquivo == "lista1.txt"){
				Chave1.completo += 'A';
				L1.incluir(Chave1, Chave2);
				L1.visualizar();
				L1.criaInd('A');
			}
			else{
				Chave1.completo += 'B';
				L2.incluir(Chave1, Chave2);			
				L2.visualizar();
				L2.criaInd('B');
			}
			break;
		case('2'):
			arquivo = EscolherArquivo();
			if(arquivo == "lista1.txt"){
				L1.excluir();
				L1.visualizar();
				L1.criaInd('A');
			}
			else{
				L2.excluir();			
				L2.visualizar();
				L2.criaInd('B');
			}
			break;
		case('3'):
			arquivo = EscolherArquivo();
			if(arquivo == "lista1.txt"){
				L1.atualizar('A');
				L1.visualizar();
				L1.criaInd('A');
			}
			else{
				L2.atualizar('B');			
				L2.visualizar();
				L2.criaInd('B');
			}
			break;
		case('4'):
			L3 = merge(L1, L2);
			L3.visualizar();
			break;
		case('5'):
			return 0;
	}
	return 1;
}

int main(){
	char lista1[] = "lista1.txt", lista2[] = "lista2.txt";
	ArquivoDeIndice L1;
	ArquivoDeIndice L2;
	ArquivoDeIndice	L3;

	L1.criar(lista1);
	L1.criaInd('A');
	L2.criar(lista2);
	L2.criaInd('B');

	while(menu(L1, L2, L3));

	return 0;
}