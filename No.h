#ifndef NO_H
#define NO_H

#include "Aresta.h"

// ============================================================
// Universidade Federal Fluminense - UFF
// Disciplina: Estruturas de Dados e Algoritmos
// Professor: Thiago Neves
// Classe: No
// Descricao: Elemento da lista de adjacencia do grafo
//            Armazena uma aresta e ponteiro para o proximo no
// ============================================================

class No {
public:
    No();
    No(Aresta* aresta);
    virtual ~No();

    Aresta* getAresta();
    No* getProximo();

    void setAresta(Aresta* aresta);
    void setProximo(No* proximo);

private:
    Aresta* aresta;
    No* proximo;
};

#endif
