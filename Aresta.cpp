#include "Aresta.h"

// ============================================================
// Construtor padrao
// ============================================================
Aresta::Aresta() {
    origem = 0;
    destino = 0;
    custo = 0.0;
}

// ============================================================
// Construtor parametrizado
// ============================================================
Aresta::Aresta(int origem, int destino, double custo) {
    this->origem = origem;
    this->destino = destino;
    this->custo = custo;
}

// ============================================================
// Destrutor
// ============================================================
Aresta::~Aresta() {}

// ============================================================
// Metodos GET
// ============================================================
int Aresta::getOrigem() {
    return origem;
}

int Aresta::getDestino() {
    return destino;
}

double Aresta::getCusto() {
    return custo;
}

// ============================================================
// Metodos SET
// ============================================================
void Aresta::setOrigem(int origem) {
    if (origem > 0)
        this->origem = origem;
}

void Aresta::setDestino(int destino) {
    if (destino > 0)
        this->destino = destino;
}

void Aresta::setCusto(double custo) {
    if (custo >= 0.0)
        this->custo = custo;
}
