#ifndef ARESTA_H
#define ARESTA_H

// ============================================================
// Universidade Federal Fluminense - UFF
// Disciplina: Estruturas de Dados e Algoritmos
// Professor: Thiago Neves
// Classe: Aresta
// Descricao: Representa a conexao entre dois bairros com
//            custo de transporte unitario
// ============================================================

class Aresta {
public:
    Aresta();
    Aresta(int origem, int destino, double custo);
    virtual ~Aresta();

    int getOrigem();
    int getDestino();
    double getCusto();

    void setOrigem(int origem);
    void setDestino(int destino);
    void setCusto(double custo);

private:
    int origem;
    int destino;
    double custo;
};

#endif
