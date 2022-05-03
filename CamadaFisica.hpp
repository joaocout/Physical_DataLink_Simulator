#include <vector>

using namespace std;

#ifndef CAMADAFISICA
#define CAMADAFISICA


// void AplicacaoTransmissora(string input, int selected_encoding);

// void CamadaDeAplicacaoTransmissora(string mensagem);

void CamadaFisicaTransmissora(vector<int> quadro);

vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(vector<int> quadro);

vector<int> CamadaFisicaTransmissoraCodificacaoManchester(vector<int> quadro);

vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(vector<int> quadro);

void MeioDeComunicacao(vector<int> fluxoBrutoDeBits);

void CamadaFisicaReceptora(vector<int> quadro);

vector<int> CamadaFisicaReceptoraDecodificacaoBinaria(vector<int> quadro);

vector<int> CamadaFisicaReceptoraDecodificacaoManchester(vector<int> quadro);

vector<int> CamadaFisicaReceptoraDecodificacaoBipolar(vector<int> quadro);

void CamadaDeAplicacaoReceptora(vector<int> quadro);

void AplicacaoReceptora(string mensagem);

#endif