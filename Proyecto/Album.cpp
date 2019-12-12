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

public:
    Album(string name, string month, int year){
        this->name = name;
        this->month = month;
        this->year = year;
        this->songs = new ListaCanciones();
    }
    
    ListaCanciones *getSongs(){ return this->songs; }
    string getName(){return this->name;}
    string getMonth(){ return this->month;}
    int getYear(){return this->year;}


};