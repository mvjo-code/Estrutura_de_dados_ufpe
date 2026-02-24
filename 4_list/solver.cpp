#include <iostream>
#include <string>
#include "trie.hpp"

using namespace std;

int main() {
    Trie trie;
    char command;
    
    // O loop continua lendo até encontrar o caractere '#' ou fim de arquivo
    while (cin >> command && command != '#') {
        if (command == 'I') {
            string word;
            cin >> word;
            // Adiciona sentinela e insere
            word += '$';
            trie.insert(word);
            // Imprime o número total de folhas (palavras)
            cout << trie.size() << endl;
        } 
        else if (command == 'D') {
            string word;
            cin >> word;
            // Adiciona sentinela e remove
            word += '$';
            trie.remove(word);
            // Imprime o número total de folhas após remoção
            cout << trie.size() << endl;
        } 
        else if (command == 'Q') {
            string word;
            cin >> word;
            // Adiciona sentinela e consulta
            word += '$';
            if (trie.contains(word)) {
                cout << "1" << endl;
            } else {
                cout << "0" << endl;
            }
        } 
        else if (command == 'L') {
            uint k;
            cin >> k;
            // Busca a K-ésima palavra
            string result = trie.getKth(k);
            
            // O enunciado pede para imprimir a palavra. 
            // O método getKth retorna a palavra COM o sentinela '$' no final.
            // Para a saída ficar limpa (apenas a palavra original), removemos o '$'.
            if (!result.empty() && result.back() == '$') {
                result.pop_back();
            }
            cout << result << endl;
        }
    }

    return 0;
}