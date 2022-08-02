// Code by Kylo
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
    std::cout << title << " (" << voteAverage << ") " << "(Released: " << release << ") \n";
}
float Movie::giveAverage()
{
    return voteAverage;
}
