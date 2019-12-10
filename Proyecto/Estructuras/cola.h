#include <iostream> 
using namespace std; 

template <class T>
class Cola
{
protected:
    class Nodo{
    public:

    Nodo *next;
    T dato;
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
    };

    
    
public:

Cola(){
    frente = 0;
    fin = 0;
    size = 0;
}

bool estaVacia();
void enqueue(T dato);
T dequeue();
int getSize();
T getFrente();
T getFin();

private:

Nodo *frente;
Nodo *fin;
int size;

};

template<class T>
bool Cola<T>::estaVacia(){
    return this->size==0;
}

template<class T>
void Cola<T>::enqueue(T dato){
    Nodo *n = new Nodo(dato);
    if(estaVacia()){
        this->frente = n;
    } else {
        this->fin->next = n; 
    }
   this->fin=n;
   this->size++; 

}

template<class T>
T Cola<T>::dequeue(){
   if(estaVacia())
   throw "Cola Vacia";
   T aux = frente->dato;
   Nodo *a = frente;
   frente = frente->next;
   delete a;
   this->size--;
   return aux;

}

template<class T>
int Cola<T>::getSize(){
  
    return this->size;
}

template<class T>
T Cola<T>::getFrente(){


        return this->frente->getDato();
    
}

template<class T>
T Cola<T>::getFin(){
  

        return this->fin->getDato();

}