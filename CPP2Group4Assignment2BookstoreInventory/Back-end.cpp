#include <iostream>
#include <vector>
#include "book.h"
#include "rapidcsv.h"
#include "Back-end.h"


using namespace std;

vector<Book> readData(string bookTitleToSearch) {
	rapidcsv::Document doc("..\\books.csv", rapidcsv::LabelParams(0, 0));

	vector<Book> filteredBooks;

	int index = 0;
	size_t found;

	while (filteredBooks.size() < filteredBooks.max_size() && index < doc.GetRowCount())
	{
		found = doc.GetCell<string>("Book-Title", index).find(bookTitleToSearch);
		if (found != string::npos)
		{
			Book b(doc.GetRowName(index), doc.GetCell<string>("Book-Title", index), doc.GetCell<string>("Book-Author", index),
				doc.GetCell<string>("Year-Of-Publication", index), doc.GetCell<string>("Publisher", index));

			filteredBooks.push_back(b);
		}
		index++;
	}
	/*
	for (int i = 0; i < 209386; i++) {
		Book b;
		b.setISBN(doc.GetRowName(i));
		b.setTitle(doc.GetCell<string>("Book-Title", i));
		b.setAuthor(doc.GetCell<string>("Book-Author", i));
		b.setYear(doc.GetCell<string>("Year-Of-Publication", i));
		b.setPublisher(doc.GetCell<string>("Publisher", i));
		books.push_back(b);
	}
	*/
	return filteredBooks;
}

