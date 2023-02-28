#include "backEnd.h"
#include <set>
#include "Book.h"
#include "Utilities.h"

using namespace std;

/* A callback function which is meant to be used with the C API(not the C++ API) of SQLite3
// This function is called once per row in the result set and appends each row to a vector
// The 1st argument is what we return
// The 2nd argument is the number of columns in the result set
// the 3rd argument is the row's data
// the 4th argument is the column names
*/
static int callback(void* list, int argCount, char** argValue, char** azColName) {
	
	/* This is for adding the record returned from the database to this backEnd into this function's first argument.*/
	vector<vector<string>>* head = static_cast<vector<vector<string>>*>(list);
	try {
		vector<string> row = vector<string>();
		for (size_t i = 0; i < argCount; i++)
		{
			if (argValue[i] != NULL) row.push_back(argValue[i]);
			else row.push_back("NULL");
		}
		head->emplace_back(row);
	}
	catch (...) {
		// abort on failure, don't let exception propogate thru sqlite3 call-stack
		return 1;
	}
	return 0;
	
}

// This takes in a username and password and checks each row of the users.csv file to find a match
// If a match is found it immedeately returns true. If it goes through the whole file and fails to find a match, it returns false.
bool checkUserPassPair(string username, string password) 
{
	// This class is a pointer to where our database is. This is how we're going to connect to the database and establish the connection.
	sqlite3* db;

	// This is a char pointer to an error message. When an error occurs &/or there's a problem with the connection, the error message will be stored here.
	char* zErrMsg = 0;

	// This is effectively our return value. This gets used for returning whether or not a function succeeded or failed. 
	// Basically there is an enum state within SQLite and this returns the state of whatever function call we make.
	int rc;

	// The first thing we have to do is open the database file. If the provided file name doesn't exist, it will make a new database file using that name.
	sqlite3_open("bookstoreInventory.db", &db);

	// Where we will store the results from our query
	vector<vector<string>> data;


	string query = "SELECT USERNAME, PASSWORD, IS_ADMIN FROM USERS WHERE USERNAME='" + username + "' AND PASSWORD='" + password + "';";
	const char* charQuery = convertStringToCharPointer(&query);

	rc = sqlite3_exec(db, charQuery, callback, &data, &zErrMsg);

	sqlite3_close(db);

	// If the database returns 1 OR MORE results. ... In the future will want to limit it to make sure that it is ONLY 1 result, but fo rnow its fine.
	if (data.size() >= 1)
	{
		// data[i] selects the row, data[0][i] selects the cell, so this checks if the USERNAME of the first result was returned.
		if (data[0][0] == username)
		{
			return true;
		}
	}
	return false;

}

bool checkUserPassAdminTrio(string username, string password)
{
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	sqlite3_open("bookstoreInventory.db", &db);

	vector<vector<string>> data;


	string query = "SELECT USERNAME, PASSWORD, IS_ADMIN FROM USERS WHERE USERNAME='" + username + "' AND PASSWORD='" + password + "' AND IS_ADMIN=1;";
	const char* charQuery = convertStringToCharPointer(&query);

	rc = sqlite3_exec(db, charQuery, callback, &data, &zErrMsg);

	sqlite3_close(db);

	// If the database returns 1 OR MORE results. ... In the future will want to limit it to make sure that it is ONLY 1 result, but fo rnow its fine.
	if (data.size() >= 1)
	{
		// data[i] selects the row, data[0][i] selects the cell, so this checks if the USERNAME of the first result was returned.
		if (data[0][0] == username)
		{
			return true;
		}
	}
	return false;
}

vector<Book> searchBooksByTitle(string bookTitleToSearch)
{
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;

	sqlite3_open("bookstoreInventory.db", &db);

	vector<vector<string>> data;
	vector<Book> booksToReturn;

	string query = "SELECT * FROM BOOKS WHERE TITLE LIKE '%" + bookTitleToSearch + "%';";
	const char* charQuery = convertStringToCharPointer(&query);

	rc = sqlite3_exec(db, charQuery, callback, &data, &zErrMsg);

	sqlite3_close(db);

	// If the database returns 1 OR MORE results.
	if (data.size() >= 1)
	{
		// data[i] selects the row, data[0][i] selects the cell
		for (size_t i = 0; i < data.size(); i++)
		{
			//ISBN, TITLE, AUTHOR, YEAR, PUBLISHER, DESC(optional, only NULLs so far), GENRE(optional, only NULLs so far), MSRP, QUANTITY
			Book b(data[i][0], data[i][1], data[i][2], stoi(data[i][3]), data[i][4], stod(data[i][7]), stoi(data[i][8]));

			booksToReturn.push_back(b);
		}
	}

	return booksToReturn;
}

