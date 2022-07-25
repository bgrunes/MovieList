#include <string>
#include <vector>
using namespace std;

class Movie {
private:
    int id;
    string title;
    float voteAverage;
    vector<string> genre;
public:
    Movie(int id, string title, float voteAverage);
    void printData();
};

// Your Watchlist:
// Pulp Fiction (9.8) (Action, Crime)

