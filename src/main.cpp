//-----------------------------------------------------------------------------
// File Name    : main.cpp
// Description  : Hides text inside of an image
// Author       : Liam Lawrence
// Created      : April 24, 2018
//
// Updated      : June 23, 2018
// Version      : 1.0
//-----------------------------------------------------------------------------


#include <iostream>
#include <random>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>


// Reads data from an image
void decodeData(unsigned int i, unsigned int j, int charLength, cv::Mat &src, std::mt19937::result_type seed,
                int randMin, int randMax) {
    std::string phrase = "";
    unsigned int word = 0;
    int color;
    auto randNum = std::bind(std::uniform_int_distribution<int>(randMin, randMax), std::mt19937(seed));

    // Main loop that assembles letters
    for (int k = 0; k < charLength; k++) {
        for (int h = 0; h < 4; h++) {
            // Randomly chooses a color channel
            color = randNum() % 3;
            word = (h == 0) ? (src.at<cv::Vec3b>(i, j)[color] & (unsigned)0x3) : (word << 2) | (src.at<cv::Vec3b>(i, j)[color] & 0x3);

            // Sets each pixel to be "skip" apart
            j+=randNum();
            if (j > src.cols) {
                j = 0;
                i++;

                if (i > src.rows) {
                    std::cout << "Error: Ran out of pixels\n";
                    return;
                }
            }
        }
        // Concatenates the chars together
        phrase += (char)word;
        word = 0;
    }

    // Outputs the final phrase
    std::cout << phrase << "\n";
}

// Encodes an image with data
void encodeData(unsigned int startY, unsigned int startX, int phraseLength, cv::Mat &src,
                std::string *wordList, std::mt19937::result_type seed, unsigned long skipSeed, int randMin, int randMax) {

    cv::Mat encodedImage = src;
    unsigned int i = startY;
    unsigned int j = startX;
    int numberOfCharacters = 0;
    int color;
    auto randNum = std::bind(std::uniform_int_distribution<int>(randMin, randMax), std::mt19937(seed));

    // Main loop that hides your phrase
    for (int k = 0; k < phraseLength; k++) {
        for (int h = 0; h < wordList[k].size(); h++) {
            for (int l = 0; l < 4; l++) {
                // Randomly picks the color channel
                color = randNum() % 3;

                // Sets each pixel to be "skip" apart
                encodedImage.at<cv::Vec3b>(i, j)[color] &= 0xFC;
                encodedImage.at<cv::Vec3b>(i, j)[color] |= (0x3 & (wordList[k][h] >> (6 - l*2)));

                // Moves the selected pixel to the right by skip
                j += randNum();
                if (j > encodedImage.cols) {
                    j = 0;
                    i++;

                    if (i > encodedImage.rows) {
                        std::cout << "Error: Ran out of pixels\n";
                        return;
                    }
                }
            }
            // Records the number of letters used
            numberOfCharacters++;
        }
    }

    // Prints out data to memorize
    std::cout << "Start X: " << startX
              << "\nStart Y: " << startY
              << "\nMin Skip: " << randMin
              << "\nMax Skip: " << randMax
              << "\nSkip seed: " << skipSeed
              << "\nCharacters: " << numberOfCharacters
              << "\n";

    // Save the final image
    cv::imwrite("../res/decode.png", encodedImage);
}


int main() {
    unsigned int xVal, yVal;
    unsigned long skipSeed;
    int numberOfWords, numberOfChars;
    int randMin, randMax;
    bool encode;

    // Grabs user input
    std::cout << "Decode(0) or Encode(1): ";
    std::cin  >> encode;

    std::cout << "Enter pixel value for the starting x: ";
    std::cin >> xVal;

    std::cout << "Enter pixel value for the starting y: ";
    std::cin >> yVal;

    std::cout << "Random Seed: ";
    std::cin >> skipSeed;
    std::mt19937::result_type seed = skipSeed;

    std::cout << "Minimum skip: ";
    std::cin >> randMin;

    std::cout << "Maximum skip: ";
    std::cin >> randMax;


    // Encode
    if (encode) {
        cv::Mat image = cv::imread("../res/encode.png");
        std::cout << "Enter the number of words in your phrase: ";
        std::cin >> numberOfWords;

        std::string wordList[numberOfWords];
        for (int i = 0; i < numberOfWords; i++) {
            std::cout << "Word " << i + 1 << ": ";
            std::cin >> wordList[i];
			wordList[i] += " ";
        }

        encodeData(yVal, xVal, numberOfWords, image, wordList, seed, skipSeed, randMin, randMax);

    // Decode
    } else {
        cv::Mat image = cv::imread("../res/decode.png");
        
        std::cout << "Enter the number of characters in your phrase: ";
        std::cin >> numberOfChars;

        decodeData(yVal, xVal, numberOfChars, image, skipSeed, randMin, randMax);
    }

    return 1;
}
