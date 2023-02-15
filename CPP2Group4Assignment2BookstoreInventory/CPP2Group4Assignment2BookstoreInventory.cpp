#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include "book.h"
#include "menu.h"
#include "backEnd.h"

using namespace std;

// This function also returns false if the inputted string is empty.
bool isNumber(const string& str)
{
    if (str.empty()) return false;
    for (char const& c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

int getCurrentYear() {
    auto now = chrono::system_clock::now();
    auto time = chrono::system_clock::to_time_t(now);
    tm tm;
    localtime_s(&tm, &time);
    int year = tm.tm_year + 1900;
    return year;
}

int main() {
    bool isValidLogin = false;
    string input;
    Menu loginMenu;
    loginMenu.menuName = "Login Menu";
    loginMenu.addItem("Log In", [&isValidLogin, &input, &loginMenu]() {
        string username;
        string password;

        // Get user's username
        cout << "Enter your Username: ";
        getline(cin, input);

        // Remove any leading or trailing white space
        input = loginMenu.trim(input);

        // Input validation
        while (input.empty()) {
            cout << "Invalid input. Username cannot be empty" << ".\n";
            cout << "Enter your Username: ";
            getline(cin, input);
            input = loginMenu.trim(input);
        }
        username = input;

        // Get user's password
        cout << "Enter your Password: ";
        getline(cin, input);

        // Remove any leading or trailing white space
        input = loginMenu.trim(input);

        // Input validation
        while (input.empty()) {
            cout << "Invalid input. Password cannot be empty" << ".\n";
            cout << "Enter your Password: ";
            getline(cin, input);
            input = loginMenu.trim(input);
        }
        // Need to encrypt input first, then set password equal to it.
        password = input;

        // Validate Login Information
        isValidLogin = checkUserPassPair(username, password);

        // If login info is valid, then set loginMenu.exitThisMenu = true;
        if (isValidLogin)
        {
            cout << "Login Successful!\n";
            loginMenu.continueThisMenu = false;
        }
        else  cout << "Invalid username/password pair\n";

    });

    loginMenu.run();

    if (isValidLogin)
    {
        Menu mainMenu;
        mainMenu.menuName = "Main Menu";
        Menu subMenu;
        subMenu.menuName = "Book List Editing Menu";

        mainMenu.addItem("Search the Database", [&input, &mainMenu]() { // Perform action for Search the Database
            cout << "Searching the Database\n";
            vector<Book> searchResults;

            // Get Book Title
            cout << "Enter a book title: ";
            getline(cin, input);

            // Remove any leading or trailing white space
            input = mainMenu.trim(input);

            // Input validation
            while (input.empty()) {
                cout << "Invalid input. Book title cannot be empty" << ".\n";
                cout << "Enter a book title: ";
                getline(cin, input);
                input = mainMenu.trim(input);
            }

            cout << "\nLoading results, please wait ... \n";
            int maxResults = 100;

            searchResults = searchBooksByTitle(input, 0, maxResults);

            // Display search results
            /*
            // the rest of the code in this MenuItem I am unsure how to reformat to look like the rest of the code in this file, ...
            // BUT we have a deadline we're working towards right now so its staying mostly the same for now!
            // Hopefully we'll be able to adjust this and its functionality later.
            */
            //No matches on search
            if (searchResults.empty())
            {
                cout << "No records were found matching search term \"" << input << "\"\n";
            }
            //display results and check if there are any more results
            else
            {
                bool searchNextPage;
                do
                {
                    // Set this to false at the start of every iteration of this loop.
                    // Only set this to true when the user is both able to and wants to go to the next page of results.
                    searchNextPage = false;

                    // Display the results
                    for (unsigned int i = 0; i < searchResults.size(); i++)
                    {
                        cout << "Book Title: " << searchResults.at(i).getTitle() << "\n";
                        cout << "Author: " << searchResults.at(i).getAuthor() << "\n";
                        cout << "Publisher: " << searchResults.at(i).getPublisher() << "\n";
                        cout << "Publication Year: " << searchResults.at(i).getYear() << "\n";
                        cout << "\n";
                    }
                    cout << "Total results: " << searchResults.size() << "\n";
                    cout << "\n";

                    // Check the size of the results vector. If its size is the same as our given max size,
                    // then there is a chance of there being more results
                    if (searchResults.size() == maxResults)
                    {
                        bool isChoosingMorePages;
                        do
                        {
                            isChoosingMorePages = true;
                            cout << "\n";
                            cout << "There appears to be more possible search results.\n";
                            cout << "1  -  Load the next page of results\n";
                            cout << "2  -  Stop searching for this title\n";
                            getline(cin, input);

                            if (input.empty()) cout << "Inputted value can not be empty.\n";
                            else if (input == "1")
                            {
                                isChoosingMorePages = false;
                                searchNextPage = true;

                                cout << "\n";
                                cout << "Loading additional results, please wait ... \n";
                                cout << "\n";

                                searchResults = searchBooksByTitle(input, searchResults.back(), maxResults);

                                // There is a chance that we get a false positive on having additional results for our search
                                // If that's the case, then searchResults should be empty and we want to break out of the while loop.
                                if (searchResults.empty())
                                {
                                    isChoosingMorePages = false;
                                    searchNextPage = false; // This will let us break out of the loop without using an actual "break" statement.
                                    cout << "No additional records were found matching search term \"" << input << "\"\n";
                                }
                            }
                            else if (input == "2")
                            {
                                isChoosingMorePages = false;
                                searchNextPage = false;
                            }
                            else
                            {
                                cout << "Inputted value {" << input << "} is not valid.\n";
                            }

                            cout << endl;

                        } while (isChoosingMorePages);
                    }

                } while (searchNextPage);
            }
        });
        mainMenu.addItem("Add a book to the Inventory", [&input, &mainMenu]() { // Perform action for Add a book to the Inventory
            cout << "Adding a book to the Inventory\n";
            string title;
            string author;
            string publisher;
            string isbn;
            string year;
            bool isISBNValid = false;
            bool isYearValid = false;

            // Get Book Information
            // Get Book ISBN
            cout << "Enter the book's ISBN: ";
            getline(cin, input);

            // Remove any leading or trailing white space
            input = mainMenu.trim(input);

            // Input validation
            while (input.length() != 13 || !isNumber(input)) {
                cout << "Invalid input. Book ISBN must be exactly 13 numerical digits" << ".\n";
                cout << "Enter the book's ISBN: ";
                getline(cin, input);
                input = mainMenu.trim(input);
            }
            isbn = input;

            // Get Book Title
            cout << "Enter a book title: ";
            getline(cin, input);

            // Remove any leading or trailing white space
            input = mainMenu.trim(input);

            // Input validation
            while (input.empty()) {
                cout << "Invalid input. Book title cannot be empty" << ".\n";
                cout << "Enter a book title: ";
                getline(cin, input);
                input = mainMenu.trim(input);
            }
            title = input;

            // Get Book Author
            cout << "Enter a book author: ";
            getline(cin, input);

            // Remove any leading or trailing white space
            input = mainMenu.trim(input);

            // Input validation
            while (input.empty()) {
                cout << "Invalid input. Book author cannot be empty" << ".\n";
                cout << "Enter a book author: ";
                getline(cin, input);
                input = mainMenu.trim(input);
            }
            author = input;

            // Get Book Year
            cout << "Enter the book's publication year: ";
            getline(cin, input);

            // Remove any leading or trailing white space
            input = mainMenu.trim(input);

            // Input validation
            while (!isNumber(input) || stoi(input) > getCurrentYear()) {
                cout << "Invalid input. Book year must be a valid year (any year from 0 to " << getCurrentYear() << ").\n";
                cout << "Enter the book's publication year: ";
                getline(cin, input);
                input = mainMenu.trim(input);
            }
            year = input;

            // Get Book Publisher
            cout << "Enter a book publisher: ";
            getline(cin, input);

            // Remove any leading or trailing white space
            input = mainMenu.trim(input);

            // Input validation
            while (input.empty()) {
                cout << "Invalid input. Book publisher cannot be empty" << ".\n";
                cout << "Enter a book publisher: ";
                getline(cin, input);
                input = mainMenu.trim(input);
            }
            publisher = input;

            // Make new Book Object
            Book bookToAdd(isbn, title, author, year, publisher);
            cout << "Adding book to Inventory, ..." << ".\n";
            //AddBookToInventory(bookToAdd); // I'm only guessing that this is what the name is going to be.
            cout << "wait, ... this hasn't been implemented yet! \n";

            cout << "Done!\n";
            cout << "\n";
        });
        mainMenu.addItem("Edit your \"book list\"", [&subMenu]() {
            subMenu.run();
        });

        subMenu.addItem("Add a book to your \"book list\" from the inventory", [&input, &subMenu]() {
            cout << "Adding a book to your \"book list\" from the inventory\n"; // Don't forget to also remove the book from the inventory

            // Get Book ISBN
            cout << "Enter the ISBN of the book you wish to add: ";
            getline(cin, input);

            // Remove any leading or trailing white space
            input = subMenu.trim(input);

            // Input validation
            while (input.length() != 13 || !isNumber(input)) {
                cout << "Invalid input. Book ISBN must be exactly 13 numerical digits" << ".\n";
                cout << "Enter the ISBN of the book you wish to add: ";
                getline(cin, input);
                input = subMenu.trim(input);
            }

            // Search the database/inventory for the given ISBN.
            cout << "\nLoading results, please wait ... \n";

            vector<Book> searchResults;// = searchBooksByISBN(input); // I'm assuming that this is a function that will be avalible for us to use,
            // but if that's not the case then this will have to change
            cout << "wait, ... this hasn't been implemented yet! \n";

            // Display search results
            //No matches on search
            if (searchResults.empty())
            {
                cout << "No records were found matching search term \"" << input << "\"\n";
            }
            //display results and check if there are any more results
            else if (searchResults.size() > 1)
            {
                cout << "[Error]: Two or more records were found matching search term \"" << input << "\"\n";
                cout << "Please contact your database administarator to inform them of this problem\n";
            }
            else
            {
                cout << "Are you sure this is the book you wish to add to your list?\n";
                cout << "Book Title: " << searchResults.at(0).getTitle() << "\n";
                cout << "Author: " << searchResults.at(0).getAuthor() << "\n";
                cout << "Publisher: " << searchResults.at(0).getPublisher() << "\n";
                cout << "Publication Year: " << searchResults.at(0).getYear() << "\n";
                cout << "\n"; // Get Book ISBN
                cout << "Enter \"Yes\" to confirm or \"No\" to cancel : ";
                getline(cin, input);

                // Remove any leading or trailing white space
                input = subMenu.trim(input);

                // Input validation
                while (input.empty() && ( input != "Yes" || input != "No") ) {
                    cout << "Invalid input. Answer needs to be either \"Yes\" or \"No\".\n";
                    cout << "Enter \"Yes\" to confirm or \"No\" to cancel : ";
                    getline(cin, input);
                    input = subMenu.trim(input);
                }
            }

            if (input == "Yes")
            {
                // Add the book in searchResults.at(0) to their "book list" (should be stored in the back end)
                // Once the book is added, delete the row that contains that book in the .csv file.
                cout << "wait, ... this hasn't been implemented yet! \n";
            }
        });
        subMenu.addItem("Print your \"book list\" to the screen", []() { // Don't forget to include the total number of items in the list
            cout << "Printing your \"book list\" to the screen\n";

            // Get book list.

            cout << "wait, ... this hasn't been implemented yet! \n";
            // Iterate through the book list and print out each book's ISBN, Title, and Author
            /*
            for (unsigned int i = 0; i < ???.size(); i++)
            {
                cout << "ISBN: " << ???.at(i).getISBN() << "\n";
                cout << "Title: " << ???.at(i).getTitle() << "\n";
                cout << "Author: " << ???.at(i).getAuthor() << "\n";
                cout << "\n";
            }
            */
            // After printing all the books to the screen, print out the total number of items in the book list
            // cout << "Total number of books: " << ???.length() << "\n";
            cout << "\n";
        });
        subMenu.addItem("Export your \"book list\" to a .csv file", []() {
            cout << "Exporting your \"book list\" to a .csv file\n";

            // Get the book list.
            cout << "wait, ... this hasn't been implemented yet! \n";

            // Create a new .csv file

            // Iterate through the book list and write each book to the new .csv file 
            // The ordering of the columns is: ISBN, Book-Title, Book-Author, Year-Of-Publication, Publisher

            // After saving the external file with all of the books from the books list, remove all of the books from the books list.

        });

        mainMenu.run();

        //If there are any books left in the user's "book list" then add them back to the .csv database/inventory and remove them from the list.

    }

    return 0;
}
