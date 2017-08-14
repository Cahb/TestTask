#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
using namespace std;
//The test task result should be located at any convenient Git repository
//Please, read the comments carefully.
//This method should revert the word sequences. (e.g. "word1 word2 word3" -> "word3 word2 word1")
void revertWords(char* arr) { // algorithm: 1 - reverse words; 2 - reverese whole string;
    if(!arr) return;
    char * wordBeginning= nullptr, * wordEnding =arr;
    auto reverseStringSequence = [](char *wordBeginning, char * wordEnding)->void{ // no capture for lambda (use as ordinary func)
        char tempChar;
        while(wordBeginning < wordEnding){
            tempChar = *wordBeginning;
            *wordBeginning++ = *wordEnding;
            *wordEnding-- = tempChar;
        }
    }; // gotta either use lambda, outer function or additional word-locating variables (used lambda, c++11);
    while( *wordEnding ){
        if (( wordBeginning == nullptr ) && (*wordEnding != ' ')  ){
            wordBeginning=wordEnding;
        }
        if(wordBeginning && ((*(wordEnding+1) == ' ') || (*(wordEnding+1) == '\0'))){
            reverseStringSequence(wordBeginning, wordEnding);
            wordBeginning = nullptr;
        }
        wordEnding++;
    }
    reverseStringSequence(arr, wordEnding-1);
}

//Revert words using previous method and return the longest.
std::string processWords(std::string const& input){
    revertWords(const_cast<char*>(input.data()));
    string longestWord;
    size_t longestSize = 0, longestWordBeginning=-1, tempBeginning=0,tempEnding=0;
    while(tempBeginning < input.size() ){
        if( (tempBeginning = input.find_first_not_of(" \0",tempBeginning) )!= string::npos){
            if( (tempEnding = input.find_first_of(" \0",tempBeginning)) != string::npos){
                if(longestSize <tempEnding - tempBeginning){
                    longestSize = tempEnding - tempBeginning+1;
                    longestWordBeginning = tempBeginning;
                }
            }
        }
        tempBeginning++;
    }
    if(longestSize) return input.substr(longestWordBeginning, longestSize-1);
    return input;
}

//Create a method to generate an array of random length (10-20) random signed integer numbers.
//Print the generated sequence in console.
signed int* arr=nullptr; // it was initially global ptr... and i'm not allowed to modify main.
unsigned int arrSize = 0; // impossible to define arr. size on-run: need add. var to store size
void intGenerator(signed int* arr) {
    auto RAND = []()->unsigned int{ //Linear congruential generator (no STDLIB.h for rand(), must've reimplement it)
        static unsigned long int next = time(NULL);
        next = next * 1103515245 + 12345;
        return (static_cast<unsigned int>((next/65536) % RAND_MAX) );
};
    auto random32BitNumber = [&RAND] () -> unsigned int{ // get pseudo-random int32 
        signed int bit=0;
        for(int x = 0 ; x < 32;x++){
            if(RAND() % 2 == 1) bit ^= 1;
            bit <<= 1;
        }
        return  bit;
};
    arrSize = 10+ (RAND() % (20 - 10)); // basic formule MIN + (rand() % (MAX - MIN))
    {
        extern signed int * arr;
        if(arr == nullptr)
            arr = new signed int[arrSize];
    }
    if(::arr && ! arr )
        arr = ::arr;
    else
        arr = new signed int[arrSize];
    for(size_t i = 0; i < arrSize; ++i){
        arr[i] = random32BitNumber();
        //arr[i] =  static_cast<signed int>(generator(randomNumberGenerator)) ;
        cout << arr[i] << " ";
    }
    cout << endl;
}

    //Using the result of previous method, find the minimal value in the array.
signed int signedMin(signed int* arr){
    if(arr == nullptr || !arr){
        intGenerator(::arr);
        arr = ::arr;
    }
    signed int min= INT32_MAX;
    for(size_t i = 0; i < arrSize;i++) {
        if(min > arr[i]){
            min = arr[i];
        }
    }
    delete[] arr;
    return min;
}

int main() //DO NOT MODIFY THIS BLOCK
{
    std::cout << "Test started" << std::endl;
    std::cout << "Please input a text with several words" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::cout << "Input text: " << input << std::endl;
    std::cout << "Longest word: " << processWords(input) << std::endl;
    std::cout << "Reverted text: " << input << std::endl;
    std::cout << "Minimal is : " << signedMin(arr) << std::endl;
    std::cout << std::endl << "Test ended";
    return 0;
}
