#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const string category, const string name, double price, int qty, const string size, const string brand) : Product(category, name, price, qty) 
{
	size_ = size;
	brand_ = brand; 
}

Clothing::~Clothing()
{

}

set<string> Clothing::keywords() const
{
	set<string> names = parseStringToWords(convToLower(name_));
	set<string> brands = parseStringToWords(convToLower(brand_));
	set<string> keywords = setUnion(names, brands);
	return keywords; 
}

string Clothing::displayString() const
{
	stringstream display; 
	display << name_ << "\n" << "Size: " << size_ << " Brand: " << brand_ << "\n" << price_ << " " << qty_ << " left." << "\n";
	return display.str(); 
}

void Clothing::dump(std::ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << "\n"; 
}