//functions to add book to inventory
void addBookToInventory(Book bookToAdd)
{
	//ofstream inventory;
	bool validInput = true;
	//inventory.open("..\\books.csv", ios::app);
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;

	int result = sqlite3_open("bookstoreInventory.db", &db);
	if (result == SQLITE_OK)
	{
		if (!validateISBN(bookToAdd.getISBN()))
			validInput = false;
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
			//inventory << bookToAdd.getISBN() << "," << bookToAdd.getTitle() << "," << bookToAdd.getAuthor() << "," << bookToAdd.getYear() << "," << bookToAdd.getPublisher();
			string query = "INSERT INTO BOOKS (ISBN,TITLE,AUTHOR,PUBLICATION_YEAR,PUBLISHER,DESCRIPTION,GENRE,MSRP,QUANTITY_ON_HAND) " \
				"VALUES ('" + bookToAdd.getISBN() + "', '" + bookToAdd.getTitle() + "', '" + bookToAdd.getAuthor() + "'," \
				" " + to_string(bookToAdd.getYear()) + ", '" + bookToAdd.getPublisher() + "', ";

			if (!bookToAdd.getDescription().empty())
			{
				//inventory << "," << bookToAdd.getDescription();
				query += "'" + bookToAdd.getDescription() + "', ";
			}
			else query += "NULL, ";

			if (!bookToAdd.getGenre().empty())
			{
				//inventory << "," << bookToAdd.getGenre();
				query += "'" + bookToAdd.getGenre() + "',";
			}
			else query += "NULL,";

			query += " " + to_string(bookToAdd.getMSRP()) + ", " + to_string(bookToAdd.getQuantity()) + ");";

			const char* charQuery = convertStringToCharPointer(&query);

			//inventory << endl;
			rc = sqlite3_exec(db, charQuery, callback, 0, &zErrMsg);
		}
		else
			cout << "Invalid input" << endl;
	}
	else
		cout << "Unable to open file" << endl;
	//inventory.close();
	sqlite3_close(db);
}

// Everything in this function has been commented out. We probably need to fix this function so that it works again!
void deleteBookFromInventory(string Title)
{/*
	rapidcsv::Document doc("..\\users.csv", rapidcsv::LabelParams(0, 0));

	unsigned int index = 0;
	size_t found;

	// This loop goes until we reach the end of the file.
	while (index < doc.GetRowCount())
	{
		found = doc.GetCell<string>("Book-Title", index).find(Title);
		if (found != string::npos)
		{
			doc.RemoveRow(index);
		}
		index++;
	}
	doc.Save();*/
	cout << "Deleting from the inventory failed, ... \n";
}

// We may want to change this function to actually check if the export was successful or not and to then return a bool that signifies this status.
// But for now, we can keep it like this.
void exportBookList(vector<Book> bookList)
{
	ofstream booklist;
	booklist.open("exportedBookList.csv");
	booklist << "ISBN,Book-Title,Book-Author,Year-Of-Publication,Publisher,Description,Genre\n";

	for (unsigned short int i = 0; i < bookList.size(); i++)
	{
		booklist << bookList.at(i).getISBN() << "," << bookList.at(i).getTitle() << "," << bookList.at(i).getAuthor() << "," << bookList.at(i).getYear() << "," << bookList.at(i).getPublisher();
		if (!bookList.at(i).getDescription().empty())
		{
			booklist << "," << bookList.at(i).getDescription();
		}
		if (!bookList.at(i).getGenre().empty())
		{
			booklist << "," << bookList.at(i).getGenre();
		}
		booklist << endl;
	}

	booklist.close();
}

