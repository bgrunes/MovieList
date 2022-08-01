#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <chrono>
#include "Map.h"
#include "heap.h"
using namespace std;

void mapGenres(std::map<string, int> &genres);
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
    std::map<string, int>::iterator it;

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
        else
        {        
            it = genres.find(genre);
            if (it != genres.end())
                createSearch(genres[genre]);
            else
                cout << "Incorrect genre name.\n";
            
        }
    }



    return 0;
}

// searches through the GENRE.csv file to map the genre to the genre ID
// Code by: Brandon
void mapGenres(std::map<string, int> &genres)
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

            genres[genre] = stoi(genreID);
            cout << "success!\n";
        }

    }

    gFile.close();
}

// Searches through MOVIE_GENRE.csv and MOVIE.csv to match the genre id to the film id then to the movie and its respective data
// Uses filestreams to traverse the files
// Code by: Brandon
void createSearch(int genreID)
{
    ifstream mgFile;
    ifstream mFile;
    string num;
    vector<string> filmId;
    string fId;
    string gId;
    string title;
    string release;
    string vote_avg;
    string vote_ct;

    mgFile.open("data\\MOVIE_GENRE.csv");

    if (!mgFile.is_open())
        cout << "ERROR: MOVIE_GENRE.csv not found\n";
    else
    {
        getline(mgFile, num);
        while (!mgFile.eof())
        {
            getline(mgFile,num, ',');
            getline(mgFile, fId, ',');
            getline(mgFile, gId, ',');

            if (stoi(gId) == genreID)
                filmId.push_back(fId);
        }

        // Test print the filmIds to make sure filestream is working
        /*for(int i = 0; i < filmId.size(); ++i)
        {
            cout << filmId[i] << "\n";
        }*/
    }
    mgFile.close();
    mFile.open("data\\MOVIE.csv");
    
    vector<Movie> movieList;
    Heap heap;
        
    Map<float, Movie> list;
    vector<float> voteAvg;

    if(!mFile.is_open())
        cout << "ERROR: MOVIE.csv not found\n";
    else
    {
        // Format of file is: ID,FILMID,TITLE,RELEASE,VOTE_AVERAGE,VOTE_COUNT

        getline(mFile, num);
        while (!mFile.eof())
        {
            getline(mFile, num, ',');
            getline(mFile, fId, ',');
            getline(mFile, title, ',');
            getline(mFile, release, ',');
            getline(mFile, vote_avg, ',');
            getline(mFile, vote_ct, '\n');

            bool checkIfTrue = false;
            for (int i = 0; i < filmId.size(); ++i)
            {
                if (filmId[i] == fId && stoi(vote_ct) > 20) 
                {
                    checkIfTrue = true;
                    break;
                }
            }

            if (checkIfTrue)
            {
                // Add the movie to the Movie List Map and the Movie List Heap
                Movie movie = Movie(stoi(fId), title, release, stof(vote_avg));
                list.insert(stof(vote_avg), movie);
                voteAvg.push_back(stof(vote_avg));
                
                movieList.push_back(movie);
            }
        }

        // Code by: Kylo
        for (int i = 0; i < movieList.size(); i++)
            heap.insert(movieList[i]);

        cout << "HEAP SORT: " << endl;
        heap.print();
    }
}
