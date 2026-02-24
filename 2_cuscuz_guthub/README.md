[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/82tWvSyT)
# Cuscuz

## Descrição

O cuscuz é um jogo que usa cartas de um baralho numeradas `1, 2, 3, ..., 9`, cada uma com os quatro possíveis naipes, Copas (`C`), Espada (`E`), Ouro (`O`), e Paus (`P`). Cada partida é disputada por `N>=2` jogadores, numerados `0..N-1`. Além dos jogadores, temos também um dealer responsável por distribuir cartas entre os jogadores.

Inicialmente o dealer distribui `T = N * H` cartas entre os jogadores **alternadamente**, isto é, cada jogador recebe a sua primeira carta, depois cada jogador recebe a sua segunda carta, etc, até que por fim cada jogador recebe a sua `H`-ésima carta. Ao final da distribuição, cada jogador tem uma mão de `H` cartas. A mão de cartas de cada jogador é organizada como uma **fila**, ou seja, cada carta nova dada ao jogador pelo dealer é adicionada **ao final** da sua mão/fila.

Em seguida, o jogo é disputado em diversas rodadas. Em cada rodada, cada jogador ainda em disputa, na ordem `0..N-1`, retira a primeira carta da sua fila e a joga num monte central (o **cuscuz**). O cuscuz é organizado como uma **pilha**, ou seja, cada nova carta é adicionada ao topo. O jogador que colocar a carta com maior valor no cuscuz vence a rodada. O valor de cada carta é dado pelo seu número `1 < 2 <...< 9` e, em caso de empate, pelo naipe `C < E < O < P`. Cada rodada pode ter um ou mais vencedores (em caso de empate na maior carta). Cada vencedor de uma rodada ganha 1 (um) ponto. Caso haja um único vencedor na rodada, ele ganha todas as cartas do cuzcuz, sendo as cartas são desempilhadas uma a uma do monte e adicionadas ao final da sua mão/fila. Em caso de empate na rodada, o monte é descartado. Caso algum jogador fique sem cartas, ele está fora do jogo e não poderá participar nas rodadas seguintes.

O jogo acaba de uma de duas maneiras: se apenas um jogador permanecer com cartas para jogar, ou se um número máximo pré-estabelecido de rodadas `M` for atingido. No primeiro caso, o vencedor será o único jogador com cartas e, no segundo, o(s) vencedor(es) serão aquele(s) que tiver(em) o maior número de pontos (podendo haver empates).


## Entrada

A entrada começa com uma linha

```
GAME N M H
```
onde:
- `N` é o número de jogadores
- `M` é o número máximo de rodadas
- `H` é o número inicial da cartas da mão de cada jogador.

Em seguida temos `T=N*H` linhas, cada uma contendo uma carta a ser distribuída entre os jogadores como explicado acima. Exemplo: `7P` (sete de paus), `2C` (dois de copas), etc.


## Saída

O programa deve imprimir inicialmente os resultados de cada rodada disputada no seguinte formato:

```
R WC WP[0] ... WP[Q-1]
```

onde 

- `R = 0,1,...` é o número da rodada
- `WC` é a carta vencedora da rodada
- `WP[0] ... WP[Q-1]` são os números dos jogadores vencedores da rodada (`Q >= 1`)

Em seguida o programa deve imprimir a lista com as pontuações dos jogadores ao final da partida

```
S[0] S[1] ... S[N-1]
```

onde 

- `S[i]` é a pontuação (número de rodadas vencidas) do jogador `#i`.

Finalmente, o programa deve imprimir as mãos dos jogadores vencedores da partida, um por linha, na forma

```
i: Q[0] ... Q[S-1]
```

sendo `Q[0]` a primeira carta, ou seja, a cabeça da fila, e `Q[S-1]` a última carta, ou seja, a cauda da fila.


## Instruções de Implementação

- Completar o arquivo [list.hpp](./list.hpp) que contém as definições dos tipos usados na solução:
    - Não alterar os nomes das classes e assinaturas das interfaces públicas 
- Completar o arquivo [solver.cpp](./solver.cpp) que é usado para gerar o executável da solução.
- Não alterar o arquivo [sanity.cpp](./sanity.cpp)
- Não alterar os arquivos de entradas/saidas de teste (*.in, *.out)
- **FAZER COMMIT APENAS DAS MODIFICAÇÕES DOS ARQUIVOS [list.hpp](./list.hpp) e [solver.cpp](./solver.cpp)**. **NÃO ADICIONAR NOVOS ARQUIVOS AO REPOSITÓRIO**.
