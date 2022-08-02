#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <map>
#include <chrono>
#include "Map.h"
#include "Heap.h"
using namespace std;

void mapGenres(std::map<string, int> &genres);
void createSearch(int genreID);
int searchResult(vector<float> vote_avg, float k);

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
    //for (it = genres.begin(); it != genres.end(); it++)
        //std::cout << it->first << ", " << it->second << "\n";
    
    std::cout << "---------------------\n";
    std::cout << "Welcome to MovieList!\n";
    std::cout << "---------------------\n\n";

    std::cout << "This program allows you to search a database of more than 160,000 movies! MovieList will give you the top 10 highest rated movies categorized by the genre of your choosing!\n"
    << "Created by Brandon Grunes, Kylo Nocom, and Imran Nasrullah\n\n";
    
    // Loop through the program until user wants to exit
    while (true)
    {
        std::cout << "Please choose a genre to search the top 10 movies or type \'exit\' to end the program.\n";
        std::cout << "Genres:\n";
        std::cout << "-------";
        std::cout << "\nAction, Adventure, Animation, \nComedy, Crime, Documentary, \nDrama, Family, Fantasy, \nHistory, Horror, Music, \nMystery, Romance, Science Fiction, \nTV Movie, Thriller, War, Western\n";
        std::cout << "Search for: \n";
        string genre;
        getline(cin, genre);
        std::cout << "\n";

        if (genre == "exit")
            break;
        else
        {        
            it = genres.find(genre);
            if (it != genres.end())
                createSearch(genres[genre]);
            else
                std::cout << "Incorrect genre name.\n";
            
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
            getline(gFile, genre, '\n');
            //std::cout << num << ", " << genreID << ", " << genre << "\n";

            genres[genre] = stoi(genreID);
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
        std::cout << "ERROR: MOVIE_GENRE.csv not found\n";
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
            std::cout << filmId[i] << "\n";
        }*/
    }
    mgFile.close();
    mFile.open("data\\MOVIE.csv");
    
    vector<Movie> movieList;
    Heap heap;
        
    Map<float, Movie> list;
    vector<float> voteAvg;

    if(!mFile.is_open())
        std::cout << "ERROR: MOVIE.csv not found\n";
    else
    {
        // Format of file is: ID,FILMID,TITLE,RELEASE,VOTE_AVERAGE,VOTE_COUNT

        getline(mFile, num);
        while (!mFile.eof())
        {
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
                
                if (voteAvg.size() == 0)
                    voteAvg.push_back(stof(vote_avg));
                else
                {
                    if (searchResult(voteAvg, stof(vote_avg)) == -1)
                        voteAvg.push_back(stof(vote_avg));
                }
                movieList.push_back(movie);
            }
        }

        // Test print voteAvg vector
        //for (float i : voteAvg)
        //    std::cout << i << " ";

        // Inserts movies into the heap and prints them out
        // Code by: Kylo
        for (int i = 0; i < movieList.size(); i++)
            heap.insert(movieList[i]);

        // Start of Heap sorted print of top 10 movies
        // Time elapsed is recorded
        std::cout << "HEAP SORT: " << endl;
        auto t1 = chrono::high_resolution_clock::now();
        heap.print();
        auto t2 = chrono::high_resolution_clock::now();
        std::cout << "\n";
        auto duration = chrono::duration_cast<chrono::microseconds>(t2-t1).count();
        std::cout << "Task finished successfully in " << duration << " microseconds!\n\n";

        // Start of Map print of top 10 movies
        // Time elapsed is recorded
        std::cout << "MAP PRINT: \n";
        t1 = chrono::high_resolution_clock::now();
        sort(voteAvg.begin(), voteAvg.end(), greater<float>());
        int countToTen = 0;
        for (int i = 0; i < voteAvg.size(); i++)
        {
            if (countToTen == 10)
                break;
            //cout << list[voteAvg[i]].size() << " ";
            for (int j = 0; j < list[voteAvg[i]].size(); j++)
            {
                if (countToTen == 10)
                    break;
                list[voteAvg[i]][j].printData();
                ++countToTen;
            }
        }
        t2 = chrono::high_resolution_clock::now();
        std::cout << "\n";
        duration = chrono::duration_cast<chrono::microseconds>(t2-t1).count();
        std::cout << "Task finished successfully in " << duration << " microseconds!\n\n";
    }
}

// Search to see if the vote average is in the vector. Return the index if found, otherwise -1
int searchResult(vector<float> vote_avg, float k)
{
    for (int i = 0; i < vote_avg.size(); i++)
    {
        if (vote_avg[i] == k)
            return i;
    }

    return -1;
}
