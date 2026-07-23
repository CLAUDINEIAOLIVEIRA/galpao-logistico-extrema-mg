#include "Grafo.h"

// ============================================================
// Construtor
// Complexidade: O(n) - inicializa n posicoes da lista
// ============================================================
Grafo::Grafo(int numVertices, int numArestas) {
    this->numVertices = numVertices;
    this->numArestas = numArestas;

    vertices = new Vertice*[numVertices];
    adjList  = new No*[numVertices];

    for (int i = 0; i < numVertices; i++) {
        vertices[i] = 0;
        adjList[i]  = 0;
    }
}

// ============================================================
// Destrutor
// Complexidade: O(n + a) - percorre vertices e arestas
// ============================================================
Grafo::~Grafo() {
    // Desaloca lista de adjacencia
    for (int i = 0; i < numVertices; i++) {
        No* atual = adjList[i];
        while (atual != 0) {
            No* prox = atual->getProximo();
            delete atual->getAresta();
            delete atual;
            atual = prox;
        }
        adjList[i] = 0;
    }
    delete[] adjList;

    // Desaloca vertices
    for (int i = 0; i < numVertices; i++) {
        if (vertices[i] != 0) {
            delete vertices[i];
            vertices[i] = 0;
        }
    }
    delete[] vertices;
}

// ============================================================
// isEmpty
// Complexidade: O(1)
// ============================================================
bool Grafo::isEmpty() {
    return numVertices == 0;
}

// ============================================================
// getNumVertices
// Complexidade: O(1)
// ============================================================
int Grafo::getNumVertices() {
    return numVertices;
}

// ============================================================
// getNumArestas
// Complexidade: O(1)
// ============================================================
int Grafo::getNumArestas() {
    return numArestas;
}

// ============================================================
// indiceVertice - retorna indice no array para dado id
// Complexidade: O(n)
// ============================================================
int Grafo::indiceVertice(int id) {
    for (int i = 0; i < numVertices; i++) {
        if (vertices[i] != 0 && vertices[i]->getId() == id)
            return i;
    }
    return -1;
}

// ============================================================
// getVertice
// Complexidade: O(n)
// ============================================================
Vertice* Grafo::getVertice(int id) {
    int idx = indiceVertice(id);
    if (idx != -1)
        return vertices[idx];
    return 0;
}

// ============================================================
// addVertice
// Complexidade: O(n) - busca posicao livre no array
// ============================================================
void Grafo::addVertice(int id, double custoInstalacao, int* demanda) {
    for (int i = 0; i < numVertices; i++) {
        if (vertices[i] == 0) {
            vertices[i] = new Vertice(id, custoInstalacao, demanda);
            return;
        }
    }
}

// ============================================================
// addAresta - adiciona aresta na lista de adjacencia
// Como o grafo e NAO DIRECIONADO, adiciona origem->destino
// e tambem destino->origem (aresta bidirecional)
// Complexidade: O(n) - chama indiceVertice para ambos os vertices
// ============================================================
void Grafo::addAresta(int origem, int destino, double custo) {
    // Adiciona origem -> destino
    int idxOrigem = indiceVertice(origem);
    if (idxOrigem != -1) {
        Aresta* a1 = new Aresta(origem, destino, custo);
        No* no1 = new No(a1);
        no1->setProximo(adjList[idxOrigem]);
        adjList[idxOrigem] = no1;
    }

    // Adiciona destino -> origem (nao direcionado)
    int idxDestino = indiceVertice(destino);
    if (idxDestino != -1) {
        Aresta* a2 = new Aresta(destino, origem, custo);
        No* no2 = new No(a2);
        no2->setProximo(adjList[idxDestino]);
        adjList[idxDestino] = no2;
    }
}

// ============================================================
// menorDistancia - auxiliar do Dijkstra
// Retorna indice do vertice nao visitado com menor distancia
// Complexidade: O(n)
// ============================================================
int Grafo::menorDistancia(double* distancias, bool* visitado) {
    double menor = INFINITO;
    int idx = -1;
    for (int i = 0; i < numVertices; i++) {
        if (!visitado[i] && distancias[i] <= menor) {
            menor = distancias[i];
            idx = i;
        }
    }
    return idx;
}

