#include "Book.h"

// Since ISBN and Year are technically numbers, they could be stored as unsigned ints.
// Possibly will add some overloaded functions to accomodate for both string and int values if we want or need to do so later.
Book::Book(string ISBN, string Title, string Author, string Year, string Publisher)
{
	setISBN(ISBN);
	setTitle(Title);
	setAuthor(Author);
	setYear(Year);
	setPublisher(Publisher);
}


// Public functions
string Book::getISBN() { return _isbn; }
string Book::getTitle() { return _title; }
string Book::getAuthor() { return _author; }
string Book::getYear() { return _year; }
string Book::getPublisher() { return _publisher; }

// Private functions 
// Once a book object's properties have been set from its constructor, those properties cannot be changed or set again. This may be changed later if needed.
void Book::setISBN(string newISBN) { _isbn = newISBN; }
void Book::setTitle(string newTitle) { _title = newTitle; }
void Book::setAuthor(string newAuthor) { _author = newAuthor; }
void Book::setYear(string newYear) { _year = newYear; }
void Book::setPublisher(string newPublisher) { _publisher = newPublisher; }

