#include <iostream>
#include <vector>
#include "book.h"
#include "rapidcsv.h"

using namespace std;



vector<Book> readData(string fileName) {
	rapidcsv::Document doc(fileName, rapidcsv::LabelParams(0, 0));


	vector<Book> books;

	for (int i = 0; i < 22; i++) {
		Book b;
		b.setISBN(doc.GetRowName(i));
		b.setTitle(doc.GetCell<string>("Book-Title", i));
		b.setAuthor(doc.GetCell<string>("Book-Author", i));
		b.setYear(doc.GetCell<string>("Year-Of-Publication", i));
		b.setPublisher(doc.GetCell<string>("Publisher", i));
		books.push_back(b);
	}
	return books;
}


bool userExists(string username, string password) {
	rapidcsv::Document doc("..\\users.csv", rapidcsv::LabelParams(0, 0));
	for (int i = 0; i < doc.GetRowCount(); i++) {
		if (doc.GetCell<string>("Username", i) == username && doc.GetCell<string>("Password", i) == password) {
			return true;
			cout << "Welcome " << username << "!" << endl;
		}
		else
			return false;
	}
}



int main() {
	
	string fileName = "..\\books.csv";
	vector<Book> books = readData(fileName);

	cout << "Book Inventory:" << endl;
	for (int i = 0; i < books.size(); i++) {
		cout << "Book: " << i + 1 << endl;
		cout << "Title: " << books[i].getTitle() << endl;
		cout << "Author: " << books[i].getAuthor() << endl;
		cout << "Publisher: " << books[i].getPublisher() << endl;
		cout << "Year: " << books[i].getYear() << endl;
		cout << "ISBN: " << books[i].getISBN() << endl;
		cout << endl;
	}
	
	string username, password;
	cout << "Enter your username: ";
	cin >> username;
	cout << "Enter your password: ";
	cin >> password;

	if (userExists(username, password)) {
		cout << "Access granted." << endl;
	}
	else {
		cout << "Access denied." << endl;
	}
	
	return 0;
}