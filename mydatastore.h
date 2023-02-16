#include <string>
#include <vector>
#include <set>
#include <map>
#include "datastore.h"

class MyDataStore: public DataStore
{
	public: 
		MyDataStore();
		~MyDataStore();
		void addProduct(Product* p);
		void addUser(User* u);
		std::vector<Product*> search(std::vector<std::string>& terms, int type);
		void dump(std::ostream& ofile);
		void addCart(std::string username, Product* p);
		void buyCart(std::string username);
		void viewCart(std::string username);
		bool validUser(std::string username); 

	private:
		std::vector<Product*> allProducts; 
		std::map<std::string, std::set<Product*>> allKeywords;
		std::map<std::string, User*> allUsers;
		std::map<std::string, std::vector<Product*>> allCarts;
}; 