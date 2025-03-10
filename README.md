# Sistema de Simulação de Detecção de Incêndios

## Descrição do Projeto

Este projeto é uma simulação de um sistema de detecção e combate de incêndios em uma floresta, usando programação paralela com `pthread`. A floresta é dividida em uma matriz de 30x30, onde cada célula representa uma área monitorada por um sensor, uma célula livre, uma célula em chamas, ou uma célula já queimada. Sensores (threads) detectam incêndios e se comunicam com os vizinhos ou com uma central de controle para combater o fogo.

## Estrutura do Projeto
. 
├── main.c # Arquivo principal que inicializa a simulação 
├── functions.c # Implementação das funções de sensores, central e combate ao fogo 
├── functions.h # Declarações das funções e definições de constantes 
├── Makefile # Arquivo Makefile para facilitar a compilação (opcional) 
└── README.md # Instruções do projeto


## Pré-requisitos

Antes de compilar e executar o projeto, certifique-se de que o sistema possui as seguintes ferramentas instaladas:

- **GCC** (GNU Compiler Collection) com suporte a pthreads
- **Make** (opcional, mas recomendado)

## Compilando 
gcc -Wall -pthread -o fire_simulation main.c functions.c

## Executando
./fire_simulation
