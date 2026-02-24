[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/pK5nu_qE)
# Embaralhamento

## Descrição

Considere um array `A = (a[0], a[1],...,a[n-1])`. Definimos quatro operações  sobre `A`:

### 1. CUT i

"Corta" o array em duas partes `L = (a[0],...,a[i-1])` e `R = (a[i],..., a[n-1])` e rearranja como 
`A'=LR`, ou seja, ao final teremos:
```
A' = (a[i],..., a[n-1], a[0],...,a[i-1])` 
```

#### Exemplo: 
```
                 |
CUT( A = [1,2,3,4,5,6,7,8,9,10,11,12], i = 4 ) = [5,6,7,8,9,10,11,12,1,2,3,4]
                 |
```

### 2. SHF i  (Shuffle Forward)

"Corta" o array em duas partes `L = (a[0],...,a[i-1])` e `R = (a[i],..., a[n-1])` e o rearranja  intercalando os elementos de `L` e `R` da **esquerda para a direita**, ou seja, ao final teremos:
```
A' = (a[0], a[i], a[1], a[i+1], ...)` 
```

#### Exemplo: 

```
                 |
SHF( A = [1,2,3,4,5,6,7,8,9,10,11,12], i = 4 ) = [1,5,2,6,3,7,4,8,9,10,11,12]
                 |
```

### 3. SHB i  (Shuffle Backwards)

"Corta" o array em duas partes `L = (a[0],...,a[i-1])` e `R = (a[i],..., a[n-1])` e o rearranja   intercalando os elementos de `L` e `R` da **direita para a esquerda**, ou seja, ao final teremos:
```
A' = (..., a[i-2], a[n-2], a[i-1], a[n-1])` 
```

#### Exemplo: 

```
                 |
SHB( A = [1,2,3,4,5,6,7,8,9,10,11,12], i = 4 ) = [5,6,7,8,1,9,2,10,3,11,4,12]
                 |
```

### 4. REA i  (Read)

"Lê" a posição `i` do array (0-based).

#### Exemplo: 

```
REA( A = [1,2,3,4,5,6,7,8,9,10,11,12], i = 4 ) = 5 
```

Neste exercício vamos implementar essas operações sobre um array de strings aleatórias.


## Entrada

A entrada é constituída por vários casos. A primeira linha contém um inteiro 
```
K
```
correspondente ao número de casos. Seguem-se `K` casos. Cada caso começa com uma linha contendo dois inteiros
```
N P
```
onde 
- `N` é o número de elementos do array,
- `P` é o número de operações executadas sobre o array.

O programa deve gerar um array `A` com `N` strings aleatórias usando a função `StringGen::randomString()` de [strgen.hpp](./strgen.hpp).
- **IMPORTANTE**: No início de cada caso, incluir uma chamada a `StringGen::reset()`

Em seguida temos `P` linhas, cada uma com uma operação de um dos tipos a seguir
- `CUT i`
- `SHF i`
- `SHB i`
- `REA i`.
O programa deve realizar cada operação em `A` conforme explicado acima.

## Saída
A cada `REA i`, o programa deve imprimir uma linha
```
a[i]
```
onde `a[i]` representa a string da posição `i` do array após as operações realizadas até aquele momento.

Ao final de cada caso, o programa deve imprimir
```
a[0] a[N-1]
// linha em branco
```
onde `a[0]` e `a[N-1]` representam, respectivamente, a primeira e última strings do array após todas as operações realizadas.

## Instruções de Implementação

- Completar o arquivo [shuffler.hpp](./shuffler.hpp) que contém as operações usadas na solução:
    - ⚠️ Não alterar as assinaturas das funções `cut`, `shf` e `shb`.
- Completar o arquivo [solver.cpp](./solver.cpp) que é usado para gerar o executável da solução.
- Não alterar o arquivo [strgen.hpp](./sanity.cpp)
- Não alterar o arquivo [sanity.cpp](./sanity.cpp)
- Não alterar os arquivos de entradas/saidas de teste (*.in, *.out)
- **FAZER COMMIT APENAS DAS MODIFICAÇÕES DOS ARQUIVOS [shuffler.hpp](./shuffler.hpp) e [solver.cpp](./solver.cpp)**. 
- ⚠️ **NÃO ADICIONAR NOVOS ARQUIVOS AO REPOSITÓRIO**.
