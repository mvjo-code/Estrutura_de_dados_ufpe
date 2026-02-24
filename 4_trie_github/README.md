[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/muMxtJBX)
# Trie

## Descrição

Uma **Trie** é uma árvore n-ária em que cada nó `N` é rotulado por um caractere `N.label` e tal que
os vértices irmãos têm todos rótulos diferentes.

```
              #
           /     \
          h        s (3)
        /  \         \
       e    i          h (4)
      /    /  \          \
 (1) r    m    s (2)       e (5)
    /
   s
```

Cada nó numa trie *representa* uma string formada pelos rótulos dos nós no caminho da raiz até ele, 
excluindo o rótulo da raiz. Por exemplo, o vértice (1) do exemplo acima representa a string "`her`", enquanto a folha (2) representa a string "`his`". A raiz representa a string vazia. Portanto, uma trie é uma estrutura de dados usada para representar um conjunto de palavras, uma por cada nó.

Para consultar se uma palavra `W` pertence ao conjunto representado pela trie, seguimos um caminho a partir da raiz respondendo aos caracteres de `W`. Por exemplo, para consultar a palavra "`she`", iniciamos pela raiz, procuramos um filho com rótulo `s`, passamos para o nó (3), depois procuramos um filho desse nó com rótulo `h`, passando ao nó (4), e finalmente procuramos um filho com rótulo `e`, chegando ao nó (5). Como conseguimos usar todas as letras, concluímos que `she` pertence ao conjunto das palavras representadas. Já se estivéssemos procurando "`shall`", ao chegarmos ao nó (4) não encontraríamos nenhum filho com rótulo `a`, e então concluiríamos que a palavra não está representada.

Para inserir uma palavra não representada `W`, nós "descemos" a partir da raiz usando o maior prefixo de `W` que está representado, e a partir daí inserimos um novo ramo para representa o sufixo restante. Por exemplo, para inserir "`shall`", descemos até o nó (4) usando o prefixo `sh`, e a partir daí inserimos uma sequência de nós (ramo) para representar o `all` restante. 

```
              #
           /     \
          h        s 
        /  \         \
       e    i          h (4)
      /    /  \       /  \
     r    s    m     a    e 
    /               /
   s               l
                  /
                 l
```

É conveniente alterar ligeiramente essa definição para representar um conjunto de palavras apenas pelas **folhas** de uma trie. Para tal, precisamos que nenhuma palavra representada seja um prefixo próprio de outra. Para conseguir isso artificialmente, adicionamos ao final de cada palavra uma caractere especial `$` chamado **sentinela**, que não aparece em nenhuma outra posição de palavra alguma. Por exemplo, para representar {`he`, `him`, `his`, `she`, `her`, `hers`}, precisamos incluir {`he$`, `him$`, `his$`, `she$`, `her$`, `hers$`}, obtendo

```
                #
             /      \
       (6)  h         s 
         /     \        \
   (7) e         i (8)    h
     /  \       /  \        \
   $    r      m    s (9)     e 
       /  \    |    |         |  
      $    s   $    $         $
           |    
           $     
```

Repare que, desta forma,, cada palavra está representada por uma folha e reciprocamente. Palavras como `he` e  `her`, que antes estavam representadas por nós internos, agora passam a ser representadas por folhas. A quantidade de palavras representadas que começam com um certo prefixo é dada pelo número de folhas na subárvore enraizada no nó correspondente a esse prefixo. Por exemplo, existem cinco palavras representadas que começam  por `h`, que é o número de folhas da subárvore enraizada em (6) na figura acima, e três palavras iniciadas em `he`, que é o número de folhas da subárvore enraizada em (7).

Finalmente, se os filhos de cada nó estiverem ordenados lexicograficamente, então um percurso em profundidade da trie visita as folhas na ordem lexicográfica das palavras representadas. No exemplo acima, as folhas seriam visitadas da esquerda para a direita, obtendo a enumeração `he`, `her`, `hers`, `him`, `his`, `she`. Assim `K`-ésima palavra em ordem lexicográfica corresponde à `K`-ésima folha.

