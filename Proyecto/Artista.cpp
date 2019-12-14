#include <iostream> 
#include "CuboDiscos.cpp" 
#include <fstream>
using namespace std;

class Artista{

private:
    string name;
    double rating;
    CuboDiscografia *discos;
public:   
    Artista(string name, double rating){
        this->rating = rating;
        this->name = name;
       this->discos = new CuboDiscografia();
    }        
    string getName(){ return this->name;};
    double getRating(){ return this->rating;};
    void setName(string name){ this->name = name;}
    void setRating(double ratinf){ this->rating = rating;}
    CuboDiscografia *getDiscografia(){ return this->discos; }
};
    