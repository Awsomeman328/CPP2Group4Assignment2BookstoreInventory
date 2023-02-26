#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <set>
#include "book.h"
#include "menu.h"
#include "Utilities.h"
#include "backEnd.h"
#include "rapidcsv.h"
#include "hash_password.h"

using namespace std;

int main() {
    bool isValidLogin = false;
    bool isValidAdmin = false;
    string input;

    Menu loginMenu;
    loginMenu.setMenuName("Login Menu");
    Menu adminMenu;
    adminMenu.setMenuName("Admin Menu");

    adminMenu.addItem("Add a new User", [&input]() {
        string username;
        string password;
        string isAdmin;
        bool isValidUser;

        // Get user's username
        cout << "Enter new Username: ";
        getline(cin, input);

        // Remove any leading or trailing white space
        input = trim(input);

        // Input validation
        while (input.empty()) {
            cout << "Invalid input. Username cannot be empty" << ".\n";
            cout << "Enter new Username: ";
            getline(cin, input);
            input = trim(input);
        }
        username = input;

        // Get user's password
        cout << "Enter user's Password: ";
        getline(cin, input);

        // Remove any leading or trailing white space
        input = trim(input);

        // Input validation
        while (input.empty()) {
            cout << "Invalid input. Password cannot be empty" << ".\n";
            cout << "Enter user's Password: ";
            getline(cin, input);
            input = trim(input);
        }
        // Need to encrypt input first, then set password equal to it.
        input = hash_password(input);
        password = input;

        // Get if the user is an Admin or not
        cout << "Enter user's admin status (0 or 1): ";
        getline(cin, input);

        // Remove any leading or trailing white space
        input = trim(input);

        // Input validation
        while (input.empty() && input != "0" && input != "1") {
            cout << "Invalid input. Admin status must be either a 0 or 1" << ".\n";
            cout << "Enter user's admin status (0 or 1): ";
            getline(cin, input);
            input = trim(input);
        }
        isAdmin = input;

        isValidUser = addNewUser(username, password, isAdmin);

        if (isValidUser)
        {
            cout << "New user successfuly created!" << endl;
        }
        else cout << "[ERROR]: New user could not be created! Please contact your database suppervisor for assistance." << endl;
    });
    adminMenu.addItem("Change a User's Password", [&input]() {
        string username;
        string password;
        bool isValidUser;

    // Get user's username
    cout << "Enter in Username: ";
    getline(cin, input);

    // Remove any leading or trailing white space
    input = trim(input);

    // Input validation
    while (input.empty()) {
        cout << "Invalid input. Username cannot be empty" << ".\n";
        cout << "Enter in Username: ";
        getline(cin, input);
        input = trim(input);
    }
    username = input;

    // Get user's password
    cout << "Enter user's Password: ";
    getline(cin, input);

    // Remove any leading or trailing white space
    input = trim(input);

    // Input validation
    while (input.empty()) {
        cout << "Invalid input. Password cannot be empty" << ".\n";
        cout << "Enter user's Password: ";
        getline(cin, input);
        input = trim(input);
    }
    // Need to encrypt input first, then set password equal to it.
    input = hash_password(input);
    password = input;

    isValidUser = changeUsersPassword(username, password);

    if (isValidUser)
    {
        cout << "New password successfuly changed!" << endl;
    }
    else cout << "[ERROR]: New password could not be changed! Please contact your database suppervisor for assistance." << endl;
    });
    adminMenu.addItem("Import a file into the database", [&input]() {
        cout << "Please ensure that the file you want to import is a .csv file named 'import.csv' and is in the same directory as this file." << endl;
        cout << "Please confirm that this is the case [y/n]: ";
        getline(cin, input);

        // Remove any leading or trailing white space
        input = trim(input);

        // Input validation
        while (input.empty() || (input != "y" && input != "n")) {
            cout << "Invalid input. " << ".\n";
            cout << "Please confirm that the above is true [y/n]: ";
            getline(cin, input);
            input = trim(input);
        }

        if (input == "y")
        {
            if (importBooks())
            {
                cout << "Import successful!" << endl;
            }
            else cout << "[ERROR]: Import could not be performed! Please contact your database suppervisor for assistance." << endl;
        }
    });

    loginMenu.addItem("Log In", [&isValidLogin, &input, &loginMenu]() {
        string username;
        string password;

        // Get user's username
        cout << "Enter your Username: ";
        getline(cin, input);

        // Remove any leading or trailing white space
        input = trim(input);

        // Input validation
        while (input.empty()) {
            cout << "Invalid input. Username cannot be empty" << ".\n";
            cout << "Enter your Username: ";
            getline(cin, input);
            input = trim(input);
        }
        username = input;

        // Get user's password
        cout << "Enter your Password: ";
        getline(cin, input);

        // Remove any leading or trailing white space
        input = trim(input);

        // Input validation
        while (input.empty()) {
            cout << "Invalid input. Password cannot be empty" << ".\n";
            cout << "Enter your Password: ";
            getline(cin, input);
            input = trim(input);
        }
        // Need to encrypt input first, then set password equal to it.
        input = hash_password(input);
        password = input;

        // Validate Login Information
        isValidLogin = checkUserPassPair(username, password);

        // If login info is valid, then set loginMenu.exitThisMenu = true;
        if (isValidLogin)
        {
            cout << "Login Successful!\n";
            loginMenu.setContinueMenu(false);
        }
        else  cout << "Invalid username/password pair\n";

    });
    loginMenu.addItem("Admin Log In", [&isValidAdmin, &input, &adminMenu]() {
        // Need to add in an Admin login
        string username;
    string password;

    // Get user's username
    cout << "Enter your Username: ";
    getline(cin, input);

    // Remove any leading or trailing white space
    input = trim(input);

    // Input validation
    while (input.empty()) {
        cout << "Invalid input. Username cannot be empty" << ".\n";
        cout << "Enter your Username: ";
        getline(cin, input);
        input = trim(input);
    }
    username = input;

    // Get user's password
    cout << "Enter your Password: ";
    getline(cin, input);

    // Remove any leading or trailing white space
    input = trim(input);

    // Input validation
    while (input.empty()) {
        cout << "Invalid input. Password cannot be empty" << ".\n";
        cout << "Enter your Password: ";
        getline(cin, input);
        input = trim(input);
    }
    // Need to encrypt input first, then set password equal to it.
    input = hash_password(input);
    password = input;

    // Validate Login Information
    isValidAdmin = checkUserPassAdminTrio(username, password);

    // If login info is valid, then set loginMenu.exitThisMenu = true;
    if (isValidAdmin)
    {
        cout << "Login Successful!\n";
        adminMenu.run();
        isValidAdmin = false;
    }
    else  cout << "Invalid login: Either incorrect username/password pair or the user account is not an admin.\n";
    });

    loginMenu.run();

    if (isValidLogin)
    {
        Menu mainMenu;
        mainMenu.setMenuName("Main Menu");
        Menu bookListMenu;
        bookListMenu.setMenuName("Book List Editing Menu");
        Menu shoppingMenu;
        shoppingMenu.setMenuName("Shopping List Menu");

        bool inShopperTable = false;
        vector<Book> usersBookList;
        multiset<Book, bool(*)(const Book&, const Book&)> shoppingList(compareBooksByMSRP); // This auto-sorts its book objects based on their prices.

        mainMenu.addItem("Search the Database", [&input]() { // Perform action for Search the Database
            cout << "Searching the Database\n";
            vector<Book> searchResults;

            // Get Book Title
            cout << "Enter a book title: ";
            getline(cin, input);

            // Remove any leading or trailing white space
            input = trim(input);

            // Input validation
            while (input.empty()) {
                cout << "Invalid input. Book title cannot be empty" << ".\n";
                cout << "Enter a book title: ";
                getline(cin, input);
                input = trim(input);
            }

            cout << "\nLoading results, please wait ... \n";
            int maxResults = 100;

            searchResults = searchBooksByTitle(input);

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

                                searchResults = searchBooksByTitle(input);

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
        mainMenu.addItem("Add a book to the Inventory", [&input]() { // Perform action for Add a book to the Inventory
            cout << "Adding a book to the Inventory\n";
            string title;
            string author;
            string publisher;
            string isbn;
            string year;
            string desc;
            string genre;
            string msrp;
            string quantity;
            bool isISBNValid = false;
            bool isYearValid = false;

            // Get Book Information
            // Get Book ISBN
            cout << "Enter the book's ISBN: ";
            getline(cin, input);

            // Remove any leading or trailing white space
            input = trim(input);

            // Input validation
            /* Need to figure out the validation method for an ISBN, ...
            while (!isNumber(input)) { // input.length() != 13 || 
                cout << "Invalid input. Book ISBN must have only numerical digits.\n";
                cout << "Enter the book's ISBN: ";
                getline(cin, input);
                input = trim(input);
            }*/
            isbn = input;

            // Get Book Title
            cout << "Enter a book title: ";
            getline(cin, input);

            // Remove any leading or trailing white space
            input = trim(input);

            // Input validation
            while (input.empty()) {
                cout << "Invalid input. Book title cannot be empty" << ".\n";
                cout << "Enter a book title: ";
                getline(cin, input);
                input = trim(input);
            }
            title = input;

            // Get Book Author
            cout << "Enter a book author: ";
            getline(cin, input);

            // Remove any leading or trailing white space
            input = trim(input);

            // Input validation
            while (input.empty()) {
                cout << "Invalid input. Book author cannot be empty" << ".\n";
                cout << "Enter a book author: ";
                getline(cin, input);
                input = trim(input);
            }
            author = input;

            // Get Book Year
            cout << "Enter the book's publication year: ";
            getline(cin, input);

            // Remove any leading or trailing white space
            input = trim(input);

            // Input validation
            while (!isStringInt(input) || stoi(input) > getCurrentYear()) {
                cout << "Invalid input. Book year must be a valid year (any year from 0 to " << getCurrentYear() << ").\n";
                cout << "Enter the book's publication year: ";
                getline(cin, input);
                input = trim(input);
            }
            year = input;

            // Get Book Publisher
            cout << "Enter a book publisher: ";
            getline(cin, input);

            // Remove any leading or trailing white space
            input = trim(input);

            // Input validation
            while (input.empty()) {
                cout << "Invalid input. Book publisher cannot be empty" << ".\n";
                cout << "Enter a book publisher: ";
                getline(cin, input);
                input = trim(input);
            }
            publisher = input;

            // Get Book Description
            cout << "Enter a book description: ";
            getline(cin, input);

            // Remove any leading or trailing white space
            // Since description/plot is an optional value in our database, it is allowed to be empty,
            // thus no input validation is required.
            desc = trim(input);

            // Get Book Genre
            cout << "Enter a book genre: ";
            getline(cin, input);

            // Remove any leading or trailing white space
            // Since genre is an optional value in our database, it is allowed to be empty,
            // thus no input validation is required.
            genre = trim(input);

            // Get Book MSRP
            cout << "Enter the book's manufacturer suggested retail price: ";
            getline(cin, input);

            // Remove any leading or trailing white space
            input = trim(input);

            // Input validation
            while (!isStringFloat(input) || stod(input) <= 0) {
                cout << "Invalid input. Book price must be a valid price (any price above 0).\n";
                cout << "Enter the book's manufacturer suggested retail price: ";
                getline(cin, input);
                input = trim(input);
            }
            msrp = input;

            // Get Book Quantity
            cout << "Enter the book's quantity: ";
            getline(cin, input);

            // Remove any leading or trailing white space
            input = trim(input);

            // Input validation
            while (!isStringInt(input) || stoi(input) < 0) {
                cout << "Invalid input. Book quantity must be a valid quantity (0 or greater).\n";
                cout << "Enter the book's quantity: ";
                getline(cin, input);
                input = trim(input);
            }
            quantity = input;


            // Make new Book Object
            
            // With Description and Genre
            if (!desc.empty() && !genre.empty())
            {
                Book bookToAdd(isbn, title, author, stoi(year), publisher, desc, genre, stod(msrp), stoi(quantity)); // DONE add desc and genre to this object.
                cout << "Adding book to Inventory, ..." << ".\n";
                addBookToInventory(bookToAdd);
            }
            else
            {
                Book bookToAdd(isbn, title, author, stoi(year), publisher, stod(msrp), stoi(quantity));
                cout << "Adding book to Inventory, ..." << ".\n";
                addBookToInventory(bookToAdd);
            }
            

            cout << "Done!\n";
            cout << "\n";
        });
        mainMenu.addItem("Edit your \"book list\"", [&bookListMenu]() {
            bookListMenu.run();
        });
        mainMenu.addItem("Edit your \"shopping list\"", [&shoppingMenu, &input, &inShopperTable]() {
            // For Week 7's HW (Assignment 5) prompt the user for if they want to add themsevles as a new SHOPPER before going to the shopping menu below.
            cout << "Would you like to create a new shopper? Y/N";
            getline(cin, input);
            if (toupper(input.at(0)) == 'Y')
            {
                string shopperName;
                    string shopperEmail;
                    cout << "Enter shopper's name: ";
                    getline(cin, shopperName);
                    cout << "Enter shopper's email: ";
                    getline(cin, shopperEmail);
                    addNewShopper(shopperName, shopperEmail);
                    inShopperTable = true;
            }
                
            shoppingMenu.run();
        });

        bookListMenu.addItem("Add a book to your \"book list\" from the inventory", [&input, &usersBookList]() {
            cout << "Adding a book to your \"book list\" from the inventory\n"; // Don't forget to also remove the book from the inventory

            // Get Book Title
            cout << "Enter a book title: ";
            getline(cin, input);

            // Remove any leading or trailing white space
            input = trim(input);

            // Input validation
            while (input.empty()) {
                cout << "Invalid input. Book title cannot be empty" << ".\n";
                cout << "Enter a book title: ";
                getline(cin, input);
                input = trim(input);
            }

            // Search the database/inventory for the given Title.
            cout << "\nLoading results, please wait ... \n";
            vector<Book> searchResults = searchBooksByTitle(input);

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
                cout << "\n";
                cout << "Enter \"Yes\" to confirm or \"No\" to cancel : ";
                //cin.ignore();
                getline(cin, input);

                // Remove any leading or trailing white space
                input = trim(input);

                // Input validation
                while (input != "Yes" && input != "No") {
                    cout << "Invalid input. Answer needs to be either \"Yes\" or \"No\".\n";
                    cout << "Enter \"Yes\" to confirm or \"No\" to cancel : ";
                    getline(cin, input);
                    input = trim(input);
                }
            }

            if (input == "Yes")
            {
                // Add the book in searchResults.at(0) to their "book list" (should be stored in the back end)
                usersBookList.push_back(searchResults.at(0));
                
                // Once the book is added, delete the row that contains that book in the .csv file.
                deleteBookFromInventory(usersBookList.at(0).getTitle());
                cout << "Book added!\n";
            }
        });
        bookListMenu.addItem("Print your \"book list\" to the screen", [&usersBookList]() { // Don't forget to include the total number of items in the list
            cout << "Printing your \"book list\" to the screen\n";
            cout << "\n";

            // Get book list and Iterate through the book list and print out each book's ISBN, Title, and Author
            for (unsigned int i = 0; i < usersBookList.size(); i++)
            {
                cout << "ISBN: " << usersBookList.at(i).getISBN() << "\n";
                cout << "Title: " << usersBookList.at(i).getTitle() << "\n";
                cout << "Author: " << usersBookList.at(i).getAuthor() << "\n";
                cout << "\n";
            }
            
            // After printing all the books to the screen, print out the total number of items in the book list
            cout << "Total number of books: " << usersBookList.size() << "\n";
            cout << "\n";
        });
        bookListMenu.addItem("Export your \"book list\" to a .csv file", [&input, &usersBookList]() {
            cout << "Exporting your \"book list\" to a .csv file\n";
            cout << endl;

            // If there is already a file named "exportedBookList.csv" when this system exports the list again, that file will be deleted and overwritten.
            // Ask user to confirm that they want to go through with this and to export "exportedBookList.csv".
            cout << "If there is already a file named \"exportedBookList.csv\" in the same directory as this file, \n";
            cout << "then that file will be completely deleted and overwritten with your new \"book list\". \n";
            cout << "Would you like to still go through with this exoirt action? [y/n]: ";
            getline(cin, input);

            // Remove any leading or trailing white space
            input = trim(input);

            // Input validation
            while (input.empty() || (input != "y" && input != "n")) {
                cout << "Invalid input. " << ".\n";
                cout << "Please confirm that the above is true [y/n]: ";
                getline(cin, input);
                input = trim(input);
            }

            if (input == "y")
            {
                // In the future, this fuction may return a bool on if this export was successful or not.
                // If we do that, then we can change the structure of this part to resemble the import function in the admin menu.
                exportBookList(usersBookList);
                cout << "Books Exported to external File!\n";
            }
            

            // After saving the external file with all of the books from the books list, remove all of the books from the books list.
            usersBookList.clear();
            cout << "User book list cleared!\n";
        });

        shoppingMenu.addItem("Add a book to your \"shopping list\" from the database.", [&input, &shoppingList]() {
            // idk if we're supposed to save this list to an external .csv file or just within memory, 
            // ... for now we'll just go for the memory. We can ask Prof. Carmon if he wants us to save it into a .csv file later.
            cout << "Adding a book to your \"shopping list\" from the database\n"; // Don't forget to also remove the book from the inventory

        // Get Book Title
        cout << "Enter a book title: ";
        getline(cin, input);

        // Remove any leading or trailing white space
        input = trim(input);

        // Input validation
        while (input.empty()) {
            cout << "Invalid input. Book title cannot be empty" << ".\n";
            cout << "Enter a book title: ";
            getline(cin, input);
            input = trim(input);
        }

        // Search the database/inventory for the given Title.
        cout << "\nLoading results, please wait ... \n";
        vector<Book> searchResults = searchBooksByTitle(input);

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
            cout << "\n";
            cout << "Enter \"Yes\" to confirm or \"No\" to cancel : ";
            //cin.ignore();
            getline(cin, input);

            // Remove any leading or trailing white space
            input = trim(input);

            // Input validation
            while (input != "Yes" && input != "No") {
                cout << "Invalid input. Answer needs to be either \"Yes\" or \"No\".\n";
                cout << "Enter \"Yes\" to confirm or \"No\" to cancel : ";
                getline(cin, input);
                input = trim(input);
            }
        }

        if (input == "Yes")
        {
            // Add the book in searchResults.at(0) to their "book list" (should be stored in the back end)
            shoppingList.emplace(searchResults.at(0));

            // Once the book is added, we used to delete the row that contains that book in the .csv file.
            // However, since this is a "shopping cart," we don't want to decrement the quantity of this book until they "purchase" it.
            //deleteBookFromInventory(searchResults.at(0).getTitle());
            cout << "Book added!\n";
        }
            });
        shoppingMenu.addItem("Display your \"shopping list\" to the screen.", [&shoppingList]() {
            cout << "Printing your \"shopping list\" to the screen\n";
            cout << "\n";

            // Get shopping list and Iterate through the shopping list and print out all of the information from each book

            multiset<Book, bool(*)(const Book&, const Book&)>::iterator shoppingListIterator = shoppingList.begin();

            while (shoppingListIterator != shoppingList.end())
            {
                cout << "ISBN: " << shoppingListIterator->getISBN() << endl;
                cout << "Title: " << shoppingListIterator->getTitle() << endl;
                cout << "Author: " << shoppingListIterator->getAuthor() << endl;
                cout << "Publication Year : " << shoppingListIterator->getYear() << endl;
                cout << "Publisher: " << shoppingListIterator->getPublisher() << endl;

                if (shoppingListIterator->getDescription().empty()) cout << "Description: NULL" << endl;
                else cout << "Description: " << shoppingListIterator->getDescription() << endl;
                if (shoppingListIterator->getGenre().empty()) cout << "Genre: NULL" << endl;
                else cout << "Genre: " << shoppingListIterator->getGenre() << endl;

                cout << "MSRP: $" << shoppingListIterator->getMSRP() << endl;
                cout << "Quantity on Hand: " << shoppingListIterator->getQuantity() << endl;
                cout << endl;

                shoppingListIterator++;
            }

            // After printing all the books to the screen, print out the total number of items in the book list
            cout << "Total number of books: " << shoppingList.size() << "\n";
            cout << "\n";
        });
        shoppingMenu.addItem("Purchase shopping cart", [&shoppingList, &inShopperTable]()
            {
                purchaseShoppingList(shoppingList);
                if (inShopperTable == true)
                {
                    cout << "In shopper table" << endl;
                }

                else
                    cout << "Guest" << endl;
            });

        mainMenu.run();

        //If there are any books left in the user's "book list" then add them back to the .csv database/inventory and remove them from the list.
        if (usersBookList.size() > 0) {
            for (unsigned int i = 0; i < usersBookList.size(); i++)
            {
                if (!usersBookList.at(i).getDescription().empty() && !usersBookList.at(i).getGenre().empty())
                {
                    Book bookToAdd(
                        usersBookList.at(i).getISBN(),
                        usersBookList.at(i).getTitle(),
                        usersBookList.at(i).getAuthor(),
                        usersBookList.at(i).getYear(),
                        usersBookList.at(i).getPublisher(),
                        usersBookList.at(i).getDescription(),
                        usersBookList.at(i).getGenre(),
                        usersBookList.at(i).getMSRP(),
                        usersBookList.at(i).getQuantity()); // DONE add desc and genre to this object.
                    cout << "Adding book back to Inventory, ..." << ".\n";
                    addBookToInventory(bookToAdd);
                }
                else
                {
                    Book bookToAdd(
                        usersBookList.at(i).getISBN(),
                        usersBookList.at(i).getTitle(),
                        usersBookList.at(i).getAuthor(),
                        usersBookList.at(i).getYear(),
                        usersBookList.at(i).getPublisher(),
                        usersBookList.at(i).getMSRP(),
                        usersBookList.at(i).getQuantity());
                    cout << "Adding book back to Inventory, ..." << ".\n";
                    addBookToInventory(bookToAdd);
                }
            }
            usersBookList.clear();
        }
    }

    return 0;
}
