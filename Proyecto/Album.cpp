#include <iostream>
#include <fstream>
#include "ListaCanciones.cpp"
using namespace std; 

class Album{

private:
    string name;
    string month;
    int year;
    ListaCanciones *songs;
    double rating;

public:
    Album(string name, string month, int year){
        this->name = name;
        this->month = month;
        this->year = year;
        this->songs = new ListaCanciones();
        this->rating = 0;
    }
    
    ListaCanciones *getSongs(){ return this->songs; }
    string getName(){return this->name;}
    string getMonth(){ return this->month;}
    int getYear(){return this->year;}
    void setRating(double rating){ this->rating = rating;}
    double getRating(){ return this->rating; }

};