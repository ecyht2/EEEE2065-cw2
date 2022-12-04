# EEEE2065-cw2
A number guessing game.

## Building

### Requirements
`Cmake` Cmake is used to compile the program. You can download cmake [here](https://cmake.org/download/).

### Compiling

``` sh
git clone https://github.com/ecyht2/EEEE2065-cw2.git
cd EEEE2065-cw2/
cmake . && cmake --build .
```

## Usage

After compilation a directory `bin/` should be created in the repository. To run it, run the command with the word to print. The program will guide you on what to do.

``` sh
bin/number-guessing-game
```

### Benchmarking for AI

This repository also provides a benchmark for the AI. It gets average number times it took the AI to guess a number from 1 to N and calculates the standard deviation. Then, it outputs the data into a csv for further processing.

``` sh
bin/ai-benchmark
```

The ai-benchmark takes in some arguments. It has the usage signature of:

``` sh
ai-benchmark min max step iteration
```

However these are optional and defaults to certain values.

| Name      | Description                                                                              | Default |
|-----------|------------------------------------------------------------------------------------------|---------|
| min       | The minimum N to use.                                                                    | 100     |
| max       | The maximum N to use.                                                                    | 5000    |
| step      | How much should the program increase the N by after each iteration until it reaches max. | 100     |
| iteration | How many samples should the benchmark take for a given N.                                | 500     |


