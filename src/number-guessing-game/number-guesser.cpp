#include "number-guesser.h"

#include <iostream>
#include <random>
#include <string>
#include <sstream>
#include <chrono>
#include <cmath>
#include <exception>

// NumberGuessingGame
/** Creates a number guessing game class.
 *
 * The game will generate a number from min-max (inclusive)
 * and users can make guesses to the number using the makeGuess() or
 * getGuess() method.
 *
 * @param min The minimum value
 * @param max The maximum value
 * */
NumberGuessingGame::NumberGuessingGame(int min, int max) {
    this->setRange(min, max);
    this->resetNumber();
}

/** Makes a guess of the generated number.
 *
 * Make a guess of the generated number. The function will return
 * 1 if the guess is larger than the number, -1 if the guess
 * is less than the number and 0 if the guess is correct.
 *
 * @param guess The guess number.
 *
 * @return The guess status. 1 if guess is too big, -1 if guess
 * is too small and 0 if the guess is correct.
 * */
int NumberGuessingGame::makeGuess(int guess) {
    this->guesses += 1;
    // Guess is greater
    if (guess > this->number) {
        return 1;
    } else if (guess < this->number) {
        // Guess is lesser
        return -1;
    } else {
        // Correct guess
        return 0;
    }
}

/** Guess the number from the standard input.
 *
 * @return false if the guess is incorrect, true if guess is
 * correct.
 * */
bool NumberGuessingGame::getGuess(void) {
    // Getting guess from standard input
    int guess;
    // https://stackoverflow.com/questions/10349857/how-to-handle-wrong-data-type-input
    if(!(std::cin >> guess)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter." << std::endl;
        return false;
    }

    // Checking Guess
    int status = makeGuess(guess);
    handleGuess(status);

    // Returning if guess is correct or not
    if (status == 0) {
        return true;
    } else {
        return false;
    }
}

/** Resets the number currently stored.
 *
 * Generates the a random number from the min to
 * max (inclusive) using a uniform distribution.
 * */
void NumberGuessingGame::resetNumber(void) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(this->min, this->max);

    this->number = distribution(generator);
    this->resetNGuesses();
}

// Setter Definisions
/** Sets the current range the random number is in (inclusive).
 *
 * The function will throw an invalid_argument if min is not < max.
 *
 * @param min The minimum value
 * @param max The maximum value
 * */
void NumberGuessingGame::setRange(int min, int max) {
    if (min < max) {
        this->min = min;
        this->max = max;
    } else {
        throw std::invalid_argument("min must be < max");
    }
}

/** Sets the current minimum the random number can be (inclusive).
 *
 * The function will throw an invalid_argument if min is not <
 * current max.
 *
 * @param min The minimum value
 * */
void NumberGuessingGame::setMin(int min) {
    this->setRange(min, this->max);
}

/** Sets the current maximum the random number can be (inclusive).
 *
 * The function will throw an invalid_argument if current min is not <
 * max.
 *
 * @param max The maximum value
 * */
void NumberGuessingGame::setMax(int max) {
    this->setRange(this->min, max);
}

// Getter Definisions
/** Gets the current range the random number is in (inclusive).
 *
 * @return The current range in the form "min-max"
 * */
std::string NumberGuessingGame::getRange(void) const {
    // https://stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c
    std::ostringstream range;
    range << this->min << "-" << this->max;
    return range.str();
}

/** Gets the current minimum the random number can be (inclusive).
 *
 * @return The current minimum
 * */
int NumberGuessingGame::getMin(void) const {
    return this->min;
}
/** Gets the current maximum the random number can be (inclusive).
 *
 * @return The current maximum
 * */
int NumberGuessingGame::getMax(void) const {
    return this->max;
}

/** Gets the number of guesses it took to guess the correct number.
 *
 * @return The number of guesses
 * */
int NumberGuessingGame::getNGuesses(void) const {
    return this->guesses;
}

/** Prints the results from the return makeGuess() into a human
 * readable format in the standard output.
 *
 * @param result The result gotten from makeGuess()
 * */
void NumberGuessingGame::handleGuess(int result) const {
    if (result == 1) {
        std::cout << "Your Guess is too high." << std::endl;
    } else if (result == -1) {
        std::cout << "Your Guess is too low." << std::endl;
    } else {
        std::cout << "Congratulations!! Your guess is correct. "
            "The number is " << this->getNumber() <<
            ". You took " << this->getNGuesses() << " guesses." << std::endl;
    }
}

