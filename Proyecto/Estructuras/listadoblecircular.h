#include <iostream> 
using namespace std; 

template<class T>
class ListaDobleCircular{
public:
    class Nodo{
    public:

        Nodo(T x){
            dato = x;
            siguiente = 0;
            anterior = 0;
        }

    T getDato(){
    return dato;
    }

    void setSiguiente(Nodo *n){
        this->siguiente = n;
    }

    void setAnterior(Nodo *n){
        this->anterior = n;
    }  

    Nodo *getSiguiente(){
        return this->siguiente;
    }

    Nodo *getAnterior(){
        return this->anterior;
    }  

    private:
    T dato;
    Nodo *siguiente;
    Nodo *anterior;    
    };

    Nodo *primero;
    Nodo *ultimo;
    ListaDobleCircular(){
        primero = 0;
        ultimo = 0;
        size = 0;
    }
    bool estaVacia();
    void insertar_inicio(T dato);
    void insertar_final(T dato);
    void insertar_en(T dato, int index);
    void borrar_en(int index);
    void vinculo_circular();
    int getSize();
private:

    int size;
};

template<class T>
bool ListaDobleCircular<T>::estaVacia(){
    return this->size==0;
}

template<class T>
int ListaDobleCircular<T>::getSize(){
  
    return this->size;
}

template<class T>
void ListaDobleCircular<T>::vinculo_circular(){
    this->primero->setAnterior(this->ultimo);
    this->ultimo->setSiguiente(this->primero);
}

template<class T>
void ListaDobleCircular<T>::insertar_inicio(T dato){
    Nodo *n = new Nodo(dato);
    if(this->estaVacia()){
        this->primero = n;
        this->ultimo = n;
    } else {
        n->setSiguiente(this->primero);
        this->primero->setAnterior(n);
        this->primero = n;        
    }
    this->vinculo_circular();
        this->size++;
}

template<class T>
void ListaDobleCircular<T>::insertar_final(T dato){
    if(this->estaVacia()){
        this->insertar_inicio(dato);
    } else {
        Nodo *n = new Nodo(dato);
        this->ultimo->setSiguiente(n);
        n->setAnterior(this->ultimo);
        this->ultimo = n;        
    }
    this->vinculo_circular();
    this->size++;
}

template<class T>
void ListaDobleCircular<T>::insertar_en(T dato, int index){
    if(index >=0 && index <= this->size){
        if(index == 0){this->insertar_inicio(dato); return;}
        if(index == this->size){this->insertar_final(dato); return;}
        Nodo *aux = this->primero;
        int x = 0;
        while (aux!=0)
        {
            if(x == index){break;}
            aux = aux->getSiguiente();
            x++;
        }
        Nodo *n = new Nodo(dato);
        aux->getAnterior()->setSiguiente(n);
        n->setAnterior(aux->getAnterior());
        n->setSiguiente(aux);
        aux->setAnterior(n);
        this->size++;
        this->vinculo_circular();
    }
}

template<class T>
void ListaDobleCircular<T>::borrar_en(int index){
    if(index >=0 && index <= this->size-1){
        if(index == 0){
        this->primero->getSiguiente()->setAnterior(NULL);
        this->primero=this->primero->getSiguiente();
        this->vinculo_circular();
        this->size--;      
        return;}
        if(index == this->size-1){
        this->ultimo->getAnterior()->setSiguiente(NULL);
        this->ultimo =  this->ultimo->getAnterior();
        this->vinculo_circular();
        this->size--;
        return;}
        Nodo *aux = this->primero;
        int x = 0;
        while (aux!=0)
        {
            if(x == index){break;}
            aux = aux->getSiguiente();
            x++;
        }
        aux->getAnterior()->setSiguiente(aux->getSiguiente());
        aux->getSiguiente()->setAnterior(aux->getAnterior());
        this->vinculo_circular();
        this->size--;
    }
}