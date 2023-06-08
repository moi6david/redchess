#include "MoiFish.h"

Posicion::Posicion(string fen){
	stringstream ss(fen);
    string elemento;
    vector<string> elementos;
    while (getline(ss, elemento, ' ')) {
        elementos.push_back(elemento);
    }
    string tableroFEN=elementos[0];
    //llenamos los valores del tablero con 0, para que esté vacío.
    for(int i=0;i<128;i++){
        tablero[i]=0;
    }
    //inicializamos en 120 para señalar que las piezas están muertas.
    for(int i=0;i<16;i++){
        piezas[0][i]=120;
        piezas[1][i]=120;
    }
    //Construimos el tablero y las piezas.
    int fila = 7;
    int columna = 0;
    int aux;
    //pb2 o pn2 es para llevar un contador de las piezas coronadas que ya guardé (las voy a guardar como si fueran los indices de los últimos peones los que coronaron).
    int pn1=8,pb1=8,pn2=15,pb2=15;  //pn1 o pb1 es para llevar un contador de los peones que ya fui guardando.
    for (char c : tableroFEN) {
        if (c == '/') {
            fila--;
            columna = 0;
        } else if (isdigit(c)) {
            columna += (c - '0');
        } else {
            unsigned char cordenada=fila*16+columna;
            if(c=='p'){
                aux=PeonN;
                piezas[1][pn1]=cordenada;
                pn1++;
            }else if(c=='r'){
                aux=TorreN;
                if(piezas[1][4]==120)piezas[1][4]=cordenada;
                else if(piezas[1][5]==120)piezas[1][5]=cordenada;
                else {
                    piezas[1][pn2]=cordenada;
                    pn2--;
                }
            }else if(c=='n'){
                aux=CaballoN;
                if(piezas[1][0]==120)piezas[1][0]=cordenada;
                else if(piezas[1][1]==120)piezas[1][1]=cordenada;
                else {
                    piezas[1][pn2]=cordenada;
                    pn2--;
                }
            }
            else if(c=='b'){
                aux=AlfilN;
                if(piezas[1][2]==120)piezas[1][2]=cordenada;
                else if(piezas[1][3]==120)piezas[1][3]=cordenada;
                else {
                    piezas[1][pn2]=cordenada;
                    pn2--;
                }
            }
            else if(c=='q'){
                aux=DamaN;
                if(piezas[1][6]==120)piezas[1][6]=cordenada;
                else {
                    piezas[1][pn2]=cordenada;
                    pn2--;
                }
            }
            else if(c=='k'){
                aux=ReyN;
                piezas[1][7]=cordenada;
            }
            else if(c=='P'){
                aux=PeonB;
                piezas[0][pb1]=cordenada;
                pb1++;
            }
            else if(c=='R'){
                aux=TorreB;
                if(piezas[0][4]==120)piezas[0][4]=cordenada;
                else if(piezas[0][5]==120)piezas[0][5]=cordenada;
                else {
                    piezas[0][pb2]=cordenada;
                    pb2--;
                }
            }
            else if(c=='N'){
                aux=CaballoB;
                if(piezas[0][0]==120)piezas[0][0]=cordenada;
                else if(piezas[0][1]==120)piezas[0][1]=cordenada;
                else {
                    piezas[0][pb2]=cordenada;
                    pb2--;
                }
            }
            else if(c=='B'){
                aux=AlfilB;
                if(piezas[0][2]==120)piezas[0][2]=cordenada;
                else if(piezas[0][3]==120)piezas[0][3]=cordenada;
                else {
                    piezas[0][pb2]=cordenada;
                    pb2--;
                }
            }
            else if(c=='Q'){
                aux=DamaB;
                if(piezas[0][6]==120)piezas[0][6]=cordenada;
                else {
                    piezas[0][pb2]=cordenada;
                    pb2--;
                }
            }
            else if(c=='K'){
                aux=ReyB;
                piezas[0][7]=cordenada;
            }
            tablero[cordenada] = aux;
            columna++;
        }
    }
    //Construimos las demás variables que tiene una posición.
    //inicializamos el turno.
    if(elementos[1]=="w")turno=0;
    else turno=1;
    //inicializamos los enroques.
    enrdama[0]=0;
    enrrey[0]=0;
    enrdama[1]=0;
    enrrey[1]=0;
    for(char c : elementos[2]){
        if(c=='-'){
            break;
        }
        else if(c=='K')enrrey[0]=1;
        else if(c=='Q')enrdama[0]=1;
        else if(c=='k')enrrey[1]=1;
        else if(c=='q')enrdama[1]=1;
    }
    //seguimos con el peon al paso.
    if(elementos[3][0]=='-')paso=0;
    else paso=CordenadaString_a_Numero(elementos[3]);
    return;
}

//1. d4 d5 2. Nf3 Nc6 3. Nc3 e6 4. e3 Bb4 5. Bb5 Nf6 6. O-O O-O 7. a3 Bxc3 8. bxc3 a6 9. Bd3 h6 10. a4 Re8 11. Ba3 Bd7 12. a5 b5 13. axb6 cxb6 14. Bd6 b5 15. Be5 Nxe5 16. Nxe5

/*Posicion LeePGN(string pgn){
	Posicion p=Posicion();
	Tiro a;
	istringstream iss(pgn);
    string token;
    int specialmove=0,dir;
    while (iss >> token) {
        if (token == "1-0" || token == "0-1" || token == "1/2-1/2") {
            // Se alcanzó el final del PGN
            break;
        }
        if (!token.empty() && (token.back() == '+' || token.back() == '#')) {   //eliminamos los signos + y #.
            token.pop_back();
        }
        //si hay una coronación.
        if (token.find('=') != std::string::npos) {
            char coronacion = token[token.length() - 1];
            if(coronacion == 'Q')specialmove = 4;
            else if(coronacion == 'R')specialmove = 5;
            else if(coronacion == 'N')specialmove = 6;
            else if(coronacion == 'B')specialmove = 7;
            token.pop_back();
            token.pop_back();
            a.coorfin=CordenadaString_a_Numero(token.substr(token.length() - 2));
            if(turno)dir=1;
            else dir=-1;
            if (token.find('x') == std::string::npos)a.coorini=a.coorfin+dir*16;
            else {
                token[0]-
            }
            p.Mueve(a,specialmove);
        }
        if (token.find('.') != std::string::npos) {
            // Se encontró un número de movimiento, se puede ignorar
            continue;
        }
        else if(token=="O-O"){
            p.Mueve(a,1);
        }
        else if(token=="O-O-O"){
            p.Mueve(a,2);
        }
        else if(islower(token[0])){
            if(token.find('x') != std::string::npos){
                if(turno){

                }
            }

        }
        else {

        }
    }
}
*/

unsigned char CordenadaString_a_Numero(string c){
    int row = c[1] - '0';
    int column = c[0] - 'a';
    int coord = (row - 1) * 16 + column;
    return coord;
}

string CordenadaNumero_a_String(unsigned char c){
    int row = c / 16 + 1;
    int column = c % 16;
    char columnChar = 'a' + column;
    string coord = "";
    coord += columnChar;
    coord += to_string(row);
    return coord;
}