/** Resets the number of guesses counter. */
void NumberGuessingGame::resetNGuesses(void) {
    this->guesses = 0;
}

/** Debug Function to get the current number.
 *
 * @return The current number being stored.
 * */
int NumberGuessingGame::getNumber(void) const {
    return this->number;
}

// AutoNumberGuesser
/** Creates a class that makes optimal guesses in a number guessing
 * game.
 *
 * @param min The minimum value
 * @param max The maximum value
 * */
AutoNumberGuesser::AutoNumberGuesser(int min, int max): NumberGuessingGame(min, max) {

}

/** Starts the number guessing algorithm.
 *
 * This is different to a similar function startRecursion() as
 * this implementation of start uses loops to make the guesses.
 *
 * @param verbose Verbose what the algorithm is doing
 *
 * @return The number of guesses
 * */
int AutoNumberGuesser::start(bool verbose) {
    // Resetting Variables
    NumberGuessingGame::resetNGuesses();
    // Initializing initial condition
    int cMax = this->getMax();
    int cMin = this->getMin();
    int guess = floor(((float) cMin + cMax) / 2);
    int guessStatus;

    do {
        // Updating Guess
        guessStatus = NumberGuessingGame::makeGuess(guess);

        // Verbosing what the algorithm is doing
        if (verbose) {
            std::cout << "Algorithm Guessed: " << guess << std::endl;
            this->handleGuess(guessStatus);
        }

        // Changing current range
        if (guessStatus == 1) {
            cMax = guess;
        } else if (guessStatus == -1) {
            cMin = guess;
            if (cMin == (cMax - 1)) {
                cMin = cMax;
            }
        }

        guess = floor(((float) cMin + cMax) / 2);
    } while(guessStatus != 0);

    return this->getNGuesses();
}

/** Starts the number guessing algorithm.
 *
 * This is different to a similar function start() as this
 * implementation of start uses function recursion to make the
 * guesses.
 *
 * @param verbose Verbose what the algorithm is doing
 *
 * @return The number of guesses
 * */
int AutoNumberGuesser::startRecursion(bool verbose) {
    // Resetting Variables
    NumberGuessingGame::resetNGuesses();
    // Initializing initial condition
    int cMin = this->getMin();
    int cMax = this->getMax();
    int guess = floor(((float) cMin + cMax) / 2);
    int guessStatus = NumberGuessingGame::makeGuess(guess);

    // Verbosing what the algorithm is doing
    if (verbose) {
        std::cout << "Algorithm Guessed: " << guess << std::endl;
        this->handleGuess(guessStatus);
    }

    // Changing current range
    if (guessStatus == 1) {
        cMax = guess;
        startRecursion(cMin, cMax, verbose);
    } else if (guessStatus == -1) {
        cMin = guess;
        if (cMin == (cMax - 1)) {
            cMin = cMax;
        }
        startRecursion(cMin, cMax, verbose);
    }

    return this->getNGuesses();
}

/** Starts the number guessing algorithm.
 *
 * This is different to a similar function start() as this
 * implementation of start uses function recursion to make the
 * guesses.
 *
 * @param cMin The current minimum
 * @param cMax The current maximum
 * @param verbose Verbose what the algorithm is doing
 *
 * @return The number of guesses
 * */
void AutoNumberGuesser::startRecursion(int cMin, int cMax, bool verbose) {
    int guess = floor(((float) cMin + cMax) / 2);
    int guessStatus = NumberGuessingGame::makeGuess(guess);

    // Verbosing what the algorithm is doing
    if (verbose) {
        std::cout << "Algorithm Guessed: " << guess << std::endl;
        this->handleGuess(guessStatus);
    }
    // Changing current range
    if (guessStatus == 1) {
        cMax = guess;
        startRecursion(cMin, cMax, verbose);
    } else if (guessStatus == -1) {
        cMin = guess;
        if (cMin == (cMax - 1)) {
            cMin = cMax;
        }
        startRecursion(cMin, cMax, verbose);
    }
}


/** Prints the results from the return makeGuess() into a human
 * readable format in the standard output.
 *
 * @param result The result gotten from makeGuess()
 * */
void AutoNumberGuesser::handleGuess(int result) const {
    if (result == 1) {
        std::cout << "Guess is too high." << std::endl;
    } else if (result == -1) {
        std::cout << "Guess is too low." << std::endl;
    } else {
        std::cout << "It took the algorithm " << this->getNGuesses() << " guesses. "
            "To guess the number " << this->getNumber() << "." << std::endl;
    }
}
