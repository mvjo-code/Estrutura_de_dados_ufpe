[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Ddjrghst)
# Hello there! 

O objetivo desse problema é criar um programa que lê nomes da entrada padrão e imprime 
```
Hello NOME! 
```
Para cada `NOME` lido


## Formato de Entrada

A entrada é dada por várias linhas, cada uma com um nome, terminada com uma linha com a string `END`.

```
NOME1
NOME2
...
NOMEN
END
```

## Formato de Saída

Para cada nome da entrada, o programa deve imprimir uma linha na forma 
```
Hello NOME!

```

## Instruções

* Modifique o arquivo [solver.cpp](solver.cpp) e faça commit sem mudar o nome do arquivo ou qualquer outro arquivo do repositório.
* A cada commit o sistema tentará executar os testes
```
make test1
make test2
```
* Cada teste de número `X=1, 2`:
    * Compila o programa `solver.cpp`
    * Executa o programa redirecionando o arquivo `X.in` para a entrada padrão e a saída padrão para o arquivo `saida.X`
    * Compara os arquivo produzido `saida.X` com a saída esperada `X.out`


