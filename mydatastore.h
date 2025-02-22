#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include "product.h"
#include "user.h"
#include "datastore.h"

class MyDataStore : public DataStore{
    public:
    MyDataStore();
    ~MyDataStore();  
    void addProduct(Product* p);
    void addUser(User* u);
    void addToCart(std::string u, size_t index, std::vector<Product*>);
    void viewCart(std::string u);
    void buyCart(std::string u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    protected:
    std::set<User*> users_;
    std::set<Product*> products_;
    std::map<User*, std::vector<Product*>> carts_;
    void toLowerCase(std::string& u);
    User* getUser(std::string u);


};




#endif