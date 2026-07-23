// ============================================================
// Universidade Federal Fluminense - UFF
// Disciplina: Estruturas de Dados e Algoritmos
// Professor: Thiago Neves
// Programa: Analise de Custos para Instalacao de Galpao
//           Logistico - Bairros de Extrema MG
// ============================================================

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Grafo.h"

// ============================================================
// Funcao: lerVertices
// Le o arquivo de vertices e adiciona ao grafo
// ============================================================
void lerVertices(Grafo* g, const char* nomeArquivo) {
    FILE* f = fopen(nomeArquivo, "r");
    if (f == NULL) {
        printf("Erro ao abrir arquivo de vertices: %s\n", nomeArquivo);
        return;
    }

    int numVertices;
    fscanf(f, "%d", &numVertices);

    for (int i = 0; i < numVertices; i++) {
        int id;
        double custoInstalacao;
        int demanda[12];

        fscanf(f, "%d %lf", &id, &custoInstalacao);
        for (int mes = 0; mes < 12; mes++)
            fscanf(f, "%d", &demanda[mes]);

        g->addVertice(id, custoInstalacao, demanda);
    }

    fclose(f);
    printf("Vertices carregados com sucesso!\n");
}

// ============================================================
// Funcao: lerArestas
// Le o arquivo de arestas e adiciona ao grafo
// ============================================================
void lerArestas(Grafo* g, const char* nomeArquivo) {
    FILE* f = fopen(nomeArquivo, "r");
    if (f == NULL) {
        printf("Erro ao abrir arquivo de arestas: %s\n", nomeArquivo);
        return;
    }

    int numArestas;
    fscanf(f, "%d", &numArestas);

    for (int i = 0; i < numArestas; i++) {
        int origem, destino;
        double custo;
        fscanf(f, "%d %d %lf", &origem, &destino, &custo);
        g->addAresta(origem, destino, custo);
    }

    fclose(f);
    printf("Arestas carregadas com sucesso!\n");
}

// ============================================================
// Funcao: lerNumVerticesArestas
// Le apenas o cabecalho dos arquivos para obter quantidades
// ============================================================
void lerNumVerticesArestas(const char* arqVertices, const char* arqArestas,
                            int* numV, int* numA) {
    FILE* fv = fopen(arqVertices, "r");
    if (fv == NULL) {
        printf("Erro ao abrir arquivo de vertices!\n");
        *numV = 0;
        *numA = 0;
        return;
    }
    fscanf(fv, "%d", numV);
    fclose(fv);

    FILE* fa = fopen(arqArestas, "r");
    if (fa == NULL) {
        printf("Erro ao abrir arquivo de arestas!\n");
        *numA = 0;
        return;
    }
    fscanf(fa, "%d", numA);
    fclose(fa);
}

// ============================================================
// Funcao: calcularMedia
// Calcula a media de um vetor de doubles
// ============================================================
double calcularMedia(double* v, int n) {
    double soma = 0.0;
    for(int i = 0; i < n; i++)
        soma += v[i];
    return soma / n;
}

// ============================================================
// Funcao: calcularDesvioPadrao
// Calcula o desvio padrao de um vetor de doubles
// ============================================================
double calcularDesvioPadrao(double* v, int n, double media) {
    double soma = 0.0;
    for(int i = 0; i < n; i++) {
        double diff = v[i] - media;
        soma += diff * diff;
    }
    return soma / n;  // variancia
    // Para desvio padrao real usariamos sqrt, mas seguimos
    // o padrao do material do professor sem math.h aqui
}

