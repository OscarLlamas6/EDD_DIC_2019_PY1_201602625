#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
using namespace std; 

class SongOrdenada{
private:
    string name;
    string album;
    string artista;
    string month;
    int year;
    double rating;
public:
    SongOrdenada(string name, string album, string artista, double rating, int year, string month){
        this->name = name;
        this->album = album;
        this->artista = artista;
        this->rating = rating;
        this->year = year;
        this->month = month;
    }

    string getMonth(){ return this->month; }
    string getName(){ return this->name; }
    string getAlbum(){ return this->album; }
    string getArtista(){ return this->artista; }
    double getRating(){ return this->rating; }
    int getYear(){ return this->year; }

    void setMonth(string month){ this->month = month; }
    void setName(string name){ this->name = name;}
    void setAlbum(string album){ this->album = album;}
    void setArtista(string artista){ this->artista = artista;}
    void setRating(double rating){ this->rating = rating; }
    void setYear(int year){ this->year = year; }

   
};

