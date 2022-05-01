#include <vector>

using namespace std;

#ifndef CAMADAENLACE
#define CAMADAENLACE


void CamadaEnlaceDadosTransmissora(vector<int> quadro);

void CamadaEnlaceDadosTransmissoraEnquadramento(vector<int> quadro);

void CamadaEnlaceDadosTransmissoraControleDeErro(vector<int> quadro);

vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(vector<int> quadro);

vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(vector<int> quadro);

void CamadaEnlaceDadosReceptora(vector<int> quadro);

void CamadaEnlaceDadosReceptoraEnquadramento(vector<int> quadro);

void CamadaEnlaceDadosReceptoraControleDeErro(vector<int> quadro);

vector<int> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(vector<int> quadro);

vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(vector<int> quadro);

#endif