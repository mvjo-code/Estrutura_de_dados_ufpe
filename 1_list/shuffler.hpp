#include <iostream>
#include <cassert>
#include <string>

// arr = array de ponteiros para strings (string**)
// size = no de elementos de arr
// pos = posicao do corte
void cut (std::string **arr, size_t size, size_t pos) 
{	
	if (size == 0 || pos == 0 || pos >= size) return;

    // Aloca arrays de PONTEIROS para strings
	std::string** temp1 = new std::string*[pos];
	std::string** temp2 = new std::string*[size - pos];
	
	//salvando parte esquerda (salvando o PONTEIRO)
	for (size_t i = 0; i < pos; i++){
		temp1[i] = arr[i]; // Acesso correto: arr[i]
	}
	
	//salvando parte direita (salvando o PONTEIRO)
	for (size_t i = pos; i < size; i++){
		temp2[i - pos] = arr[i]; // Acesso correto: arr[i]
	}

	//completando rearranjo:
	for (size_t i = 0; i < size - pos; i++){
		arr[i] = temp2[i];
	}
	for (size_t i = 0; i < pos; i++){
		arr[size - pos + i] = temp1[i];
	}

	delete[] temp1;
	delete[] temp2;

}

// arr = array de ponteiros para strings (string**)
// size = no de elementos de arr
// pos = posicao do corte
void shf (std::string **arr, size_t size, size_t pos) 
{
	if (size == 0 || pos == 0 || pos >= size) return;

	// Aloca arrays de PONTEIROS para strings
	std::string** temp1 = new std::string*[pos];
	std::string** temp2 = new std::string*[size - pos];
	
	//salvando parte esquerda (salvando o PONTEIRO)
	for (size_t i = 0; i < pos; i++){
		temp1[i] = arr[i]; // Acesso correto: arr[i]
	}
	
	//salvando parte direita (salvando o PONTEIRO)
	for (size_t i = pos; i < size; i++){
		temp2[i - pos] = arr[i]; // Acesso correto: arr[i]
	}

	//completando rearranjo
	size_t a = 0, b = 0, k = 0;
	while ((a < pos) && (b < size - pos)){

		if (k % 2 == 0){  //posições pares
			arr[k] = temp1[a];
			a++;
			
		}
		else{   //posições ímpares
			arr[k] = temp2[b];
			b++;
		}
		k++;
			
	}
	
	//colocando o que sobrou:
	while (a < pos){
		arr[k] = temp1[a];
		k++;
		a++;
	}
	while (b < size - pos){
		arr[k] = temp2[b];
		k++;
		b++;
	}
	
	delete[] temp1;
	delete[] temp2;
}

// arr = array de ponteiros para strings (string**)
// size = no de elementos de arr
// pos = posicao do corte
void shb (std::string **arr, size_t size, size_t pos) 
{
	if (size == 0 || pos == 0 || pos >= size) return;

    size_t size_L = pos;
    size_t size_R = size - pos;

	// Aloca arrays de PONTEIROS para strings
    std::string** temp1 = new std::string*[size_L];
    std::string** temp2 = new std::string*[size_R];
    
    //salvando partes (salvando o PONTEIRO)
    for (size_t i = 0; i < size_L; i++){
        temp1[i] = arr[i];
    }
    for (size_t i = 0; i < size_R; i++){
        temp2[i] = arr[pos + i];
    }

    // Contadores: a e b para os arrays temp, k para o array arr
    int a = (int)size_L - 1; // Último índice de L
    int b = (int)size_R - 1; // Último índice de R
    int k = (int)size - 1;   // Último índice de destino

    int q = 0; // Variável auxiliar para alternância R, L, R, L...

    while ((a >= 0) && (b >= 0)){

        if (q == 1){  // É a vez de L
            arr[k] = temp1[a];
            a--;
            q = 0;
        }
        else{   // É a vez de R
            arr[k] = temp2[b];
            b--;
            q = 1;
        }
        k--;
    }
    
    //colocando o que sobrou (L)
    while (a >= 0){
        arr[k] = temp1[a];
        k--;
        a--;
    }
    
    //colocando o que sobrou (R)
    while (b >= 0){
        arr[k] = temp2[b];
        k--;
        b--;
    }
    
    delete[] temp1;
    delete[] temp2;
}