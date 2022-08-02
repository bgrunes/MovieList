#include <string>
#include <vector>
using namespace std;
#pragma once

class Movie {
private:
    int id;
    string title;
    string release;
    float voteAverage;
    vector<string> genre;
public:
    Movie(int id, string title, string release, float voteAverage);
    Movie& operator=(const Movie& m);
    float giveAverage();
    void printData();
};

// Your Watchlist:
// Pulp Fiction (9.8) (Action, Crime)
