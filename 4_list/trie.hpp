#include <string>
#include <cassert>
#include <iostream>

using namespace std;

// Definindo uint para garantir compatibilidade
typedef unsigned int uint;

class Trie {
    struct Node {
        char label;       
        uint nchd;
        uint leafCount;  // número de folhas na subárvore
        Node *firstChd;
        Node *sibling;

        Node(char c) : label(c), nchd(0), leafCount(0), firstChd(nullptr), sibling(nullptr) {}

        ~Node() {
            if (firstChd) delete firstChd;
            if (sibling) delete sibling;
        }

        // Retorna o filho com o rótulo c
        Node *getChd(char c) {
            Node* curr = firstChd;
            while (curr) {
                if (curr->label == c) return curr;
                curr = curr->sibling;
            }
            return nullptr;
        }
       
        // Adiciona um filho mantendo a ordem alfabética (IMPORTANTE para o getKth)
        Node *addChd(char c) {
            Node* newNode = new Node(c);
            
            if (!firstChd || c < firstChd->label) {
                newNode->sibling = firstChd;
                firstChd = newNode;
            } else {
                Node* curr = firstChd;
                while (curr->sibling && curr->sibling->label < c) {
                    curr = curr->sibling;
                }
                newNode->sibling = curr->sibling;
                curr->sibling = newNode;
            }
            nchd++;
            return newNode;
        }
   
        // Insere a string word[start:]
        bool insert(const string &word, int start = 0) {
            if (start == word.length()) return false; 

            char c = word[start];
            Node* child = getChd(c);
            bool createdNew = false;

            if (!child) {
                child = addChd(c);
                createdNew = true;
            }

            // Se é o último char (o sentinela $), conta como folha
            if (start == word.length() - 1) {
                if (!createdNew) return false; // Já existia
                child->leafCount = 1;
                this->leafCount++;
                return true;
            }

            bool inserted = child->insert(word, start + 1);
            if (inserted) {
                this->leafCount++;
            }
            return inserted;
        }

        // Remove a string word[start:]
        bool remove(const string &word, int start = 0) {
            if (start == word.length()) return false;

            char c = word[start];
            Node* child = getChd(c);
            if (!child) return false;

            if (start == word.length() - 1) {
                this->leafCount--;
                removePhysicalChild(child);
                return true;
            }

            bool removed = child->remove(word, start + 1);

            if (removed) {
                this->leafCount--;
                if (child->leafCount == 0) {
                    removePhysicalChild(child);
                }
            }
            return removed;
        }

        void removePhysicalChild(Node* target) {
            if (!firstChd) return;
            if (firstChd == target) {
                firstChd = target->sibling;
                target->sibling = nullptr;
                delete target;
                nchd--;
                return;
            }
            Node* curr = firstChd;
            while (curr->sibling) {
                if (curr->sibling == target) {
                    curr->sibling = target->sibling;
                    target->sibling = nullptr;
                    delete target;
                    nchd--;
                    return;
                }
                curr = curr->sibling;
            }
        }

        // Busca a K-ésima string
        string getKth(uint k, string prefix) {
            Node* curr = firstChd;
            while (curr) {
                if (k < curr->leafCount) {
                    if (curr->label == '$') {
                        return prefix + '$';
                    }
                    return curr->getKth(k, prefix + curr->label);
                } else {
                    k -= curr->leafCount;
                    curr = curr->sibling;
                }
            }
            return "";
        }
    };

private:
    Node *root; 
    
public:
    Trie() {
        root = new Node(' '); // Raiz dummy
    }

    ~Trie() {
        delete root;
    }

    uint size() {
        return root->leafCount;
    }
  
    bool contains(const string &word) {
        Node* curr = root;
        for (char c : word) {
            curr = curr->getChd(c);
            if (!curr) return false;
        }
        return true;
    }
   
    bool insert(const string &word) {
        return root->insert(word, 0);
    }
    
    bool remove(const string &word) {
        return root->remove(word, 0);
    }
  
    string getKth(uint k) {
        if (k >= root->leafCount) return "";
        return root->getKth(k, "");
    }
};