#include "MoiFish.h"

void Arreglo_Ataques(){
    int j,arr_ataques[239]; //239 son todas las posibles diferencias de indices entre casillas (van desde -119 a 119).
    for(int i=0;i<=238;i++){
        j=i-119;
        if(j<8&&j>-8)arr_ataques[i]=2;
        else if(j%17==0)arr_ataques[i]=5;
        else if(j%16==0)arr_ataques[i]=2;
        else if(j%15==0)arr_ataques[i]=5;
        else if(abs(j)==18||abs(j)==14||abs(j)==33||abs(j)==31)arr_ataques[i]=6;
        else arr_ataques[i]=0;
    }
    arr_ataques[119]=0;
    arr_ataques[102]=4;
    arr_ataques[104]=4;
    arr_ataques[118]=1;
    arr_ataques[120]=1;
    arr_ataques[103]=1;
    arr_ataques[135]=1;
    arr_ataques[134]=3;
    arr_ataques[136]=3;
    return;
}


Posicion::Posicion(){ //Constructor con la posición inicial.
	int i;
	turno=0;
	enrdamaB=1;
	enrdamaN=1;
	enrreyN=1;
	enrreyB=1;
	paso=0;
	tablero[0]=TorreB; tablero[1]=CaballoB; tablero[2]=AlfilB; tablero[3]=DamaB;
	tablero[4]=DamaN; tablero[5]=AlfilB; tablero[6]=CaballoB; tablero[7]=TorreB;
	for(i=16;i<24;i++){
		tablero[i]=PeonB;
		tablero[i-8]=CasillaV;
	}
	for(i=25;i<95;i++){
		tablero[i]=CasillaV;
	}
	for(i=96;i<104;i++){
		tablero[i]=PeonN;
	}
	tablero[112]=TorreN; tablero[113]=CaballoN; tablero[114]=AlfilN; tablero[115]=DamaN;
	tablero[116]=ReyN; tablero[117]=AlfilN; tablero[118]=CaballoN; tablero[119]=TorreN;
	piezasB[0]=1; piezasB[1]=6; piezasB[2]=2; piezasB[3]=5;
	piezasB[4]=0; piezasB[5]=7; piezasB[6]=3; piezasB[7]=4;
	for(i=8;i<16;i++){
		piezasB[i]=i+8;
		piezasN[i]=i+88;
	}
	piezasN[0]=113; piezasN[1]=118; piezasN[2]=117; piezasN[3]=114;
	piezasN[4]=112; piezasN[5]=119; piezasN[6]=115; piezasN[7]=116;
}

Posicion::Posicion(unsigned char *tab,unsigned char *pB,unsigned char *pN,bool t,bool edN,bool erN,bool edB,bool erB,bool p){
	int i;
	paso=p;
	for(i=0;i<128;i++){
		tablero[i]=tab[i];
	}
	turno=t;
	enrdamaN=edN;
	enrreyN=erN;
	enrdamaB=edB;
	enrreyB=erB;
	for(i=0;i<16;i++){
		piezasB[i]=pB[i];
		piezasN[i]=pN[i];
	}
	return;
}

Nodo::Nodo* GeneraNodo(Nodo* nodoAnterior,Tiro t){
    Posicion p=nodoAnterior->get_Posicion();
    p.tablero[t.coorfin]=p.tablero[t.coorini];      //actualiza el valor de la casilla final.
    p.tablero[t.coorini]=CasillaV;                  //actualiza el valor de la casilla inicial.
    if(p.turno)p.piezasN[t.pieza]=t.coorfin;        //actualiza el valor de la pieza que se movio.
    else p.piezasB[t.pieza]=t.coorfin;
    if (t.pieza==4){                                //actualiza el valor de los enroques.
        if (p.turno)p.enrdamaN=0;
        else p.enrdamaB=0;
    }
    else if (t.pieza==5){
        if (p.turno)p.enrreyN=0;
        else p.enrreyB=0;
    }
    else if (t.pieza==7){
        if(p.turno){
            enrdamaN=0;
            enrreyN=0;
        }
        else{
            enrdamaB=0;
            enrreyB=0;
        }
    }
    if(p.tablero[t.coorfin]!=CasillaV){         //actualiza el valor de la pieza comida
        for(int i=0;i<16;i++){
            if(p.turno){
                if(p.piezasB[i]==t.coorfin){
                    p.piezasB[i]=120;
                    break;
                }
            }
            else {
                if(p.piezasN[i]==t.coorfin){
                    p.piezasN[i]=120;
                    break;
                }
            }
        }
    }
    if(p.turno){                                        //actualiza el peon que se puede comer al paso
        if((pieza>=8)&&(p.piezasN[pieza]>=96)&&(p.tablero[p.piezasN[pieza]]==PeonN)&&(t.coorini-t.coorfin==32)){
            p.paso=t.coorfin;
        }
        else p.paso=120;
    }
    else {
        if((pieza>=8)&&(p.piezasB[pieza]<24)&&(p.tablero[p.piezasB[pieza]]==PeonB)&&(t.coorfin-t.coorini==32)){
            p.paso=t.coorfin;
        }
        else p.paso=120;
    }
    if(p.turno)p.turno=0;                       //actualiza el turno.
    else p.turno=1;
    Nodo *Nuevo;
    Nuevo=crearNodo(p);
    return Nuevo;
}

bool Posicion::TiroValido(Tiro t){
    if(tablero[t.coorini]==0)return 0;
}

void agregarRama(Nodo* padre, Nodo* rama) {
    padre->ramas.push_back(rama);
}

