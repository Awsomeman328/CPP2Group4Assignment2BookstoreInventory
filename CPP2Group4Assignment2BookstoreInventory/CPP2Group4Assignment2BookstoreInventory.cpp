#include "Book.h"
#include <iostream>
#include "Back-end.h"
#include <vector>
<<<<<<< Updated upstream
#include <string>
#include "rapidcsv.h"
=======
#include "book.h"
#include "backEnd.h"
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>
#include "hash_password.h"



>>>>>>> Stashed changes

using namespace std;



int main()
{

<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
    //variable declaration
    rapidcsv::Document doc("..\\books.csv", rapidcsv::LabelParams(0, 0));
    string username;
    string password;
    vector<Book> database;
    vector<Book> searchResults;
    bool validLogin;
    string searchInput;
    size_t maxResults = 50;
    unsigned int lastLine = 0;
<<<<<<< Updated upstream
    unsigned int endOfDoc = doc.GetRowCount();
    bool continueLoop = true;
    string continueInput;

    //TODO: Replace "login check function" with actual function and test
    //login process
    // do
    // {
    //     cout << "Please enter your username: ";
    //     cin >> username;
    //     cout << "Please enter your password: ";
    //     cin >> password;

    //     if (login check function)
    //     {
    //         validLogin = true;
    //     }
    //     else
    //     {
    //         validLogin = false;
    //         cout << "Invalid username/password, press 'x' to exit or any other key to continue: ";
    //         cin >> input;
    //         if (toupper(input.at(0)) == 'X')
    //         {
    //             break;
    //         }
    //     }
    // } while (!validLogin);
=======
    unsigned int maxResults = 50;
    bool isChoosingMorePages = true;
    bool searchNextPage;
	
	

    cout << "Welcome to the bookstore database and inventory!" << endl;
>>>>>>> Stashed changes
    
    while (continueLoop)
    {
        //search bar functionality
        cout << "Enter a book title: ";
        cin >> searchInput;

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

<<<<<<< Updated upstream
            //failsafe to prevent a vector of thousands of objects eating all memory
            if (searchResults.size() > 100)
            {
                cout << "Too many results. Terminating search." << endl;
                break;
            }
=======
                input = "";
                do
                {
                    cout << "Please enter your password: ";
                    getline(cin, input);
                    if (input.empty()) cout << "Inputted password is not vald. [Cannot be empty]" << endl;
                    else
                    {
                        // Need to encrypt input first, then set password equal to it.
						password = hash_password(input);
                        password = input;
                    }
                } while (input.empty());
>>>>>>> Stashed changes


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
        cin >> continueInput;

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