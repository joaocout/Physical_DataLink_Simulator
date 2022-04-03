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
    //usando getline, para que espacos tambem sejam lidos
    getline(std::cin, mensagem);
    
    CamadaDeAplicacaoTransmissora(mensagem);
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

    CamadaFisicaTransmissora(quadro);
}


void CamadaFisicaTransmissora(vector<int> quadro){
    int tipoDeCodificacao = 1;
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


vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(vector<int> quadro){
    //codificacao binaria pode retornar os bits diretamente
    return quadro;
}

vector<int> CamadaFisicaTransmissoraCodificacaoManchester(vector<int> quadro){
    vector<int> result;
    bitset<2> clock("01");
    
    for(int bit: quadro) {
        //XOR do bit com os bits do clock

        //se o bit for 1, invertemos o clock
        if(bitset<1> (bit).any()) {
            for(char c: (~clock).to_string()) {
                result.push_back(c - '0');
            }
        }
        //se for zero, o valor eh igual ao clock
        else{
            for(char c: clock.to_string()){
                result.push_back(c - '0');
            }
        }
    }

    return result;
}

vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(vector<int> quadro){

    return quadro;
}


void MeioDeComunicacao(vector<int> fluxoBrutoDeBits){
    vector<int> fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits, fluxoBrutoDeBitsPontoB;

    //passando os bits do ponto A para o ponto B
    for(int value : fluxoBrutoDeBitsPontoA) {
        fluxoBrutoDeBitsPontoB.push_back(value);
    }
    CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}


void CamadaFisicaReceptora(vector<int> quadro){
    int tipoDeCodificacao = 1;
    vector<int> fluxoBrutoDeBits;

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


vector<int> CamadaFisicaReceptoraDecodificacaoBinaria(vector<int> quadro){
    //podemos retornar os bits diretamente
    return quadro;
}

vector<int> CamadaFisicaReceptoraDecodificacaoManchester(vector<int> quadro){
    vector<int> result;

    //clock como string de bits pra facilitar comparacao
    const string clock = "01";

    for(unsigned int i=0; i<quadro.size(); i+=2) {
        //criando par de bits atual
        string bit_pair = to_string(quadro[i]) + to_string(quadro[i+1]);
        // se o par de bits for igual ao clock, retornamos 0
        if(bit_pair == clock) {
            result.push_back(0);
        }
        // se o par de bits for diferente do clock, retornamos 1
        else{
            result.push_back(1);
        }
    }
    return result;
}

vector<int> CamadaFisicaReceptoraDecodificacaoBipolar(vector<int> quadro){
    return quadro;
}


void CamadaDeAplicacaoReceptora(vector<int> quadro){
    string mensagem = "";

    //transformando o quadro pra string de bits, pra facilitar conversao
    string string_quadro = "";
    for (int bit: quadro) {
        string_quadro.append(to_string(bit));
    }

    //transformando os bitsets de tamanho 8, de volta para char, de acordo com a tabela ascii
    for(unsigned int i=0; i<string_quadro.size(); i+=8) {
        cout << string_quadro.substr(i, 8) << ":" <<(char) bitset<8>(string_quadro.substr(i, 8)).to_ulong() << endl;
        mensagem.push_back((char)bitset<8>(string_quadro.substr(i, 8)).to_ullong());
    }

    AplicacaoReceptora(mensagem);
}


void AplicacaoReceptora(string mensagem){
    cout << "A mensagem recebida foi: " << mensagem << endl;
}