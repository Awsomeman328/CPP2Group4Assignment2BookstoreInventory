#include "Book.h"

class Book
{
public:
	Book();
	~Book();

private:
	string ISBN;
	string title;
	string suthor;
	string year;
	string publisher;
};

Book::Book()
{
}

Book::~Book()
{
}