// ============================================================
// dijkstra - calcula caminho minimo da origem a todos vertices
// Complexidade: O(n^2) - dois lacos aninhados sobre vertices
// ============================================================
void Grafo::dijkstra(int origem, double* distancias) {
    bool* visitado = new bool[numVertices];

    // Inicializacao
    for (int i = 0; i < numVertices; i++) {
        distancias[i] = INFINITO;
        visitado[i]   = false;
    }

    int idxOrigem = indiceVertice(origem);
    if (idxOrigem == -1) {
        delete[] visitado;
        return;
    }

    distancias[idxOrigem] = 0.0;

    // Processa todos os vertices
    for (int count = 0; count < numVertices; count++) {
        int u = menorDistancia(distancias, visitado);
        if (u == -1) break;
        visitado[u] = true;

        // Percorre lista de adjacencia do vertice u
        No* atual = adjList[u];
        while (atual != 0) {
            Aresta* a = atual->getAresta();
            int idxDest = indiceVertice(a->getDestino());

            if (idxDest != -1 && !visitado[idxDest]) {
                double novaDist = distancias[u] + a->getCusto();
                if (novaDist < distancias[idxDest]) {
                    distancias[idxDest] = novaDist;
                }
            }
            atual = atual->getProximo();
        }
    }

    delete[] visitado;
}

// ============================================================
// bellmanFord - calcula caminho minimo da origem a todos vertices
// Complexidade: O(n * a) - n-1 relaxamentos sobre todas arestas
// ============================================================
void Grafo::bellmanFord(int origem, double* distancias) {
    // Inicializacao
    for (int i = 0; i < numVertices; i++)
        distancias[i] = INFINITO;

    int idxOrigem = indiceVertice(origem);
    if (idxOrigem == -1) return;

    distancias[idxOrigem] = 0.0;

    // Relaxa todas as arestas numVertices-1 vezes
    for (int count = 0; count < numVertices - 1; count++) {
        for (int u = 0; u < numVertices; u++) {
            if (distancias[u] == INFINITO) continue;

            No* atual = adjList[u];
            while (atual != 0) {
                Aresta* a = atual->getAresta();
                int idxDest = indiceVertice(a->getDestino());

                if (idxDest != -1) {
                    double novaDist = distancias[u] + a->getCusto();
                    if (novaDist < distancias[idxDest]) {
                        distancias[idxDest] = novaDist;
                    }
                }
                atual = atual->getProximo();
            }
        }
    }
}

