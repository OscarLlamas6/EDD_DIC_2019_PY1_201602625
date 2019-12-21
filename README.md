# [ESTRUCTURAS DE DATOS] PROYECTO 1, DICIEMBRE 2019

pPrimer proyecto desarrollado en lenguaje c++ enfocado en estructuras lineas y no lineales. Datos del desarrollador:

  - Nombre: Oscar Alfredo Llamas Lemus
  - Carne: 201602625

# Music++

  Alguna de las estructuras utlizadas son:
  
   - Pila (Stack):
   
```sh
include <iostream> 
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
```
   - Cola (Queue)

```sh
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
```
  
 - Lista doblemente enlasada

```sh
#include <iostream> 
using namespace std; 

template<class T>
class ListaDoble{
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
    ListaDoble(){
        primero = 0;
        ultimo = 0;
        size = 0;
    }
    bool estaVacia();
    void insertar_inicio(T dato);
    void insertar_final(T dato);
    void insertar_en(T dato, int index);
    void borrar_en(int index);
    int getSize();
private:

    int size;
};

template<class T>
bool ListaDoble<T>::estaVacia(){
    return this->size==0;
}

template<class T>
int ListaDoble<T>::getSize(){
  
    return this->size;
}



template<class T>
void ListaDoble<T>::insertar_inicio(T dato){
    Nodo *n = new Nodo(dato);
    if(this->estaVacia()){
        this->primero = n;
        this->ultimo = n;
        this->size++;
    } else {
        n->setSiguiente(this->primero);
        this->primero->setAnterior(n);
        this->primero = n;
        this->size++;
    }
}

template<class T>
void ListaDoble<T>::insertar_final(T dato){
    if(this->estaVacia()){
        this->insertar_inicio(dato);
    } else {
        Nodo *n = new Nodo(dato);
        this->ultimo->setSiguiente(n);
        n->setAnterior(this->ultimo);
        this->ultimo = n;
        this->size++;
    }
}

template<class T>
void ListaDoble<T>::insertar_en(T dato, int index){
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
        
    }
}

template<class T>
void ListaDoble<T>::borrar_en(int index){
    if(index >=0 && index <= this->size-1){
        if(index == 0){
        this->primero->getSiguiente()->setAnterior(NULL);
        this->primero=this->primero->getSiguiente();
        this->size--;      
        return;}
        if(index == this->size-1){
        this->ultimo->getAnterior()->setSiguiente(NULL);
        this->ultimo =  this->ultimo->getAnterior();
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
        this->size--;
    }
}
```
 - Lista circular:
```sh
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
```

 





