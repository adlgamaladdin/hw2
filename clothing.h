#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

class Clothing : public Product{
public:
Clothing(std::string name, double price, int qty, std::string size, std::string brand);
virtual ~Clothing();
std::set<std::string> keywords() const;
bool isMatch(std::vector<std::string>& searchTerms) const;
std::string displayString() const;
void dump(std::ostream& os) const;
//basic accessesors
std::string getSize() const;
std::string getBrand() const;

protected:
std::string size_;
std::string brand_;
};

#endif