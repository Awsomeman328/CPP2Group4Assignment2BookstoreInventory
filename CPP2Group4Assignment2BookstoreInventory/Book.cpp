#include "Book.h"

// Since ISBN and Year are technically numbers, they could be stored as unsigned ints.
// Possibly will add some overloaded functions to accomodate for both string and int values if we want or need to do so later.
Book::Book(string ISBN, string Title, string Author, string Year, string Publisher)
{
	SetISBN(ISBN);
	SetTitle(Title);
	SetAuthor(Author);
	SetYear(Year);
	SetPublisher(Publisher);
}

// Public functions
string Book::GetISBN() { return _isbn; }
string Book::GetTitle() { return _title; }
string Book::GetAuthor() { return _author; }
string Book::GetYear() { return _year; }
string Book::GetPublisher() { return _publisher; }

// Private functions 
// Once a book object's properties have been set from its constructor, those properties cannot be changed or set again. This may be changed later if needed.
void Book::SetISBN(string newISBN) { _isbn = newISBN; }
void Book::SetTitle(string newTitle) { _title = newTitle; }
void Book::SetAuthor(string newAuthor) { _author = newAuthor; }
void Book::SetYear(string newYear) { _year = newYear; }
void Book::SetPublisher(string newPublisher) { _publisher = newPublisher; }