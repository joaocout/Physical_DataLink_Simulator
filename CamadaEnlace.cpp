#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include "CamadaFisica.hpp"
#include "CamadaEnlace.hpp"

using namespace std;

int main () {

    // lendo msg
    string mensagem;
    std::cout << "Digite uma mensagem:" << endl;
    getline(std::cin, mensagem);

    vector<int> quadro;

    //transformando em bits
    for(char c: mensagem){
        //caracter ja transformado para bits, de acordo com a tabela ascii
        string ascii_code = bitset<8>(c).to_string();
        //salvando no vector, cada bit do codigo ascii, como inteiro
        for(char c: ascii_code){
            quadro.push_back(c - '0');
        }
    }

    CamadaEnlaceDadosTransmissora(quadro);

    return 0;

}

void CamadaEnlaceDadosTransmissora(vector<int> quadro){
    CamadaEnlaceDadosTransmissoraEnquadramento(quadro);
    // CamadaEnlaceDadosTransmissoraControleDeErro(quadro);
    // CamadaFisicaTransmissora(quadro);
}

void CamadaEnlaceDadosTransmissoraEnquadramento(vector<int> quadro){
    int tipoDeEnquadramento = 1;
    vector<int> quadroEnquadrado;

    switch(tipoDeEnquadramento){
        case 0:
            quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(quadro);
            break;
        case 1:
            quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(quadro);
            break;
    }

    CamadaEnlaceDadosReceptora(quadroEnquadrado);
}

void CamadaEnlaceDadosTransmissoraControleDeErro(vector<int> quadro){

}

vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(vector<int> quadro){
    vector <int> result;

    // cabecalho = 1100 (12)
    vector<int> cabecalho;
    for(char value : string("1100")) {
        cabecalho.push_back(value - '0');
    }

    int i = 0;
    // campo de carga util sempre com tamanho 8
    for(int value : quadro) {
        // a cada 8 bits, inserir cabecalho antes
        if(i%8 == 0) result.insert(result.end(), cabecalho.begin(), cabecalho.end());
        result.push_back(value);
        i++;
    }

    return result;
}

vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(vector<int> quadro){
    vector<int> result;

    for(int value : quadro) cout << value;
    cout << endl;

    vector<int> esc, flag;
    string s_esc = "00011011", s_flag = "00001111";
    for(char value : s_flag) {
        flag.push_back(value - '0');
    }

    // setando esc = 0001 1011
    for(char value : s_esc) {
        esc.push_back(value - '0');
    }

    int i = 0;
    // campo de carga util sempre com tamanho 8
    for(int value : quadro) {
        // inserindo flag no inicio
        if(i%8 == 0) result.insert(result.end(), flag.begin(), flag.end());

        result.push_back(value);
        i++;

        // inserindo flag no fim
        if(i%8 == 0) result.insert(result.end(), flag.begin(), flag.end());
    }
 
    // salvando vetor num string temporario, pra facilitar insercao de esc
    string temp = "";
    for(int value : result) {
        temp.push_back(value + '0');
    }

    // como escolhemos tamanhos fixos para os quadros, a carga util vira em posicoes fixas (1, 4, 7, 10 ...)
    int i_byte = 0; // indice do byte atual
    int i_prox_carga_util = 1; // indice da prox carga util

    for(int i = 0; i<temp.size(); i+=8) {
        string s = temp.substr(i, 8);   // byte atual

        // indice do byte atual eh igual ao indice do prox byte de carga util
        if(i_byte == i_prox_carga_util) {
            
            // se for um esc ou flag, adicionamos esc antes
            if(s == s_esc || s == s_flag) result.insert(result.begin()+i, esc.begin(), esc.end());
            i_prox_carga_util += 3;
        }

        i_byte++;
    }

    return result;
}

void CamadaEnlaceDadosReceptora(vector<int> quadro){
    CamadaEnlaceDadosReceptoraEnquadramento(quadro);
    // CamadaEnlaceDadosReceptoraControleDeErro(quadro);
    // CamadaDeAplicacaoReceptora(quadro);
}

void CamadaEnlaceDadosReceptoraEnquadramento(vector<int> quadro){
    int tipoDeEnquadramento = 1;
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

vector<int> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(vector<int> quadro){
    vector<int> result;

    // transformando pra string pra facilitar retirada de header
    string temp = "";
    for(int value : quadro) temp.push_back(value + '0');

    // lendo primeiros bits do header e transformando pra int
    string next_header = temp.substr(0, 4);
    int size_next_quadro = bitset<4>(next_header).to_ullong() - 4;

    for(int i = 4; i<temp.size(); i++) {
        if(size_next_quadro > 0) {
            result.push_back(temp[i] - '0');
            size_next_quadro--;
        }
        else {
            next_header = temp.substr(i, 4);
            size_next_quadro = bitset<4>(next_header).to_ullong() - 4;
            i+=3;
        }
    }
    return result;

}

vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(vector<int> quadro){
    vector<int> result;

    for(int value : quadro) cout << value;
    cout << endl;

    vector<int> esc, flag;
    string s_esc = "00011011", s_flag = "00001111";
    // setando flag = 0000 1111
    for(char value : s_flag) flag.push_back(value - '0');

    // setando esc = 0001 1011
    for(char value : s_esc) esc.push_back(value - '0');

    string temp = "";
    for(int value : quadro) temp.push_back(value + '0');
    
    bool last_esc = false;
    bool iniciou = false;
    for(int i=0; i<temp.size(); i+=8) {
        string s = temp.substr(i, 8);

        // se o ultimo byte eh esc, salvamos o atual independenete do conteudo
        if(last_esc) {
            for (char value: s) result.push_back(value - '0');
            last_esc = false;
        }
        else {
            // se chegou em um esc, devemos lembrar, pois o prox byte eh cargo util
            if(s == s_esc) last_esc = true;

            // pulando bytes de flag
            else if(s == s_flag) {
                // chegou na primeira flag, entao eh o inicio
                if(iniciou == false) iniciou = true;
                // chegou na proxima flag, entao eh o final
                else iniciou = false;
            }
            else {
                // passando bits pra resultado
                for (char value : s) result.push_back(value - '0');
            }
        }
    }

    return result;
}