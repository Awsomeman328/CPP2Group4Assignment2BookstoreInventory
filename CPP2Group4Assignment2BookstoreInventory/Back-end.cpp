#include <iostream>
#include <vector>
#include "book.h"
#include "rapidcsv.h"
#include "Back-end.h"


using namespace std;

// This function is hard coded to look up only the information from the books.csv file.
// If you choose to enter a maxResults value, the recomendation is anything under 100,000.
// Anything higher than the default (135680) will be capped to the default to prevent crashes and exceptions.
vector<Book> readData(string bookTitleToSearch, size_t maxResults) {
	rapidcsv::Document doc("..\\books.csv", rapidcsv::LabelParams(0, 0));

	vector<Book> filteredBooks;
	if (maxResults > 135680) maxResults = 135680;
	filteredBooks.reserve(maxResults);

	unsigned int index = 0;
	size_t found;

	// I have no idea what the actual max_size() of filteredBooks will be as when I tested it before 
	// I was able to get over 200,000 results without it breaking, but now I can barely get it over 180,000
	// For now, I'm just gunna say that our absolute maximum limit for our results size is 135,600.
	// I got this number by dividing the total number of books in our file in half.
	// So basically, if over half of the books are making it through the filter, then the filter is not specific enough
	while (filteredBooks.size() < (maxResults) && index < doc.GetRowCount())
	{
		found = doc.GetCell<string>("Book-Title", index).find(bookTitleToSearch);
		if (found != string::npos)
		{
			Book b(doc.GetRowName(index), 
				doc.GetCell<string>("Book-Title", index), 
				doc.GetCell<string>("Book-Author", index),
				doc.GetCell<string>("Year-Of-Publication", index), 
				doc.GetCell<string>("Publisher", index));

			filteredBooks.push_back(b);
		}
		index++;
	}
	filteredBooks.shrink_to_fit();

	return filteredBooks;
}

// Overloaded function to allow the front-end programmer to input the index (int) that they want to start at.
// If the startingIndex is greater than the number of rows in the file, then index is set to 0.
vector<Book> readData(string bookTitleToSearch, unsigned int startingIndex, size_t maxResults) {
	rapidcsv::Document doc("..\\books.csv", rapidcsv::LabelParams(0, 0));

	vector<Book> filteredBooks;
	if (maxResults > 135680) maxResults = 135680;
	filteredBooks.reserve(maxResults);

	if (startingIndex > doc.GetRowCount()) startingIndex = 0;

	unsigned int index = startingIndex;
	size_t found;

	while (filteredBooks.size() < (maxResults) && index < doc.GetRowCount())
	{
		found = doc.GetCell<string>("Book-Title", index).find(bookTitleToSearch);
		if (found != string::npos)
		{
			Book b(doc.GetRowName(index),
				doc.GetCell<string>("Book-Title", index),
				doc.GetCell<string>("Book-Author", index),
				doc.GetCell<string>("Year-Of-Publication", index),
				doc.GetCell<string>("Publisher", index));

			filteredBooks.push_back(b);
		}
		index++;
	}
	filteredBooks.shrink_to_fit();

	return filteredBooks;
}

vector<Book> readData(string bookTitleToSearch, Book bookToStartFrom, size_t maxResults) {
	rapidcsv::Document doc("..\\books.csv", rapidcsv::LabelParams(0, 0));

	vector<Book> filteredBooks;
	if (maxResults > 135680) maxResults = 135680;
	filteredBooks.reserve(maxResults);

	size_t index = 0;
	size_t found;

	for (size_t i = 0; i < doc.GetRowCount(); i++)
	{
		found = doc.GetRowName(i).find(bookToStartFrom.getISBN());
		if (found != string::npos)
		{
			index = i;
			break;
		}
	}

	while (filteredBooks.size() < (maxResults) && index < doc.GetRowCount())
	{
		found = doc.GetCell<string>("Book-Title", index).find(bookTitleToSearch);
		if (found != string::npos)
		{
			Book b(doc.GetRowName(index),
				doc.GetCell<string>("Book-Title", index),
				doc.GetCell<string>("Book-Author", index),
				doc.GetCell<string>("Year-Of-Publication", index),
				doc.GetCell<string>("Publisher", index));

			filteredBooks.push_back(b);
		}
		index++;
	}
	filteredBooks.shrink_to_fit();

	return filteredBooks;
}