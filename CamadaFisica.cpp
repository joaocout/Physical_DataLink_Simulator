#include <iostream>
#include <string>
#include "CamadaFisica.hpp"

using namespace std;

void main(){
    AplicacaoTransmissora();
}

void AplicacaoTransmissora(){
    string mensagem;
    cout << "Digite uma mensagem:" << endl;
    cin >> mensagem;

    CamadaDeAplicacaoTransmissora(mensagem);
}

void CamadaDeAplicacaoTransmissora(string mensagem){
    int quadro[] = mensagem;
    CamadaFisicaTransmissora(quadro);
}

void CamadaFisicaTransmissora(int quadro[]){
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

int[] CamadaFisicaTransmissoraCodificacaoBinaria(int quadro[]){
    
}

int[] CamadaFisicaTransmissoraCodificacaoManchester(int quadro[]){
    
}

int[] CamadaFisicaTransmissoraCodificacaoBipolar(int quadro[]){
    
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

int[] CamadaFisicaReceptoraCodificacaoBinaria(int quadro[]){
    
}

int[] CamadaFisicaReceptoraCodificacaoManchester(int quadro[]){
    
}

int[] CamadaFisicaReceptoraCodificacaoBipolar(int quadro[]){
    
}

void CamadaDeAplicacaoReceptora(int quadro[]){
    string mensagem = quadro[];
    AplicacaoReceptora(mensagem);
}

void AplicacaoReceptora(string mensagem){
    cout << "A mensagem recebida foi:" << mensagem << endl;
}

