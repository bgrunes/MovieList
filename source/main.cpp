#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include <sstream>
#include "movie.h"

void mapGenres(map<string, int> &genres);
void createSearch(int genreID);

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

        // FIXME: Change to vector<string> and loop print(?)
        std::cout << "Genres: Action, Adventure, Animation, Comedy, Crime, Documentary, Drama, Family, Fantasy, History, Horror, Music, Mystery, Romance, Science Fiction, TV Movie, Thriller, War, Western\n";

        std::string genre;
        cin >> genre;

        if (genre == "exit")
            break;
        else if (genre == "Action")
        {        
            createSearch(genres[genre]);
        }
    }
    return 0;
}

// searches through the GENRE.csv file to map the genre to the genre ID
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

        // used to move the buffer over the headers 
        getline(gFile, num);

        // Checks whether gFile is at the end of the file
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

// Searches through MOVIE_GENRE.csv and MOVIE.csv to match the genre id to the film id then to the movie and its respective data
// Uses filestreams to traverse the files
void createSearch(int genreID)
{
    ifstream mgFile;
    ifstream mFile;
    mgFile.open("data\\MOVIE_GENRE.csv");

    if (!mgFile.is_open())
        std::cout << "ERROR: MOVIE_GENRE.csv not found\n";
    else
    {
        string id;
        vector<string> filmId;
        string fId;
        string gId;
        getline(mgFile, id);
        while (!mgFile.eof())
        {
            getline(mgFile,id, ',');
            getline(mgFile, fId, ',');
            getline(mgFile, gId, ',');

            if (std::stoi(gId) == genreID)
                filmId.push_back(fId);
        }

        for(string i : filmId)
        {
            std::cout << i << "\n";
        }
    }
}
