#include <sstream>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const string name, double price, int qty,
  const string size, const string brand)
  : Product("clothing", name, price, qty),
  size_(size),
  brand_(brand)
{
}

Clothing::~Clothing()
{ 
}

set<string> Clothing::keywords()const{
  set<string> nameKeywords = parseStringToWords(name_);
  set<string> brandKeywords = parseStringToWords(brand_);

  set<string> result = setUnion(nameKeywords, brandKeywords);

  return result;
}

string Clothing::displayString() const{
  stringstream ss;

  ss << name_ << endl;
  ss << "Size: " << size_ << " Brand: " << brand_ << endl;
  ss << price_ << " " << qty_ << " left.";

  return ss.str();
}

void Clothing::dump(ostream& os) const{
  Product::dump(os);
  os << size_ << endl;
  os << brand_ << endl;
}