/*
	Universidade de Brasilia - Departamento de Ciência da Computacao
	Organizacao de Arquivos - Turma C
	Gabriel Vieira Arimatea - 15/0126956
	Vanessa Rodrigues Galeno - 16/0147069
*/

#include "Registros.hpp"

using namespace std;


void menu(){
	int resp=0;
	ArquivoDeIndice L1;
	ArquivoDeIndice L2;

	do{
		cout << "\tEscolha uma das opcoes e digite o numero correspondente:" << endl;
		cout << "1) Incluir registros." << endl << "2) Excluir registros." << endl << "3) Atualizar registros." << endl << "4) Visualizar todos os registros." << endl;
		cin >> resp;
		if(resp<1 || resp>4)
			cout << endl << "Opcao inválida, escolha uma das opcoes abaixo:" << endl << endl;
	}while(resp<1 || resp>4);

	switch(resp){
		case(1):
			cout << "Te enganei, nao da pra incluir ainda." << endl;
			// 
			break;
		case(2):
			cout << "Te enganei, nao da pra excluir ainda." << endl;
			break;
		case(3):
			cout << "Te enganei, nao da pra atualizar ainda." << endl;
			break;
		case(4):
			cout << "Te enganei, nao da pra visualizar ainda." << endl;
			break;
	}
}

int main(){
	menu();

	return 0;
}