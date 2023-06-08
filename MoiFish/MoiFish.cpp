#include "MoiFish.h"

void Arreglo_Ataques(int (&arr_ataques)[239]){
    int j; //239 son todas las posibles diferencias de indices entre casillas (van desde -119 a 119).
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
    return ;
}

Posicion::Posicion(){ //Constructor con la posición inicial.
	int i;
	turno=0;
	enrdama[0]=1;
	enrdama[1]=1;
	enrrey[0]=1;
	enrrey[1]=1;
	paso=0;
	tablero[0]=TorreB; tablero[1]=CaballoB; tablero[2]=AlfilB; tablero[3]=DamaB;
	tablero[4]=ReyB; tablero[5]=AlfilB; tablero[6]=CaballoB; tablero[7]=TorreB;
	for(i=16;i<24;i++){
		tablero[i]=PeonB;
		piezas[0][i-8]=i;
	}
	for(i=25;i<95;i++){
		tablero[i]=CasillaV;
	}
	for(i=96;i<104;i++){
		tablero[i]=PeonN;
	}
	tablero[112]=TorreN; tablero[113]=CaballoN; tablero[114]=AlfilN; tablero[115]=DamaN;
	tablero[116]=ReyN; tablero[117]=AlfilN; tablero[118]=CaballoN; tablero[119]=TorreN;
	piezas[0][0]=1; piezas[0][1]=6; piezas[0][2]=2; piezas[0][3]=5;
	piezas[0][4]=0; piezas[0][5]=7; piezas[0][6]=3; piezas[0][7]=4;
	for(i=8;i<16;i++){
		piezas[0][i]=i+8;
		piezas[1][i]=i+88;
	}
	piezas[1][0]=113; piezas[1][1]=118; piezas[1][2]=117; piezas[1][3]=114;
	piezas[1][4]=112; piezas[1][5]=119; piezas[1][6]=115; piezas[1][7]=116;
}

int Posicion::Jacke(){
    unsigned char pieza,rey;
    int indice,j,aux;
    for(int i=0;i<16;i++){  //se revisa que ninguna de las 16 piezas del rival esté dando jaque.
        pieza=piezas[turno][i];
        rey=piezas[!turno][7];
        if(pieza==120)continue; //la pieza ya falleció.
        indice=rey-pieza+119;
        if(arr_ataques[indice]==0)continue;     //0 es que ninguna pieza puede atacar de esa manera.
        else if(arr_ataques[indice]==1){        //1 es que la torre, la dama y el rey pueden atacar.
            if((tablero[pieza]>>1)==Torre)return 1;
            else if((tablero[pieza]>>1)==Dama)return 1;
            else if((tablero[pieza]>>1)==Rey)return 1;
            else continue;
        }
        else if(arr_ataques[indice]==2){        //2 es que son solo la dama y la torre pueden quienes podrían ser las piezas que ataquen de esa manera.
            if((tablero[pieza]>>1)!=Dama){
                if((tablero[pieza]>>1)!=Torre)continue;
            }
            if(indice-119<8&&indice-119>-8){
                if(rey>pieza)j=1;
                else j=-1;
            }
            else {
                if(rey>pieza)j=16;
                else j=-16;
            }
            aux=pieza+j;
            while(aux!=rey){
                if(tablero[aux]!=CasillaV){
                    aux=-1;
                    break;
                }
                aux+=j;
            }
            if(aux==-1)continue;
            else return 1;
        }
        else if(arr_ataques[indice]==3){        //El rey, la dama, el alfil y el peon blanco pueden atacar (es una casilla en diagonal hacia arriba).
            if((tablero[pieza]>>1)==Rey)return 1;
            else if((tablero[pieza]>>1)==Dama)return 1;
            else if((tablero[pieza]>>1)==Alfil)return 1;
            else if(tablero[pieza]==PeonB)return 1;
            else continue;
        }
        else if(arr_ataques[indice]==4){        //El rey, la dama, el alfil y el peon negro pueden atacar (es una casilla en diagonal hacia abajo).
            if((tablero[pieza]>>1)==Rey)return 1;
            else if((tablero[pieza]>>1)==Dama)return 1;
            else if((tablero[pieza]>>1)==Alfil)return 1;
            else if(tablero[pieza]==PeonN)return 1;
            else continue;
        }
        else if(arr_ataques[indice]==5){        //La dama y el alfil pueden atacar. (Varias casillas en diagonal).
            if((tablero[pieza]>>1)!=Dama){
                if((tablero[pieza]>>1)!=Alfil)continue;
            }
            if(indice-119%15==0){
                if(rey>pieza)j=15;
                else j=-15;
            }
            else {
                if(rey>pieza)j=17;
                else j=-17;
            }
            aux=pieza+j;
            while(aux!=rey){
                if(tablero[aux]!=CasillaV){
                    aux=-1;
                    break;
                }
                aux+=j;
            }
            if(aux==-1)continue;
            else return 1;
        }
        else if(arr_ataques[indice]==6){        //El caballo es la única pieza que podría atacar de esa manera.
            if((tablero[pieza]>>1)!=Caballo)continue;
            else return 1;
        }
    }
    return 0;
}

