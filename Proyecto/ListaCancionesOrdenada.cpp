#include <iostream>
#include <iostream>
#include <fstream>
#include "NodoCancionOrdenado.cpp"
using namespace std; 

class ListaCancionesOrdenada{

private:
    int size;
    NodoCancionOrdenado *primero;
    NodoCancionOrdenado *ultimo;
public:
    ListaCancionesOrdenada(){
        this->primero = 0;
        this->ultimo = 0;
        this->size = 0;
    }
    
    NodoCancionOrdenado *getPrimero(){ return this->primero; }
    NodoCancionOrdenado *getUltimo(){ return this->ultimo; }
    int getSize(){ return this->size;}
    bool estaVacia(){ return this->size==0;}


    void insertar_alinicio(string name, string album, string artista, double rating,  int year, string month){
        SongOrdenada *c = new SongOrdenada(name, album, artista, rating, year, month);
        NodoCancionOrdenado *n = new NodoCancionOrdenado(c);
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


    void insertar_alfinal(string name, string album, string artista, double rating,  int year, string month){       
        if(this->estaVacia()){
            this->insertar_alinicio(name, album, artista, rating, year, month);
        } else {
            SongOrdenada *c = new SongOrdenada(name, album, artista, rating, year, month);
            NodoCancionOrdenado *n = new NodoCancionOrdenado(c);
            this->ultimo->setSiguiente(n);
            this->ultimo = n;
            size++;
        }
    }

    void insertar_en(string name, string album, string artista, double rating, int year, string month, int index){
        if(index>=0 && index<=this->size){
            if(index == 0){this->insertar_alinicio(name, album, artista, rating, year, month);return;}
            if(index == this->size){this->insertar_alfinal(name, album, artista, rating, year, month); return;}
            NodoCancionOrdenado *aux = this->primero;
            int x = 0;
            while(aux!=0){
                if(x == index-1){ break;}
                aux = aux->getSiguiente();
                x++;
            }
            SongOrdenada *c = new SongOrdenada(name, album, artista, rating, year, month);
            NodoCancionOrdenado *n = new NodoCancionOrdenado(c);
            n->setSiguiente(aux->getSiguiente());
            aux->setSiguiente(n);
            this->size++;
        }
    }

    void insertar_ordenado(string name, string album, string artista, double rating, int year, string month){
        if(this->estaVacia()){
            insertar_alinicio(name, album, artista, rating, year, month); return;
        }
        int index = 0;
        NodoCancionOrdenado *aux = this->primero;
        while(aux!=0){
            if(name.compare(this->getPrimero()->getCancion()->getName()) == -1){ index=0; break;} //Ingresa al inicio
            if(name.compare(this->getUltimo()->getCancion()->getName()) == 1 || name.compare(this->getUltimo()->getCancion()->getName()) == 0){index=size; break;} //Ingresa al final
            if(name.compare(aux->getCancion()->getName()) == 1 || name.compare(this->getUltimo()->getCancion()->getName()) == 0){ index++;} //Busca la posición correcta
            if(name.compare(aux->getSiguiente()->getCancion()->getName()) == -1){ break;} //valida si ya encontro la posición correcta
            aux = aux->getSiguiente();  
        }
        this->insertar_en(name, album, artista, rating, year, month, index); //llama al metodo para insertar en el index indicado
    }


    double CalculateRating(){
        double result = 0;
        NodoCancionOrdenado *aux = this->primero;
        while(aux!=0){
        result+=aux->getCancion()->getRating();
        aux = aux->getSiguiente();
        }
        double d = (double)this->size;
        result = result / d;
        return result;
    }

    NodoCancionOrdenado *getCancion(int index){
       if(index>0 && index <=this->size){
        if(index == this->size){ return this->ultimo;}
         else {
            NodoCancionOrdenado *aux = this->primero;
            int x = 1;
            while(aux!=0){
                if(x == index){ break;}
                aux = aux->getSiguiente();
                x++;
            }
            return aux;
            }              
       } else {return 0;}
    }

    bool CancionExiste(int year, string month, string album, string name, string artist){
        if(this->size == 0){
            return false;
        } else {
            NodoCancionOrdenado *aux = this->primero;
            while(aux!=0){
                if(aux->getCancion()->getYear()==year && aux->getCancion()->getMonth()==month
                && aux->getCancion()->getAlbum()==album && aux->getCancion()->getName() == name
                && aux->getCancion()->getArtista() == artist){ return true; }
                aux = aux->getSiguiente();
            }
            return false;
        }
    }
};