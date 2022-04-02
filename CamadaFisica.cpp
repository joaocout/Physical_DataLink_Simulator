#include <iostream>
#include <string>
#include <bitset>
#include <vector>

#include "CamadaFisica.hpp"

using namespace std;

int main(){
    AplicacaoTransmissora();
    return 0;
}

void AplicacaoTransmissora(){
    string mensagem;
    cout << "Digite uma mensagem:" << endl;
    cin >> mensagem;

    CamadaDeAplicacaoTransmissora(mensagem);
}

void CamadaDeAplicacaoTransmissora(string mensagem){
    
    string bits;
    for(char c: mensagem){
        //convertendo cada char pra bits
        bits.append((bitset<8>(c)).to_string());
    }

    //mensagem convertida pra bits
    bitset<8> quadro(bits);

    cout << quadro << endl;

    //CamadaFisicaTransmissora(quadro);
}


/*
void CamadaFisicaTransmissora(vector<int> quadro){
    int tipoDeCodificacao = 0;
    int fluxoBrutoDeBits[];

    switch (tipoDeCodificacao)
    {
    case 0:
        fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
        break;
    case 1:
        fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);
        break;
    case 2:
        fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBipolar(quadro);
        break;
    default:
        break;
    }
    MeioDeComunicacao(fluxoBrutoDeBits);
}

void MeioDeComunicacao(int fluxoBrutoDeBits[]){
    int fluxoBrutoDeBitsPontoA[], fluxoBrutoDeBitsPontoB[];

    fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

    while (fluxoBrutoDeBitsPontoB.length != fluxoBrutoDeBitsPontoA)
    {
        fluxoBrutoDeBitsPontoB += fluxoBrutoDeBitsPontoA;
    }

    CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
    
}

void CamadaFisicaReceptora(int quadro[]){
    int tipoDeCodificacao = 0;
    int fluxoBrutoDeBits[];

    switch (tipoDeCodificacao)
    {
    case 0:
        fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoBinaria(quadro);
        break;
    case 1:
        fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoManchester(quadro);
        break;
    case 2:
        fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoBipolar(quadro);
        break;
    default:
        break;
    }
    CamadaDeAplicacaoReceptora(fluxoBrutoDeBits);
}

void CamadaDeAplicacaoReceptora(int quadro[]){
    string mensagem = quadro[];
    AplicacaoReceptora(mensagem);
}

int* CamadaFisicaTransmissoraCodificacaoBinaria(int quadro[]){
    
}

int* CamadaFisicaTransmissoraCodificacaoManchester(int quadro[]){
    
}

int* CamadaFisicaTransmissoraCodificacaoBipolar(int quadro[]){
    
}

int[] CamadaFisicaReceptoraCodificacaoBinaria(int quadro[]){
    
}

int[] CamadaFisicaReceptoraCodificacaoManchester(int quadro[]){
    
}

int[] CamadaFisicaReceptoraCodificacaoBipolar(int quadro[]){
    
}

void AplicacaoReceptora(string mensagem){
    cout << "A mensagem recebida foi:" << mensagem << endl;
}
*/