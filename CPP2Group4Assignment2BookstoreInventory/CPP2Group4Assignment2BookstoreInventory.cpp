#include "Book.h"
#include <iostream>
#include "Back-end.h"
#include <vector>
#include <string>
#include "rapidcsv.h"

using namespace std;

int main()
{
    //variable declaration
    rapidcsv::Document doc("..\\books.csv", rapidcsv::LabelParams(0, 0));
    string username;
    string password;
    string input;
    vector<Book> database;
    vector<Book> searchResults;
    bool validLogin;
    string searchInput;
    size_t maxResults = 50;
    unsigned int lastLine = 0;
    unsigned int endOfDoc = doc.GetRowCount();
    bool continueLoop = true;
    string continueInput;
    
    // login process
    do
    {
        cout << "Please enter your username: ";
        std::cin >> username;
        cout << "Please enter your password: ";
        std::cin >> password;

        if (userExists(username, password))
        {
            validLogin = true;
        }
        else
        {
            validLogin = false;
            cout << "Invalid username/password, press 'x' to exit or any other key to continue: ";
            std::cin >> input;
            if (toupper(input.at(0)) == 'X')
            {
                break;
            }
        }
    } while (!validLogin);
    
    while (continueLoop)
    {
        //search bar functionality
        cout << "Enter a book title: ";
        std::cin >> searchInput;

        while (lastLine < endOfDoc)
        {
            database = readData(searchInput, lastLine, maxResults);
            if (!database.empty())
            {
                for (unsigned short int i = 0; i < database.size(); i++)
                {
                    searchResults.push_back(database.at(i));
                }
                database.clear();
            }

            //failsafe to prevent a vector of thousands of objects eating all memory
            if (searchResults.size() > 100)
            {
                cout << "Too many results. Terminating search." << endl;
                break;
            }


            lastLine += (unsigned int)maxResults;
        }

        //display search results

        //No hits on search
        if (searchResults.empty())
        {
            cout << "No records were found matching search term '" << searchInput << "'" << endl;
        }
        //display results
        else
        {
            for (unsigned int i = 0; i < searchResults.size(); i++)
            {
                cout << "Book Title: " << searchResults.at(i).getTitle() << endl;
                cout << "Author: " << searchResults.at(i).getAuthor() << endl;
                cout << "Publisher: " << searchResults.at(i).getPublisher() << endl;
                cout << "Publication Year: " << searchResults.at(i).getYear() << endl << endl;
            }

        }
        cout << "Press 'X' to quit, or any other key to continue. ";
        std::cin >> continueInput;

        if (toupper(continueInput.at(0)) == 'X')
            continueLoop = false;
        else
            searchResults.clear();
    }

    




	// string fileName = "..\\books.csv";
	// vector<Book> books = readData("e");

	// cout << "Book Inventory:" << endl;
	// /*for (int i = 0; i < books.size(); i++) {
	// 	cout << "Title: " << books[i].getTitle() << endl;
	// 	cout << "Author: " << books[i].getAuthor() << endl;
	// 	cout << "Publisher: " << books[i].getPublisher() << endl;
	// 	cout << "Year: " << books[i].getYear() << endl;
	// 	cout << "ISBN: " << books[i].getISBN() << endl;
	// 	cout << endl;
	// }*/
	// cout << "Total matches found: " << books.size() << endl;
	return 0;
}