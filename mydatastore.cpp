#include "mydatastore.h"
#include "util.h"

using namespace std;

void MyDataStore::addProduct(Product* p){
    set<string> keywords = p->keywords();
    set<string>::iterator i;
    for(i = keywords.begin(); i != keywords.end(); ++ i){
        map<string, set<Product*>>::iterator item = productMap.find(*i);
        if(item == productMap.end()){
            productMap.insert(pair<string, set<Product*>>(*i, set<Product*>()));
            item = productMap.find(*i);
        }
        (item->second).insert(p);
    }
}

void MyDataStore::addUser(User* u){
    users.insert(pair<string, User*>(u->getName(), u));
    carts.insert(pair<string, vector<Product*>>(u->getName(), std::vector<Product*>()));
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type){
    // type = 1 OR, 0 AND
    set<Product*> res;
    vector<string>::iterator i;
    for(i = terms.begin(); i != terms.end(); ++ i){
        map<string, set<Product*>>::iterator item = productMap.find(*i);
        if(item == productMap.end())
            continue;
        
        if(type == 1)
            res = setUnion<Product*>(res, item->second);
        else
            res = i == terms.begin() ? item->second : setIntersection<Product*>(res, item->second);
    }

    vector<Product*> ans;
    for(set<Product*>::iterator j = res.begin(); j != res.end(); ++ j)
        ans.push_back(*j);

    return ans;
}

void MyDataStore::dump(std::ostream& ofile){
    
    set<Product*> products;
    for(map<string, set<Product*>>::iterator i = productMap.begin(); i != productMap.end(); ++ i)
        products = setUnion<Product*>(products, i->second);
    
    ofile << "<products>" << endl;
    for(set<Product*>::iterator i = products.begin(); i != products.end(); ++ i)
        (*i)->dump(ofile);
    ofile << "</products>" << endl << "<users>" << endl;

    for(map<string, User*>::iterator i = users.begin(); i != users.end(); ++ i)
        i->second->dump(ofile);
    ofile << "</users>" << endl;
}

void MyDataStore::buycart(std::string username){
    map<string, vector<Product*>>::iterator item = carts.find(username);
    if(item == carts.end()){
        cout << "Invalid username" << endl;
        return;
    }
    vector<Product*> cart(item->second);
    User* user = users[username];
    size_t i = 0;
    while(i < cart.size()){
        if(cart[i]->getPrice() < user->getBalance() && cart[i]->getQty() > 0){
            user->deductAmount(cart[i]->getPrice());
            cart.erase(cart.begin() + i);
        } else{
            i ++;
        }
    }
}

void MyDataStore::viewcart(std::string username){
    map<string, vector<Product*>>::iterator item = carts.find(username);
    if(item == carts.end()){
        cout << "Invalid username" << endl;
        return;
    }
    vector<Product*> cart(item->second);

    for(size_t i = 0; i < cart.size(); ++ i){
        cout << i + 1 << ": " << cart[i]->displayString() << endl;
    }
}

void MyDataStore::addToCart(string username, Product* product){
    map<string, vector<Product*>>::iterator item = carts.find(username);
    if(item == carts.end()){
        cout << "Invalid request" << endl;
        return;
    }
    carts[username].push_back(product);
}

MyDataStore:: ~MyDataStore(){
    set<Product*> products;
    for(map<string, set<Product*>>::iterator i = productMap.begin(); i != productMap.end(); ++ i)
        products = setUnion<Product*>(products, i->second);
    
    for(set<Product*>::iterator i = products.begin(); i != products.end(); ++ i)
        delete *i;
    
    for(map<string, User*>::iterator i = users.begin(); i != users.end(); ++ i)
        delete i->second;
}