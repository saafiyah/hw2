#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const string category, const string name, double price, int qty, const string isbn, const string author) : Product(category, name, price, qty) 
{
	isbn_ = isbn;
	author_ = author; 
}

Book::~Book()
{

}

set<string> Book::keywords() const
{
	set<string> names = parseStringToWords(convToLower(name_));
	set<string> authors = parseStringToWords(convToLower(author_));
	set<string> keywords = setUnion(names, authors);
	keywords.insert(isbn_);
	return keywords; 
}

string Book::displayString() const
{
	stringstream display; 
	display << name_ << "\n" << "Author: " << author_ << " ISBN: " << isbn_ << "\n" << price_ << " " << qty_ << " left." << "\n";
	return display.str(); 
}

void Book::dump(std::ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << "\n"; 
}