void Posicion::Mueve(Tiro a,int specialmove){      //specialmove es 1 para enroque corto, 2 para enroque largo, 3 para captura al paso, 4 para coronar dama, 5 para coronar torre, 6 para coronar caballo, 7 para coronar alfil.
    //actualizamos el valor de captura al paso.
    if(specialmove==1){
        a.pieza=7;
        if(turno){
            a.coorini=116;
            a.coorfin=118;
            piezas[1][5]=117;
            tablero[119]=0;
            tablero[117]=TorreN;
        }
        else {
            a.coorini=4;
            a.coorfin=6;
            piezas[0][5]=5;
            tablero[7]=0;
            tablero[5]=TorreB;
        }
    }
    else if(specialmove==2){
        a.pieza=7;
        if(turno){
            a.coorini=116;
            a.coorfin=114;
            piezas[1][4]=115;
            tablero[112]=0;
            tablero[115]=TorreN;
        }
        else {
            a.coorini=4;
            a.coorfin=6;
            piezas[0][4]=3;
            tablero[0]=0;
            tablero[3]=TorreB;
        }
    }
    else if(specialmove==3){
        if(a.coorfin>48){
            for(int i=8;i<16;i++){
                if(piezas[1][i]==paso-16){
                    piezas[1][i]=120;
                    tablero[paso-16]=0;
                    break;
                }
            }
        }
        else {
            for(int i=8;i<16;i++){
                if(piezas[0][i]==paso+16){
                    piezas[0][i]=120;
                    tablero[paso+16]=0;
                    break;
                }
            }
        }
    }
    if(a.pieza>7&&(tablero[a.coorini]>>1==Peon)){
        if(a.coorini+32==a.coorfin)paso=a.coorini+16;
        else if(a.coorfin+32==a.coorini)paso=a.coorfin+16;
        else paso=0;
    }
    else paso=0;
    //actualizamos los valores de enroques.
    if(a.pieza==7){
        enrdama[turno]=0;
        enrrey[turno]=0;
    }
    else if(a.pieza==4)enrdama[turno]=0;
    else if(a.pieza==5)enrrey[turno]=0;
    //acualizamos el valor de la pieza que fue capturada (si es que hubo captura).
    if(tablero[a.coorfin]!=CasillaV){
        for(int i=0;i<16;i++){
            if(piezas[!turno][i]==a.coorfin){
                piezas[!turno][i]=120;
                break;
            }
        }
    }
    //actualizamos el tablero, la pieza que se movió y el turno.
    tablero[a.coorfin]=tablero[a.coorini];
    tablero[a.coorini]=0;
    piezas[turno][a.pieza]=a.coorfin;
    turno=!turno;
    if(specialmove>3){
        if(specialmove==4)tablero[a.coorfin]=(Dama<<1)|turno;
        else if(specialmove==5)tablero[a.coorfin]=(Torre<<1)|turno;
        else if(specialmove==6)tablero[a.coorfin]=(Caballo<<1)|turno;
        else if(specialmove==7)tablero[a.coorfin]=(Alfil<<1)|turno;
    }
    return;
}

Nodo* crearNodo(Posicion pos){
    Nodo* nodo = new Nodo;
    nodo->P = pos;
    return nodo;
}

bool Posicion::TiroValido(Tiro t){  //no terminada
    if(tablero[t.coorini]==0)return 0;
    return 1;
}

void agregarRama(Nodo* padre, Nodo* rama) {
    padre->ramas.push_back(rama);
}


