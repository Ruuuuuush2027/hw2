#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "product.h"
#include "user.h"
#include<map>

class MyDataStore: public DataStore{
public:
    MyDataStore(){};
    ~MyDataStore();

    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);

    void buycart(std::string username);
    void viewcart(std::string username);
    void addToCart(std::string username, Product* product);

private:
    std::map<std::string, std::set<Product*>> productMap; // keyword to list of products
    std::map<std::string, User*> users;
    std::map<std::string, std::vector<Product*>> carts; // username as key, vector of products as cart
};

#endif