bool validateISBN(string ISBN)
{
	bool validISBN = true;

	//if (ISBN.size() != 13)
		//validISBN = false;
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

/*bool validatePubYear(string pubYear)
{
	bool validPubYear = true;

	if (!isNumber(pubYear))
		validPubYear = false;

	return validPubYear;
}*/

bool validatePubYear(int pubYear)
{
	bool validPubYear = (pubYear >= 0);
	return validPubYear;
}

bool validatePublisher(string publisher)
{
	bool validPublisher = true;

	if (publisher.empty())
		validPublisher = false;

	return validPublisher;
}

bool addNewUser(string username, string password, string isAdmin) 
{
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	sqlite3_open("bookstoreInventory.db", &db);
	const char* data = "Callback function called";
	vector<vector<string>> head;

	string query = "INSERT INTO USERS (USERNAME,PASSWORD,IS_ADMIN) " \
		"VALUES ('" + username + "', '" + password + "', " + isAdmin + ");";

	const char* charQuery = convertStringToCharPointer(&query);

	rc = sqlite3_exec(db, charQuery, callback, 0, &zErrMsg);

	// check that the user was created sucessfully
	query = "SELECT USERNAME, PASSWORD, IS_ADMIN FROM USERS WHERE USERNAME='" + username + "' AND PASSWORD='" + password + "' AND IS_ADMIN=" + isAdmin + ";";

	charQuery = convertStringToCharPointer(&query);

	rc = sqlite3_exec(db, charQuery, callback, &head, &zErrMsg);

	sqlite3_close(db);

	// If the database returns 1 OR MORE results. ... In the future will want to limit it to make sure that it is ONLY 1 result, but fo rnow its fine.
	if (head.size() >= 1)
	{
		// data[i] selects the row, data[0][i] selects the cell, so this checks if the USERNAME of the first result was returned.
		if (head[0][0] == username && head[0][1] == password && head[0][2] == isAdmin)
		{
			return true;
		}
	}
	return false;
}

bool changeUsersPassword(string username, string newPassword) 
{
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	sqlite3_open("bookstoreInventory.db", &db);
	const char* data = "Callback function called";
	vector<vector<string>> head;

	string query = "UPDATE USERS SET PASSWORD='" + newPassword + "' WHERE USERNAME='" + username + "';";

	const char* charQuery = convertStringToCharPointer(&query);

	rc = sqlite3_exec(db, charQuery, callback, 0, &zErrMsg);

	// check that the user was created sucessfully
	query = "SELECT USERNAME, PASSWORD, IS_ADMIN FROM USERS WHERE USERNAME='" + username + "' AND PASSWORD='" + newPassword + "';";

	charQuery = convertStringToCharPointer(&query);

	rc = sqlite3_exec(db, charQuery, callback, &head, &zErrMsg);

	sqlite3_close(db);

	// If the database returns 1 OR MORE results. ... In the future will want to limit it to make sure that it is ONLY 1 result, but fo rnow its fine.
	if (head.size() >= 1)
	{
		// data[i] selects the row, data[0][i] selects the cell, so this checks if the USERNAME of the first result was returned.
		if (head[0][0] == username && head[0][1] == newPassword)
		{
			return true;
		}
	}
	return false;
}

bool importBooks() 
{
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	sqlite3_open("bookstoreInventory.db", &db);

	const char* data = "Callback function called";

	string query;
	const char* charQuery;

	size_t i;
	bool isRecordValid;

	rapidcsv::Document doc("import.csv", rapidcsv::LabelParams(0, 0));
	for (i = 0; i < doc.GetRowCount(); i++)
	{
		isRecordValid = true;

		// get data from csv file
		string isbn = doc.GetRowName(i);
		string title = doc.GetCell<string>("Book-Title", i);
		string author = doc.GetCell<string>("Book-Author", i);
		string year = doc.GetCell<string>("Year-Of-Publication", i); // Need to check if valid year
		string publisher = doc.GetCell<string>("Publisher", i);
		string description = doc.GetCell<string>("Description", i);
		string genre = doc.GetCell<string>("Genre", i);
		string msrp = doc.GetCell<string>("MSRP", i); // Need to check if valid price
		string quantity = doc.GetCell<string>("Quantity-On-Hand", i); // need to check if valid quantity

		// Validation ... For now is just assuming that everything is valid, but will want to change this later.
		/*if (year.empty()) // Year can be empty/NULL, but give a warning for it.
		{
			cout << "[WARNING]: Book " << isbn << " titled '" << title << "' at Row #" << i << "'s [year] cell value is empty!" << endl;
			year = "NULL";
			isRecordValid = true;
		}
		else if (!isStringPositiveInt(year))
		{
			cout << "[ERROR]: Book " << isbn << " titled '" << title << "' at Row #" << i << "'s [year] cell value is not a valid positive Int!" << endl;
			isRecordValid = false;
		}
		else if (stoi(year) > 2023)
		{
			cout << "[ERROR]: Book " << isbn << " titled '" << title << "' at Row #" << i << "'s [year] cell value is greater than the current year (2023)!" << endl;
			isRecordValid = false;
		}
		else
		{
			isRecordValid = true;
		}*/

		query = "INSERT INTO BOOKS (ISBN,TITLE,AUTHOR,PUBLICATION_YEAR,PUBLISHER,DESCRIPTION,GENRE,MSRP,QUANTITY_ON_HAND) " \
			"VALUES ('" + isbn + "', '" + title + "', '" + author + "', " + year + ", '" + publisher + "'," \
			" '" + description + "', '" + genre + "', " + msrp + ", " + quantity + "); ";

		// Convert string query into a character pointer
		charQuery = convertStringToCharPointer(&query);

		/* Executing another SQL statement */
		rc = sqlite3_exec(db, charQuery, callback, 0, &zErrMsg);
	}

	// For now, there is no check to see if the import is successful, it is just assumed that it works. ... But we will want to change this later.
	return true;
}

void addNewShopper(string name, string email)
{
	cout << "PLACEHOLDER FUNCTION, PAY NO ATTENTION TO THE MAN BEHIND THE CURTAIN" << endl;
}

void purchaseShoppingList(multiset<Book, bool(*)(const Book&, const Book&)> &shoppingList)
{
	cout << "PLACEHOLDER FUNCTION, PAY NO ATTENTION TO THE MAN BEHIND THE CURTAIN" << endl;
}

double calcTotalPrice(multiset<Book, bool(*)(const Book&, const Book&)> shoppingList)
{
	double totalPrice = 0;
	multiset<Book, bool(*)(const Book&, const Book&)>::iterator shoppingListIterator = shoppingList.begin();
	while (shoppingListIterator != shoppingList.end())
	{
		totalPrice += shoppingListIterator->getMSRP();
		shoppingListIterator++;
	}
	return totalPrice;
}