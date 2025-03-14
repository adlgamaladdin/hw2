#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> intersection;
    for(typename std::set<T>::iterator it = s1.begin(); it != s1.end(); ++it){ // runs in O(n)
        if(s2.find(it) != s2.end()){ // runs in log (n) // checks to see if key in set1 is in set 2
            intersection.insert(*it);
        }
    }
    return intersection;
}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    typename std::set<T>::iterator it;
    std::set<T> result = s1;  
    for(typename std::set<T>::iterator it = s2.begin(); it != s2.end(); ++it){ // runs in O(n)
        result.insert(*it);
    }
    return result;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

bool isISBN(std::string word);


// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
