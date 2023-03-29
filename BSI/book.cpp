#include "book.h"

// Constructors
Book::Book(string ISBN, string Title, string Author, unsigned int Year, string Publisher,
    double MSRP, unsigned int Quantity)
{
    bool result = false;

    // After changing these to return bools if they suceeded or not, if any of these return false make the result false.
    // Make sure to not accidentally set result back to true if a later set function returns true.
    setISBN(ISBN);
    setTitle(Title);
    setAuthor(Author);
    setYear(Year);
    setPublisher(Publisher);
    setMSRP(MSRP);
    setQuantity(Quantity);

    // This marks if this Book object is valid or not.
    setIsValid(result);
}
Book::Book(string ISBN, string Title, string Author, unsigned int Year, string Publisher,
    string Description, string Genre, double MSRP, unsigned int Quantity)
{
    bool result = false;

    // After changing these to return bools if they suceeded or not, if any of these return false make the result false.
    // Make sure to not accidentally set result back to true if a later set function returns true.
    setISBN(ISBN);
    setTitle(Title);
    setAuthor(Author);
    setYear(Year);
    setPublisher(Publisher);
    setDescription(Description);
    setGenre(Genre);
    setMSRP(MSRP);
    setQuantity(Quantity);

    // This marks if this Book object is valid or not.
    setIsValid(result);
}

// Public functions
bool Book::getIsValid() const { return _isValid; }
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
void Book::setIsValid(bool b) { _isValid = b; }
void Book::setISBN(string newISBN) { _isbn = newISBN; }
void Book::setTitle(string newTitle) { _title = newTitle; }
void Book::setAuthor(string newAuthor) { _author = newAuthor; }
void Book::setYear(unsigned int newYear) { _year = newYear; }
void Book::setPublisher(string newPublisher) { _publisher = newPublisher; }
void Book::setDescription(string newDescription) { _description = newDescription; }
void Book::setGenre(string newGenre) { _genre = newGenre; }
void Book::setMSRP(double newMSRP) { _msrp = newMSRP; }
void Book::setQuantity(unsigned int newQuantity) { _quantity = newQuantity; }
