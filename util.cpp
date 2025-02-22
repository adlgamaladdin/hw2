#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    std::set<std::string> words; // this will hold the keywords
    std::stringstream s(rawWords); // we will use a string stream to parse through our rawWords string
    rawWords = ""; // since our stringstream is storing the rawwords we can repurpose this variable to check if our input is valid
    while(s >> rawWords){  // this will keep going until stringstream gives an error
        if(isISBN(rawWords)){ // uses helper function to check if current word is an ISBN
            words.insert(rawWords); // if it is then we insert
        }
        else{
            std::string temp = ""; // stores string as far as we've iterated so far
            for(size_t i = 0; i < rawWords.length(); i++){
                if(ispunct(rawWords[i])){ // if the current character is puncation
                    if(temp.length() >= 2){ // we check to see if the string up to the puncation is 2 or greater
                        words.insert(convToLower(temp)); // if it is we insert
                    }
                    temp = ""; // reset temp to nothing after we found puncation
                }
                else{
                temp += rawWords[i]; // if punctuation isnt found we concat the character to temp
                }
            }
            if(temp.length() >=2){ // final check to see if rest of word is big enough to add
                words.insert(convToLower(temp));
            }
        }
    }
    return words;
}

// helper function 1
bool isISBN(std::string word){
    for(char ch : word){
        if(ch > 57){
            return false;
        }
    }
    return true;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
