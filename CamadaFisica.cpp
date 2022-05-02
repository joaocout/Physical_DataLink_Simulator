#include <iostream>
#include <string>
#include <bitset>
#include <vector>

#include "CamadaFisica.hpp"

using namespace std;

/*
int main(){
    AplicacaoTransmissora();
    return 0;
}
*/

int encoding;

void AplicacaoTransmissora(string input, int selected_encoding){
    //string mensagem;
    //std::cout << "Digite uma mensagem:" << endl;
    //usando getline, para que espacos tambem sejam lidos
    //getline(std::cin, mensagem);

    encoding = selected_encoding;

    CamadaDeAplicacaoTransmissora(input);
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
    int tipoDeCodificacao = encoding;
    vector<int> fluxoBrutoDeBits;


    cout << endl << "Mensagem após transformação para bits: " << endl;
    for(int bit: quadro){
        cout << bit;
    }
    cout << endl;


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


    cout << endl << "Quadro codificado: " << endl;
    for(int value: fluxoBrutoDeBits) {
        cout << value;
    }
    cout << endl;


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
    //valores podem ser 0, 1 e -1
    vector<int> result;

    // salvando valor do ultimo bit 1
    int last_value = 0;
    for(int bit: quadro){
        //se o bit for 0, o valor retorna pra zero
        if(bit == 0) {
            result.push_back(bit);
        }
        //se nao, o valor pode ser 1 ou -1
        else {
            //se ainda nao houveram bits 1, o valor eh 1, e setamos previous pra 1
           if(last_value == 0) {
               result.push_back(1);
               last_value = 1;
           } 
           // se o anterior foi 1, o proximo deve ser -1
           else if(last_value == 1) {
               result.push_back(-1);
               last_value = -1;
           }
           // se o anterior foi -1, o proximo deve ser 1
           else {
               result.push_back(1);
               last_value = 1;
           }
        }
    }

    return result;
}


void MeioDeComunicacao(vector<int> fluxoBrutoDeBits){
    int erro, porcentagemDeErros = 0;
    vector<int> fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits, fluxoBrutoDeBitsPontoB;

    //passando os bits do ponto A para o ponto B
    for(int i = 0; i < fluxoBrutoDeBitsPontoA.size(); i++){
        if((rand()%100) >= 50){
            fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA[i]);
        } else {
            fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA[i] == 0 ? 1 : 0);
        }
    }
    // for(int value : fluxoBrutoDeBitsPontoA) {
    //     if((rand()%100) >= 50){

    //     }
    //     fluxoBrutoDeBitsPontoB.push_back(value);
    // }
    CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}


void CamadaFisicaReceptora(vector<int> quadro){
    int tipoDeCodificacao = encoding;
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


    cout << endl << "Quadro após decodificação: " << endl;
    for(int bit: fluxoBrutoDeBits) {
        cout << bit;
    }
    cout << endl;

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
    vector<int> result;

    for(int value: quadro) {
        if(value!=0){
            // se o valor for 1, ou -1, era originalmente 1
            result.push_back(1);
        }
            // se o valor for 0, era originalmente 0
        else {
            result.push_back(0);
        }
    }   
    return result;

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
        mensagem.push_back((char)bitset<8>(string_quadro.substr(i, 8)).to_ullong());
    }

    AplicacaoReceptora(mensagem);
}


void AplicacaoReceptora(string mensagem){
    cout << endl << "A mensagem recebida foi: " << mensagem << endl << endl;
}