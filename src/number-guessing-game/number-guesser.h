#ifndef NUMBER_GUESSER_H_
#define NUMBER_GUESSER_H_

#include <string>

/** A number guessing game.
 *
 * Initialize the class with the minimum and maximum number. Then,
 * call the getGuess() method. This will prompt for user input from the
 * standard input. Upon each guess, the game will tell the user if the number
 * is too big or too small or the guess is correct.
 * */
class NumberGuessingGame {
        public:
                /** Creates a number guessing game class.
                 *
                 * The game will generate a number from min-max (inclusive)
                 * and users can make guesses to the number using the makeGuess() or
                 * getGuess() method.
                 *
                 * @param min The minimum value
                 * @param max The maximum value
                 * */
                NumberGuessingGame(int min = 0, int max = 10);
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
                int makeGuess(int guess);
                /** Guess the number from the standard input.
                 *
                 * @return false if the guess is incorrect, true if guess is
                 * correct.
                 * */
                virtual bool getGuess(void);
                // Setter
                /** Resets the number currently stored.
                 *
                 * Generates the a random number from the min to
                 * max (inclusive) using a uniform distribution.
                 * */
                virtual void resetNumber(void);
                /** Sets the current range the random number is in (inclusive).
                 *
                 * The function will throw an invalid_argument if min is not < max.
                 *
                 * @param min The minimum value
                 * @param max The maximum value
                 * */
                void setRange(int min, int max);
                /** Sets the current minimum the random number can be (inclusive).
                 *
                 * The function will throw an invalid_argument if min is not <
                 * current max.
                 *
                 * @param min The minimum value
                 * */
                void setMin(int min);
                /** Sets the current maximum the random number can be (inclusive).
                 *
                 * The function will throw an invalid_argument if current min is not <
                 * max.
                 *
                 * @param max The maximum value
                 * */
                void setMax(int max);
                // Getter
                /** Gets the current range the random number is in (inclusive).
                 *
                 * @return The current range in the form "min-max"
                 * */
                std::string getRange(void) const;
                /** Gets the current minimum the random number can be (inclusive).
                 *
                 * @return The current minimum
                 * */
                int getMin(void) const;
                /** Gets the current maximum the random number can be (inclusive).
                 *
                 * @return The current maximum
                 * */
                int getMax(void) const;
                /** Gets the number of guesses it took to guess the correct number.
                 *
                 * @return The number of guesses
                 * */
                int getNGuesses(void) const;
        protected:
                /** Prints the results from the return makeGuess() into a human
                 * readable format in the standard output.
                 *
                 * @param result The result gotten from makeGuess()
                 * */
                virtual void handleGuess(int result) const;
                /** Resets the number of guesses counter. */
                void resetNGuesses(void);
                /** Debug Function to get the current number.
                 *
                 * @return The current number being stored.
                 * */
                int getNumber(void) const;
        private:
                int number = 0; /**<The current number. */
                int min = 0; /**<The current minimum number. */
                int max = 10; /**<The current maximum number. */
                int guesses = 0; /**<The number of guesses made. */
};

/** A class that plays NumberGuessingGame in an optimal way. */
class AutoNumberGuesser: public NumberGuessingGame {
        public:
                /** Creates a class that makes optimal guesses in a number guessing
                 * game.
                 *
                 * @param min The minimum value
                 * @param max The maximum value
                 * */
                AutoNumberGuesser(int min = 0, int max = 10);
                /** Starts the number guessing algorithm.
                 *
                 * This is different to a similar function startRecursion() as
                 * this implementation of start uses loops to make the guesses.
                 *
                 * @param verbose Verbose what the algorithm is doing
                 *
                 * @return The number of guesses
                 * */
                virtual int start(bool verbose = false);
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
                virtual int startRecursion(bool verbose = false);
        protected:
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
                virtual void startRecursion(int cMin, int cMax, bool verbose = false);
                /** Prints the results from the return makeGuess() into a human
                 * readable format in the standard output.
                 *
                 * @param result The result gotten from makeGuess()
                 * */
                virtual void handleGuess(int result) const override;
};

#endif // NUMBER-GUESSER_H_
