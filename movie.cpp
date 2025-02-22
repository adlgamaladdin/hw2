#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>
#include "product.h"
#include "movie.h"
#include "util.h"

Movie::Movie(std::string name, double price, int qty, std::string genre, std::string rating) : Product("movie", name, price, qty){
    genre_ = genre;
    rating_ = rating;
}

Movie::~Movie(){

}

std::set<std::string> Movie::keywords() const{
    std::set<std::string> keyw = parseStringToWords(name_);
    keyw.insert(convToLower(genre_)); 
    return keyw;
}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const{

    return true;
}

std::string Movie::displayString() const{
    std::stringstream s;
    s << name_ << "\nGenre: " << genre_ << " Rating: " << rating_ << "\n" << price_ << " " << qty_ << " left.";
    return s.str();
}

void Movie::dump(std::ostream& os) const{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << "\n";
}

std::string Movie::getGenre() const{
    return genre_;
}
std::string Movie::getRating() const{
    return rating_;
}

