#pragma once
#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book
{
public:
    Book(string ISBN, string Title, string Author, unsigned int Year, string Publisher,
        double MSRP, unsigned int Quantity);
    Book(string ISBN, string Title, string Author, unsigned int Year, string Publisher,
        string Description, string Genre, double MSRP, unsigned int Quantity);
    bool getIsValid() const;
    string getTitle() const;
    string getAuthor() const;
    string getPublisher() const;
    string getISBN() const;
    unsigned int getYear() const;
    string getDescription() const;
    string getGenre() const;
    double getMSRP() const;
    unsigned int getQuantity() const;


private:
    bool _isValid; // This flags for if this Book object is a valid Book. This gets set in the constructor and never changed.
    string _isbn; // This can't be NULL and must have values containing only numbers and the letter X and is 16 characters or less.
    string _title; // This can't be NULL.
    string _author; // This can’t be a NULL and must be 255 characters or less.
    unsigned int _year; // This can’t be NULL and must be 0 or higher and 2023 or lower.
    string _publisher; // This can’t be a NULL and must be 255 characters or less.
    string _description; // This CAN be NULL or a valid string.
    string _genre; // This CAN be NULL or a valid string with 255 characters or less.
    double _msrp; // This can’t be NULL and must be 0 or higher. Using a double to get the decimal values from the database and to be more accurate than a float.
    unsigned int _quantity; // This can’t be NULL and must be 0 or higher.

    void setIsValid(bool b);
    void setISBN(string i);
    void setTitle(string t);
    void setAuthor(string a);
    void setPublisher(string p);
    void setYear(unsigned int y);
    void setDescription(string d);
    void setGenre(string g);
    void setMSRP(double m);
    void setQuantity(unsigned int q);
};

#endif // BOOK_H
