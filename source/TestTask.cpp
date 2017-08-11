//#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstring>
#include <random>
#include <stack>
#include <sstream>
#include <ctime>

using namespace std;

//The test task result should be located at any convenient Git repository
//Please, read the comments carefully.

//This method should revert the word sequences. (e.g. "word1 word2 word3" -> "word3 word2 word1")
void revertWords(char *arr){
    if(!arr || arr == nullptr || strlen(arr) <1) return; // basic case
    stringstream whiteSpacesRemover;
    string stringsBuffer, singleWordBuffer;
    size_t stackSize=0;
    stringsBuffer = arr;
    stack <string> tempStack;
    if( stringsBuffer.find_first_not_of(" \t") == string::npos) return; // basically - str is either empty \ contains single word
    whiteSpacesRemover << stringsBuffer;                                // which means nothing to revert
    stringsBuffer.clear();
    while ((whiteSpacesRemover >> singleWordBuffer)){
        stringsBuffer += singleWordBuffer + " ";
    }
    stringsBuffer.resize(stringsBuffer.size()-1); // remove last space;
    strcpy(arr,stringsBuffer.c_str());
    whiteSpacesRemover.clear();
    whiteSpacesRemover << stringsBuffer;
    while ((whiteSpacesRemover >> singleWordBuffer)){
        tempStack.push(singleWordBuffer + " ");
    }
    stackSize = tempStack.size();
    std::memset(arr, 0, strlen(arr)); // clear string, just in case
    stringsBuffer.clear();
    for(size_t i = 0; i < stackSize;++i){
        stringsBuffer += tempStack.top();
        tempStack.pop();
    }
    std::memcpy(arr, stringsBuffer.c_str(),stringsBuffer.size());
    arr[stringsBuffer.size()-1]='\0';
}

//Revert words using previous method and return the longest.
std::string processWords(std::string const& input){
    string singleWordString;
    stringstream words;
    size_t wordSize=0, longestWordIndex=-1;
    wordSize = input.find_first_not_of(" \t");
    if(input.size() < 1  || wordSize == string::npos) return input;
    wordSize = 0;
    revertWords(const_cast<char*>(input.data()));
    const_cast<string&>(input).resize(strlen(input.c_str())+1);
    /*
            Most of the time modified data would be smaller than the data of original string,
            because it discards some tabs \ whitespaces etc. and thus producing trash in
            string array;
            this is why we need a const_cast for the data itself, and the cast for string,
            to call resize
    */
    words << input;
    vector <string> wordsVector; // to easy-find the longest (by index)
    while ((words >> singleWordString)){
        wordsVector.push_back(singleWordString + "\0");
    }
    wordSize = -1;
    longestWordIndex= 0;
    wordSize = 0;
    if(wordsVector.size() == 1) return wordsVector[0]; // if there's only one word == it's the longest one
    for(size_t i = 0; i < wordsVector.size();i++){
        if(wordsVector[i].size() > wordSize){
            wordSize = wordsVector[i].size();
            longestWordIndex = i;
        }
    }
    return wordsVector[longestWordIndex];
}

//Create a method to generate an array of random length (10-20) random signed integer numbers.
//Print the generated sequence in console.
signed int* arr=nullptr; // it was initially global ptr... and i'm not allowed to modify main.
unsigned int arrSize = 0; // impossible to define arr. size on-run: need add. var to store size
void intGenerator(signed int* arr) {
    std::mt19937_64 randomNumberGenerator;
    randomNumberGenerator.seed(time(NULL)); // pseudo-random seed based on time to gen. rnd numbers
    uniform_int_distribution <signed int> generator(INT32_MIN,INT32_MAX);
    uniform_int_distribution <unsigned> lengthGenerator(10,20);
    arrSize = lengthGenerator(randomNumberGenerator);
    {
        extern signed int * arr; // used extern because of the given global variable ptr.
        if(arr == nullptr)
            arr = new signed int[arrSize];
    }
    if(::arr && ! arr )
        arr = ::arr;
    else
        arr = new signed int[arrSize];
    for(size_t i = 0; i < arrSize; ++i){
            arr[i] =  static_cast<signed int>(generator(randomNumberGenerator)) - INT32_MAX;
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
