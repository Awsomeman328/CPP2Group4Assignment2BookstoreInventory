#include <iostream>
#include <string>
#include <vector>
#include "rapidcsv.h" // Probably Don't need this
#include "book.h"
#include "backEnd.h"

using namespace std;

int main()
{
    //variable declaration
    string username;
    string password;
    string input;
    vector<Book> searchResults;
    bool validLogin;
    string searchInput;
    unsigned int maxResults = 50;
    unsigned int lastLine = 0;
    bool searchNextPage;
    //size_t endOfDoc = backEnd.getBooksDoc().GetRowCount();
    bool continueLoop = true;
    
    // login process
    do
    {
        cout << "Please enter your username: ";
        cin >> username;
        cout << "Please enter your password: ";
        cin >> password;

        if (checkUserPassPair(username, password))
        {
            validLogin = true;
        }
        else
        {
            validLogin = false;
            cout << "Invalid username/password, press 'x' to exit or any other key to continue: ";
            cin >> input;
            if (toupper(input.at(0)) == 'X')
            {
                break;
            }
        }
    } while (!validLogin);
    cout << "Welcome " << username << "!" << endl;
    cout << endl;
    
    while (continueLoop)
    {
        //search bar functionality
        cout << "Enter a book title: ";
        cin >> searchInput;

        cout << "Loading results, please wait ... " << endl;

        searchResults = searchBooksByTitle(searchInput, lastLine, maxResults);

        /*while (lastLine < endOfDoc)
        {
            database = backEnd.searchBooksByTitle(searchInput, lastLine, maxResults);
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
        }*/

        //display search results

        //No hits on search
        if (searchResults.empty())
        {
            cout << "No records were found matching search term '" << searchInput << "'" << endl;
        }
        //display results
        else
        {
            searchNextPage = true;
            do
            {
                for (unsigned int i = 0; i < searchResults.size(); i++)
                {
                    cout << "Book Title: " << searchResults.at(i).getTitle() << endl;
                    cout << "Author: " << searchResults.at(i).getAuthor() << endl;
                    cout << "Publisher: " << searchResults.at(i).getPublisher() << endl;
                    cout << "Publication Year: " << searchResults.at(i).getYear() << endl << endl;
                }
                if (searchResults.size() == maxResults)
                {
                    cout << "There appears to be more possible search results." << endl;
                    cout << "Press 'Y' to load the next page of results, or any other key to continue.";
                    cin.ignore();
                    cin >> input;

                    if (toupper(input.at(0)) == 'Y')
                    {
                        searchNextPage = true;
                        searchResults = searchBooksByTitle(searchInput, searchResults.back(), maxResults);
                    }
                    else
                    {
                        searchNextPage = false;
                    }
                }
            } while (searchNextPage);
        }
        cout << "Press 'X' to quit, or any other key to continue. ";
        cin >> input;

        if (toupper(input.at(0)) == 'X')
            continueLoop = false;
        else
            searchResults.clear();
    }

	return 0;
}