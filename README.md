# TRABALHO - Tabelas Hash

Este projeto implementa um **Catálogo de Filmes por Gênero**, aplicando conceitos de Estruturas de Dados 2, com destaque para Tabela Hash, Lista Encadeada e Árvore AVL.

---

## ✅ Objetivo

- Catalogar filmes por gênero, facilitando buscas e ordenações.  
- Utilizar ao menos duas estruturas de dados além da Tabela Hash, sendo **uma obrigatoriamente de ED2**.  
- Trabalhar com dados prontos e analisar a complexidade de tempo das operações.  

---

## ✅ Funcionalidades

- **Tabela Hash**: vetor de 1009 posições, que armazena ponteiros para listas encadeadas.  
- **Lista Encadeada**: armazena diferentes gêneros de filmes em cada posição da hash, permitindo colisões controladas.  
- **AVL Tree**: cada gênero possui sua própria AVL para armazenar os filmes, ordenados pela avaliação.  
- Busca completa de todos os filmes de um gênero solicitado  
- Busca de filmes que contenham parte do título digitado pelo usuário

---

## ✅ Ideias (Loucuras da Minha Cabeça 😄)

- Um script Python (`movie.py`) antigo, foi modificado ele gera dados de filmes aleatórios.
- O código em C++ chama esse script automaticamente via `system()` para gerar filmes sempre que o usuário desejar.
- Foi uma forma divertida de integrar Python + C++, Tive essa curiosidade, de fato funciona (no meu PC)

---

## ✅ Análise de Complexidade (Tempo)

| Função                  | Complexidade |
|-------------------------|--------------|
| AVL insert              | O(log n)     |
| AVL inorder             | O(n)         |
| AVL countNodes          | O(n)         |
| Hash insert             | ???????????? |
| Hash printByGenre       | O(n + m)     |
| Hash countAllMovies     | O(n)         |
| GenerateMovies (C++)    | O(1)         |
| GenerateMovies (Python) | O(n)         |
| loadFile                | O(n)         |

*Observação*:  
- **n** = quantidade total de filmes  
- **m** = tamanho médio das listas encadeadas

---

## ✅ Pré-requisitos

- `g++` (no Linux instale com `sudo apt install build-essential`)
- `python3` (no Linux instale com `sudo apt install python3`)

---

## ✅ Instalação

```bash
git clone git@github.com:LlGEIRINHO/Hashing-Homework.git
cd Hashing-Homework
