#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Vertice.h"
#include "Aresta.h"
#include "No.h"

// ============================================================
// Universidade Federal Fluminense - UFF
// Disciplina: Estruturas de Dados e Algoritmos
// Professor: Thiago Neves
// Classe: Grafo
// Descricao: TAD Grafo com lista de adjacencia para modelar
//            bairros de uma cidade e calcular custos logisticos
//            para instalacao de galpoes
// ============================================================

#define INFINITO 999999999.0

class Grafo {
public:
    // Construtor e Destrutor
    Grafo(int numVertices, int numArestas);
    virtual ~Grafo();

    // Insercao
    void addVertice(int id, double custoInstalacao, int* demanda);
    void addAresta(int origem, int destino, double custo);

    // Consulta
    Vertice* getVertice(int id);
    int getNumVertices();
    int getNumArestas();
    bool isEmpty();

    // Algoritmos de caminho minimo
    void dijkstra(int origem, double* distancias);
    void bellmanFord(int origem, double* distancias);
    void floydWarshall(int origem, double* distancias);

    // Calculo logistico
    double custoOperacaoMensal(int verticeOrigem, int mes, double* distancias);
    double custoOperacaoAnual(int verticeOrigem);
    int melhorBairro();

    // Impressao
    void imprimirGrafo();
    void imprimirDistancias(int origem, double* distancias);
    void imprimirCustos();

private:
    int numVertices;
    int numArestas;
    Vertice** vertices;   // array de ponteiros para Vertice
    No** adjList;         // lista de adjacencia

    // Auxiliares
    int indiceVertice(int id); // retorna indice do vertice com dado id
    int menorDistancia(double* distancias, bool* visitado);
};

#endif
