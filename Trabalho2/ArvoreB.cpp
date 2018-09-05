#include "ArvoreB.hpp"

bool EhMaior(RegistroP chave1, RegistroP chave2){
    for (int i = 0; i < 7; ++i)
        if(chave1.chave[i] < chave2.chave[i]) return false;
    return true;
}

No::No(int ordem, bool EhFolha1){
    int t = ordem;
    EhFolha = EhFolha1;

    chaves = new RegistroP [t-1];
    filhos = new No *[t];

    numero = 0;
}

No* No::procura(RegistroP Registro){
    int i = 0;
    while (i < numero && EhMaior(Registro, chaves[i]))
        i++;
 
    if (chaves[i].chave == Registro.chave)
        return this;
 
    if (EhFolha == true)
        return NULL;
 
    return filhos[i]->procura(Registro);
}

int No::procuraChave(RegistroP Registro){
    int pos = 0;
    while(pos < numero && !EhMaior(chaves[pos], Registro)){
        ++pos;
    }
    return pos;
}

void No::incerirNaoCheio(RegistroP Registro){
    int i = numero-1;
 
    if (EhFolha)
    {
        while (i >= 0 && EhMaior(chaves[i], Registro))
        {
            chaves[i+1] = chaves[i];
            i--;
        }
 
        chaves[i+1] = Registro;
        numero = numero+1;
    }
    else 
    {
        while (i >= 0 && EhMaior(chaves[i], Registro))
            i--;
 
        if (filhos[i+1]->numero == ordem-1)
        {
            dividirFilho(i+1, filhos[i+1]);
 
            if (!EhMaior(chaves[i+1], Registro))
                i++;
        }
        filhos[i+1]->incerirNaoCheio(Registro);
    }
}

void No::dividirFilho(int NumFilho, No *noF){
    int grau = ordem/2;
    No *temp = new No(noF->ordem, noF->EhFolha);
    temp->numero = grau - 1;

    for (int i = 0; i < grau-1; ++i)
        temp->chaves[i] = noF->chaves[i+grau];

    if (noF->EhFolha == false){
        for (int i = 0; i < grau; ++i)
            temp->filhos[i] = noF->filhos[i+grau];
    }
    
    noF->numero = grau-1;

    for (int i = numero; i >= NumFilho+1; --i)
        filhos[i+1] = filhos[i];

    filhos[NumFilho+1] = temp;

    for (int i = numero - 1; i >= NumFilho; --i)
        chaves[i+1] = chaves[grau - 1];

    chaves[NumFilho] = noF->chaves[grau - 1];

    numero += 1;

}

void No::remover(RegistroP Registro){
    int pos = procuraChave(Registro);

    if (pos < numero && chaves[pos].chave == Registro.chave){
        if(EhFolha)
            removeDaFolha(pos);
        else
            removeDaNaoFolha(pos);
    }
    else{
        if(EhFolha){
            cout << "A chave " << Registro.chave << "não existe";
            return;
        }

        bool flag = ((pos == numero)? true : false);

        if(filhos[pos]->numero < ordem/2)
            fill(pos);

        if(flag && pos > numero)
            filhos[pos-1]->remover(Registro);
        else
            filhos[pos]->remover(Registro);
    }
    return;
}

void No::removeDaFolha(int pos){
    for (int i = pos+1; i < numero; ++i)
        chaves[i-1] = chaves[i];

    numero--;

    return;
}

void No::removeDaNaoFolha(int pos){
    RegistroP reg = chaves[pos];

    if(filhos[pos]->numero >= ordem/2){
        RegistroP ant = getAnterior(pos);
        chaves[pos] = ant;
        filhos[pos]->remover(ant);
    }

    else if(filhos[pos+1]->numero >= ordem/2){
        RegistroP prox = getSucessor(pos);
        chaves[pos] = prox;
        filhos[pos+1]->remover(prox);
    }

    else{
        merge(pos);
        filhos[pos]->remover(reg);
    }
    return;
}

RegistroP No::getAnterior(int pos){
    No *temp = filhos[pos];
    while(!temp->EhFolha)
        temp = temp->filhos[temp->numero];

    return temp->chaves[temp->numero-1];
}

RegistroP No::getSucessor(int pos){
    No *temp = filhos[pos + 1];
    while(!temp->EhFolha)
        temp = temp->filhos[0];

    return temp->chaves[0];
}

void No::fill(int pos){
    if (pos!=0 && filhos[pos-1]->numero>=ordem/2)
        pegaDoAnterior(pos);
 
    else if (pos!=numero && filhos[pos+1]->numero>=ordem/2)
        pegaDoProximo(pos);
 
    else
    {
        if (pos != numero)
            merge(pos);
        else
            merge(pos-1);
    }
    return;
}