// ============================================================
// floydWarshall - calcula caminho minimo entre TODOS os pares
// Retorna apenas a linha correspondente ao vertice de origem
// Complexidade: O(n³) - tres lacos aninhados sobre vertices
// ============================================================
void Grafo::floydWarshall(int origem, double* distancias) {
    // Aloca matriz n x n
    double** dist = new double*[numVertices];
    for (int i = 0; i < numVertices; i++) {
        dist[i] = new double[numVertices];
        for (int j = 0; j < numVertices; j++) {
            if (i == j)
                dist[i][j] = 0.0;
            else
                dist[i][j] = INFINITO;
        }
    }

    // Inicializa com as arestas existentes
    for (int u = 0; u < numVertices; u++) {
        No* atual = adjList[u];
        while (atual != 0) {
            Aresta* a = atual->getAresta();
            int idxDest = indiceVertice(a->getDestino());
            if (idxDest != -1)
                dist[u][idxDest] = a->getCusto();
            atual = atual->getProximo();
        }
    }

    // Relaxamento Floyd-Warshall
    // Para cada vertice intermediario k
    for (int k = 0; k < numVertices; k++) {
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                if (dist[i][k] != INFINITO && dist[k][j] != INFINITO) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    // Extrai apenas a linha da origem
    int idxOrigem = indiceVertice(origem);
    if (idxOrigem != -1) {
        for (int j = 0; j < numVertices; j++)
            distancias[j] = dist[idxOrigem][j];
    }

    // Desaloca matriz
    for (int i = 0; i < numVertices; i++)
        delete[] dist[i];
    delete[] dist;
}

// ============================================================
// custoOperacaoMensal
// Calcula custo de operacao para um mes especifico
// custo = soma(distancia[destino] * demanda[destino][mes])
// Complexidade: O(n)
// ============================================================
double Grafo::custoOperacaoMensal(int verticeOrigem, int mes, double* distancias) {
    double custo = 0.0;
    for (int i = 0; i < numVertices; i++) {
        if (vertices[i] != 0 && distancias[i] != INFINITO) {
            custo += distancias[i] * vertices[i]->getDemanda(mes);
        }
    }
    return custo;
}

// ============================================================
// custoOperacaoAnual
// Calcula custo de operacao anual somando os 12 meses
// Complexidade: O(n^2) - dijkstra O(n^2) + 12 * custoMensal O(n)
// ============================================================
double Grafo::custoOperacaoAnual(int verticeOrigem) {
    double* distancias = new double[numVertices];
    dijkstra(verticeOrigem, distancias);

    double custoAnual = 0.0;
    for (int mes = 0; mes < 12; mes++) {
        custoAnual += custoOperacaoMensal(verticeOrigem, mes, distancias);
    }

    delete[] distancias;
    return custoAnual;
}

// ============================================================
// melhorBairro
// Retorna o id do bairro com menor custoGalpao
// custoGalpao = custoInstalacao - custoOperacaoAnual
// Complexidade: O(n^3) - para cada vertice executa dijkstra O(n^2)
// ============================================================
int Grafo::melhorBairro() {
    int melhorId    = -1;
    double menorCusto = INFINITO;

    for (int i = 0; i < numVertices; i++) {
        if (vertices[i] == 0) continue;

        double custoOp   = custoOperacaoAnual(vertices[i]->getId());
        double custoGal  = vertices[i]->getCustoInstalacao() - custoOp;

        printf("Bairro %d: custoInstalacao=%.2f custoOperacao=%.2f custoGalpao=%.2f\n",
               vertices[i]->getId(),
               vertices[i]->getCustoInstalacao(),
               custoOp,
               custoGal);

        if (custoGal < menorCusto) {
            menorCusto = custoGal;
            melhorId   = vertices[i]->getId();
        }
    }
    return melhorId;
}

// ============================================================
// imprimirGrafo
// Complexidade: O(n + a)
// ============================================================
void Grafo::imprimirGrafo() {
    printf("\n=== GRAFO - BAIRROS DE EXTREMA MG ===\n");
    for (int i = 0; i < numVertices; i++) {
        if (vertices[i] == 0) continue;
        printf("Vertice %d (custo instalacao: %.2f)\n",
               vertices[i]->getId(),
               vertices[i]->getCustoInstalacao());
        printf("  Adjacentes: ");
        No* atual = adjList[i];
        if (atual == 0) printf("nenhum");
        while (atual != 0) {
            Aresta* a = atual->getAresta();
            printf("[->%d custo:%.2f] ", a->getDestino(), a->getCusto());
            atual = atual->getProximo();
        }
        printf("\n");
    }
    printf("=====================================\n\n");
}

// ============================================================
// imprimirDistancias
// Complexidade: O(n)
// ============================================================
void Grafo::imprimirDistancias(int origem, double* distancias) {
    printf("\n=== DISTANCIAS A PARTIR DO VERTICE %d ===\n", origem);
    for (int i = 0; i < numVertices; i++) {
        if (vertices[i] == 0) continue;
        if (distancias[i] == INFINITO)
            printf("Vertice %d: INALCANCAVEL\n", vertices[i]->getId());
        else
            printf("Vertice %d: %.2f\n", vertices[i]->getId(), distancias[i]);
    }
    printf("==========================================\n\n");
}

// ============================================================
// imprimirCustos
// Complexidade: O(n^3)
// ============================================================
void Grafo::imprimirCustos() {
    printf("\n=== ANALISE DE CUSTOS - GALPOES LOGISTICOS ===\n");
    printf("%-10s %-18s %-18s %-18s\n",
           "Bairro", "CustoInstalacao", "CustoOperacao", "CustoGalpao");
    printf("------------------------------------------------------------------\n");

    for (int i = 0; i < numVertices; i++) {
        if (vertices[i] == 0) continue;

        double custoOp  = custoOperacaoAnual(vertices[i]->getId());
        double custoGal = vertices[i]->getCustoInstalacao() - custoOp;

        printf("%-10d %-18.2f %-18.2f %-18.2f\n",
               vertices[i]->getId(),
               vertices[i]->getCustoInstalacao(),
               custoOp,
               custoGal);
    }
    printf("------------------------------------------------------------------\n\n");
}
