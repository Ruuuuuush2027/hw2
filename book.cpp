#include "book.h"
#include "util.h"
using namespace std;

set<string> Book::keywords() const{
    set<string> res;
    set<string> temp = parseStringToWords(name_);
    set<string>::iterator i;
    for(i = temp.begin(); i != temp.end(); ++ i)
        res.insert(*i);
    
    temp = parseStringToWords(author_);
    for(i = temp.begin(); i != temp.end(); ++ i)
        res.insert(*i);
    
    res.insert(isbn_);
    return res;
}

string Book::displayString() const{
    string res(name_);
    res += "\nAuthor: ";
    res += author_;
    res += " ISBN: ";
    res += isbn_;
    res += "\n";
    res += to_string(price_);
    res += " ";
    res += to_string(qty_);
    res += " left.";
    return res;
}

void Book::dump(ostream& os) const{
    Product::dump(os);
    os << isbn_ << "\n" << author_ << endl;
}