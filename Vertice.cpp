#include "Vertice.h"

// ============================================================
// Construtor padrao
// ============================================================
Vertice::Vertice() {
    id = 0;
    custoInstalacao = 0.0;
    for (int i = 0; i < 12; i++)
        demanda[i] = 0;
}

// ============================================================
// Construtor parametrizado
// ============================================================
Vertice::Vertice(int id, double custoInstalacao, int* demanda) {
    this->id = id;
    this->custoInstalacao = custoInstalacao;
    for (int i = 0; i < 12; i++)
        this->demanda[i] = demanda[i];
}

// ============================================================
// Destrutor
// ============================================================
Vertice::~Vertice() {}

// ============================================================
// Metodos GET
// ============================================================
int Vertice::getId() {
    return id;
}

double Vertice::getCustoInstalacao() {
    return custoInstalacao;
}

int Vertice::getDemanda(int mes) {
    if (mes >= 0 && mes < 12)
        return demanda[mes];
    return 0;
}

// ============================================================
// Metodos SET
// ============================================================
void Vertice::setId(int id) {
    if (id > 0)
        this->id = id;
}

void Vertice::setCustoInstalacao(double custo) {
    if (custo >= 0.0)
        this->custoInstalacao = custo;
}

void Vertice::setDemanda(int mes, int valor) {
    if (mes >= 0 && mes < 12 && valor >= 0)
        demanda[mes] = valor;
}
