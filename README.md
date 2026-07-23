# 🏭 Análise de Custos para Instalação de Galpão Logístico
## Utilizando Grafos e Algoritmos de Caminho Mínimo

![C++](https://img.shields.io/badge/C++-00599C?style=flat&logo=cplusplus&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=flat&logo=linux&logoColor=black)
![UFF](https://img.shields.io/badge/UFF-Volta%20Redonda-blue)

> **Disciplina:** Estrutura de Dados e Algoritmos  
> **Professor:** Thiago Neves  
> **Instituição:** Universidade Federal Fluminense — UFF, Volta Redonda  
> **Programa:** Pós-Graduação em Modelagem Computacional (PPGCM)  
> **Autora:** Claudineia Moreira de Oliveira  
> **Ano:** 2026

---

## 📋 Descrição

Sistema computacional para **apoio à decisão na instalação de galpões logísticos** em 15 bairros reais de Extrema, Minas Gerais. O problema é modelado como um **grafo não direcionado ponderado**, onde:

- **Vértices** → bairros candidatos à instalação do galpão
- **Arestas** → conexões entre bairros com distâncias reais (Google Maps)

O sistema calcula os custos de operação mensais e anuais para cada bairro candidato e indica o bairro com menor **custoGalpão**:

```
custoGalpão = custoInstalação − custoOperaçãoAnual
```

---

## 🗺️ Contexto — Extrema, MG

Extrema é um dos principais polos logísticos do Brasil, com estoque superior a **650 mil m²** às margens da Rodovia Fernão Dias (BR-381). Com apenas 53 mil habitantes, a cidade exporta quase U$ 100 milhões e abriga empresas como Mercado Livre, Magazine Luiza e VBI Log.

---

## 🏗️ Estrutura do Projeto

```
📦 galpao-logistico-extrema-mg
├── 📄 Vertice.h          # Declaração da classe Vertice
├── 📄 Vertice.cpp        # Implementação da classe Vertice
├── 📄 Aresta.h           # Declaração da classe Aresta
├── 📄 Aresta.cpp         # Implementação da classe Aresta
├── 📄 No.h               # Declaração da classe No
├── 📄 No.cpp             # Implementação da classe No
├── 📄 Grafo.h            # Declaração do TAD Grafo
├── 📄 Grafo.cpp          # Implementação do TAD Grafo
├── 📄 main.cpp           # Programa principal
├── 📄 vertices.txt       # Dados dos 15 bairros de Extrema-MG
├── 📄 arestas.txt        # 22 arestas com distâncias reais
└── 📄 README.md          # Este arquivo
```

---

## 🧩 TAD Grafo — Classes

| Classe | Responsabilidade |
|---|---|
| `Vertice` | Bairro candidato: id, custo de instalação e 12 demandas mensais |
| `Aresta` | Conexão entre bairros: origem, destino e custo de transporte |
| `No` | Elemento da lista de adjacência: ponteiro para Aresta e próximo No |
| `Grafo` | TAD principal: lista de adjacência, algoritmos e cálculos logísticos |

---

## ⚙️ Interface do TAD Grafo

```cpp
// Construtor e Destrutor
Grafo(int numVertices, int numArestas);
~Grafo();

// Inserção
void addVertice(int id, double custoInstalacao, int* demanda);
void addAresta(int origem, int destino, double custo);  // não direcionado

// Consulta
Vertice* getVertice(int id);
int getNumVertices();
int getNumArestas();
bool isEmpty();

// Algoritmos de caminho mínimo
void dijkstra(int origem, double* distancias);       // O(n²)
void bellmanFord(int origem, double* distancias);    // O(n×a)
void floydWarshall(int origem, double* distancias);  // O(n³)

// Cálculo logístico
double custoOperacaoMensal(int origem, int mes, double* distancias);
double custoOperacaoAnual(int verticeOrigem);
int melhorBairro();
```

---

## 📊 Análise de Complexidade

| Método | Complexidade |
|---|---|
| `dijkstra()` | O(n²) |
| `bellmanFord()` | O(n × a) |
| `floydWarshall()` | O(n³) |
| `custoOperacaoAnual()` | O(n²) |
| `melhorBairro()` | O(n³) |
| `addAresta()` | O(n) |
| `getVertice()` | O(n) |

---

## 🏘️ Dados de Teste — 15 Bairros de Extrema-MG

| ID | Bairro | Custo Instalação (R$) |
|---|---|---|
| 1 | Centro | 2.500.000,00 |
| 2 | Distrito Industrial | 8.500.000,00 |
| 3 | Bairro dos Pires (BR-381) | 4.500.000,00 |
| 4 | São Bráz | 3.200.000,00 |
| 5 | Bairro dos Tenentes | 2.800.000,00 |
| 6 | Condomínio Logístico | 12.000.000,00 |
| 7 | Divisa SP/MG | 3.800.000,00 |
| 8 | Ponte Alta | 2.200.000,00 |
| 9 | Pessegueiros | 3.600.000,00 |
| 10 | Ponte Nova | 2.100.000,00 |
| 11 | Morbidelli | 2.800.000,00 |
| 12 | Vila Rica | 2.300.000,00 |
| **13 ★** | **Salto de Baixo** | **1.800.000,00** |
| 14 | Parque Logístico | 5.500.000,00 |
| 15 | Morada da Serra | 2.600.000,00 |

> ★ **Bairro vencedor** — menor custoGalpão: R$ 1.215.634,50

---

## 🚀 Como Compilar e Executar

### Requisitos
- Ubuntu 24.04 LTS (ou equivalente)
- g++ 13.3.0 ou superior

### Compilação
```bash
g++ Vertice.cpp Aresta.cpp No.cpp Grafo.cpp main.cpp -o analise
```

### Execução
```bash
./analise
```

---

## 📈 Resultados

### Comparação dos Algoritmos (30 repetições, 15 vértices)

| Algoritmo | Complexidade | Tempo Médio |
|---|---|---|
| Dijkstra | O(n²) | 0.000003s |
| Bellman-Ford | O(n×a) | 0.000027s |
| Floyd-Warshall | O(n³) | 0.000023s |

### Análise de Sensibilidade

| Cenário | Var. Instalação | Var. Operação | Bairro Vencedor |
|---|---|---|---|
| Base | 0% | 0% | **B13 — Salto de Baixo** |
| Otimista | -20% | -20% | **B13 — Salto de Baixo** |
| Pessimista | +20% | +20% | **B13 — Salto de Baixo** |
| Alta Instalação | +50% | 0% | **B13 — Salto de Baixo** |
| Alta Operação | 0% | +50% | **B13 — Salto de Baixo** |

> O Bairro 13 — Salto de Baixo — manteve-se vencedor em **todos os cenários**, demonstrando robustez da decisão.

---

## 📁 Formato dos Arquivos de Entrada

### vertices.txt
```
<número de vértices>
<id> <custoInstalacao> <dem1> <dem2> ... <dem12>
```

### arestas.txt
```
<número de arestas>
<origem> <destino> <custo>
```

---

## 🔬 Ambiente de Desenvolvimento

| Item | Descrição |
|---|---|
| Dispositivo | DESKTOP-50V4UVQ |
| Sistema Operacional | Ubuntu 24.04 LTS via VirtualBox |
| Processador | 13th Gen Intel Core i5-1334U (1.30 GHz) |
| Memória RAM | 16,0 GB |
| Compilador | g++ 13.3.0 |
| Editor | Gedit |

---

## 📚 Referências

- DIJKSTRA, E. W. A note on two problems in connexion with graphs. *Numerische Mathematik*, v. 1, n. 1, p. 269–271, 1959.
- BELLMAN, R. On a routing problem. *Quarterly of Applied Mathematics*, v. 16, n. 1, p. 87–90, 1958.
- CORMEN, T. H. et al. *Introduction to Algorithms*. 3. ed. MIT Press, 2009.
- VENCESLAU, I.; LIMA, F. L. S. Guerra dos lugares .com. *Caminhos de Geografia*, v. 25, n. 102, 2024. (**Qualis A1**)
- CUSHMAN & WAKEFIELD. Polos Logísticos Brasileiros. 2022.

---

## 📝 Licença

Trabalho acadêmico — PPGCM/UFF — 2026
