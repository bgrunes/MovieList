#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include <sstream>
#include "movie.h"

void mapGenres(map<string, int> &genres);
void searchByGenre(map<string, int> genres, )

int main() {
    // Main menu:
    // 1. Search for top films by genre
    // 2. View / organize watchlist
    // 3. Quit


    // 1. Search genre
    // Which of the following genres do you want to search for?

    // use if / else . We could do a map? We could do a vector of pair of string and int? Iterate through vector, find out which is action, print out numbers.
    // if else statement
    // if (input = "Action") {}
    // datasearch(28);

    // #1. Pulp Fiction
    // #2. Pulp Fiction

    // A. Add an entry to watchlist?
    // B. Keep searching


    // 1.5. Search by title ?


    // 1. Action


    // 2.

    // Store the matches between genres and their IDs, mapGenres function handles filestream to GENRE.csv
    std::map<string, int> genres;
    mapGenres(genres);

    std::cout << "Welcome to MovieList!" << std::endl;
    
    // Describe what movie list is and does (?)
    while (true)
    {
    std::cout << "Please choose a genre to search the top 10 movies or type \'exit\' to end the program.\n";

    // FIXME: Change to vector<string> and loop print
    std::cout << "Genres: Action, Adventure, Animation, Comedy, Crime, Documentary, Drama, Family, Fantasy, History, Horror, Music, Mystery, Romance, Science Fiction, TV Movie, Thriller, War, Western\n";

    std::string genre;
    cin >> genre;


    // TODO: Make into function(?)
    if (genre == "exit")
        break;
    else if (genre == "Action")
    {

    }
    else if (genre == "Adventure")
    {

    }
    else if (genre == "Animation")
    {

    }
    else if (genre == "Comedy")
    {

    }
    else if (genre == "Crime")
    {

    }
    else if (genre == "Documentary")
    {

    }
    else if (genre == "Drama")
    {

    }
    else if (genre == "Family")
    {

    }
    else if (genre == "Fantasy")
    {

    }
    else if (genre == "History")
    {

    }
    else if (genre == "Horror")
    {

    }
    else if (genre == "Music")
    {

    }
    else if (genre == "Mystery")
    {

    }
    else if (genre == "Romance")
    {

    }
    else if (genre == "Science Fiction")
    {

    }
    else if (genre == "TV Movies")
    {

    }
    else if (genre == "Thriller")
    {

    }
    else if (genre == "War")
    {

    }
    else if (genre == "Western")
    {

    }
    }
    return 0;
}

void mapGenres(map<string, int> &genres)
{
    ifstream gFile;

    gFile.open("data\\GENRE.csv");

    if (!gFile.is_open())
        std::cout << "ERROR: GENRE.csv not found\n";
    else
    {
        string num;
        string genreID;
        string genre;
        getline(gFile, num);
        while (!gFile.eof())
        {
            getline(gFile, num, ',');
            getline(gFile, genreID, ',');
            getline(gFile, genre, ',');
            //std::cout << num << ", " << genreID << ", " << genre << "\n";

            genres[genre] = stoi(genreID);
        }

    }
}
