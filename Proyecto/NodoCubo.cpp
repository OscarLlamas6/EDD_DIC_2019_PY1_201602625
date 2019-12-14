#include <iostream> 
#include "Album.cpp"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class NodoCubo{

private:
    NodoCubo *izquierda;
    NodoCubo *derecha;
    NodoCubo *arriba;
    NodoCubo *abajo;
    NodoCubo *adelante;
    NodoCubo *atras;
    int x; //año
    int y; //mes
    Album *disco;

public:
   

    NodoCubo(int x, string y, Album *a){

        string mes = y;
        std::for_each(mes.begin(), mes.end(), [](char & c) {
		c = ::tolower(c);});

        if(mes == "enero"){
            this->y = 1;
        } else if(mes == "febrero"){
            this->y = 2;
        } else if(mes == "marzo"){
            this->y = 3;
        } else if(mes == "abril"){
            this->y = 4;
        } else if(mes == "mayo"){
            this->y = 5;
        } else if(mes == "junio"){
            this->y = 6;
        } else if(mes == "julio"){
            this->y = 7;
        } else if(mes == "agosto"){
            this->y = 8;
        } else if(mes == "septiembre"){
            this->y = 9;
        } else if(mes == "octubre"){
            this->y = 10;
        } else if(mes == "noviembre"){
            this->y = 11;
        } else if(mes == "diciembre"){
            this->y = 12;
        } else if(mes == ""){
            this->y = -1;
        } else{
            this->y = 13;
        }
        this->disco = a;
        this->x = x;
        this->izquierda = 0;
        this->derecha = 0;
        this->arriba = 0;
        this->abajo = 0;
        this->adelante = 0;
        this->atras = 0;
    }
    //////SETTERS
    void setIzquierda(NodoCubo *n){ this->izquierda = n;}
    void setDerecha(NodoCubo *n){ this->derecha = n;}
    void setArriba(NodoCubo *n){ this->arriba = n;}
    void setAbajo(NodoCubo *n){ this->abajo = n;}
    void setAdelante(NodoCubo *n){ this->adelante = n;}
    void setAtras(NodoCubo *n){ this->atras = n;}
    //////GETTERS
    Album *getAlbum(){ return this->disco; }
    int getX(){ return this->x; }
    int getY(){ return this->y; }
    NodoCubo *getIzquierda(){ return this->izquierda; }
    NodoCubo *getDerecha(){ return this->derecha; }
    NodoCubo *getArriba(){ return this->arriba; }
    NodoCubo *getAbajo(){ return this->abajo; }
    NodoCubo *getAdelante(){ return this->adelante; }
    NodoCubo *getAtras(){ return this->atras; }


};