// ============================================================
// Funcao: compararAlgoritmos
// Executa Dijkstra e Bellman-Ford 30 vezes para cada vertice
// Calcula media e desvio padrao dos tempos de execucao
// ============================================================
void compararAlgoritmos(Grafo* g) {
    int n = g->getNumVertices();
    int REPETICOES = 30;  // mesma quantidade do trabalho anterior
    double* distDijkstra  = new double[n];
    double* distBellman   = new double[n];
    double* distFloyd     = new double[n];

    // Arrays para armazenar tempos das 30 repeticoes
    double* temposDij   = new double[REPETICOES];
    double* temposBel   = new double[REPETICOES];
    double* temposFloyd = new double[REPETICOES];

    printf("\n=== COMPARACAO DIJKSTRA x BELLMAN-FORD x FLOYD-WARSHALL ===\n");
    printf("    (media de %d repeticoes por origem)\n", REPETICOES);
    printf("%-10s %-18s %-18s %-18s %-18s %-18s %-18s\n",
           "Origem", "Media Dij(s)", "DesvPad Dij",
           "Media Bel(s)", "DesvPad Bel",
           "Media FW(s)", "DesvPad FW");
    printf("------------------------------------------------------------------------------------------------------\n");

    double totalDijkstra = 0.0;
    double totalBellman  = 0.0;
    double totalFloyd    = 0.0;

    for (int i = 1; i <= n; i++) {
        clock_t t1, t2;

        // Executa 30 repeticoes para cada origem
        for(int rep = 0; rep < REPETICOES; rep++) {
            // Mede tempo do Dijkstra
            t1 = clock();
            g->dijkstra(i, distDijkstra);
            t2 = clock();
            temposDij[rep] = ((double)(t2 - t1)) / CLOCKS_PER_SEC;

            // Mede tempo do Bellman-Ford
            t1 = clock();
            g->bellmanFord(i, distBellman);
            t2 = clock();
            temposBel[rep] = ((double)(t2 - t1)) / CLOCKS_PER_SEC;

            // Mede tempo do Floyd-Warshall
            t1 = clock();
            g->floydWarshall(i, distFloyd);
            t2 = clock();
            temposFloyd[rep] = ((double)(t2 - t1)) / CLOCKS_PER_SEC;
        }

        // Calcula media e desvio padrao
        double mediaDij   = calcularMedia(temposDij,   REPETICOES);
        double mediaBel   = calcularMedia(temposBel,   REPETICOES);
        double mediaFloyd = calcularMedia(temposFloyd, REPETICOES);
        double desvDij    = calcularDesvioPadrao(temposDij,   REPETICOES, mediaDij);
        double desvBel    = calcularDesvioPadrao(temposBel,   REPETICOES, mediaBel);
        double desvFloyd  = calcularDesvioPadrao(temposFloyd, REPETICOES, mediaFloyd);

        totalDijkstra += mediaDij;
        totalBellman  += mediaBel;
        totalFloyd    += mediaFloyd;

        printf("%-10d %-18.6f %-18.6f %-18.6f %-18.6f %-18.6f %-18.6f\n",
               i, mediaDij, desvDij, mediaBel, desvBel, mediaFloyd, desvFloyd);

        // Verifica se os resultados sao iguais
        bool iguais = true;
        for (int j = 0; j < n; j++) {
            double diff = distDijkstra[j] - distBellman[j];
            if (diff < 0) diff = -diff;
            if (diff > 0.0001) {
                iguais = false;
                break;
            }
        }
        if (!iguais)
            printf("  AVISO: resultados diferentes para origem %d!\n", i);
    }

    printf("------------------------------------------------------------------------------------------------------\n");
    printf("%-10s %-18.6f %-18s %-18.6f %-18s %-18.6f\n",
           "TOTAL", totalDijkstra, "", totalBellman, "", totalFloyd);
    printf("======================================================================================================\n\n");

    delete[] distDijkstra;
    delete[] distBellman;
    delete[] distFloyd;
    delete[] temposDij;
    delete[] temposBel;
    delete[] temposFloyd;
}

// ============================================================
// Funcao: analisarCustosMensais
// Calcula e imprime os custos mensais para cada bairro
// ============================================================
void analisarCustosMensais(Grafo* g) {
    int n = g->getNumVertices();
    double* distancias = new double[n];

    printf("\n=== CUSTOS DE OPERACAO MENSAIS POR BAIRRO ===\n");
    printf("%-8s", "Bairro");
    for (int mes = 1; mes <= 12; mes++)
        printf("  Mes%-4d", mes);
    printf("  Total\n");
    printf("------------------------------------------------------------------------------------\n");

    for (int i = 1; i <= n; i++) {
        g->dijkstra(i, distancias);
        double total = 0.0;
        printf("%-8d", i);
        for (int mes = 0; mes < 12; mes++) {
            double custoMes = g->custoOperacaoMensal(i, mes, distancias);
            printf("  %-8.2f", custoMes);
            total += custoMes;
        }
        printf("  %-10.2f\n", total);
    }
    printf("------------------------------------------------------------------------------------\n\n");

    delete[] distancias;
}

