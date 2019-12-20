#include <iostream> 
#include <fstream>
using namespace std;

class ArtistaRating{

private:
    string name;
    double rating;
public:   
    ArtistaRating(string name, double rating){
        this->rating = rating;
        this->name = name;
    }        
    string getName(){ return this->name;};
    double getRating(){ return this->rating;};
    void setName(string name){ this->name = name;}
    void setRating(double ratinf){ this->rating = rating;}
};
    