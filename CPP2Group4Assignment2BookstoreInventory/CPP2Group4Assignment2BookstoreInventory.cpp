#include <iostream>
#include <vector>
#include "rapidcsv.h"
#include "book.h"
#include "back-end.h"


using namespace std;

int main() {
	string fileName = "..\\books.csv";
	vector<Book> books = readData("e");

	cout << "Book Inventory:" << endl;
	/*for (int i = 0; i < books.size(); i++) {
		cout << "Title: " << books[i].getTitle() << endl;
		cout << "Author: " << books[i].getAuthor() << endl;
		cout << "Publisher: " << books[i].getPublisher() << endl;
		cout << "Year: " << books[i].getYear() << endl;
		cout << "ISBN: " << books[i].getISBN() << endl;
		cout << endl;
	}*/
	cout << "Total matches found: " << books.size() << endl;
	return 0;
}