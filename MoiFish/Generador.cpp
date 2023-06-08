#include "MoiFish.h"

int GeneraJugadasValidas(Nodo* raiz){
    int aux=0,i,a[6]={0,0,0,0,0,0};
    unsigned char pieza;
    Posicion p=raiz->get_Posicion();
    for(i=0;i<16;i++){
        pieza=p.piezas[p.turno][i];
        if(pieza==120)continue;
        if((i==0)||(i==1))a[0]+=GeneraMovimientosCaballo(raiz,pieza,i);
        else if((i==2)||(i==3))a[1]+=GeneraMovimientosAlfil(raiz,pieza,i);
        else if((i==4)||(i==5))a[2]+=GeneraMovimientosTorre(raiz,pieza,i);
        else if(i==6)a[3]+=GeneraMovimientosDama(raiz,pieza,i);
        else if(i==7)a[4]+=GeneraMovimientosRey(raiz,pieza,i);
        else {
            if(p.tablero[pieza]>>1==Peon)a[5]+=GeneraMovimientosPeon(raiz,pieza,i);
            else if(p.tablero[pieza]>>1==Dama)a[3]+=GeneraMovimientosDama(raiz,pieza,i);
            else if(p.tablero[pieza]>>1==Torre)a[2]+=GeneraMovimientosTorre(raiz,pieza,i);
            else if(p.tablero[pieza]>>1==Alfil)a[1]+=GeneraMovimientosAlfil(raiz,pieza,i);
            else if(p.tablero[pieza]>>1==Caballo)a[0]+=GeneraMovimientosCaballo(raiz,pieza,i);
        }
    }
    //cout<<"Caballo: "<<a[0]<<endl;
    //cout<<"Alfil: "<<a[1]<<endl;
    //cout<<"Torre: "<<a[2]<<endl;
    //cout<<"Dama: "<<a[3]<<endl;
    //cout<<"Rey: "<<a[4]<<endl;
    //cout<<"Peon: "<<a[5]<<endl;
    aux=a[0]+a[1]+a[2]+a[3]+a[4]+a[5];
    return aux;
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
                if(!p.Jacke()){
                    Nodo* nuevo=crearNodo(p);
                    agregarRama(raiz,nuevo);
                    contador+=1;
                }
                p=raiz->get_Posicion();
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
            j++;
            if(!(fin&0x88)){
                if((p.tablero[fin]==0)){
                    t.coorini=inicial;
                    t.coorfin=fin;
                    t.pieza=ind_pieza;
                    p.Mueve(t);
                    if(!p.Jacke()){
                        Nodo* nuevo=crearNodo(p);
                        agregarRama(raiz,nuevo);
                        contador+=1;
                    }
                    p=raiz->get_Posicion();
                }
                else if(p.turno!=(p.tablero[fin]&1)){
                    t.coorini=inicial;
                    t.coorfin=fin;
                    t.pieza=ind_pieza;
                    p.Mueve(t);
                    if(!p.Jacke()){
                        Nodo* nuevo=crearNodo(p);
                        agregarRama(raiz,nuevo);
                        contador+=1;
                    }
                    p=raiz->get_Posicion();
                    break;
                }
                else break;
            }
            else break;
        }
    }
    return contador;
}

int GeneraMovimientosAlfil(Nodo* raiz,unsigned char inicial,int ind_pieza){
    Posicion p=raiz->get_Posicion();
    Tiro t;
    int fin,contador=0,j;
    for(int i=0;i<4;i++){
        j=1;
        while(1){
            if(i==0)fin=inicial+17*j;
            else if(i==1)fin=inicial-17*j;
            else if(i==2)fin=inicial+15*j;
            else fin=inicial-15*j;
            j++;
            if(!(fin&0x88)){
                if((p.tablero[fin]==0)){
                    t.coorini=inicial;
                    t.coorfin=fin;
                    t.pieza=ind_pieza;
                    p.Mueve(t);
                    if(!p.Jacke()){
                        Nodo* nuevo=crearNodo(p);
                        agregarRama(raiz,nuevo);
                        contador+=1;
                    }
                    p=raiz->get_Posicion();
                }
                else if(p.turno!=(p.tablero[fin]&1)){
                    t.coorini=inicial;
                    t.coorfin=fin;
                    t.pieza=ind_pieza;
                    p.Mueve(t);
                    if(!p.Jacke()){
                        Nodo* nuevo=crearNodo(p);
                        agregarRama(raiz,nuevo);
                        contador+=1;
                    }
                    p=raiz->get_Posicion();
                    break;
                }
                else break;
            }
            else break;
        }
    }
    return contador;
}

int GeneraMovimientosPeon(Nodo* raiz,unsigned char inicial,int ind_pieza){
    Posicion p=raiz->get_Posicion();
    Tiro t;
    int fin,contador=0,dir;
    if(p.turno==0)dir=1;
    else dir=-1;
    for(int i=0;i<5;i++){
        if(i==0){
            fin=inicial+16*dir;
            if(p.tablero[fin]!=0){
                i++;
                continue;
            }
        }
        else if(i==1){
            if(p.turno&&inicial<96)continue;
            else if(!p.turno&&inicial>24)continue;
            fin=inicial+32*dir;
            if(p.tablero[fin]!=0)continue;
        }
        else if(i==2){
            fin=inicial+15*dir;
            if(fin&0x88)continue;
            if(p.tablero[fin]==0)continue;
            if(p.turno==(p.tablero[fin]&1))continue;
        }
        else if(i==3){
            fin=inicial+17*dir;
            if(fin&0x88)continue;
            if(p.tablero[fin]==0)continue;
            if(p.turno==(p.tablero[fin]&1))continue;
        }
        else {
            if(p.paso==0)break;
            else{
                if((p.paso==inicial+15*dir)||(p.paso==inicial+17*dir)){
                    fin=p.paso;
                }else break;
            }
        }
        t.coorfin=fin;
        t.coorini=inicial;
        t.pieza=ind_pieza;
        p.Mueve(t);
        if(!p.Jacke()){
            Nodo* nuevo=crearNodo(p);
            agregarRama(raiz,nuevo);
            contador+=1;
        }
        p=raiz->get_Posicion();
    }
    return contador;
}

int GeneraMovimientosDama(Nodo* raiz,unsigned char inicial,int ind_pieza){
    int contador;
    contador=GeneraMovimientosAlfil(raiz,inicial,ind_pieza);
    contador+=GeneraMovimientosTorre(raiz,inicial,ind_pieza);
    return contador;
}

int GeneraMovimientosRey(Nodo* raiz,unsigned char inicial,int ind_pieza){ //faltan los enroques
    Posicion p=raiz->get_Posicion();
    Tiro t;
    int fin,contador=0;
    for(int i=0;i<10;i++){
        if(i==0)fin=inicial+1;
        else if(i==1)fin=inicial-15;
        else if(i==2)fin=inicial-16;
        else if(i==3)fin=inicial-17;
        else if(i==4)fin=inicial-1;
        else if(i==5)fin=inicial+15;
        else if(i==6)fin=inicial+16;
        else if(i==7)fin=inicial+17;
        else continue;
        if(!(fin&0x88)){
            if((p.tablero[fin]==0)||(p.turno!=(p.tablero[fin]&1))){
                t.coorini=inicial;
                t.coorfin=fin;
                t.pieza=ind_pieza;
                p.Mueve(t);
                if(!p.Jacke()){
                    Nodo* nuevo=crearNodo(p);
                    agregarRama(raiz,nuevo);
                    contador+=1;
                }
                p=raiz->get_Posicion();
            }
        }
    }
    return contador;
}

