#ifndef VERTICE_H
#define VERTICE_H

// ============================================================
// Universidade Federal Fluminense - UFF
// Disciplina: Estruturas de Dados e Algoritmos
// Professor: Thiago Neves
// Classe: Vertice
// Descricao: Representa um bairro candidato para instalacao
//            de galpao logistico
// ============================================================

class Vertice {
public:
    Vertice();
    Vertice(int id, double custoInstalacao, int* demanda);
    virtual ~Vertice();

    int getId();
    double getCustoInstalacao();
    int getDemanda(int mes); // mes de 0 a 11

    void setId(int id);
    void setCustoInstalacao(double custo);
    void setDemanda(int mes, int valor);

private:
    int id;
    double custoInstalacao;
    int demanda[12]; // demanda estimada para cada mes do ano
};

#endif
