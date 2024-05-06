/*
===============================================================================
BLAKE BUTZ
COP4530
PROJECT 6
Date: 4/24/2024

SUMMARY:
The purpose of this file is to collect the statistics of words, numbers, and 
characters usage in a file (redirected as the standard input). It then prints
to standard output the top counted words, numbers, and characters. Where top
is a global const variable. 
===============================================================================
*/
#include <iostream>  
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

const int TOP = 10;  // Constant for printing top elements

// Function prototypes
void countWords(string input, unordered_map<string, pair<int,int>>& wordFrequency);
void countNumbers(string input, unordered_map<string, pair<int,int>>& numberFrequency);
void countCharacters(string input, unordered_map<string, pair<int,int>>& characterFrequency);
string toLowercase(string str);
void printTop(const vector<pair<string, pair<int,int>>> rank, string name);

int main() 
{
    
    unordered_map<string, pair<int,int>> wordFrequency;  // Map for word frequency
    unordered_map<string, pair<int,int>> numberFrequency;  // Map for number frequency
    unordered_map<string, pair<int,int>> characterFrequency;  // Map for character frequency

    // Read input until end of file is reached
    string input;  // String to store input
    char c;  // Temporary char variable for input
    while (cin.get(c)) {  // Read input character by character
        input += c;  // Concatenate each character to the input string
    }

    countCharacters(input, characterFrequency);  // Count characters in the input
    countWords(input, wordFrequency);  // Count words in the input
    countNumbers(input, numberFrequency);  // Count numbers in the input
    
    

    // Print the characters
    // Convert characterFrequency to a vector of pairs
    vector<pair<string, pair<int,int>>> sortedCharacters(characterFrequency.begin(), characterFrequency.end());

    // Sort the vector based on the values in ascending order
    stable_sort(sortedCharacters.begin(), sortedCharacters.end(), [](const pair<string, pair<int,int>>& a, const pair<string, pair<int,int>>& b) {
        if (a.second.first != b.second.first) 
            return a.second.first > b.second.first; // Sort by frequency in ascending order
        else if (a.first == "\\t")
            return true;
        else if (b.first == "\\t")
            return false;
        else if (a.first == "\\n")
            return true;
        else if (b.first == "\\n")
            return false;
        else 
            return a.first < b.first; // Sort by ASCII value in ascending order
    
    });
    printTop(sortedCharacters, "characters");  // Print the top characters

    // Print the words
    // Convert characterFrequency to a vector of pairs
    vector<pair<string, pair<int,int>>> sortedWords(wordFrequency.begin(), wordFrequency.end());

    // Sort the vector based on the values in ascending order
    stable_sort(sortedWords.begin(), sortedWords.end(), [](const pair<string, pair<int,int>>& a, const pair<string, pair<int,int>>& b) {
        if(a.second.first != b.second.first)
            return a.second.first > b.second.first; // Sort by frequency in ascending order
        else
            return a.second.second < b.second.second;
    });
    printTop(sortedWords, "words");  // Print the top words

    // Print the numbers
    // Convert characterFrequency to a vector of pairs
    vector<pair<string, pair<int,int>>> sortedNumbers(numberFrequency.begin(), numberFrequency.end());

    // Sort the vector based on the values in ascending order
    stable_sort(sortedNumbers.begin(), sortedNumbers.end(), [](const pair<string, pair<int,int>>& a, const pair<string, pair<int,int>>& b) {
        if(a.second.first != b.second.first)
            return a.second.first > b.second.first; // Sort by frequency in ascending order
        else
            return a.second.second < b.second.second;    
    });
    printTop(sortedNumbers, "numbers");  // Print the top numbers

    return 0;  // Exit with success
}

// Function to count words in the input
void countWords(string input, unordered_map<string, pair<int,int>>& wordFrequency)
{
    string word;  // Temporary string to store each word

    for (char c : input)  // Loop through each character in the input
    {
        if (isalpha(c))  // If the character is a letter
        {
            word += c;  // Append it to the current word
        } 
        else if (!word.empty())  // If the current word is not empty
        {
            word = toLowercase(word);  // Convert the word to lowercase
            ++wordFrequency[word].first;  // Increment the frequency count of the word
            if(wordFrequency[word].first == 1) // Only update the priority if it is a new word
                    wordFrequency[word].second = wordFrequency.size();
            word.clear();  // Clear the current word for the next iteration
        }
    }

    // Push the last word if not empty
    if (!word.empty()) {
        word = toLowercase(word);  // Convert the last word to lowercase
        ++wordFrequency[word].first;  // Increment the frequency count of the last word
        if(wordFrequency[word].first == 1) // Only update the priority if it is a new word
                    wordFrequency[word].second = wordFrequency.size();
    }
}

// Function to count numbers in the input
void countNumbers(string input, unordered_map<string, pair<int,int>>& numberFrequency)
{
    string number;  // Temporary string to store each number
    for (char c : input)  // Loop through each character in the input
    {
        if (isdigit(c))  // If the character is a digit
        {
            number += c;  // Append it to the current number
        } 
        else if (!number.empty())  // If the current number is not empty
        {
            ++numberFrequency[number].first;  // Increment the frequency count of the number
            if(numberFrequency[number].first == 1) // Only update the priority if it is a new number
                    numberFrequency[number].second = numberFrequency.size();
            number.clear();  // Clear the current number for the next iteration
        }
    }

    // Push the last number if not empty
    if (!number.empty()) {
        ++numberFrequency[number].first;  // Increment the frequency count of the last number
    }
}

// Function to count characters in the input
void countCharacters(string input, unordered_map<string, pair<int,int>>& characterFrequency)
{
    for (char c : input)  // Loop through each character in the input
    {
        string letter;  // Temporary string to store each character
        if (c == '\t')  // If the character is a tab
        {
            letter = "\\t"; // Represent tab as "\t"
        }
        else if (c == '\n')  // If the character is a newline
        {
            letter = "\\n"; // Represent newline as "\n"
        }
        else 
            letter = c; // For other characters, convert to string normally
        ++characterFrequency[letter].first;  // Increment the frequency count of the character
    }

}

// Function to convert a string to lowercase
string toLowercase(string str) 
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);  // Convert each character to lowercase
    return str;  // Return the lowercase string
}

// Function to print the top elements
void printTop(const vector<pair<string, pair<int,int>>> rank, string name)
{
    cout << "Total " << rank.size() << " different " << name << ", ";  // Print total count of elements
    if(rank.size() < TOP)  // If the total count is less than the top constant
        cout << rank.size() << " most used " << name << ":" << endl;  // Print all elements
    else
        cout << TOP << " most used " << name << ":" << endl;  // Print only the top constant number of elements

    int count = 0;  // Counter for iterating through elements
    auto pair = rank.begin();  // Iterator for the rank vector
    while(pair!= rank.end() && count < TOP)  // Iterate through the rank vector until reaching the top constant or the end
    {
        cout << "No. " << setw(2) << ++count << ": ";  // Print the count of the element
        cout << setw(18) << left << pair->first << setw(6) << right << pair->second.first << endl;  // Print the element and its frequency
        ++pair;  // Move to the next element in the rank vector
    }
    cout << endl;  // Add a newline at the end
}
