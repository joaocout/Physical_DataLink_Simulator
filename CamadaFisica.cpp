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
    getline(std::cin, mensagem);
    
    CamadaDeAplicacaoTransmissora(mensagem);
}

void CamadaDeAplicacaoTransmissora(string mensagem){
    vector<int> quadro;
    
    //convertendo cada char para bits e salvando no vector quadro
    for(char c: mensagem){
        //caracter ja transformado para bits, de acordo com a tabela ascii
        string ascii_code = bitset<8>(c).to_string();
        //salvando no vector como inteiro
        for(char c: ascii_code){
            quadro.push_back(c - '0');
        }
    }

    CamadaFisicaTransmissora(quadro);
}


void CamadaFisicaTransmissora(vector<int> quadro){
    int tipoDeCodificacao = 0;
    vector<int> fluxoBrutoDeBits;

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

//binaria pode retornar os bits diretamente (?)
vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(vector<int> quadro){
    vector<int> result = quadro;
    return result;
}

vector<int> CamadaFisicaTransmissoraCodificacaoManchester(vector<int> quadro){
    vector<int> result = quadro;

    return result;
}

vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(vector<int> quadro){
    vector<int> result = quadro;

    return result;
}

void MeioDeComunicacao(vector<int> fluxoBrutoDeBits){
    vector<int> fluxoBrutoDeBitsPontoA, fluxoBrutoDeBitsPontoB;

    fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

    for(int value : fluxoBrutoDeBitsPontoA) {
        fluxoBrutoDeBitsPontoB.push_back(value);
    }


    //chegou ate aqui
    for(int i: fluxoBrutoDeBitsPontoB){
        cout << i;
    }

    cout << endl;
}

/*
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