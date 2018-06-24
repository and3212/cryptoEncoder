//-----------------------------------------------------------------------------
// File Name    : ascii_to_dec.cpp
// Description  : Converts words to the sum of their ASCII letters
// Author       : Liam Lawrence
// Created      : June 23, 2018
//
// Version      : 1.0
//-----------------------------------------------------------------------------


#include <iostream>
#include <string>

int main() {
    std::string s;
    int value = 0;

    // Loops through the five words
    for (int i = 0; i < 5; i++) {
        std::cout << "Word " << i + 1 << ": ";
        std::cin >> s;

    // Sums their ASCII values
    for (int j = 0; j < s.length(); j++) {
        value += s.at(j);		
    }

    // Prints the value out and resets it for the next word
        std::cout << "      - " << value << "\n\n";
        value = 0;
    }
}
