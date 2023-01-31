#include "book.h"
#include "rapidcsv.h"


vector<Book> readData(string fileName) {
	rapidcsv::Document doc(fileName, rapidcsv::LabelParams(-1, -1));

	int numRows = doc.GetRowCount();
	int numCols = doc.GetColumnCount();

	vector<Book> books;

	for (int i = 0; i < numRows; i++) {
		Book b;
		b.setISBN(doc.GetCell<string>("ISBN", i));
		b.setTitle(doc.GetCell<string>("Title", i));
		b.setAuthor(doc.GetCell<string>("Author", i));
		b.setYear(doc.GetCell<string>("Year", i));
		b.setPublisher(doc.GetCell<string>("Publisher", i));
		books.push_back(b);
	}
	
	return books;
}








using namespace std;

