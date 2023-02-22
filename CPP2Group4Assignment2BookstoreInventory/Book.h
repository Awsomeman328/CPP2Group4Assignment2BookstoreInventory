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
    string getTitle();
    string getAuthor();
    string getPublisher();
    string getISBN();
    unsigned int getYear();
    string getDescription();
    string getGenre();
    double getMSRP();
    unsigned int getQuantity();


private:
    string _isbn; // Because these can start with one or more 0's and the last digit can sometimes be an 'X', this has to be a string.
    string _title; // This can't be NULL.
    string _author; // This can't be NULL.
    unsigned int _year; // This must have a value of 0 or higher, the current year number or lower, or NULL.
    string _publisher; // This can't be NULL.
    string _description; // This can be NULL because it could be missing.
    string _genre; // This can be NULL because it could be missing.
    double _msrp; // This can't be less than 0 and can't be NULL. Using a double to get the decimal values from the database and to be more accurate than a float.
    unsigned int _quantity; // This can't be less than 0 and can't be NULL.

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

#endif