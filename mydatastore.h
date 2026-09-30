#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

#include "datastore.h"
#include "product.h"
#include "user.h"

class MyDataStore : public DataStore{
  public:
    MyDataStore();
    virtual ~MyDataStore();
    virtual void addProduct(Product* p);
    virtual void addUser (User* u);
    virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);
    virtual void dump(std::ostream& ofile);
    void addToCart(std::string username, Product* p);
    void viewCart(std::string username);
    void buyCart(std::string username);

  private:
    std::vector<Product*> products_;
    std::map<std::string, User*> users_;
    std::map<std::string, std::set<Product*> > keywordMap_;
    std::map<std::string, std::vector<Product*> > carts_;
};

#endif