// ============================================================
// Funcao: analiseSensibilidade
// Varia custos de instalacao e operacao em percentuais
// e verifica se o bairro vencedor muda
// ============================================================
void analiseSensibilidade(Grafo* g) {
    printf("\n=== ANALISE DE SENSIBILIDADE ===\n");
    printf("%-20s %-15s %-15s %-15s %-15s\n",
           "Cenario", "Var.Inst.(%)", "Var.Op.(%)", "Melhor Bairro", "CustoGalpao");
    printf("--------------------------------------------------------------------------------\n");

    // Cenarios: {variacao instalacao, variacao operacao}
    double cenarios[5][2] = {
        {  0.0,   0.0},  // Base
        {-20.0, -20.0},  // Otimista
        { 20.0,  20.0},  // Pessimista
        { 50.0,   0.0},  // Alta instalacao
        {  0.0,  50.0},  // Alta operacao
    };

    const char* nomes[5] = {
        "Base",
        "Otimista (-20%)",
        "Pessimista (+20%)",
        "Alta Instalacao",
        "Alta Operacao"
    };

    int n = g->getNumVertices();
    double* distancias = new double[n];

    for(int c = 0; c < 5; c++) {
        double varInst = 1.0 + cenarios[c][0] / 100.0;
        double varOp   = 1.0 + cenarios[c][1] / 100.0;

        int melhorId     = -1;
        double menorCusto = 999999999.0;

        for(int i = 1; i <= n; i++) {
            Vertice* v = g->getVertice(i);
            if(v == 0) continue;

            g->dijkstra(i, distancias);

            // Calcula custo de operacao anual com variacao
            double custoOp = 0.0;
            for(int mes = 0; mes < 12; mes++)
                custoOp += g->custoOperacaoMensal(i, mes, distancias) * varOp;

            // Aplica variacao no custo de instalacao
            double custoInst = v->getCustoInstalacao() * varInst;
            double custoGal  = custoInst - custoOp;

            if(custoGal < menorCusto) {
                menorCusto = custoGal;
                melhorId   = i;
            }
        }

        printf("%-20s %-15.1f %-15.1f %-15d %-15.2f\n",
               nomes[c], cenarios[c][0], cenarios[c][1],
               melhorId, menorCusto);
    }

    printf("--------------------------------------------------------------------------------\n\n");
    delete[] distancias;
}
// ============================================================
// PROGRAMA PRINCIPAL
// ============================================================
int main() {
    printf("============================================================\n");
    printf("  SISTEMA DE ANALISE LOGISTICA - GALPOES EM EXTREMA MG\n");
    printf("============================================================\n\n");

    // Nomes dos arquivos de entrada
    const char* arqVertices = "vertices.txt";
    const char* arqArestas  = "arestas.txt";

    // Le numero de vertices e arestas
    int numV = 0, numA = 0;
    lerNumVerticesArestas(arqVertices, arqArestas, &numV, &numA);

    if (numV == 0 || numA == 0) {
        printf("Erro ao ler arquivos de entrada!\n");
        return 1;
    }

    printf("Numero de vertices: %d\n", numV);
    printf("Numero de arestas:  %d\n\n", numA);

    // Cria o grafo
    Grafo* g = new Grafo(numV, numA);

    // Carrega dados dos arquivos
    lerVertices(g, arqVertices);
    lerArestas(g, arqArestas);

    // Imprime estrutura do grafo
    g->imprimirGrafo();

    // Compara Dijkstra x Bellman-Ford
    compararAlgoritmos(g);

    // Analisa custos mensais
    analisarCustosMensais(g);

    // Imprime tabela de custos finais
    g->imprimirCustos();

    // Determina o melhor bairro
    int melhor = g->melhorBairro();
    printf("\n============================================================\n");
    printf("  RESULTADO: O GALPAO DEVE SER INSTALADO NO BAIRRO %d\n", melhor);
    printf("============================================================\n\n");

    // Analise de sensibilidade
    analiseSensibilidade(g);

    // Libera memoria
    delete g;

    return 0;
}


