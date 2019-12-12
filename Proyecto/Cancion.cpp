#include <iostream>
using namespace std; 

class Cancion{
private:
    string name;
    string album;
    string artista;
    double rating;
public:
    Cancion(string name, string album, string artista, double rating){
        this->name = name;
        this->album = album;
        this->artista = artista;
        this->rating = rating;
    }
    string getName(){ return this->name; }
    string getAlbum(){ return this->album; }
    string getArtista(){ return this->artista; }
    double getRating(){ return this->rating; }

    void setName(string name){ this->name = name;}
    void setAlbum(string album){ this->album = album;}
    void setArtista(string artista){ this->artista = artista;}
    void setRating(double rating){ this->rating = rating; }

};