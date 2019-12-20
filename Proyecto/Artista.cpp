#include <iostream> 
#include "CuboDiscos.cpp"
#include "ListaAlbumsOrdenados.cpp"
#include <fstream>
using namespace std;

class Artista{

private:
    string name;
    double rating;
    CuboDiscografia *discos;
    ListaAlbumsOrdenados *albums_rating;
public:   
    Artista(string name, double rating){
        this->rating = rating;
        this->name = name;
        this->discos = new CuboDiscografia();
        this->albums_rating = new ListaAlbumsOrdenados();
    }        
    string getName(){ return this->name;};
    double getRating(){ return this->rating;};
    void setName(string name){ this->name = name;}
    void setRating(double ratinf){ this->rating = rating;}
    CuboDiscografia *getDiscografia(){ return this->discos; }
    ListaAlbumsOrdenados *getAlbumsOrdenados(){ return this->albums_rating; }
};
    