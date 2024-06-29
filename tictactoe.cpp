#include <iostream>
#include <string>

using namespace std;

typedef string tipoClave;
typedef int tipoInfo;

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
 * int sum % TAM
 * ******
 * */
int h(tipoClave k) {
    int sum = 0;
    for (char c : k) {
        sum += c;
    }
    return sum % TAM;
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
            nodo->info += I;
            return 1;  // La clave ya existe
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
    return 0; 
}
/*****
 * int main
 * ******
 * Funcion main la cual lee por consola las acciones a realizar en la tabla hash y las realiza
 * ******
 * Input:
 * por consola se lee las acciones a realizar en la tabla hash
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

    // leo las acciones y los estados del tablero
    int accion;
    while (cin >> accion && accion != 3) {
        tipoClave clave;
        for (int i = 0; i < 3; i++) {
            string linea;
            cin >> linea;
            clave += linea;
        }
        if (accion == 1) {
            hashInsert(clave, 1);
        } else if (accion == 2) {
            cout << hashSearch(clave) << endl;
        }
    }

    return 0;
}
