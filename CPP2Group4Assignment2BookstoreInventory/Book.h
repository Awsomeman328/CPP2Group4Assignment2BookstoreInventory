#pragma once

#include <string>

using namespace std;

class Book
{
public:
	Book(string ISBN, string Title, string Author, string Year, string Publisher);
	string GetISBN();
	string GetTitle();
	string GetAuthor();
	string GetYear();
	string GetPublisher();

private:
	string _isbn; // Could be an unsigned int, but since we're getting this info from a string format we'll start it as a string for now. Might change this later.
	string _title;
	string _author;
	string _year; // Could be an unsigned int, but since we're getting this info from a string format we'll start it as a string for now. Might change this later.
	string _publisher;
	void SetISBN(string newISBN);
	void SetTitle(string newTitle);
	void SetAuthor(string newAuthor);
	void SetYear(string newYear);
	void SetPublisher(string newPublisher);
};

