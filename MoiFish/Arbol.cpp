#include "MoiFish.h"


int GeneraArbol(Nodo* raiz,int proff){
    static int n=0;
    n+=GeneraJugadasValidas(raiz);
    if(proff==1){
        for(auto rama : raiz->ramas){
            Evalua(rama);
        }
        return n;
    }
    else{
        for(auto rama : raiz->ramas){
            GeneraArbol(rama,proff-1);
        }
    }
    return n;
}

void liberarArbol(Nodo* nodo) {
    for (auto rama : nodo->ramas) {
        liberarArbol(rama);
    }
    delete nodo;
}
