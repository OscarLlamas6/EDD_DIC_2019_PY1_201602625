#include <iostream>
#include <fstream>
using namespace std; 

class CuboDiscografia{

private:
    double rating;

public:
    CuboDiscografia(){
        this->rating=0;
    }
    void setRating(double rating){ this->rating = rating;}
    double getRating(){ return this->rating;}

};