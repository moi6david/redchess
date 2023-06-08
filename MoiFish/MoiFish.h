#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

#define CasillaV 0b00000000 // 0b indica que el número está en formato binario

#define PeonB 0b00000010       //el último bit indica el color (cero para blanco y 1 para negro)
#define TorreB 0b00000100      //el penúltimo indica si es peón, el antepenúltimo si es caballo, etc.
#define CaballoB 0b00001000
#define AlfilB 0b00010000
#define DamaB 0b00100000
#define ReyB 0b01000000

#define PeonN 0b00000011
#define TorreN 0b00000101
#define CaballoN 0b00001001
#define AlfilN 0b00010001
#define DamaN 0b00100001
#define ReyN 0b01000001

#define Peon 0b0000001          //con solo 7 bits es para tener las variables sin el color.
#define Torre 0b0000010
#define Caballo 0b0000100
#define Alfil 0b0001000
#define Dama 0b0010000
#define Rey 0b0100000

extern int arr_ataques[239];

struct Tiro{
	unsigned char pieza,coorini,coorfin;    //pieza es el inidice del arreglo piezas[0] o piezas[1]
};

class Posicion{
	public:
	unsigned char tablero[128];
	unsigned char piezas[2][16];
	bool turno; //0 si le toca al blanco y 1 si le toca al negro.
	bool enrdama[2],enrrey[2]; //1 si se puede el enroque y 0 si no se puede. el primer indice es para el blanco y el segundo para el negro
	unsigned char paso;   //paso guarda el valor de si hay alguna captura al paso que se pueda hacer.
    //Si paso es cero no hay posibles capturas al paso y si no entonces guarda el valor de la casilla que se puede capturar al paso.
	Posicion();
	Posicion(string fen);
	int EvaluaPosicion();
	//Jacke devuelve 0 si no hay jaque y 1 si sí lo hay.
	//Si es turno de las blancas revisará si las negras están en jaque y viceversa.
	//Esto se hace así porque la función sirve para verificar que el movimiento previo era legal.
	int Jacke();
	void Pinta();
	bool TiroValido(Tiro t);
	void Mueve(Tiro a,int specialmove=0);
};

class Nodo{
	public:
		Posicion P;
		int valor;
	    vector<Nodo*> ramas;
		Posicion get_Posicion(){
			return P;
		}
};

Nodo* crearNodo(Posicion pos);

void agregarRama(Nodo* padre, Nodo* rama);

int GeneraMovimientosCaballo(Nodo* raiz,unsigned char inicial,int ind_pieza);
int GeneraMovimientosAlfil(Nodo* raiz,unsigned char inicial,int ind_pieza);
int GeneraMovimientosTorre(Nodo* raiz,unsigned char inicial,int ind_pieza);
int GeneraMovimientosPeon(Nodo* raiz,unsigned char inicial,int ind_pieza);
int GeneraMovimientosRey(Nodo* raiz,unsigned char inicial,int ind_pieza);
int GeneraMovimientosDama(Nodo* raiz,unsigned char inicial,int ind_pieza);

int FinJuego(int fin);
void liberarArbol(Nodo* nodo);
void Arreglo_Ataques(int (&arr_ataques)[239]);
int GeneraJugadasValidas(Nodo* raiz);
int GeneraArbol(Nodo* raiz,int proff);
void Juega();
unsigned char CordenadaString_a_Numero(string c);
string CordenadaNumero_a_String(unsigned char c);
void PruebaGenerador(unsigned char inicial,int ind_pieza,int fin);
int Evalua(Nodo *x);
