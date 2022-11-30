#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <array>
#include <list>

#include "number-guesser.h"
#include "histogram.h"

using namespace std;

/** Main function to intialize and play a number guessing
 * game.
 *
 * Starts the number guessing game from number 1-10. Users
 * will be prompted to guess the number. The program will tell
 * the user if the number is too big or too small or the guess
 * was correct.
 *
 * @param argc The amount of argument that is passed in.
 * @param argv The arguments that are passed in.
 * */
int main(int argc, char *argv[]) {
    // Getting Player
    string player;
    cout << "Who is playing the game? (AI, PLAYER): ";
    cin >> player;
    while (player != "AI" && player != "PLAYER") {
        cout << "Invalid Player, try again. "
             << "Who is playing the game? (AI, PLAYER): ";
        cin >> player;
    }

    // Getting Max
    int N = 10;
    cout << "Enter maximum number to generate (must be > 1): ";
    while (!(cin >> N) || N < 2) {
        cin.clear(); //clear bad input flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
        cout << "Invalid input; please re-enter. " << endl;
        cout << "Enter maximum number to generate (must be > 1): ";
    }

    // Player
    if (player == "PLAYER") {
        NumberGuessingGame guesser(1, N);

        // Player gameplay loop
        do {
            std::cout << "Enter a number: ";
        } while (!guesser.getGuess());
    } else if (player == "AI") { // AI
        // Getting Iteration
        int iteration = 200;
        cout << "Enter the amount of iteration: ";
        while (!(cin >> iteration) || iteration < 1) {
            cin.clear(); //clear bad input flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
            cout << "Invalid input; please re-enter. " << endl;
            cout << "Enter the amount of iteration: ";
        }

        // Initializing list
        list<int> data;

        // Gathering Data
        AutoNumberGuesser auto_guesser(1, N);
        for (int i = 0; i < iteration; i++) {
            auto_guesser.start(false);
            data.push_back(auto_guesser.getNGuesses());
            auto_guesser.resetNumber();
        }

        // Setting up and printing histogram
        Histogram histogram(data);
        histogram.print(HistogramFlags::HORIZONTAL);

        // Calculating mean
        int sz = data.size();
        int sum = accumulate(data.begin(), data.end(), 0);
        float mean = (float) sum / (float) sz;

        // Calculating Variance and Standard Deviation
        auto x_square = [](int accumulator, const int& val) {
            return accumulator + val * val;
        };
        float mean2 = std::accumulate(data.begin(), data.end(), 0.0, x_square) / (float) sz;
        float var = mean2 - mean * mean;
        float std = sqrt(var);

        // Printing Values
        cout << "Mean: " << mean << endl;
        cout << "Variance: " << var << endl;
        cout << "Standard Deviation: " << std << endl;
    } else { // Redudancy Code
        cerr << "Invalid player. " << endl;
        return 1;
    }
    return 0;
}
