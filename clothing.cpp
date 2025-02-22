#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>
#include "product.h"
#include "clothing.h"
#include "util.h"

Clothing::Clothing(std::string name, double price, int qty, std::string size, std::string brand) : Product("clothing", name, price, qty){
    size_ = size;
    brand_ = brand;
}
Clothing::~Clothing(){
    
}

std::set<std::string> Clothing::keywords() const{
    std::string temp = name_ + " " + brand_;
    std::set<std::string> keyw = parseStringToWords(temp);
    return keyw;
}

bool Clothing::isMatch(std::vector<std::string>& searchTerms) const{
    return true;
}

std::string Clothing::displayString() const{
    std::stringstream s;
    s << name_ << "\nSize: " << size_ << " Brand: " << brand_ << "\n" << price_ << " " << qty_ << " left.";
    return s.str();
}

void Clothing::dump(std::ostream& os) const{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << "\n";
}

std::string Clothing::getSize() const{
    return size_;
}
std::string Clothing::getBrand() const{
    return brand_;
}

