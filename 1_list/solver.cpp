#include <fstream>
#include <iostream>
#include <string>
#include "strgen.hpp"
#include "shuffler.hpp"


int main() {
	size_t k, n, p;  //casos, tamanho do array e numero de operações

	std::cin >> k;//primeira entrada(número de casos)

	while (k > 0){    //while para os casos
		StringGen::reset();

		std::cin >> n >> p; //entrando com tamanho do array e numero de operações
		std::string **estrutura = new string*[n];

		size_t y;
		for (y=0; y<n; y++){  //for para criar as strings
			estrutura[y] = new string{StringGen::randomString()};

		}

		while (p > 0){  //while para as operações
			std::string operacao;
			size_t corte;

			std::cin >> operacao >> corte;
			
			//fazendo operações
			if (operacao == "CUT"){
				cut(estrutura, n, corte);
			}
			else if (operacao == "SHF"){
				shf(estrutura, n, corte);
			}
			else if (operacao == "SHB"){
				shb(estrutura, n, corte);
			}
			else if (operacao == "REA"){
				std::cout << *estrutura[corte] << endl;
			}
			p --;
		}

		std::cout << *estrutura[0] << " " << *estrutura[n-1] << endl;
		std::cout << endl;

		 // Primeiro: Libera cada string alocada individualmente (new string)
        for (size_t i = 0; i < n; ++i) {
            delete estrutura[i];
        }
        // Segundo: Libera o array de ponteiros (new string*[n])
        delete[] estrutura;

		k--;
	}

	return 0;
	// IMPORTANTE:
	// Incluir uma chamada a StringGen::reset() no inicio de cada caso
}