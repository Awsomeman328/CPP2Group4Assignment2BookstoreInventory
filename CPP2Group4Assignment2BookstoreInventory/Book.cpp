#include "book.h"

// 
Book::Book(string ISBN, string Title, string Author, unsigned int Year, string Publisher, 
	double MSRP, unsigned int Quantity)
{
	setISBN(ISBN);
	setTitle(Title);
	setAuthor(Author);
	setYear(Year);
	setPublisher(Publisher);
	setMSRP(MSRP);
	setQuantity(Quantity);
}
Book::Book(string ISBN, string Title, string Author, unsigned int Year, string Publisher, 
	string Description, string Genre, double MSRP, unsigned int Quantity)
{
	setISBN(ISBN);
	setTitle(Title);
	setAuthor(Author);
	setYear(Year);
	setPublisher(Publisher);
	setDescription(Description);
	setGenre(Genre);
	setMSRP(MSRP);
	setQuantity(Quantity);
}

// Public functions
string Book::getISBN() const { return _isbn; }
string Book::getTitle() const { return _title; }
string Book::getAuthor() const { return _author; }
unsigned int Book::getYear() const { return _year; }
string Book::getPublisher() const { return _publisher; }
string Book::getDescription() const { return _description; }
string Book::getGenre() const { return _genre; }
double Book::getMSRP() const { return _msrp; }
unsigned int Book::getQuantity() const { return _quantity; }

// Private functions 
// Once a book object's properties have been set from its constructor, those properties cannot be changed or set again. This may be changed later if needed.
void Book::setISBN(string newISBN) { _isbn = newISBN; }
void Book::setTitle(string newTitle) { _title = newTitle; }
void Book::setAuthor(string newAuthor) { _author = newAuthor; }
void Book::setYear(unsigned int newYear) { _year = newYear; }
void Book::setPublisher(string newPublisher) { _publisher = newPublisher; }
void Book::setDescription(string newDescription) { _description = newDescription; }
void Book::setGenre(string newGenre) { _genre = newGenre; }
void Book::setMSRP(double newMSRP) { _msrp = newMSRP; }
void Book::setQuantity(unsigned int newQuantity) { _quantity = newQuantity; }
