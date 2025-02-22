#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>
#include "product.h"
#include "book.h"
#include "util.h"

Book::Book(std::string name, double price, int qty, std::string ISBN, std::string Author) : Product("book", name, price, qty){
    ISBN_ = ISBN;
    Author_ = Author;
}

Book::~Book(){
    
}

std::set<std::string> Book::keywords() const{
    std::string temp = name_ + " ";
    temp += Author_;
    std::set<std::string> keyw = parseStringToWords(temp);
    keyw.insert(ISBN_); //makes ISBN a searchable item
    // std::stringstream s(name_); // string stream to store the entire name of the book
    // s << " " <<  Author_; // adds the authors name to the end
    // std::string temp;
    // while(s >> temp){
    //     keyw.insert(temp); 
    // }
    return keyw;
}

bool Book::isMatch(std::vector<std::string>& searchTerms) const{
    return true;
}

std::string Book::displayString() const{
    std::stringstream s;
    s << name_ << "\nAuthor: " << Author_ << " ISBN: " << ISBN_ << "\n" << price_ << " " << qty_ << " left.";
    return s.str();
}

void Book::dump(std::ostream& os) const{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << ISBN_ << "\n" << Author_ << "\n";
}

std::string Book::getISBN() const{
    return ISBN_;
}
std::string Book::getAuthor() const{
    return Author_;
}

