#include "clothing.h"
#include "util.h"
using namespace std;

set<string> Clothing::keywords() const{
    set<string> res;
    set<string> temp = parseStringToWords(name_);
    set<string>::iterator i;
    for(i = temp.begin(); i != temp.end(); ++ i)
        res.insert(*i);
    
    temp = parseStringToWords(brand_);
    for(i = temp.begin(); i != temp.end(); ++ i)
        res.insert(*i);
    
    return res;
}

string Clothing::displayString() const{
    string res(name_);
    res += "\nSize: ";
    res += size_;
    res += " Brand: ";
    res += brand_;
    res += "\n";
    res += to_string(price_);
    res += " ";
    res += to_string(qty_);
    res += " left.";
    return res;
}

void Clothing::dump(ostream& os) const{
    Product::dump(os);
    os << size_ << "\n" << brand_ << endl;
}