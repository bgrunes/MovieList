#include "Movie.h"

class Heap {
private:
    vector<Movie> vectorOfMovs;
public:
    Heap();
    void insert(Movie m);
    Movie maxElem();
    void print();
};