void No::pegaDoAnterior(int pos){
    No *filho=filhos[pos];
    No *primo=filhos[pos-1];
 
    for (int i=filho->numero-1; i>=0; i--)
        filho->chaves[i+1] = filho->chaves[i];
 
    if (!filho->EhFolha)
    {
        for(int i=filho->numero; i>=0; i--)
            filho->filhos[i+1] = filho->filhos[i];
    }
 
    filho->chaves[0] = chaves[pos-1];
 
    if(!filho->EhFolha)
        filho->filhos[0] = primo->filhos[primo->numero];
 
    chaves[pos-1] = primo->chaves[primo->numero-1];
 
    filho->numero += 1;
    primo->numero -= 1;
 
    return;
}

void No::pegaDoProximo(int pos){
    No *filho=filhos[pos];
    No *primo=filhos[pos+1];
 
    filho->chaves[(filho->numero)] = chaves[pos];
 
    if (!(filho->EhFolha))
        filho->filhos[(filho->numero)+1] = primo->filhos[0];
 
    chaves[pos] = primo->chaves[0];
 
    for (int i=1; i<primo->numero; ++i)
        primo->chaves[i-1] = primo->chaves[i];
 
    if (!primo->EhFolha)
    {
        for(int i=1; i<=primo->numero; ++i)
            primo->filhos[i-1] = primo->filhos[i];
    }
 
    filho->numero += 1;
    primo->numero -= 1;
 
    return;
}

void No::merge(int pos){
    No *filho = filhos[pos];
    No *primo = filhos[pos+1];
 
    filho->chaves[(ordem/2)-1] = chaves[pos];
 
    for (int i=0; i<primo->numero; ++i)
        filho->chaves[i+(ordem/2)] = primo->chaves[i];
 
    if (!filho->EhFolha)
    {
        for(int i=0; i<=primo->numero; ++i)
            filho->filhos[i+(ordem/2)] = primo->filhos[i];
    }
 
    for (int i=pos+1; i<numero; ++i)
        chaves[i-1] = chaves[i];
 
    for (int i=pos+2; i<=numero; ++i)
        filhos[i-1] = filhos[i];
 
    filho->numero += primo->numero+1;
    numero--;
 
    delete(primo);
    return;
}

void ArvoreB::visualizar(){
    
}

void ArvoreB::incerir(RegistroP Registro){
    int ordem = 4;
    if (caminho == NULL)
    {
        caminho = new No(4, true);
        caminho->chaves[0] = Registro;
        caminho->numero = 1;
    }
    else
    {
        if (caminho->numero == ordem-1)
        {
            No *s = new No(4, false);
 
            s->filhos[0] = caminho;
 
            s->dividirFilho(0, caminho);
 
            int i = 0;
            if (!EhMaior(s->chaves[0], Registro))
                i++;
            s->filhos[i]->incerirNaoCheio(Registro);
 
            caminho = s;
        }
        else 
            caminho->incerirNaoCheio(Registro);
    }
}

void ArvoreB::remover(RegistroP Registro){
    if (!caminho)
    {
        cout << "Arvore vazia" << endl;
        return;
    }
 
    caminho->remover(Registro);
 
    if (caminho->numero==0)
    {
        No *tmp = caminho;
        if (caminho->EhFolha)
            caminho = NULL;
        else
            caminho = caminho->filhos[0];
 
        delete tmp;
    }
    return;
}

void ArvoreB::criar(char *arquivo){
    ifstream File;
    string matricula, nome, curso, chave, aux, turma;
    RegistroP ChaveP;
    int n;

    File.open(arquivo);
    if(!File.is_open()){
        cout << "Arquivo nao encontrado" << endl;
        exit(EXIT_FAILURE);
    }

    do{                     // laço de repetição para executar enquanto o arquivo não acaba
        File >> nome;
        ChaveP.completo = nome + ' ';
        aux = nome;
        aux[0] = toupper(aux[0]);
        chave = aux[0];
        aux[1] = toupper(aux[1]);
        chave = chave + aux[1];
        aux[2] = toupper(aux[2]);
        chave = chave + aux[2];
        do{
            File >> nome;
            if(nome[0] < '0' || nome[0] > '9') ChaveP.completo += nome + ' ';
            else{
                matricula = nome;
                ChaveP.completo += '\t' + matricula ;
                break;
            }
        }while((nome[0] < '0' || nome[0] > '9'));
        ChaveP.completo += '\t';
        chave = chave + matricula;
        ChaveP.chave = chave;
        File >> curso;
        ChaveP.completo += curso + '\t';
        File >> turma;
        ChaveP.completo += turma + '\t';

        this->incerir(ChaveP);
    }while(File.good());
    cout << endl;
    File.close();
}