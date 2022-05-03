#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <math.h>
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

    CamadaEnlaceDadosTransmissora(quadro);

    // CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro);

    // CamadaFisicaTransmissora(quadro);
}

void CamadaEnlaceDadosTransmissora(vector<int> quadro){
    CamadaEnlaceDadosTransmissoraEnquadramento(quadro);
    CamadaEnlaceDadosTransmissoraControleDeErro(quadro);
    //CamadaFisicaTransmissora(quadro);
}


// ENQUADRAMENTO
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
// FIM ENQUADRAMENTO


// CONTROLE DE ERRO
void CamadaEnlaceDadosTransmissoraControleDeErro(vector<int> quadro){
    int tipoDeControleDeErro = 2;

    switch(tipoDeControleDeErro){
        case 0:
            CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro); 
            break;
        case 1:
            //CRC
            CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro);
            break;
        case 2:
            //Hamming
            CamadaEnlaceDadosTransmissoraControleDeErroCodigoHamming(quadro);
            break;
    }

}

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(vector<int> quadro){

    int cont = 0;

	for (int i = 0; i < quadro.size(); i++){
		if(quadro[i] == 1) {
			cont++;
		}
	}
    if (cont % 2 == 0){
        quadro.push_back(0);
    } else {
        quadro.push_back(1);
    }

    return quadro;

}

void CamadaEnlaceDadosTransmissoraControleDeErroCRC(vector<int> quadro){
    static uint32_t tabela[256];
    bool tabelaCriada = false;
    uint32_t resto, crc = 0;
    uint8_t octeto;
    const char *p, *q;
    vector < int >resultado;

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
        string_quadro.append(to_string (bit));
    }
    string mensagem = "";
    //transformando os bitsets de tamanho 8, de volta para char, de acordo com a tabela ascii
    for (unsigned int i = 0; i < string_quadro.size(); i += 8){
        mensagem.push_back((char) bitset < 8 > (string_quadro.substr(i, 8)).to_ullong());
    }
    q = &mensagem[0] + mensagem.size();
    for (p = &mensagem[0]; p < q; p++){
        octeto = *p;
        crc = (crc >> 8) ^ tabela[(crc & 0xff) ^ octeto];
    }

    cout << crc << endl;
    printf("%" PRIX32 "\n", ~crc);

    // const string aux = to_string (~crc);
    // for (int i = 0; i < 32; i++){
    //     resultado.push_back((int) aux[i]);
    // }
    //return resultado;
    //return ~crc;

    //polinomio CRC-32(IEEE 802)
}

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCodigoHamming(vector<int> quadro) {
    // a = 0110 0001
    // hamming = 110111010001
    cout << "before: ";
    for(int value: quadro) cout << value;
    cout << endl;

    int prox_bit_ver = 1;
    for(int i = 0; i<quadro.size(); i++) {

        if(prox_bit_ver - 1 == i) {
            // proximo bit de verificacao eh a proxima potencia de 2 (1, 2, 4, 8, ...)
            prox_bit_ver *= 2;

            // inserimos 0 na posicao i, por enquanto
            vector<int> temp = {0}; 
            quadro.insert(quadro.begin()+i, temp.begin(), temp.end());

        }
    }

    prox_bit_ver = 1;
    //somando bits 1 e salvando no proprio quadro
    for(int i = 0; i<quadro.size(); i++) {

        // pulamos bits de verificacao
        if(prox_bit_ver - 1 != i) {
            bitset<32> index (i+1);

            for(int j = 0; j < index.size(); j++) {
                if(index[j] == 1) quadro[pow(2, j) - 1] += quadro[i];
            }

        }
        else {
            prox_bit_ver *= 2;
        }

    }
    
    prox_bit_ver = 1;
    for(int i = 0; i<quadro.size(); i++) {

        // se for um dos bits de redundancia
        if(prox_bit_ver - 1 == i) {
            
            // eh impar, bit deve ser 1
            if(quadro[i]%2 == 1) quadro[i] = 1;
            else quadro[i] = 0;
            

            prox_bit_ver*=2;
        }

    }

    for(int value : quadro) {
        cout << value;
    }

    cout << endl;

    cout << "after: ";
    for(int value: quadro) cout << value;
    cout << endl;

    return quadro;

    /*
    

int m, r = 0, parity;    //m = no. of data bits, r = no. of redundant bits
    
    m = quadro.size();
    
    //finding no. of redundant bits
    while(pow (2,r) < m + r + 1){
        r++;
    }
    
    int hamming[m + r],j = 0,k = 0;    
    
    //finding positions of redundant bits.
    for(int i = 1; i <= m + r; i++){
        
        if( i == pow( 2, j )){
            hamming[i] = -1;    //-1 is initial value of redundant bits
            j++;
        }
        else{
            hamming[i] = quadro[k];
            k++;
        }
    }

    for(int i = 1; i <= m + r; i++)
    cout<<hamming[i]<<" ";

    cout << endl;
    
    k = 0;
    int x, min, max = 0;
    //finding parity bit
    for (int i = 1; i <= m + r; i = pow (2, k)){
      k++;
      parity = 0;
      j = i;
      x = i;
      min = 1;
      max = i;
       while ( j <= m + r){
          for (x = j; max >= min && x <= m + r; min++, x++){
              if (hamming[x] == 1)
                  parity = parity + 1;;
          }
          j = x + i;
          min = 1;
      }
      
      //checking for even parity
      if (parity % 2 == 0){ 
         hamming[i] = 0;
      }
      else{
        hamming[i] = 1;
      }
  }
    
    cout<<"\nHamming code is: ";
    for(int i = 1; i <= m + r; i++)
        cout<<hamming[i]<<" ";

    cout << endl;


    */
}
// FIM CONTROLE DE ERRO


void CamadaEnlaceDadosReceptora(vector<int> quadro){
    CamadaEnlaceDadosReceptoraEnquadramento(quadro);
    CamadaEnlaceDadosReceptoraControleDeErro(quadro);
    //CamadaDeAplicacaoReceptora(quadro);
}


// RECEPTORA ENQUADRAMENTO
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
// FIM RECEPTORA ENQUADRAMENTO


// RECEPTORA CONTROLE DE ERRO
void CamadaEnlaceDadosReceptoraControleDeErro(vector<int> quadro){
    int tipoDeControleDeErro = 0;

    switch(tipoDeControleDeErro){
        case 0:
            //bit de paridade
            CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar(quadro);
            break;
        case 1:
            //CRC
            break;
        case 2:
            //codigo de hamming
            break;
    }
}

vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar(vector<int> quadro){
    int cont = 0;
	for ( int i = 0; i < quadro.size(); i++){
		if(quadro[i] == 1) {
			cont++;
		}
	}
 
    if (cont % 2 == 1){
        cout << "Erro encontrado!" << endl;
    }

    quadro.pop_back();
    return quadro;
}

vector<int> CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(vector<int> quadro) {



    return quadro;
}
// FIM RECEPTORA CONTROLE DE ERRO