int GeneraMovimientosCaballo(Nodo* raiz,unsigned char inicial,int ind_pieza){
    Posicion p=raiz->get_Posicion();
    Tiro t;
    int fin,contador=0;
    for(int i=0;i<8;i++){
        if(i==0)fin=inicial+18;
        else if(i==1)fin=inicial-18;
        else if(i==2)fin=inicial+14;
        else if(i==3)fin=inicial-14;
        else if(i==4)fin=inicial+31;
        else if(i==5)fin=inicial-31;
        else if(i==6)fin=inicial+33;
        else fin=inicial-33;
        if(!(fin&0x88)){
            if((p.tablero[fin]==0)||(p.turno!=(p.tablero[fin]&1))){
                t.coorini=inicial;
                t.coorfin=fin;
                t.pieza=ind_pieza;
                p.Mueve(t);
                if(p.Jacke())p=raiz->get_Posicion();
                else{
                    Nodo* nuevo=crearNodo(p);
                    agregarRama(raiz,nuevo);
                    contador+=1
                }
            }
        }
    }
    return contador;
}

int GeneraMovimientosTorre(Nodo* raiz,unsigned char inicial,int ind_pieza){
    Posicion p=raiz->get_Posicion();
    Tiro t;
    int fin,contador=0,j;
    for(int i=0;i<4;i++){
        j=1;
        while(1){
            if(i==0)fin=inicial+j;
            else if(i==1)fin=inicial-j;
            else if(i==2)fin=inicial+16*j;
            else fin=inicial-16*j;
            if(!(fin&0x88)){
                if((p.tablero[fin]==0)){
                    t.coorini=inicial;
                    t.coorfin=fin;
                    t.pieza=ind_pieza;
                    p.Mueve(t);
                    if(p.Jacke())p=raiz->get_Posicion();
                    else{
                        Nodo* nuevo=crearNodo(p);
                        agregarRama(raiz,nuevo);
                        contador+=1
                    }
                }
                else if(p.turno!=(p.tablero[fin]&1)){
                    t.coorini=inicial;
                    t.coorfin=fin;
                    t.pieza=ind_pieza;
                    p.Mueve(t);
                    if(p.Jacke())p=raiz->get_Posicion();
                    else{
                        Nodo* nuevo=crearNodo(p);
                        agregarRama(raiz,nuevo);
                        contador+=1
                    }
                    break;
                }
            }
            else break;
        }
    }
    return contador;
}

int GeneraMovimientosAlfil(Nodo* raiz,unsigned char inicial){

}

int GeneraMovimientosPeon(Nodo* raiz,unsigned char, inicial){

}

int GeneraMovimientosDama(Nodo* raiz,unsigned char inicial){

}

int GeneraMovimientosRey(Nodo* raiz,unsigned char inicial){

}

void GeneraJugadasValidas(Nodo* raiz){
    int aux=0;
    unsigned char pieza;
    Posicion p=raiz->get_Posicion();
    if(p.turno){
        for(int i=0;i<16;i++){
            pieza=p.piezasN[i];
            if(pieza!=120){
                if((i==0)||(i==1))aux+=GeneraMovimientosCaballo(raiz,pieza);
                else if((i==2)||(i==3))aux+=GeneraMovimientosAlfil(raiz,pieza);
                else if((i==4)||(i==5))aux+=GeneraMovimientosTorre(raiz,pieza);
                else if(i==6)aux+=GeneraMovimientosDama(raiz,pieza);
                else if(i==7)aux+=GeneraMovimientosRey(raiz,pieza);
                else {
                    if(p.tablero[pieza]==PeonN)aux+=GeneraMovimientosPeon(raiz,pieza);
                    else if(p.tablero[pieza]==DamaN)aux+=GeneraMovimientosDama(raiz,pieza);
                    else if(p.tablero[pieza]==TorreN)aux+=GeneraMovimientosTorre(raiz,pieza);
                    else if(p.tablero[pieza]==AlfilN)aux+=GeneraMovimientosAlfil(raiz,pieza);
                    else if(p.tablero[pieza]==CaballoN)aux+=GeneraMovimientosCaballo(raiz,pieza);
                    else{cout<<"error tipo 1"<<endl;}
                }
            }
        }
    }
    else {
        for(int i=0;i<16;i++){
            pieza=p.piezasB[i];
            if(pieza!=120){
                if((i==0)||(i==1))aux += GeneraMovimientosCaballo(raiz,pieza);
                else if((i==2)||(i==3))aux+=GeneraMovimientosAlfil(raiz,pieza);
                else if((i==4)||(i==5))aux+=GeneraMovimientosTorre(raiz,pieza);
                else if(i==6)aux+=GeneraMovimientosDama(raiz,pieza);
                else if(i==7)aux+=GeneraMovimientosRey(raiz,pieza);
                else {
                    if(p.tablero[pieza]==PeonB)aux+=GeneraMovimientosPeon(raiz,pieza);
                    else if(p.tablero[pieza]==DamaB)aux+=GeneraMovimientosDama(raiz,pieza);
                    else if(p.tablero[pieza]==TorreB)aux+=GeneraMovimientosTorre(raiz,pieza);
                    else if(p.tablero[pieza]==AlfilB)aux+=GeneraMovimientosAlfil(raiz,pieza);
                    else if(p.tablero[pieza]==CaballoB)aux+=GeneraMovimientosCaballo(raiz,pieza);
                    else{cout<<"error tipo 1"<<endl;}
                }
            }
        }
    }
    return aux;
}

void GeneraArbol(Nodo* raiz,int proff){
    if(proff==1){
        GeneraJugadasValidas(raiz);
    }
    else{
        GeneraJugadasValidas(raiz);
        for(auto rama : raiz->ramas){
            GeneraArbol(rama,proff-1);
        }
    }
    return ;
}

void liberarArbol(Nodo* nodo) {
    for (auto rama : nodo->ramas) {
        liberarArbol(rama);
    }
    delete nodo;
}
