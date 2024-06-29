#include <iostream>
#include <string>
#include <fstream>
using namespace std;

typedef int tipoClave;
typedef string tipoInfo;

struct Nodo {
    tipoClave clave;
    tipoInfo info;
    Nodo* siguiente;
};

const int TAM = 100;  // Tamaño de la tabla hash

Nodo* HT[TAM];
/*****
 * int h
 * ******
 * Funcion que retorna la posicion en la tabla hash de la clave k
 * ******
 * Input:
 * tipoClave k
 * .......
 * ******
 * Returns:
 * int k % TAM
 * ******
 * */
int h(tipoClave k) {
    return k % TAM;
}
/*****
 * int hashInsert
 * ******
 * Funcion que inserta en la tabla hash la clave k y su informacion I
 * ******
 * Input:
 * tipoClave k, tipoInfo I
 * .......
 * ******
 * Returns:
 * int 1
 * ******
 * */
int hashInsert(tipoClave k, tipoInfo I) {
    int pos = h(k);
    Nodo* nodo = HT[pos];

    while (nodo != nullptr) {
        if (nodo->clave == k) {
            return 0;  
        }
        nodo = nodo->siguiente;
    }
    nodo = new Nodo;
    nodo->clave = k;
    nodo->info = I;
    nodo->siguiente = HT[pos];
    HT[pos] = nodo;
    return 1;
}
/*****
 * int hashDelete
 * ******
 * Funcion que elimina de la tabla hash la clave k y retorna su informacion
 * ******
 * Input:
 * tipoClave k
 * .......
 * ******
 * Returns:
 * tipoInfo info
 * ******
 * */
tipoInfo hashDelete(tipoClave k) {
    int pos = h(k);
    Nodo* nodo = HT[pos];
    Nodo* prev = nullptr;
    while (nodo != nullptr) {
        if (nodo->clave == k) {
            tipoInfo info = nodo->info;
            if (prev == nullptr) {
                HT[pos] = nodo->siguiente;
            } else {
                prev->siguiente = nodo->siguiente;
            }
            delete nodo;
            return info;
        }
        prev = nodo;
        nodo = nodo->siguiente;
    }
    return "Valor inválido";  
}
/*****
 * tipoInfo hashSearch
 * ******
 * Funcion que busca en la tabla hash la clave k y retorna su informacion
 * ******
 * Input:
 * tipoClave k
 * .......
 * ******
 * Returns:
 * tipoInfo
 * ******
 * */
tipoInfo hashSearch(tipoClave k) {
    int pos = h(k);
    Nodo* nodo = HT[pos];
    while (nodo != nullptr) {
        if (nodo->clave == k) {
            return nodo->info;
        }
        nodo = nodo->siguiente;
    }
    return "Valor inválido";  // La clave no existe
}
/*****
 * int main
 * ******
 * Funcion main la cual lee un archivo de premios y un archivo con los numeros comprados y retorna los premios que se ganaron
 * ******
 * Input:
 * Un archivo de premios y un input por consola con los numeros comprados
 * .......
 * ******
 * Returns:
 * int 0
 * ******
 * */
int main() {
    // Inicializa la tabla hash
    for (int i = 0; i < TAM; i++) {
        HT[i] = nullptr;
    }

    ifstream archivo("premios.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de premios." << endl;
        return 1;
    }

    // Lee la cantidad de premios
    int n;
    archivo >> n;

    // Lee los premios e inserta en la tabla hash
    for (int i = 0; i < n; i++) {
        tipoClave clave;
        tipoInfo info;
        archivo >> clave;
        getline(archivo, info);  
        hashInsert(clave, info);
    }

    archivo.close();

    // Lee la cantidad de personas
    int k;
    cin >> k;

    // Lee los números comprados e imprime los premios
    for (int i = 0; i < k; i++) {
        tipoClave clave;
        cin >> clave;
        tipoInfo info = hashSearch(clave);
        if (info != "Valor inválido") {
            cout << info << endl;
            hashDelete(clave);
        } else {
            cout << "No tiene premio" << endl;
        }
    }

    return 0;
}
