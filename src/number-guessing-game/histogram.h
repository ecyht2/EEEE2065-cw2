#ifndef HISTOGRAM_H_
#define HISTOGRAM_H_

#include <map>
#include <list>
#include <iostream>
#include <iomanip>

/** Enumeration for Histogram Flags. */
enum HistogramFlags {
VERTICAL,
HORIZONTAL
};

/** A class that prints a histogram. */
template <class T>
class Histogram {
        public:
                /** Constructs a histogram using a list of variables.
                 *
                 * @param list A list representing the data to plot.
                 * */
                Histogram(std::list<T> &list) {
                        this->setData(list);
                }
                /** Constructs a histogram using a map of keys representing
                 * the entry and the value representing the count of the entry.
                 *
                 * @param map The map to use.
                 * */
                Histogram(std::map<T, int> &map) {
                        this->setData(map);
                }
                /** Prints out the histogram to standard output.
                 *
                 * @param flag To print the histogram horizontally or vertically.
                 * */
                virtual void print(HistogramFlags flag) const {
                        switch (flag) {
                                case HistogramFlags::VERTICAL:
                                        this->printVertical();
                                        break;
                                case HistogramFlags::HORIZONTAL:
                                        this->printHorizontal();
                                        break;
                        }
                }
                /** Sets the current data stored in the histogram class using a list.
                 *
                 * @param list A list representing the data to plot.
                 * */
                void setData(std::list<T> &list) {
                        for (T i: list) {
                                this->value_map[i] += 1;
                        }
                        this->calcHighest();
                        this->calcLowest();
                }
                /** Sets the current data stored in the histogram using a map of keys
                 * representing the entry and the value representing the count of the entry.
                 *
                 * @param map The map to use.
                 * */
                void setData(std::map<T, int> &map) {
                        this->value_map = map;
                        this->calcHighest();
                        this->calcLowest();
                }
                /** Gets a map of data where the keys are the entries and the values are
                 * the entry count.
                 *
                 * @return The data.
                 * */
                std::map<T, int> getData(void) const {
                        return this->value_map;
                }
                /** Gets the current entry with the highest count.
                 *
                 * @return A std::pair<T, int> containing the highest count.
                 * */
                std::pair<T, int> getHighest(void) const {
                        return this->highest_count;
                }
                /** Gets the current entry with the lowest count.
                 *
                 * @return A std::pair<T, int> containing the lowest count.
                 * */
                std::pair<T, int> getLowest(void) const {
                        return this->lowest_count;
                }
        protected:
                /** Function use to print a horizontal histogram. */
                virtual void printHorizontal(void) const {
                        // Looping all values
                        for (auto i: this->value_map) {
                                // Printing label
                                std::cout << std::setw(5) << i.first << "/";
                                std::cout << std::setw(5) << i.second << " ";
                                // Printing stars
                                for (int j = 0; j < i.second; j++) {
                                        std::cout << "*";
                                }
                                // Newline for new label
                                std::cout << std::endl;
                        }
                }
                /** Function use to print a vertical histogram. */
                virtual void printVertical(void) const {
                        // Printing stars
                        for (int i = this->highest_count.second; i > 0; i--) {
                                // Looping over all keys to check if the count is greater
                                for (auto pair: this->value_map) {
                                        if (pair.second >= i) {
                                                std::cout << std::setw(5) << "*";
                                        } else {
                                                std::cout << std::setw(5) << "";
                                        }
                                }
                                std::cout << std::endl;
                        }
                        // Printing labels
                        for (auto pair: this->value_map) {
                                std::cout << std::setw(5) << pair.first;
                        }
                        std::cout << std::endl;
                        // Printing Value
                        for (auto pair: this->value_map) {
                                std::cout << std::setw(5) << pair.second;
                        }
                        std::cout << std::endl;
                }
                /** Function to calculate the current entry with the highest count. */
                void calcHighest(void) {
                        std::pair<T, int> curr_highest;
                        for (auto i: this->value_map) {
                                if (i.second > curr_highest.second) {
                                        curr_highest = {i.first, i.second};
                                }
                        }
                        this->highest_count = curr_highest;
                }
                /** Function to calculate the current entry with the lowest count. */
                void calcLowest(void) {
                        std::pair<T, int> curr_lowest = *this->value_map.begin();
                        for (auto i: this->value_map) {
                                if (i.second < curr_lowest.second) {
                                        curr_lowest = {i.first, i.second};
                                }
                        }
                        this->lowest_count = curr_lowest;
                }
        private:
                std::map<T, int> value_map; /**<Data for the histogram. */
                std::pair<T, int> highest_count; /**<A pair containing the current entry with the highest count. */
                std::pair<T, int> lowest_count; /**<A pair containing the current entry with the lowest count. */
};

#endif // HISTOGRAM_H_
