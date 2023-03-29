#include "book.h"

// Constructors
Book::Book(string ISBN, string Title, string Author, unsigned int Year, string Publisher,
    double MSRP, unsigned int Quantity)
{
    bool result = true;

    // Try to set all of the appropreate values for this book. Each of these setters first tests if the values are valid.
    // If any of them return false, then set isValid false. Otherwise, set it to true.
    if (!setISBN(ISBN) || !setTitle(Title) || !setAuthor(Author) || !setYear(Year) || !setPublisher(Publisher) || !setMSRP(MSRP) || !setQuantity(Quantity))
    {
        result = false;
    }

    // This marks if this Book object is valid or not.
    setIsValid(result);
}
Book::Book(string ISBN, string Title, string Author, unsigned int Year, string Publisher,
    string Description, string Genre, double MSRP, unsigned int Quantity)
{
    bool result = true;

    // Try to set all of the appropreate values for this book. Each of these setters first tests if the values are valid.
    // If any of them return false, then set isValid false. Otherwise, set it to true.
    if (!setISBN(ISBN) || !setTitle(Title) || !setAuthor(Author) || !setYear(Year) || !setPublisher(Publisher) ||
            !setDescription(Description) || !setGenre(Genre) || !setMSRP(MSRP) || !setQuantity(Quantity))
    {
        result = false;
    }

    // This marks if this Book object is valid or not.
    setIsValid(result);
}

// Public functions
// Getters
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
// Validators
bool Book::validateISBN(string ISBN)
{
    if (ISBN.c_str() == NULL || ISBN.empty() || ISBN.size() > 16)
        return false;

    for (unsigned short int i = 0; i < ISBN.size(); i++)
    {
        if (!isdigit(ISBN.at(i)) && (ISBN.at(i) != 'X'))
            return false;
    }

    return true;
}
bool Book::validateTitle(string title)
{
    bool validTitle = true;

    if (title.c_str() == NULL || title.empty())
        validTitle = false;

    return validTitle;
}
bool Book::validateAuthor(string author)
{
    bool validAuthor = true;

    if (author.c_str() == NULL || author.empty()|| author.size() >255)
        validAuthor = false;

    return validAuthor;
}
bool Book::validatePubYear(int pubYear)
{
    bool validPubYear = (pubYear >= 0 && pubYear <= 2023);
    return validPubYear;
}
bool Book::validatePublisher(string publisher)
{
    bool validPublisher = !(publisher.c_str() == NULL) && !publisher.empty() && publisher.size() <= 255;
    return validPublisher;
}
bool Book::validateDescription(string description)
{
    //bool validDescription = description.size() <= 255;
    return true;
}
bool Book::validateGenre(string genre)
{
    bool validGenre = genre.c_str() == NULL || genre.size() <= 255;
    return validGenre;
}
bool Book::validateMSRP(double msrp)
{
    bool validMsrp = (msrp != NULL && msrp >= 0);
    return validMsrp;
}
bool Book::validateQuantity(int quantity)
{
    bool validQuantity = (quantity != NULL && quantity >= 0);
    return validQuantity;
}


// Private functions
// Once a book object's properties have been set from its constructor, those properties cannot be changed or set again. This may be changed later if needed.
void Book::setIsValid(bool b) { _isValid = b; }
bool Book::setISBN(string newISBN)
{
    if (validateISBN(newISBN))
    {
        _isbn = newISBN;
        return true;
    }
    return false;
}
bool Book::setTitle(string newTitle)
{
    if (validateTitle(newTitle))
    {
        _title = newTitle;
        return true;
    }
    return false;
}
bool Book::setAuthor(string newAuthor)
{
    if (validateAuthor(newAuthor))
    {
        _author = newAuthor;
        return true;
    }
    return false;
}
bool Book::setYear(unsigned int newYear)
{
    if (validatePubYear(newYear))
    {
        _year = newYear;
        return true;
    }
    return false;
}
bool Book::setPublisher(string newPublisher)
{
    if (validatePublisher(newPublisher))
    {
        _publisher = newPublisher;
        return true;
    }
    return false;
}
bool Book::setDescription(string newDescription)
{
    if (validateDescription(newDescription))
    {
        _description = newDescription;
        return true;
    }
    return false;
}
bool Book::setGenre(string newGenre)
{
    if (validateGenre(newGenre))
    {
        _genre = newGenre;
        return true;
    }
    return false;
}
bool Book::setMSRP(double newMSRP)
{
    if (validateMSRP(newMSRP))
    {
        _msrp = newMSRP;
        return true;
    }
    return false;
}
bool Book::setQuantity(unsigned int newQuantity)
{
    if (validateQuantity(newQuantity))
    {
        _quantity = newQuantity;
        return true;
    }
    return false;
}
