/*
	Universidade de Brasilia - Departamento de Ciência da Computacao
	Organizacao de Arquivos - Turma C
	Gabriel Vieira Arimatea - 15/0126956
	Vanessa Rodrigues Galeno - 16/0147069
*/

#include "Registros.hpp"

using namespace std;

const char* EscolherArquivo(){
	int resp;
	const char *arq;

	cout << endl << "\tEscolha qual arquivo você deseja abrir:" << endl;
	do{
		cout << "1) lista1.txt" << endl << "2) lista2.txt" << endl;
		cout << endl << ">> ";
		cin >> resp;
		if(resp < 1 || resp > 2)
			cout << endl << "Opcao inválida, escolha uma das opções abaixo:" << endl;
	}while(resp < 1 || resp > 2);
	if(resp == 1) arq = "lista1.txt";
	else arq = "lista2.txt";
	return arq;
}

void menu(){
	int resp;
	const char* arquivo;
	char lista1[] = "lista1.txt", lista2[] = "lista2.txt";
	ArquivoDeIndice L1;

	L1.criar(lista1);
	cout<< endl << "fim lista 1" << endl;
	L2.criar(lista2);

	cout << endl << "\tEscolha uma das opcoes e digite o numero correspondente:" << endl;
	do{
		cout << "1) Incluir registros." << endl << "2) Excluir registros." << endl << "3) Atualizar registros." << endl << "4) Visualizar todos os registros." << endl;
		cout << "5) Sair." << endl;
		cout << endl << ">> ";
		cin >> resp;
		if(resp<1 || resp>5)
			cout << endl << "Opcao inválida, escolha uma das opções abaixo:" << endl << endl;
	}while(resp<1 || resp>5);

	switch(resp){
		case(1):
			arquivo = EscolherArquivo();
			// 
			break;
		case(2):
			cout << "Te enganei, nao da pra excluir ainda." << endl;
			arquivo = EscolherArquivo();

			break;
		case(3):
			cout << "Te enganei, nao da pra atualizar ainda." << endl;
			arquivo = EscolherArquivo();
			break;
		case(4):
			cout << "Te enganei, nao da pra visualizar ainda." << endl;
			arquivo = EscolherArquivo();
			break;
		case(5):
			return;
	}
}

int main(){
	menu();

	return 0;
}