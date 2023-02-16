#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const string category, const string name, double price, int qty, const string genre, const string rating) : Product(category, name, price, qty) 
{
	genre_ = genre;
	rating_ = rating; 
}

Movie::~Movie()
{

}

set<string> Movie::keywords() const
{
	set<string> names = parseStringToWords(convToLower(name_));
	set<string> genres = parseStringToWords(convToLower(genre_));
	set<string> keywords = setUnion(names, genres);
	return keywords; 
}

string Movie::displayString() const
{
	stringstream display; 
	display << name_ << "\n" << "Genre: " << genre_ << " Rating: " << rating_ << "\n" << price_ << " " << qty_ << " left." << "\n";
	return display.str(); 
}

void Movie::dump(std::ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << "\n"; 
}