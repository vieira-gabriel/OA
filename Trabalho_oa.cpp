/*
	Universidade de Brasilia - Departamento de Ciência da Computacao
	Organizacao de Arquivos - Turma C
	Gabriel Vieira Arimatea - 15/0126956
	Vanessa Rodrigues Galeno - 16/0147069
*/

#include<stdio.h>
#include<stdlib.h>
#include <string>
#include <cstring>
#include <stdexcept>
#include<string.h>
#include <iostream>
#include <fstream>

using namespace std;


void menu(){
	int resp=0;

	do{
		printf("Escolha uma das opcoes e digite o numero correspondente:\n");
		printf("1) Incluir registros.\n2) Excluir registros.\n3) Atualizar registros.\n4) Visualizar todos os registros.\n");
		scanf("%d",&resp);
		if(resp<1 || resp>4)
			printf("\nOpcao inválida, escolha uma das opcoes abaixo:\n\n");
	}while(resp<1 || resp>4);

	switch(resp){
		case(1):
			printf("Te enganei, nao da pra incluir ainda.\n");
			break;
		case(2):
			printf("Te enganei, nao da pra excluir ainda.\n");
			break;
		case(3):
			printf("Te enganei, nao da pra atualizar ainda.\n");
			break;
		case(4):
			printf("Te enganei, nao da pra visualizar ainda.\n");
			break;
	}
}

int main(){
	menu();

	return 0;
}