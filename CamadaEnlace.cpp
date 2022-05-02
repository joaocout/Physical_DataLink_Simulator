#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include "CamadaFisica.hpp"
#include "CamadaEnlace.hpp"
#include <inttypes.h>

using namespace std;

int main(){
    string test;
    getline(std::cin, test);
    CamadaDeAplicacaoTransmissora(test);
    return 0;
}

void CamadaDeAplicacaoTransmissora(string mensagem){
    //usando vector de int, ao inves de int[], por ser um recurso padrao do c++
    //vector tem tamanho variavel, e nos auxilia com certas funcionalidades
    vector<int> quadro;
    
    //convertendo cada char para bits e salvando no vector quadro
    for(char c: mensagem){
        //caracter ja transformado para bits, de acordo com a tabela ascii
        string ascii_code = bitset<8>(c).to_string();
        //salvando no vector, cada bit do codigo ascii, como inteiro
        for(char c: ascii_code){
            quadro.push_back(c - '0');
        }
    }

    CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro);

    //CamadaFisicaTransmissora(quadro);
}

void CamadaEnlaceDadosTransmissora(vector<int> quadro){
    CamadaEnlaceDadosTransmissoraEnquadramento(quadro);
    CamadaEnlaceDadosTransmissoraControleDeErro(quadro);
    //CamadaFisicaTransmissora(quadro);
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
            CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro);
            break;
        case 2:
            //Hamming
            break;
    }

}

vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(vector<int> quadro){

}

vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(vector<int> quadro){

}

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(vector<int> quadro){

}

void CamadaEnlaceDadosTransmissoraControleDeErroCRC(vector<int> quadro){
    static uint32_t tabela[256];
    bool tabelaCriada = false;
    uint32_t resto, crc = 0;
    uint8_t octeto;
    const char *p, *q;
    vector<int>resultado;

    if (!tabelaCriada){
        for (int i = 0; i < 256; i++){
            resto = i;
            for (int j = 0; j < 8; j++){
                if (resto & 1){
                    resto >>= 1;
                    resto ^= 0xedb88320;
                }
                else{
                    resto >>= 1;
                }
            }
            tabela[i] = resto;
        }
        tabelaCriada = true;
    }

    crc = ~crc;

    //transformando o quadro pra string de bits, pra facilitar conversao
    string string_quadro = "";
    for (int bit:quadro){
        string_quadro.append(to_string(bit));
    }
    string mensagem = "";
    //transformando os bitsets de tamanho 8, de volta para char, de acordo com a tabela ascii
    for (unsigned int i = 0; i < string_quadro.size(); i += 8){
        mensagem.push_back((char) bitset <8> (string_quadro.substr(i, 8)).to_ullong());
    }
    q = &mensagem[0] + mensagem.size();
    for (p = &mensagem[0]; p < q; p++){
        octeto = *p;
        crc = (crc >> 8) ^ tabela[(crc & 0xff) ^ octeto];
    }

    bitset<32> bitsCrc(crc);
    //cout << bitsCrc << endl;
    string crcToConvert = (bitsCrc.to_string());
    for(int k = 0; k < crcToConvert.size(); k++){
        quadro.push_back(crcToConvert[k]-'0');
    }
    
    // for (int element : quadro){
    //     cout << element;
    // }

    //printf("\n%" PRIX32 "\n", ~crc);

    //polinomio CRC-32(IEEE 802)
}

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCodigoHamming(vector<int> quadro){

}

void CamadaEnlaceDadosReceptora(vector<int> quadro){
    CamadaEnlaceDadosReceptoraEnquadramento(quadro);
    CamadaEnlaceDadosReceptoraControleDeErro(quadro);
    //CamadaDeAplicacaoReceptora(quadro);
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
    int tipoDeControleDeErro = 0;

    switch(tipoDeControleDeErro){
        case 0:
            //bit de paridade
            break;
        case 1:
            //CRC
            break;
        case 2:
            //codigo de hamming
            break;
    }
}

vector<int> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(vector<int> quadro){

}

vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(vector<int> quadro){

}

vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar(vector<int> quadro){
    //verificar se houve erro
}

vector<int> CamadaEnlaceDadosReceptoraControleDeErroCRC(vector<int> quadro){
    //verificar se houve erro
    
}

vector<int> CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(vector<int> quadro){
    //verificar se houve erro
}