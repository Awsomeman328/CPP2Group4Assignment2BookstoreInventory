#include "Book.h"
#include <iostream>
#include "Back-end.h"
#include <vector>
#include <string>

using namespace std;

int main()
{
    //variable declaration
    string username;
    string password;
    vector<Book> database;
    vector<Book> searchResults;
    bool validLogin;
    string input;

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
    
    




	string fileName = "..\\books.csv";
	vector<Book> books = readData("e");

	cout << "Book Inventory:" << endl;
	/*for (int i = 0; i < books.size(); i++) {
		cout << "Title: " << books[i].getTitle() << endl;
		cout << "Author: " << books[i].getAuthor() << endl;
		cout << "Publisher: " << books[i].getPublisher() << endl;
		cout << "Year: " << books[i].getYear() << endl;
		cout << "ISBN: " << books[i].getISBN() << endl;
		cout << endl;
	}*/
	cout << "Total matches found: " << books.size() << endl;
	return 0;
}