Se a trie estiver ordenada dessa forma, podemos consultar mais rapidamente a `K`-ésima palavra  representada `Wk`. Para isso, armazenarmos em cada nó `N` o número de folhas na sua subárvore. Chamemos esse valor do **peso** do nó `N.weight`.  No exemplo acima, o nó (6) tem peso 5, o nó (7) tem peso 3, e a raiz tem peso 6. Cada folha tem peso 1. O peso de alguns nós precisam ser atualizados a cada modificação da trie. Porém, para consultar a `K`-ésima palavra (`K=0,1,...`), procedemos da seguinte forma. Começando pela raiz, vamos somando os pesos dos nós seus filhos da esquerda para a direita enquanto a soma for `<= K`. Seja `S` o maior valor possível da soma `<=K` e  `V` o filho cujo peso faria a soma extrapolar `K`. Isso significa que as `S` folhas das subárvores dos nós anteriores a `V` são todos menores do que `Wk`. Por outro lado, se considerarmos as palavras da subárvore de `V`, então teríamos mais do que `K` palavras. Logo, `Wk` deve estar na subárvore enraizada em `V`. Porém como já deixamos `S` palavras "pra trás", precisamos procurar a palavra de ordem `K' = K-S` nessa subárvore.

Por exemplo, suponha que estamos procurando a palavra de ordem `K=4` (`his`) na  figura acima. No primero momento, teríamos `S=0` e `V`=(6). Portanto, temos de procurar (recursivamente) a folha de ordem `K'=K-S=4` na subárvore enraizada em (6). Nesse segundo passo, temos `S'=3` e `V'=`(8). Precisamos portanto procurar a folha de ordem `K"=K'-S'=1` na árvore enraizada em (8). Agora `S"=1` e `V"`=(9). Finalmente precisamos procuar a folha de ordem `K"-S"=1-1=0` na subárvore enraizada em (9). A primeira e única folha desse nó corresponde exatamente à palavra procurada.


## Entrada

A entrada é constituída de várias linhas, cada uma correspondendo a uma operação da trie num dos formatos a seguir:

- `I W` : Insere a palavra `W` na trie.
- `D W` : Remove a palavra `W` da trie.
- `Q W` : Consulta a palavra `W` da trie.
- `L K` : Consulta a `K`-ésima palavra em ordem lexicográfica representada na trie.

A entrada termina com uma linha

```
#
```

**IMPORTANTE**: Não esquecer de acrescentar o sentinela `$` às palavras no arquivo de entrada antes das inserções/remoções/consultas.

## Saída

Para cada operação na entrada, o programa deve imprimir a saída correspondente da sequinte forma.

- `I W` : Imprime a quantidade de palavras representadas (folhas) da trie após a inserção. Repare que, caso a trie já contenha a palavra `W`, a inserção não provoca qualquer mudança e o número de palavras representadas permanece inalterado.
- `D W` : Imprime a quantidade de palavras representadas (folhas) da trie após a remoção. Caso a trie não contenha a palavra `W`, a remoção não provoca qualquer mudança e o número de palavras representadas permanece inalterado.
- `Q W` : Imprime `1` caso a trie contenha a palavra `W`, ou `0` caso contrário. 
- `L K` : Imprime a `K`-ésima palavra em ordem lexicográfica representada na trie.

## Instruções de Implementação

- Completar o arquivo [trie.hpp](./trie.hpp) que contém as definições dos tipos  usados na solução:
- Completar o arquivo [solver.cpp](./solver.cpp) que é usado para gerar o executável da solução.
- Não alterar o arquivo [sanity.cpp](./sanity.cpp)
- Não alterar os arquivos de entradas/saidas de teste (*.in, *.out)
- **FAZER COMMIT APENAS DAS MODIFICAÇÕES DOS ARQUIVOS [trie.hpp](./trie.hpp) e [solver.cpp](./solver.cpp)**. **NÃO ADICIONAR NOVOS ARQUIVOS AO REPOSITÓRIO**.