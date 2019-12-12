#include <iostream> 
//#include "CuboDiscos.cpp"
#include "Discografia.cpp"
using namespace std;

class Artista{

private:
    string name;
    double rating;
    Discography discos;
public:   
    Artista(string name, double rating){
        this->rating = rating;
        this->name = name;
    }        
    string getName(){ return this->name;};
    double getRating(){ return this->rating;};
    void setName(string name){ this->name = name;}
    void setRating(double ratinf){ this->rating = rating;}
};
    