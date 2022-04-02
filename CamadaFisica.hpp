#ifndef CAMADAFISICA
#define CAMADAFISICA

#include <vector>

using namespace std;

void AplicacaoTransmissora();
void CamadaDeAplicacaoTransmissora(string mensagem);
void CamadaFisicaTransmissora(int quadro[]);
vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(int quadro[]);
vector<int> CamadaFisicaTransmissoraCodificacaoManchester(int quadro[]);
vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(int quadro[]);
void MeioDeComunicacao(int fluxoBrutoDeBits[]);
void CamadaFisicaReceptora(int quadro[]);
vector<int> CamadaFisicaReceptoraDecodificacaoBinaria(int quadro[]);
vector<int> CamadaFisicaReceptoraDecodificacaoManchester(int quadro[]);
vector<int> CamadaFisicaReceptoraDecodificacaoBipolar(int quadro[]);
void CamadaDeAplicacaoReceptora(string mensagem);
void AplicacaoReceptora(int quadro[]);

#endif