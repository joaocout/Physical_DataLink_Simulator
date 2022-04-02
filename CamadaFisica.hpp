#ifndef CAMADAFISICA // include guard
#define CAMADAFISICA

void main();
void AplicacaoTransmissora();
void CamadaDeAplicacaoTransmissora(string mensagem);
void CamadaFisicaTransmissora(int quadro[]);
int[] CamadaFisicaTransmissoraCodificacaoBinaria(int quadro[]);
int[] CamadaFisicaTransmissoraCodificacaoManchester(int quadro[]);
int[] CamadaFisicaTransmissoraCodificacaoBipolar(int quadro[]);
void MeioDeComunicacao(int fluxoBrutoDeBits[]);
void CamadaFisicaReceptora(int quadro[]);
int[] CamadaFisicaReceptoraDecodificacaoBinaria(int quadro[]);
int[] CamadaFisicaReceptoraDecodificacaoManchester(int quadro[]);
int[] CamadaFisicaReceptoraDecodificacaoBipolar(int quadro[]);
void CamadaDeAplicacaoReceptora(string mensagem);
void AplicacaoReceptora(int quadro[]);

#endif