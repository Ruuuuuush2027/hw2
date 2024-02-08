#include "movie.h"
#include "util.h"
using namespace std;

set<string> Movie::keywords() const{
    set<string> res;
    set<string> temp = parseStringToWords(name_);
    set<string>::iterator i;
    for(i = temp.begin(); i != temp.end(); ++ i)
        res.insert(*i);
    
    string str("");
    for(size_t i = 0; i < genre_.size(); i ++)
        str += tolower(genre_[i]);

    res.insert(str);
    return res;
}

string Movie::displayString() const{
    string res(name_);
    res += "\nGenre: ";
    res += genre_;
    res += " Rating: ";
    res += rating_;
    res += "\n";
    res += to_string(price_);
    res += " ";
    res += to_string(qty_);
    res += " left.";
    return res;
}

void Movie::dump(ostream& os) const{
    Product::dump(os);
    os << genre_ << "\n" << rating_ << endl;
}