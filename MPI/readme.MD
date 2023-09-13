# Integrantes do Grupo:
Guilherme Dallmann Lima e João Paulo Brito de Almeida

# Disciplina
Introdução ao Processamento Paralelo  e Distribuído

# implementação: Jogo de Damas
Implementação do Jogo de Damas utilizando MPI e OpenMP.

## Pré-requisitos

- Ambiente configurado para execução de programas em C utilizando MPI e OpenMP.

## Compilação

mpicc damaMPI.c -o damaMPI

## Execução

mpirun -quiet --host localhost:2 ./damaMPI
