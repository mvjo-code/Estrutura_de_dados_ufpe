#include <iostream>
#include "hashtable.hpp"

using namespace std;

int main()
{
    int Mmin, Fmin, Fmax;
    if (!(cin >> Mmin >> Fmin >> Fmax)) return 0;

    LPHashTable lp(Mmin, Fmin, Fmax);
    RHHashTable rh(Mmin, Fmin, Fmax);

    string cmd, placa;
    
    int maxD0 = -1; 
    int maxD1 = -1;
    bool hasSearch = false;

    while (cin >> cmd && cmd != "END") {
        cin >> placa;
        
        // Calcula a chave para imprimir na saida
        uint key = HashTable::HashKey(placa);

        if (cmd == "IN") {
            ipair p0 = lp.add(placa);
            ipair p1 = rh.add(placa);
            cout << key << " " << p0.first << " " << p0.second << " " << p1.first << " " << p1.second << endl;
        } 
        else if (cmd == "OUT") {
            ipair p0 = lp.del(placa);
            ipair p1 = rh.del(placa);
            if (p0.first == -1) {
                // CORRECAO: Imprimir a key antes dos -1
                cout << key << " -1 -1 -1 -1" << endl;
            } else {
                cout << key << " " << p0.first << " " << p0.second << " " << p1.first << " " << p1.second << endl;
            }
        } 
        else if (cmd == "SCH") {
            hasSearch = true;
            ipair p0 = lp.get(placa);
            ipair p1 = rh.get(placa);
            
            if (p0.first != -1) {
                if (p0.second > maxD0) maxD0 = p0.second;
            }
            if (p1.first != -1) {
                if (p1.second > maxD1) maxD1 = p1.second;
            }

            if (p0.first == -1) {
                // CORRECAO: Imprimir a key antes dos -1
                cout << key << " -1 -1 -1 -1" << endl;
            } else {
                cout << key << " " << p0.first << " " << p0.second << " " << p1.first << " " << p1.second << endl;
            }
        }
    }

    if (hasSearch) {
        cout << maxD0 << " " << maxD1 << endl;
    } else {
        cout << "-1 -1" << endl; 
    }

    return 0;
}