#include "movie.h"
#include <iostream>

Movie::Movie(int id, string title, float voteAverage)
{
    this->id = id;
    this->title = title;
    this->voteAverage = voteAverage;
}

void Movie::printData()
{
    std::cout << title << " (" << voteAverage << ") " << "(";

    for(int i = 0; i < genre.size(); ++i)
    {
        if (i == genre.size() - 1)
            std::cout << genre[i];
        else
            std::cout << genre[i] << ", ";
    }

    std::cout << ")\n";
}
