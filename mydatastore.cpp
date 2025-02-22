#include "mydatastore.h"
#include <string>
#include <set>
#include <cctype>
#include <vector>
#include <map>
#include <utility>
#include "product.h"
#include "util.h"
#include "user.h"
#include "datastore.h"

MyDataStore::MyDataStore() : DataStore(){

}

MyDataStore::~MyDataStore() {  
    for(std::set<Product*>::iterator it = products_.begin(); it != products_.end(); it++){
        delete *it;
    }
    products_.clear(); 
    for(std::set<User*>::iterator it = users_.begin(); it != users_.end(); it++){
        delete *it;
    }
    users_.clear();
    carts_.clear();
}

void MyDataStore::addProduct(Product* p){
    products_.insert(p);
}

void MyDataStore::addUser(User* u){
    users_.insert(u);
    std::vector<Product*> cart;
    carts_.insert(std::make_pair(u, cart));
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
    std::vector<Product*> result;
    std::vector<std::string> searchTerms;
    for (size_t i = 0; i < terms.size(); i++) {
        std::string lowerTerm = convToLower(terms[i]);
        std::set<std::string> words = parseStringToWords(lowerTerm);
        for (std::set<std::string>::iterator it = words.begin(); it != words.end(); ++it) {
            std::string word = *it;
            if (word.length() >= 2) {
                searchTerms.push_back(word);
            }
        }
    }
    if (type == 0) {
        std::set<Product*> andResults;
        bool firstTerm = true;
        for (size_t i = 0; i < terms.size(); i++) {
            std::set<Product*> currTermResults;
            for (std::set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it) {
                std::set<std::string> keywords = (*it)->keywords();
                if (keywords.find(searchTerms[i]) != keywords.end()) {
                    currTermResults.insert(*it);
                }
            }
            if (firstTerm) {
                andResults = currTermResults;  
                firstTerm = false;
            } else {
                std::set<Product*> intersection;
                for (std::set<Product*>::iterator it = andResults.begin(); it != andResults.end(); ++it) {
                    if (currTermResults.find(*it) != currTermResults.end()) {
                        intersection.insert(*it);
                    }
                }
                andResults = intersection;
            }
            if (andResults.empty()) {
                break;
            }
        }

        for (std::set<Product*>::iterator it = andResults.begin(); it != andResults.end(); ++it) {
            result.push_back(*it);
        }
    } else if (type == 1) {  
        std::set<Product*> orResults;

        for (size_t i = 0; i < terms.size(); i++) {
            for (std::set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it) {
                std::set<std::string> keywords = (*it)->keywords();
                if (keywords.find(terms[i]) != keywords.end()) {
                    orResults.insert(*it); 
                }
            }
        }
        for (std::set<Product*>::iterator it = orResults.begin(); it != orResults.end(); ++it) {
            result.push_back(*it);
        }
    }

    return result;
}

void MyDataStore::dump(std::ostream& ofile){
    ofile << "<products>" << std::endl;
    for(std::set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it){
        (*it)->dump(ofile) ;
    }
    ofile <<"</products> \n" << "<users> \n";
    for(std::set<User*>::iterator it = users_.begin(); it != users_.end(); ++it){
        (*it)->dump(ofile);
    }
    ofile << "</users>" << std::endl;
}

void MyDataStore::addToCart(std::string u, size_t index, std::vector<Product*> hits){
    if(getUser(u) == NULL || index < 0 || index > hits.size()){
        std::cout << "Invalid Request" << std::endl;
        return;
    }
    User* currUser = getUser(u);
    carts_[currUser].push_back(hits[index-1]);
}

void MyDataStore::viewCart(std::string u){
 if(getUser(u) == NULL){
        std::cout << "Invalid Username" << std::endl;
        return;
    }
    std::vector<Product*> currCart = carts_[getUser(u)];
    for(size_t i = 0; i < currCart.size(); i++){
        std::cout << "Item " << i+1 << + "\n" << currCart[i]->displayString() << std::endl;
    }
}

void MyDataStore::buyCart(std::string u){
    if(getUser(u) == NULL){
        std::cout << "Invalid Username" << std::endl;
        return;
    }
    User* currUser = getUser(u);
    std::vector<Product*>& currCart = carts_[currUser];
    std::vector<Product*>::iterator it = currCart.begin();
    while(it != currCart.end()){
        Product* currProd = *it;
        if(currProd->getPrice() <= currUser->getBalance() && currProd->getQty() > 0){
            currProd->subtractQty(1);
            currUser->deductAmount(currProd->getPrice());
            it = currCart.erase(it);
        }
        else{
            ++it;
        }
    }

}

User* MyDataStore::getUser(std::string u){
    toLowerCase(u);
    for(std::set<User*>::iterator it = users_.begin(); it != users_.end(); ++it){
        std::string temp = (*it)->getName();
        if(temp == u){ // if user is found return user
            return *it;
        }
    }
    return NULL; // return NULL if not found
}

void MyDataStore::toLowerCase(std::string& u){
    for(size_t i = 0; i <= u.length(); i++){
        u[i] = tolower(u[i]);
    }
}
