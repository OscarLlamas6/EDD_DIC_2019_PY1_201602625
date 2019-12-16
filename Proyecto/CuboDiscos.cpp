#include <iostream>
#include <fstream>
#include "NodoCubo.cpp"
#include <string>
#include <time.h>
using namespace std; 

class CuboDiscografia{

private:
    NodoCubo *raiz;
    int size;
public:
    CuboDiscografia(){ 
        this->raiz = new NodoCubo(-1,"", new Album("","",0));
        this->size =0;
     }

    NodoCubo *getRaiz(){ return this->raiz;}
    
    int getSize(){ return this->size; }

    void sleepcp(int milliseconds) { // Función para pausar ejecución

    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end)
    {
    }
}


    void insertar_nodo(int x, string y, Album *a){
        add_X(x, a); //Creamos cabecera en X (en caso que no exista)
        add_Y(y, a); //Creamos cabecera en Y (en caso que no exista)
        NodoCubo *n = new NodoCubo(x,y,a); //Creamos nuevo nodo
        if(!NodoExiste(x,n->getY())){       
        X_link(n, x); //Seteamos enlaces en X
        Y_link(n, n->getY()); //Seteamos enlaces en Y
        }else {
        ApilarNodo(n, x, n->getY());
        }
        this->size++;
    }



    bool NodoExiste(int x, int y){ //VERIFICAMOS SI YA EXISTE UN NODO CREADO EN UNA COORDENADA ESPECIFICA
        
        NodoCubo *fil;
        NodoCubo *aux = this->raiz->getAdelante();
        while(aux!=0){
        fil = aux->getDerecha();
        while(fil !=0){
            if(fil->getX() == x && fil->getY() == y){
                return true;
            }
        fil = fil ->getDerecha();
        }
        aux = aux ->getAdelante(); 
        }
        return false;            
    }

    void ApilarNodo(NodoCubo *n, int x, int y){ //APILAMOS NODOS EN EJE Z
        NodoCubo *aux = this->raiz;
        while(aux->getX()!=x){aux = aux->getDerecha();}
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

    void add_X(int x, Album *a){ //AGREGAMOS CABECERA EN X   
        if(this->raiz->getDerecha()==0){
            NodoCubo *n = new NodoCubo(x,"",a);
            this->raiz->setDerecha(n);
            n->setIzquierda(this->raiz);
        } else {
            NodoCubo *aux = this->raiz;
            while(aux->getDerecha()!=0 && aux->getDerecha()->getX()<x){
                aux = aux->getDerecha();
            }
            if(aux->getDerecha()==0){
               NodoCubo *n = new NodoCubo(x,"",a);
               aux->setDerecha(n);
               n->setIzquierda(aux); 
            } else if (aux->getDerecha()->getX()!=x) {
                NodoCubo *n = new NodoCubo(x,"",a);
                n->setDerecha(aux->getDerecha());
                aux->getDerecha()->setIzquierda(n);
                n->setIzquierda(aux);
                aux->setDerecha(n);
            }
        }        
    }

    void add_Y(string y, Album *a){ //AGREGAMOS CABECERA EN Y
        NodoCubo *n = new NodoCubo(-1,y,a);     
        if(this->raiz->getAdelante()==0){            
            this->raiz->setAdelante(n);
            n->setAtras(this->raiz);
        } else {
            NodoCubo *aux = this->raiz;
            while(aux->getAdelante()!=0 && aux->getAdelante()->getY()<n->getY()){
                aux = aux->getAdelante();
            }
            if(aux->getAdelante()==0){
               aux->setAdelante(n);
               n->setAtras(aux); 
            } else if (aux->getAdelante()->getY()!=n->getY()) {
                n->setAdelante(aux->getAdelante());
                aux->getAdelante()->setAtras(n);
                n->setAtras(aux);
                aux->setAdelante(n);
            }
        } 
    }
    
     void X_link(NodoCubo *n, int x){ //SETEAMOS ENLACES EN X
        NodoCubo *aux = this->raiz;
        while(aux->getX()!=x){
            aux = aux->getDerecha();
        }
        if(aux->getAdelante()==0){
            aux->setAdelante(n);
            n->setAtras(aux);
        } else {
            while(aux->getAdelante() != 0 && aux->getAdelante()->getY() < n->getY()){
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

    void Y_link(NodoCubo *n, int y){ //SETEAMOS ENLACES EN Y
        NodoCubo *aux = this->raiz;
        while(aux->getY()!=y){
            aux = aux->getAdelante();
        }
        if(aux->getDerecha()==0){
            aux->setDerecha(n);
            n->setIzquierda(aux);
        } else { 
             while(aux->getDerecha() != 0 && aux->getDerecha()->getX() < n->getX()){
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

    NodoCubo *getAlbum(int index){
        if(index>0 && index <=this->size){
        int x = 1;
        NodoCubo *aux = this->getRaiz()->getDerecha();
        while(aux!=0){
            NodoCubo *b = aux->getAdelante();
            while(b!=0){
                NodoCubo *a = b;
                while(a!=0){
                    if(x==index){ return a; }
                    x++;
                    a = a->getArriba();
                }
                b = b->getAdelante();
            }
            aux = aux->getDerecha();
        }

        } else { return 0; }
    }
};