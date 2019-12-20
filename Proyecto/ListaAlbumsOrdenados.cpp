#include <iostream>
#include <iostream>
#include <fstream>
#include "NodoAlbumOrdenado.cpp"
using namespace std; 

class ListaAlbumsOrdenados{

private:
    int size;
    NodoAlbumOrdenado *primero;
    NodoAlbumOrdenado *ultimo;
public:
    ListaAlbumsOrdenados(){
        this->primero = 0;
        this->ultimo = 0;
        this->size = 0;
    }
    
    NodoAlbumOrdenado *getPrimero(){ return this->primero; }
    NodoAlbumOrdenado *getUltimo(){ return this->ultimo; }
    int getSize(){ return this->size;}
    bool estaVacia(){ return this->size==0;}


    void insertar_alinicio(string name, double rating){
        AlbumOrdenado *a = new AlbumOrdenado(name, rating);
        NodoAlbumOrdenado *n = new NodoAlbumOrdenado(a);
        if(this->estaVacia()){
            this->primero = n;
            this->ultimo = n;
            this->size++;
        }else {
            n->setSiguiente(this->primero);
            this->primero = n;
            this->size++;
        }

    }


    void insertar_alfinal(string name, double rating){       
        if(this->estaVacia()){
            this->insertar_alinicio(name,rating);
        } else {
            AlbumOrdenado *a = new AlbumOrdenado(name,  rating);
            NodoAlbumOrdenado *n = new NodoAlbumOrdenado(a);
            this->ultimo->setSiguiente(n);
            this->ultimo = n;
            size++;
        }
    }

    void insertar_en(string name, double rating, int index){
        if(index>=0 && index<=this->size){
            if(index == 0){this->insertar_alinicio(name, rating);return;}
            if(index == this->size){this->insertar_alfinal(name, rating); return;}
            NodoAlbumOrdenado *aux = this->primero;
            int x = 0;
            while(aux!=0){
                if(x == index-1){ break;}
                aux = aux->getSiguiente();
                x++;
            }
            AlbumOrdenado *a = new AlbumOrdenado(name, rating);
            NodoAlbumOrdenado *n = new NodoAlbumOrdenado(a);
            n->setSiguiente(aux->getSiguiente());
            aux->setSiguiente(n);
            this->size++;
        }
    }

    void insertar_ordenado(string name, double rating){
        if(this->estaVacia()){
            insertar_alinicio(name, rating); return;
        }
        int index = 0;
        NodoAlbumOrdenado *aux = this->primero;
        while(aux!=0){
            if(rating>this->getPrimero()->getAlbum()->getRating()){ index=0; break;} //Ingresa al inicio
            if(rating<this->getUltimo()->getAlbum()->getRating()){index=size; break;} //Ingresa al final
            if(rating<=aux->getAlbum()->getRating()){ index++;} //Busca la posición correcta
            if(rating>aux->getSiguiente()->getAlbum()->getRating()){ break;} //valida si ya encontro la posición correcta
            aux = aux->getSiguiente();  
        }
        this->insertar_en(name, rating, index); //llama al metodo para insertar en el index indicado
    }


};