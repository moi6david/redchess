#include "MoiFish.h"

int arr_ataques[239];

int main() {
    // Creamos el árbol
    Arreglo_Ataques(arr_ataques);
    Posicion P=Posicion();
    Nodo *raiz = crearNodo(P);
    int n=GeneraArbol(raiz,4);
    cout<<n<<endl;
    liberarArbol(raiz);
    return 0;
}
