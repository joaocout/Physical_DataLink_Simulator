#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include "CamadaFisica.hpp"

void CamadaEnlaceDadosTransmissora(vector<int> quadro){
    CamadaEnlaceDadosTransmissoraEnquadramento(quadro);
    CamadaEnlaceDadosTransmissoraControleDeErro(quadro);
    CamadaFisicaTransmissora(quadro);
}
void CamadaEnlaceDadosTransmissoraEnquadramento(vector<int> quadro){
    int tipoDeEnquadramento = 0;
    vector<int> quadroEnquadrado;

    switch(tipoDeEnquadramento){
        case 0:
            quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(quadro);
            break;
        case 1:
            quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(quadro);
            break;
    }
}
void CamadaEnlaceDadosTransmissoraControleDeErro(vector<int> quadro){
    int tipoDeControleDeErro = 0;

    switch(tipoDeControleDeErro){
        case 0:
            //bit de paridade
            break;
        case 1:
            //CRC
            break;
    }

}

void CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(vector<int> quadro){

}

void CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(vector<int> quadro){

}

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(){

}

void CamadaEnlaceDadosTransmissoraControleDeErroCRC(){
    //polinomio CRC-32(IEEE 802)
}

void CamadaEnlaceDadosReceptora(vector<int> quadro){
    CamadaEnlaceDadosReceptoraEnquadramento(quadro);
    CamadaEnlaceDadosReceptoraControleDeErro(quadro);
    CamadaDeAplicacaoReceptora(quadro);
}

void CamadaEnlaceDadosReceptoraEnquadramento(vector<int> quadro){
    int tipoDeEnquadramento = 0;
    vector<int> quadroDesenquadrado;

    switch(tipoDeEnquadramento){
        case 0:
            quadroDesenquadrado = CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(quadro);
            break;
        case 1:
            quadroDesenquadrado = CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(quadro);
            break;
    }
}

void CamadaEnlaceDadosReceptoraControleDeErro(vector<int> quadro){

}

void CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(vector<int> quadro){

}

void CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(vector<int> quadro){

}