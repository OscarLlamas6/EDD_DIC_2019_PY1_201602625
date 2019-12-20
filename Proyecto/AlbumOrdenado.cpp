#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
using namespace std; 

class AlbumOrdenado{

private:
    string name;
    double rating;
public:
    AlbumOrdenado(string name, double rating){
        this->name = name;
        this->rating = rating;
    }

    string getName(){ return this->name;}
    double getRating(){ return this->rating; }
    void setName(string name){ this->name = name;}
    void setRating(double rating){ this->rating = rating; }
};
