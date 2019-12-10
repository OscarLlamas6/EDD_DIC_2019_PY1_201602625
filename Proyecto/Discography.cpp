#include <iostream>
//#include "Cubo.cpp"
using namespace std; 

class Discography{

private:
    double rating;
    //Cubo albums;
public:
    Discography(){
        this->rating=0;
    }
    void setRating(double rating){ this->rating = rating;}
    double getRating(){ return this->rating;}
    //Cubo getAlbums(){return this->albums;}
};