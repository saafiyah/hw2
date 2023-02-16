#include "util.h"
#include "mydatastore.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

MyDataStore::MyDataStore()
{

}

MyDataStore::~MyDataStore()
{
	map<string, User*>::iterator it; 
	for (it = allUsers.begin(); it != allUsers.end(); it++)
  { 
		delete it->second; 
	}
	for(size_t i = 0; i < allProducts.size(); i++)
	{
		delete allProducts[i];
	}
}

void MyDataStore::addProduct(Product* p)
{
	allProducts.push_back(p);
	set<string> keyword = p->keywords();
	set<string>::iterator it;
	map<string, set<Product*>>::iterator it2;
	for(it = keyword.begin(); it != keyword.end(); it++)
	{
		it2 = allKeywords.find(*it);
		if(it2 == allKeywords.end())
		{
			set<Product*> temp;
			temp.insert(p);
			allKeywords.insert(make_pair(*it, temp));
		}
		else
		{
			it2->second.insert(p);
		}
	}
}

void MyDataStore::addUser(User* u)
{
	allUsers.insert(make_pair(u->getName(), u));
	vector<Product*> cart; 
	allCarts.insert(make_pair(u->getName(), cart));
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type)
{
	set <Product*> retset;
	for (vector<string>::iterator it = terms.begin(); it != terms.end(); it++)
	{
		set <Product*> temp;
		temp = allKeywords[*it];
		if(type == 0)
		{
			if(it == terms.begin())
			{
				retset = temp;
			}
			else
			{
				retset = setIntersection<Product*> (retset, temp);
			}
		}
		else if(type == 1)
		{
				retset = setUnion<Product*>(retset,temp);
		}
	}
	vector <Product*> retvect(retset.begin(), retset.end());
	return retvect;
}

void MyDataStore::dump(ostream& ofile)
{
	ofile << "<products>" << endl;
	vector<Product*>::iterator itProduct;
	map<string, User*>::iterator itMap;
	for(itProduct = allProducts.begin(); itProduct != allProducts.end(); itProduct++)
	{
		(*itProduct)->dump(ofile); 
	}
	ofile << "</products>" << endl;
	ofile << "<users>" << endl;
	for(itMap = allUsers.begin(); itMap != allUsers.end(); itMap++)
	{
		itMap->second->dump(ofile); 
	}
	ofile << "</users>" << endl;
}

void MyDataStore::addCart(string username, Product* p)
{
	map<string, vector<Product*>>::iterator it = allCarts.find(username);
  (it->second).push_back(p);

  if(it == allCarts.end())
	{
    vector<Product*> newCart;
		newCart.push_back(p);
		allCarts.insert(make_pair(username, newCart));
  }
}

void MyDataStore::buyCart(string username)
{
	map<string, User*>::iterator user = allUsers.find(username); 
	map<string, vector<Product*>>::iterator itCart = allCarts.find(username); 
	vector<Product*> curr;
	curr = itCart->second; 
	vector<Product*> newc;
	for(vector<Product*>::iterator itProd = curr.begin(); itProd != curr.end(); itProd++)
	{
		if((*itProd)->getQty() > 0 && user->second->getBalance() >= (*itProd)->getPrice())
		{
			user->second->deductAmount((*itProd)->getPrice());
			(*itProd)->subtractQty(1);
		}
		else
		{
			newc.push_back(*itProd); 
		}
	}
	allCarts[username] = newc; 
}

void MyDataStore::viewCart(string username)
{
	vector<Product*> curr;
	curr = allCarts.find(username)->second;
	int item = 1;
	vector<Product*>::iterator it; 
	for (it = curr.begin(); it != curr.end(); it++)
  { 
		cout << "Item " << item << endl;
		item++;
		cout << (*it)->displayString() << endl;
	}
}

bool MyDataStore::validUser(string username)
{
	if(allUsers.find(username) != allUsers.end())
	{
		return true;
	}
	return false;
}
