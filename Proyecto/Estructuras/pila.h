#include <iostream> 
using namespace std; 

template <class T>
class Pila
{
protected:  
    class Nodo{
public:
        Nodo(T x){
            dato = x;
            next = 0;
        }

void setNext(Nodo *n){
    next = n;
}

Nodo *getNext(){
    return next;
}

T getDato(){
    return dato;
}

    
private:
    Nodo *next;
    T dato;
    };


public:
Pila(){
    cima = 0;
    size = 0;
}

bool estaVacia();
void push(T dato);
T pop();
int getSize();

private:

Nodo *cima;
int size;

};

template<class T>
bool Pila<T>::estaVacia(){
    return this->size==0;
}

template<class T>
void Pila<T>::push(T dato){
    Nodo *n = new Nodo(dato);

if(estaVacia()){
    this->cima = n;
    this->size++;
} else {
    n->setNext(this->cima);
    this->cima = n;
    this->size++;
}
}

template<class T>
T Pila<T>::pop(){
    T aux = this->cima->getDato();
    this->cima = this->cima->getNext();
    this->size--;
    return aux;
}

template<class T>
int Pila<T>::getSize(){
  
    return this->size;
}
