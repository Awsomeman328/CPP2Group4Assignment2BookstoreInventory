#include <iostream>
#include <vector>
#include "book.h"
#include "rapidcsv.h"


using namespace std;

vector<Book> readData(string fileName) {
	rapidcsv::Document doc(fileName, rapidcsv::LabelParams(0, 0));

	int numRows = doc.GetRowCount();
	int numCols = doc.GetColumnCount();

	vector<Book> books;

	for (int i = 0; i < 100; i++) {
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

int main() {
	string fileName = "..\\books.csv";
	vector<Book> books = readData(fileName);

	cout << "Book Inventory:" << endl;
	for (int i = 0; i < books.size(); i++) {
		cout << "Title: " << books[i].getTitle() << endl;
		cout << "Author: " << books[i].getAuthor() << endl;
		cout << "Publisher: " << books[i].getPublisher() << endl;
		cout << "Year: " << books[i].getYear() << endl;
		cout << "ISBN: " << books[i].getISBN() << endl;
		cout << endl;
	}
	return 0;
}