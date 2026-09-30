#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const string name, double price, int qty,
  const string isbn, const string author)
  : Product("book", name, price, qty),
  isbn_(isbn),
  author_(author)
{
}

Book::~Book()
{
}

set<string> Book::keywords()const{
  set<string> nameKeywords = parseStringToWords(name_);
  set<string> authorKeywords = parseStringToWords(author_);

  set<string> result = setUnion(nameKeywords, authorKeywords);

  result.insert(convToLower(isbn_));

  return result;
}

string Book::displayString() const{
  stringstream ss;

  ss << name_ << endl;
  ss << "Author: " << author_ << " ISBN: " << isbn_ << endl;
  ss << price_ << " " << qty_ << " left.";

  return ss.str();
}

void Book::dump(ostream& os) const{
  Product::dump(os);
  os << isbn_ << endl;
  os << author_ << endl;
}