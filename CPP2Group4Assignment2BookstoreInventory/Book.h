#pragma once
#include <string>

using namespace std;

class Book {
public:
    Book() {}
    Book(string ISBN, string Title, string Author, string Year, string Publisher);
    string getTitle();
    string getAuthor();
    string getPublisher();
    string getISBN();
    string getYear();

private:
    string _title;
    string _author;
    string _publisher;
    string _isbn;
    string _year;

    void setISBN(string i);
    void setTitle(string t);
    void setAuthor(string a);
    void setPublisher(string p);
    void setYear(string y);
};