#include <iostream>
#include <fstream>
#include <string>
#include "Nodo.cpp"
using namespace std; 

class CuboDisperso{

private:
    Nodo *raiz; 
public:
    CuboDisperso(){ this->raiz = new Nodo(-1,-1,-1);}
    Nodo *getRaiz(){ return this->raiz;}

    void insertar_nodo(int x, int y, int dato){
        add_X(x); //Creamos cabecera en X (en caso que no exista)
        add_Y(y); //Creamos cabecera en Y (en caso que no exista)
        Nodo *n = new Nodo(x,y,dato); //Creamos nuevo nodo
        if(!NodoExiste(x,y)){        
        X_link(n, x); //Seteamos enlaces en X
        Y_link(n, y); //Seteamos enlaces en Y
        }else {
        ApilarNodo(n, x, y);
        }
    }


    void ApilarNodo(Nodo *n, int x, int y){ //APILAMOS NODOS EN EJE Z
        Nodo *aux = this->raiz;
        while(aux->getDato()!=x){aux = aux->getDerecha();}
        while(aux->getY() != y){aux = aux->getAdelante();}
        if(aux->getArriba()==0){
            aux->setArriba(n);
            n->setAbajo(aux);
        } else {
            while(aux->getArriba() != 0){ aux = aux->getArriba();}
            aux->setArriba(n);
            n->setAbajo(aux);
        }
    }

    bool NodoExiste(int x, int y){ //VERIFICAMOS SI YA EXISTE UN NODO CREADO EN UNA COORDENADA ESPECIFICA
        Nodo *aux = this->raiz;
        while(aux->getDato()!=x){aux = aux->getDerecha();}
        while(aux->getAdelante() != 0){
            if(aux->getY() == y){return true;}
            aux = aux ->getAdelante();
        }
        return false;       
    }

    void X_link(Nodo *n, int x){ //SETEAMOS ENLACES EN X
        Nodo *aux = this->raiz;
        while(aux->getDato()!=x){
            aux = aux->getDerecha();
        }
        if(aux->getAdelante()==0){
            aux->setAdelante(n);
            n->setAtras(aux);
        } else {
            while(aux->getAdelante() != 0 && aux->getY() < n->getY()){
                aux = aux ->getAdelante();                         
            }
           if(aux->getAdelante()==0){
                aux->setAdelante(n);
                n->setAtras(aux);
            } else {
                n->setAdelante(aux->getAdelante());
                aux->getAdelante()->setAtras(n);
                n->setAtras(aux);
                aux->setAdelante(n);
                }            
        }
    }

    void Y_link(Nodo *n, int y){ //SETEAMOS ENLACES EN Y
        Nodo *aux = this->raiz;
        while(aux->getDato()!=y){
            aux = aux->getAdelante();
        }
        if(aux->getDerecha()==0){
            aux->setDerecha(n);
            n->setIzquierda(aux);
        } else { 
             while(aux->getDerecha() != 0 && aux->getX() < n->getX()){
                aux = aux ->getDerecha();                         
            }
            if(aux->getDerecha()==0){
                aux->setDerecha(n);
                n->setIzquierda(aux);
            } else {
                n->setDerecha(aux->getDerecha());
                aux->getDerecha()->setIzquierda(n);
                n->setIzquierda(aux);
                aux->setDerecha(n);
            }
            
        }
    }

    void add_X(int x){ //AGREGAMOS CABECERA EN X
        if(this->raiz->getDerecha()==0){
            Nodo *n = new Nodo(x,-1,x);
            this->raiz->setDerecha(n);
            n->setIzquierda(this->raiz);
        } else {
            Nodo *aux = this->raiz;
            while(aux->getDerecha()!=0 && aux->getDerecha()->getDato()<x){
                aux = aux->getDerecha();
            }
            if(aux->getDerecha()==0){
               Nodo *n = new Nodo(x,-1,x);
               aux->setDerecha(n);
               n->setIzquierda(aux); 
            } else if (aux->getDerecha()->getDato()!=x) {
                Nodo *n = new Nodo(x,-1,x);
                n->setDerecha(aux->getDerecha());
                aux->getDerecha()->setIzquierda(n);
                n->setIzquierda(aux);
                aux->setDerecha(n);
            }
        }        
    }

    void add_Y(int y){ //AGREGAMOS CABECERA EN Y
        if(this->raiz->getAdelante()==0){
            Nodo *n = new Nodo(-1,y,y);
            this->raiz->setAdelante(n);
            n->setAtras(this->raiz);
        } else {
            Nodo *aux = this->raiz;
            while(aux->getAdelante()!=0 && aux->getAdelante()->getDato()<y){
                aux = aux->getAdelante();
            }
            if(aux->getAdelante()==0){
               Nodo *n = new Nodo(-1,y,y);
               aux->setAdelante(n);
               n->setAtras(aux); 
            } else if (aux->getAdelante()->getDato()!=y) {
                Nodo *n = new Nodo(-1,y,y);
                n->setAdelante(aux->getAdelante());
                aux->getAdelante()->setAtras(n);
                n->setAtras(aux);
                aux->setAdelante(n);
            }
        } 
    }
};