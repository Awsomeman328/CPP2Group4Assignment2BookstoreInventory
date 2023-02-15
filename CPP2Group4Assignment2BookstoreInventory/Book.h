#pragma once
#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book 
{
public:
    Book(string ISBN, string Title, string Author, string Year, string Publisher, string Description, string Genre);
    string getTitle();
    string getAuthor();
    string getPublisher();
    string getISBN();
    string getYear();
    string getDescription();
    string getGenre();

private:
    string _title;
    string _author;
    string _publisher;
    string _isbn;
    string _year;
    string _description;
    string _genre;

    void setISBN(string i);
    void setTitle(string t);
    void setAuthor(string a);
    void setPublisher(string p);
    void setYear(string y);
    void setDescription(string d);
    void setGenre(string g);
};

#endif