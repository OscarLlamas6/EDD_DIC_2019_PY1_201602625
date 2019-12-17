#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include "Cola_Canciones.cpp"
#include "Pila_Canciones.cpp"
#include "ListaShuffle.cpp"
#include "ListaCircular.cpp"
using namespace std; 

class Playlist {

private:
    string name;
    string tipo;
    ColaCanciones *queue;
    PilaCanciones *stack;
    ListaShuffle *shuffle;
    ListaCircular *circular;

public:
    Playlist(string name, string tipo){
        this->name = name;
        this->tipo = tipo;
        if(tipo == "queue"){
            this->queue = new ColaCanciones();
            this->stack = 0;
            this->shuffle = 0;
            this ->circular = 0;
        } else if (tipo == "stack"){
            this->queue = 0;
            this->stack = new PilaCanciones();
            this->shuffle = 0;
            this ->circular = 0;
        } else if (tipo == "shuffle"){
            this->queue = 0;
            this->stack = 0;
            this->shuffle = new ListaShuffle();
            this ->circular = 0;
        } else if (tipo == "circular"){
            this->queue = 0;
            this->stack = 0;
            this->shuffle = 0;
            this ->circular = new ListaCircular();
        }
    }

    string getName(){ return this->name; }
    string getTipo() { return this->tipo; }
    ColaCanciones *getQueue(){ return this->queue; }
    PilaCanciones *getStack(){ return this->stack; }
    ListaShuffle *getShuffle(){ return this->shuffle; }
    ListaCircular *getCircular(){ return this->circular; }

};

