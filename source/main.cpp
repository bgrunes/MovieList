#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include <sstream>
#include "movie.h"
#include "Map.h"
using namespace std;

void mapGenres(std::map<string, string> &genres);
void createSearch(string genreID);

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
    std::map<string, string> genres;
    mapGenres(genres);

    map<int, Movie> list;

    cout << "Welcome to MovieList!" << endl;
    
    // Describe what movie list is and does (?)
    while (true)
    {
        cout << "Please choose a genre to search the top 10 movies or type \'exit\' to end the program.\n";

        // FIXME: Change to vector<string> and loop print(?)
        cout << "Genres:\nAction, Adventure, Animation, \nComedy, Crime, Documentary, \nDrama, Family, Fantasy, \nHistory, Horror, Music, \nMystery, Romance, Science Fiction, \nTV Movie, Thriller, War, Western\n";

        string genre;
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
// Code by: Brandon Grunes
void mapGenres(std::map<string, string> &genres)
{
    ifstream gFile;

    gFile.open("data\\GENRE.csv");

    if (!gFile.is_open())
        cout << "ERROR: GENRE.csv not found\n";
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
            getline(gFile, genre, '\n');
            //cout << num << ", " << genreID << ", " << genre << "\n";

            genres[genre] = genreID;
        }

    }
}

// Searches through MOVIE_GENRE.csv and MOVIE.csv to match the genre id to the film id then to the movie and its respective data
// Uses filestreams to traverse the files
// Code by: Brandon Grunes
void createSearch(string genreID)
{
    ifstream mgFile;
    ifstream mFile;
    mgFile.open("data\\MOVIE_GENRE.csv");

    if (!mgFile.is_open())
        cout << "ERROR: MOVIE_GENRE.csv not found\n";
    else
    {
        string num;
        vector<string> filmId;
        string fId;
        string gId;
        getline(mgFile, num);
        while (!mgFile.eof())
        {
            getline(mgFile,num, ',');
            getline(mgFile, fId, ',');
            getline(mgFile, gId, ',');

            if (gId == genreID)
                filmId.push_back(fId);
        }

        // Test print the filmIds to make sure filestream is working
        for(int i = 0; i < filmId.size(); ++i)
        {
            cout << filmId[i] << "\n";
        }
    }

    mFile.open("data\\MOVIE.csv");

    if(!mFile.is_open())
        cout << "ERROR: MOVIE.csv not found\n";
    else
    {
        // Format of file is: ID,FILMID,TITLE,VOTE_AVERAGE
        string id, fId, title, vote_avg;
        getline(mFile, id);
        while (!mFile.eof())
        {
            getline(mFile, id, ',');
            getline(mFile, fId, ',');
            
        }
    }
}
