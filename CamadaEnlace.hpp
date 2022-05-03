#include <vector>

using namespace std;

#ifndef CAMADAENLACE
#define CAMADAENLACE


void CamadaEnlaceDadosTransmissora(vector<int> quadro);

vector<int> CamadaEnlaceDadosTransmissoraEnquadramento(vector<int> quadro);

vector<int> CamadaEnlaceDadosTransmissoraControleDeErro(vector<int> quadro);

vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(vector<int> quadro);

vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(vector<int> quadro);

void CamadaEnlaceDadosReceptora(vector<int> quadro);

vector<int> CamadaEnlaceDadosReceptoraEnquadramento(vector<int> quadro);

vector<int> CamadaEnlaceDadosReceptoraControleDeErro(vector<int> quadro);

vector<int> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(vector<int> quadro);

vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(vector<int> quadro);

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(vector<int> quadro);

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCRC(vector<int> quadro);

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCodigoHamming(vector<int> quadro);

vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar(vector<int> quadro);

vector<int> CamadaEnlaceDadosReceptoraControleDeErroCRC(vector<int> quadro);

vector<int> CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(vector<int> quadro);

#endif