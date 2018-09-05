/*
	Universidade de Brasilia - Departamento de Ciência da Computacao
	Organizacao de Arquivos - Turma C
	Gabriel Vieira Arimatea - 15/0126956
*/

#include "ArvoreB.hpp"

using namespace std;

int menu(ArvoreB Arvore){
	char resp;
	string arquivo;
	RegistroP Chave;
	string nome, curso, turma, excl, busca;


	cout << endl << "\tEscolha uma das opcoes e digite o numero correspondente:" << endl;
	do{
		cout << "1) Incluir registros." << endl << "2) Excluir registros." << endl << "3) Buscar registros.";
		cout << "4) Sair." << endl;
		cout << endl << ">> ";
		cin >> resp;
		if(resp<'1' || resp>'4')
			cout << endl << "Opcao inválida, escolha uma das opções abaixo:" << endl << endl;
	}while(resp<'1' || resp>'4');

	switch(resp){
		case('1'):
			
			cout << endl << endl << "\tInforme os dados do registro que deseja incluir:" << endl;		//Informacoes do registro que deve ser excluido.
			cout << "Qual eh o nome? ";
			getline (cin, nome);
			getline (cin, nome);
			Chave.completo += nome + '\t';
			nome[0] = toupper(nome[0]);
			nome[1] = toupper(nome[1]);
			nome[2] = toupper(nome[2]);
			Chave.chave = Chave.chave + nome[0];
			Chave.chave = Chave.chave + nome[1];
			Chave.chave = Chave.chave + nome[2];
			cout << "Qual eh a matricula? ";
			cin >> Chave.chave;
			Chave.completo += Chave.chave + '\t';
			do{
				cout << "Qual eh seu curso?(Entre com as duas iniciais em maiusculo) ";
				cin>>curso;
				cout<<"CURSO DIGITADO: "<<curso<<endl;
				if(curso.size() > 2)
					cout << "Entre com apenas as duas iniciais em maiusculo" << endl;
				else if((curso[0] < 'A' && curso[1] < 'A') || (curso[0] > 'Z' && curso[1] > 'Z'))
					cout << "Entrada inválida" << endl;
			}while((curso[0] < 'A' && curso[1] < 'A') || (curso[0] > 'Z' && curso[1] > 'Z') || curso.size() > 2);
			Chave.completo += curso + '\t';
			do{
				cout << "Qual eh sua turma? ";
				cin >> turma;
				turma[0] = toupper(turma[0]);
				if(turma.size() > 1 && (turma[0] < 'A' || turma[0] > 'Z'))
					cout << "Entre com uma turma valida" << endl;
			}while(turma.size() > 1 && (turma[0] < 'A' || turma[0] > 'Z'));
			Chave.completo += turma;

			Arvore.incerir(Chave);
			break;
		case('2'):
			do{
				cout << "Qual chave deseja excluir? ";
				cin >> excl;
				if (excl.size() != 8 && (excl[0] < 'A' || excl[0] > 'Z') && (excl[1] < 'A' || excl[1] > 'Z') && (excl[2] < 'A' || excl[2] > 'Z')
					&& (excl[3] < '0' || excl[3] > '9') && (excl[4] < '0' || excl[4] > '9') && (excl[5] < '0' || excl[5] > '9') && (excl[6] < '0' || excl[6] > '9')
					&& (excl[7] < '0' || excl[7] > '9'))
					cout << "Chave inválida" << endl;
			}while(excl.size() != 8 && (excl[0] < 'A' || excl[0] > 'Z') && (excl[1] < 'A' || excl[1] > 'Z') && (excl[2] < 'A' || excl[2] > 'Z')
					&& (excl[3] < '0' || excl[3] > '9') && (excl[4] < '0' || excl[4] > '9') && (excl[5] < '0' || excl[5] > '9') && (excl[6] < '0' || excl[6] > '9')
					&& (excl[7] < '0' || excl[7] > '9'));
			Chave.chave = excl;
			Arvore.remover(Chave);
			break;
		case('3'):
			do{
				cout << "Qual chave deseja procurar? ";
				cin >> busca;
				if (busca.size() != 8 && (busca[0] < 'A' || busca[0] > 'Z') && (busca[1] < 'A' || busca[1] > 'Z') && (busca[2] < 'A' || busca[2] > 'Z')
					&& (busca[3] < '0' || busca[3] > '9') && (busca[4] < '0' || busca[4] > '9') && (busca[5] < '0' || busca[5] > '9') && (busca[6] < '0' || busca[6] > '9')
					&& (busca[7] < '0' || busca[7] > '9'))
					cout << "Chave inválida" << endl;
			}while(busca.size() != 8 && (busca[0] < 'A' || busca[0] > 'Z') && (busca[1] < 'A' || busca[1] > 'Z') && (busca[2] < 'A' || busca[2] > 'Z')
					&& (busca[3] < '0' || busca[3] > '9') && (busca[4] < '0' || busca[4] > '9') && (busca[5] < '0' || busca[5] > '9') && (busca[6] < '0' || busca[6] > '9')
					&& (busca[7] < '0' || busca[7] > '9'));
			Chave.chave = busca;
			//Arvore.search(Chave);
			break;
		case('4'):
			return 0;
	}
	return 1;
}



int main(){
	char lista[] = "lista.txt";
	ArvoreB Arvore;

	Arvore.criar(lista);

	while(menu(Arvore));

	return 0;
}