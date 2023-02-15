#include "backEnd.h"
#include <fstream>
#include <cctype>
#include "Utilities.h"

using namespace std;

// This takes in a username and password and checks each row of the users.csv file to find a match
// If a match is found it immedeately returns true. If it goes through the whole file and fails to find a match, it returns false.
bool checkUserPassPair(string username, string password) 
{
	rapidcsv::Document doc("..\\users.csv", rapidcsv::LabelParams(0, 0));
	for (int i = 0; i < doc.GetRowCount(); i++) {
		if (doc.GetRowName(i) == username && doc.GetCell<string>("Password", i) == password) {
			return true;
		}
	}
	return false;
}

// This function is hard coded to look up only the information from the books.csv file.
// If you choose to enter a maxResults value, the recomendation is anything under 100,000.
// Anything higher has an increaded chance of crashes and exceptions so we reduce maxResults back down to 100,000 for safety.
vector<Book> searchBooksByTitle(string bookTitleToSearch, size_t maxResults) 
{
	rapidcsv::Document doc("..\\books.csv", rapidcsv::LabelParams(0, 0));

	vector<Book> filteredBooks;
	if (maxResults <= 0) maxResults = 100000; // maxRseults can't be 0 or negative
	if (maxResults > 100000) maxResults = 100000; // maxResults can't be too high
	filteredBooks.reserve(maxResults); // reserving the memory space is porbably not necessary, but just in case we do so.

	unsigned int index = 0;
	size_t found;

	/*
	// I have no idea what the actual max_size() of filteredBooks will be as when I tested it before 
	// I was able to get over 200,000 results without it breaking, but now I can barely get it over 180,000
	// For now, I'm just gunna say that our absolute maximum limit for our results size is 135,680.
	// I got this number by dividing the total number of books in our file in half, and for our actual default we'll round it down to make it even.
	// So basically, if over 1/3 of the books are making it through the filter, then the filter is probably not specific enough.
	// Either that, or if the user entered a valid maxResults then we merely reached their defined limit.
	*/

	// This loop goes until we fill our results up to our designated max or until we reach the end of the file.
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
	// If we are reserving space for this vector, then we need to make sure to shrink it before returning it.
	filteredBooks.shrink_to_fit();

	return filteredBooks;
}

// Overloaded function to allow the front-end programmer to input the index (int) that they want to start at.
// If the startingIndex is greater than the number of rows in the file, then index is set to 0.
vector<Book> searchBooksByTitle(string bookTitleToSearch, unsigned int startingIndex, size_t maxResults) 
{
	rapidcsv::Document doc("..\\books.csv", rapidcsv::LabelParams(0, 0));

	vector<Book> filteredBooks;
	if (maxResults <= 0) maxResults = 100000; // maxRseults can't be 0 or negative
	if (maxResults > 100000) maxResults = 100000; // maxResults can't be too high
	filteredBooks.reserve(maxResults); // reserving the memory space is porbably not necessary, but just in case we do so.

	if (startingIndex > doc.GetRowCount()) startingIndex = 0;

	unsigned int index = startingIndex;
	size_t found;

	// This loop goes until we fill our results up to our designated max or until we reach the end of the file.
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
	// If we are reserving space for this vector, then we need to make sure to shrink it before returning it.
	filteredBooks.shrink_to_fit();

	return filteredBooks;
}
// Overloaded function to allow the front-end programmer to input the Book object/row that they want to start at.
// This will go through the doc until it finds the matching book ISBN, then it will run as normal starting from that book.
vector<Book> searchBooksByTitle(string bookTitleToSearch, Book bookToStartFrom, size_t maxResults) 
{
	rapidcsv::Document doc("..\\books.csv", rapidcsv::LabelParams(0, 0));

	vector<Book> filteredBooks;
	if (maxResults <= 0) maxResults = 100000; // maxRseults can't be 0 or negative
	if (maxResults > 100000) maxResults = 100000; // maxResults can't be too high
	filteredBooks.reserve(maxResults); // reserving the memory space is porbably not necessary, but just in case we do so.

	size_t index = 0;
	size_t found;

	// This loop takes the ISBN of the entered Book object and attempts to find the row in the file that matches
	// If it finds the book, it sets our index to be the next book in the file.
	// If it doesn't find the book, then index remains at 0. 
	for (size_t i = 0; i < doc.GetRowCount(); i++)
	{
		found = doc.GetRowName(i).find(bookToStartFrom.getISBN());
		if (found != string::npos)
		{
			index = i + 1;
			break;
		}
	}

	// If the index is still 0, that means that the above loop couldn't find the given/inputted Book in the file.
	if (index == 0)
	{
		// As such, the expected outcome is for this scenario to return an empty filteredBooks vector.
		// Setting the index to the end of the file just skips the next while loop to run the last 2 lines of code in this function.
		index = doc.GetRowCount();
	}

	// This loop goes until we fill our results up to our designated max or until we reach the end of the file.
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
	// If we are reserving space for this vector, then we need to make sure to shrink it before returning it.
	filteredBooks.shrink_to_fit();

	return filteredBooks;
}

//functions to add book to inventory
void addBookToInventory(Book bookToAdd)
{
	ofstream inventory;
	bool validInput = true;
	inventory.open("..\\books.csv", ios::app);
	if (inventory.is_open())
	{
		if (!validateISBN(bookToAdd.getISBN()))
		{
			validInput = false;
		};
		if (!validateTitle(bookToAdd.getTitle()))
			validInput = false;
		if (!validateAuthor(bookToAdd.getAuthor()))
			validInput = false;
		if (!validatePubYear(bookToAdd.getYear()))
			validInput = false;
		if (!validatePublisher(bookToAdd.getPublisher()))
			validInput = false;

		if (validInput)
		{
			inventory << bookToAdd.getISBN() << "," << bookToAdd.getTitle() << "," << bookToAdd.getAuthor() << "," << bookToAdd.getYear() << "," << bookToAdd.getPublisher();
			if (!bookToAdd.getDescription().empty())
			{
				inventory << "," << bookToAdd.getDescription();
			}
			if (!bookToAdd.getGenre().empty())
			{
				inventory << "," << bookToAdd.getGenre();
			}
			inventory << endl;
		}
		else
			cout << "Invalid input" << endl;
	}
	else
		cout << "Unable to open file" << endl;
	inventory.close();
}

bool validateISBN(string ISBN)
{
	bool validISBN = true;

	if (ISBN.size() != 13)
		validISBN = false;
	for (unsigned short int i = 0; i < ISBN.size(); i++)
	{
		if (!isdigit(ISBN.at(i)))
			validISBN = false;
	}
	return validISBN;
}

bool validateTitle(string title)
{
	bool validTitle = true;

	if (title.empty())
		validTitle = false;

	/*for (unsigned short int i = 0; i < title.size(); i++)
	{
		if (!isalnum(title.at(i)))
			validTitle = false;
	}*/
	return validTitle;
}

bool validateAuthor(string author)
{
	bool validAuthor = true;

	if (author.empty())
		validAuthor = false;

	/*for (unsigned short int i = 0; i < author.size(); i++)
	{
		if (!isalpha(author.at(i)))
			validAuthor = false;
	}*/
	return validAuthor;
}

bool validatePubYear(string pubYear)
{
	bool validPubYear = true;

	if (!isNumber(pubYear))
		validPubYear = false;
	
	return validPubYear;
}

bool validatePublisher(string publisher)
{
	bool validPublisher = true;

	if (publisher.empty())
		validPublisher = false;

	return validPublisher;
}