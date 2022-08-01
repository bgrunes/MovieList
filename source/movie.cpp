#include "movie.h"
#include <iostream>

Movie::Movie(int id, string title, string release, float voteAverage)
{
    this->id = id;
    this->title = title;
    this->release = release;
    this->voteAverage = voteAverage;
}

Movie& Movie::operator=(const Movie &m) {
    id = m.id;
    title = m.title;
    release = m.release;
    voteAverage = m.voteAverage;
    return *this;
}

void Movie::printData()
{
    std::cout << title << " (" << voteAverage << ") " << "(" << release << ") " << "(";

    for(int i = 0; i < genre.size(); ++i)
    {
        if (i == genre.size() - 1)
            std::cout << genre[i];
        else
            std::cout << genre[i] << ", ";
    }

    std::cout << ")\n";
}

// kylo
float Movie::giveAverage()
{
    return voteAverage;
}
