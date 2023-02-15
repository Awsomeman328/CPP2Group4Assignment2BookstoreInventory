#include <iostream>
#include <string>
#include <vector>
#include "book.h"
#include "backEnd.h"

using namespace std;

int main()
{
    //variable declaration
    string username;
    string password;
    string input;
    bool validLogin = false;
    bool continueLogingIn = true;
    bool confirmExitingChoice = false;
    bool isSearchValid = false;
    bool checkingSearchResults = true;
    bool continueSearchingDatabase = true;
    bool continueLoop = true;
    string searchInput;
    vector<Book> searchResults;
    unsigned int lastLine = 0;
    unsigned int maxResults = 50;
    bool isChoosingMorePages = true;
    bool searchNextPage;

    cout << "Welcome to the bookstore database and inventory!" << endl;
    
    // login menu
    do
    {
        cout << endl;
        cout << "What would you like to do? (To choose an option, input the number and press the Enter key)" << endl;
        cout << "1  -  Log In" << endl;
        cout << "0  -  Exit Program" << endl;

        getline(cin, input);
        if (input.empty()) cout << "Inputted value can not be empty.";
        else if (input == "1")
        {
            // login process
            do
            {
                cout << "Now starting the LogIn process, ..." << endl;
                input = "";
                continueLogingIn = true;
                do
                {
                    cout << "Please enter your username: ";
                    getline(cin, input);
                    if (input.empty()) cout << "Inputted username is not vald. [Cannot be empty]" << endl;
                    else username = input;

                } while (input.empty());

                input = "";
                do
                {
                    cout << "Please enter your password: ";
                    getline(cin, input);
                    if (input.empty()) cout << "Inputted password is not vald. [Cannot be empty]" << endl;
                    else
                    {
                        // Need to encrypt input first, then set password equal to it.
                        password = input;
                    }
                } while (input.empty());

                validLogin = checkUserPassPair(username, password);

                if (validLogin)
                {
                    cout << "Login Successful!" << endl;
                    continueLogingIn = false;
                }
                else
                {
                    do
                    {
                        input = "";
                        cout << endl;
                        cout << "Invalid username/password pair, would you like to try again or go back to the main menu?" << endl;
                        cout << "1  -  Yes, let me try logging in again" << endl;
                        cout << "0  -  No, return to menu" << endl;
                        getline(cin, input);
                        if (input.empty()) cout << "Inputted value can not be empty." << endl;
                        else if (input == "1")
                        {
                            cout << "Restarting Log In Process ..." << endl;
                            confirmExitingChoice = true;
                        }
                        else if (input == "0")
                        {
                            cout << "Cancelling Log In Process, returning to menu, ..." << endl;
                            confirmExitingChoice = true;
                            continueLogingIn = false;
                        }
                        else
                        {
                            cout << "Inputted value {" << input << "} is not valid." << endl;
                        }
                    } while (!confirmExitingChoice);
                }
            } while (continueLogingIn);
        }
        else if (input == "0")
        {
            // Exiting Program
            do
            {
                input = "";
                confirmExitingChoice = false;
                cout << endl;
                cout << "Are you sure that you want to exit and close this program?" << endl;
                cout << "1  -  Yes, please exit and close" << endl;
                cout << "0  -  No, return to menu" << endl;
                getline(cin, input);
                if (input.empty()) cout << "Inputted value can not be empty." << endl;
                else if (input == "1")
                {
                    cout << "Now Exiting Program" << endl;
                    exit(0);
                }
                else if (input == "0")
                {
                    cout << "Cancelling Exiting Program, returning to menu, ..." << endl;
                    confirmExitingChoice = true;
                }
                else
                {
                    cout << "Inputted value {" << input << "} is not valid." << endl;
                }
            } while (!confirmExitingChoice);
        }
        else
        {
            cout << "Inputted value {" << input << "} is not valid." << endl;
        }
    } while (!validLogin);

    cout << "Welcome " << username << "!" << endl;
    cout << endl;
    
    while (continueLoop)
    {
        input = "";
        cout << endl;
        cout << "What would you like to do?" << endl;
        cout << "1  -  Search the Database" << endl;
        cout << "2  -  Add a book to the Inventory" << endl;
        cout << "3  -  Add a book to a list from the Inventory" << endl;
        cout << "0  -  Exit Program" << endl;

        getline(cin, input);
        if (input.empty()) cout << "Inputted value can not be empty." << endl;
        else if (input == "1")
        {
            // 1 Searching the Database
            do
            {
                continueSearchingDatabase = true;
                do
                {
                    isSearchValid = false;
                    input = "";
                    cout << "Enter a book title: ";
                    getline(cin, input);
                    if (input.empty()) cout << "Inputted value can not be empty." << endl;
                    else if (input.length() < 3) cout << "Inputted value must be at least 3 characters long" << endl;
                    else isSearchValid = true;

                } while (!isSearchValid);

                searchInput = input;

                cout << endl;
                cout << "Loading results, please wait ... " << endl;
                cout << endl;

                searchResults = searchBooksByTitle(searchInput, lastLine, maxResults);

                //display search results

                //No matches on search
                if (searchResults.empty())
                {
                    cout << "No records were found matching search term '" << searchInput << "'" << endl;
                }
                //display results and check if there are any more results
                else
                {
                    do
                    {
                        // Set this to false at the start of every iteration of this loop. 
                        // Only set this to true when the user is both able to and wants to go to the next page of results.
                        searchNextPage = false;

                        // Display the results
                        for (unsigned int i = 0; i < searchResults.size(); i++)
                        {
                            cout << "Book Title: " << searchResults.at(i).getTitle() << endl;
                            cout << "Author: " << searchResults.at(i).getAuthor() << endl;
                            cout << "Publisher: " << searchResults.at(i).getPublisher() << endl;
                            cout << "Publication Year: " << searchResults.at(i).getYear() << endl;
                            cout << endl;
                        }
                        cout << "Total results: " << searchResults.size() << endl;
                        cout << endl;

                        // Check the size of the results vector. If its size is the same as our given max size, 
                        // then there is a chance of there being more results
                        if (searchResults.size() == maxResults)
                        {
                            do
                            {
                                isChoosingMorePages = true;
                                cout << endl;
                                cout << "There appears to be more possible search results." << endl;
                                cout << "1  -  Load the next page of results" << endl;
                                cout << "0  -  Stop searching for this title" << endl;
                                getline(cin, input);

                                if (input.empty()) cout << "Inputted value can not be empty." << endl;
                                else if (input == "1")
                                {
                                    isChoosingMorePages = false;
                                    searchNextPage = true;

                                    cout << endl;
                                    cout << "Loading additional results, please wait ... " << endl;
                                    cout << endl;

                                    searchResults = searchBooksByTitle(searchInput, searchResults.back(), maxResults);

                                    // There is a chance that we get a false positive on having additional results for our search
                                    // If that's the case, then searchResults should be empty and we want to break out of the while loop.
                                    if (searchResults.empty())
                                    {
                                        isChoosingMorePages = false;
                                        searchNextPage = false; // This will let us break out of the loop without using an actual "break" statement.
                                        cout << "No additional records were found matching search term '" << searchInput << "'" << endl;
                                    }
                                }
                                else if (input == "0")
                                {
                                    isChoosingMorePages = false;
                                    searchNextPage = false;
                                }
                                else
                                {
                                    cout << "Inputted value {" << input << "} is not valid." << endl;
                                }

                                cout << endl;

                            } while (isChoosingMorePages);
                        }

                    } while (searchNextPage);
                }

                // Ask user if they wish to continue searching the database or exit to the main menu.
                do
                {
                    checkingSearchResults = true;
                    input = "";
                    cout << endl;
                    cout << "Would you like to search the database again or return back to the main menu? " << endl;
                    cout << "1  -  Yes, let me search the database again" << endl;
                    cout << "0  -  No, return to main menu" << endl;
                    getline(cin, input);
                    if (input.empty()) cout << "Inputted value can not be empty." << endl;
                    else if (input == "1")
                    {
                        cout << "Restarting searching Process ..." << endl;
                        checkingSearchResults = false;
                    }
                    else if (input == "0")
                    {
                        cout << "Cancelling searching Process, returning to menu, ..." << endl;
                        checkingSearchResults = false;
                        continueSearchingDatabase = false;
                    }
                    else
                    {
                        cout << "Inputted value {" << input << "} is not valid." << endl;
                    }
                } while (checkingSearchResults);

                cout << endl;
                searchResults.clear();

            } while (continueSearchingDatabase);
        }
        else if (input == "2")
        {
            // 2 Adding a book to the Inventory
            cout << "This functionality is currently unavalible, ..." << endl;
            cout << endl;
        }
        else if (input == "3")
        {
            // 3 Adding a book to a list from the Inventory
            cout << "This functionality is currently unavalible, ..." << endl;
            cout << endl;
        }
        else if (input == "0")
        {
            // 0 Exiting Program
            do
            {
                input = "";
                confirmExitingChoice = false;
                cout << endl;
                cout << "Are you sure that you want to exit and close this program?" << endl;
                cout << "1  -  Yes, please exit and close" << endl;
                cout << "0  -  No, return to menu" << endl;
                getline(cin, input);
                if (input.empty()) cout << "Inputted value can not be empty." << endl;
                else if (input == "1")
                {
                    cout << "Now Exiting Program" << endl;
                    exit(0);
                }
                else if (input == "0")
                {
                    cout << "Cancelling Exiting Program, returning to menu, ..." << endl;
                    confirmExitingChoice = true;
                }
                else
                {
                    cout << "Inputted value {" << input << "} is not valid." << endl;
                }
            } while (!confirmExitingChoice);
        }
        else
        {
            cout << "Inputted value {" << input << "} is not valid." << endl;
        }
    }

	return 0;

}