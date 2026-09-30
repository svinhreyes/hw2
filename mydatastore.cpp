#include "mydatastore.h"
#include "util.h"

using namespace std;

MyDataStore::MyDataStore()
{
}

MyDataStore::~MyDataStore(){
  for(unsigned int i = 0; i < products_.size(); i++){
    delete products_[i];
  }

  map<string, User*>::iterator it;

  for(it = users_.begin(); it != users_.end(); ++it){
    delete it->second;
  }
}

void MyDataStore::addProduct(Product* p){
  products_.push_back(p);
  set<string> keys = p->keywords();
  set<string>::iterator it;

  for(it = keys.begin(); it != keys.end(); ++it){
    keywordMap_[*it].insert(p);
  }
}

void MyDataStore::addUser(User* u){
  users_[u->getName()] = u;
}

vector <Product*> MyDataStore::search(vector<string>& terms, int type){
  vector<Product*> results;

  if(terms.size() == 0){
    return results;
  }

  set<Product*> matches;
  string firstTerm = convToLower(terms[0]);

  if(keywordMap_.find(firstTerm) != keywordMap_.end()){
    matches = keywordMap_[firstTerm];
  }

  if(type ==0){
    for(unsigned int i = 1; i < terms.size(); i++){
      string term = convToLower(terms[i]);
      set<Product*> currentMatches;
      
      if(keywordMap_.find(term) != keywordMap_.end()){
        currentMatches = keywordMap_[term];
      }

      matches = setIntersection(matches, currentMatches);
    }
  }else if(type == 1){
    for(unsigned int i = 1; i < terms.size(); i++){
      string term = convToLower(terms[i]);
      set<Product*> currentMatches;

      if(keywordMap_.find(term) != keywordMap_.end()){
        currentMatches = keywordMap_[term];
      }

      matches = setUnion(matches, currentMatches);
    }
  }
  set<Product*>::iterator it;
  
  for(it = matches.begin(); it != matches.end(); ++it){
    results.push_back(*it);
  }

  return results;
}

void MyDataStore::dump(ostream& ofile){
  ofile << "<products>" << endl;

  for(unsigned int i = 0; i < products_.size(); i++){
    products_[i]->dump(ofile);
  }

  ofile << "</products>" << endl;
  ofile << "<users>" << endl;
  map<string, User*>::iterator it;

  for(it = users_.begin(); it != users_.end(); ++it){
    it->second->dump(ofile);
  }

  ofile << "</users>" << endl;
}

void MyDataStore::addToCart(string username, Product* p){
  if(users_.find(username) == users_.end()){
    cout << "Invalid request" << endl;
    return;
  }

  carts_[username].push_back(p);
}

void MyDataStore::viewCart(string username){
  if(users_.find(username) == users_.end()){
    cout << "Invalid username" << endl;
    return;
  }
  
  vector<Product*>& cart = carts_[username];

  for(unsigned int i = 0; i < cart.size(); i++){
    cout << "Item " << i + 1 << endl;
    cout << cart[i]->displayString() << endl;
  }
}

void MyDataStore::buyCart(string username){
  if(users_.find(username) == users_.end()){
    cout << "Invalid username" << endl;
    return;
  }

  User* user = users_[username];
  vector<Product*>& cart = carts_[username];
  unsigned int i = 0;
  while(i < cart.size()){
    Product* product = cart[i];

    if(product->getQty() > 0 && user->getBalance() >= product->getPrice()){
      product->subtractQty(1);
      user->deductAmount(product->getPrice());
      cart.erase(cart.begin() + i);
    }else{
      i++;
    }
  }
}