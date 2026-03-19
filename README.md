# 🚀 Desafio F-D-E  
## 🧠 Desafio 5: Mínimo de um Array  
**CPU – Torneio de Processadores**  
**Disciplina: Infraestrutura de Hardware**

---

## 📌 Badges

![Status](https://img.shields.io/badge/status-em%20desenvolvimento-yellow)
![Disciplina](https://img.shields.io/badge/disciplina-Infraestrutura%20de%20Hardware-blue)
![Tipo](https://img.shields.io/badge/projeto-CPU%20Simulada-purple)
![Linguagem](https://img.shields.io/badge/linguagem-C-lightgrey)
![Instituição](https://img.shields.io/badge/instituição-CESAR%20School-orange)

---

## 📖 Descrição do Problema

O objetivo deste desafio é implementar uma lógica de baixo nível capaz de percorrer um vetor de dados na memória, identificar o menor valor presente entre eles e armazenar esse resultado em um endereço de memória específico.

O processador deve executar o ciclo clássico de **Fetch-Decode-Execute (F-D-E)** partindo do endereço inicial até encontrar a instrução de parada (**HALT**).

---

## ⚙️ Fundamentação Técnica

### 🔄 Ciclo Fetch-Decode-Execute (F-D-E)

O funcionamento do processador neste projeto segue o modelo clássico de execução de instruções:

- **Fetch (Busca)**  
  O processador acessa a memória principal para buscar a próxima instrução, utilizando o contador de programa (PC).

- **Decode (Decodificação)**  
  A instrução é interpretada pela unidade de controle, que identifica a operação a ser realizada e os operandos envolvidos.

- **Execute (Execução)**  
  A operação é efetivamente executada, podendo envolver cálculos aritméticos/lógicos, acesso à memória ou alteração do fluxo de execução.

Esse ciclo se repete continuamente até que a instrução **HALT** seja encontrada, encerrando a execução.

---

### 📉 Objetivo do Algoritmo

O algoritmo implementado tem como finalidade:

1. Percorrer sequencialmente um vetor armazenado na memória
2. Comparar os valores elemento a elemento
3. Manter atualizado o menor valor encontrado durante a execução
4. Armazenar o resultado final em uma posição de memória previamente definida

#### 🧩 Características Relevantes

- Implementação em **baixo nível**, simulando comportamento real de hardware
- Controle explícito de memória e fluxo de execução
- Uso de instruções básicas (leitura, comparação, salto condicional)
- Dependência direta do ciclo F-D-E para funcionamento correto

---

## ▶️ Como Executar

```bash
gcc main.c -o output
./output
```

1. Clone o repositório:
   ```bash
   git clone https://github.com/EduardaSouzaOL/CPU-Atividade.git