#include <stdexcept>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdbool.h>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>

using namespace std;

int main(){
	ofstream BD;							// Objeto do arquivo para escrita
	ifstream BDs;							// Objeto do arquivo para leitura
	string nome, numero;

	BD.open("usuarios.txt");				// Abre arquivo
	BD << "teste 1\n";						// Escreve no arquivo
	BD.close();								// Fecha arquivo de escrita


	BDs.open("usuarios.txt");				// Abre arquivo

	BDs >> nome;							// Lê uma string até o " "
	cout << nome << " ";					// Similar ao printf. Imprime "nome" e depois imprime " "
	BDs >> numero;							// Pega o número que está logo após o nome
	cout << numero << endl;					// Imprime "numero". endl = \n

	BDs.close();							// Fecha arquivo de leitura

	cout << "Fim do primeiro teste" << endl << endl;

	BD.open("usuarios.txt",std::fstream::app);	// Aqui ele abre um arquivo existente pra escrita, caso n exista o "app" no final,
												//ele sobrescreve no que ja existia no arquivo
	BD << "teste 2\n";
	BD.close();

	BDs.open("usuarios.txt");

	BDs >> nome;
	BDs >> numero;
	while(BDs.good()){						// laço de repetição para executar enquanto o arquivo não acaba
		cout << nome << " ";
		cout << numero << endl;
		BDs >> nome;
		BDs >> numero;
	}
	BDs.close();
	return 0;
}