#pragma once
#include <fstream>
#include <cctype>
#include <vector>
#include "rapidcsv.h"
#include "sqlite3.h"
#include "Book.h"
#include "Utilities.h"
#include <set>

using namespace std;

// These are all of the functions that we made in the backEnd.cpp file.
// We may want to change this to show ONLY the functions that we want to be called from outside the backEnd, but for now its fine.

bool checkUserPassPair(string username, string password);
bool checkUserPassAdminTrio(string username, string password);
vector<Book> searchBooks(string inputToSearch, int searchType);
bool validateISBN(string ISBN);
bool validateTitle(string title);
bool validateAuthor(string author);
bool validatePubYear(int pubYear);
bool validatePublisher(string publisher);
void addBookToInventory(Book bookToAdd);
void deleteBookFromInventory(string ISBN);
void exportBookList(vector<Book> bookList);
bool addNewUser(string username, string password, string isAdmin);
bool changeUsersPassword(string username, string newPassword);
bool importBooks();
bool checkUserPassAdminTrio(string username, string password);
void addNewShopper(string firstName, string lastName, string email);
bool purchaseShoppingList(string shopperFirstName, string shopperLastName, string shopperEmail,
	multiset<Book, bool(*)(const Book&, const Book&)>& shoppingList);
double calcTotalPrice(multiset<Book, bool(*)(const Book&, const Book&)> shoppingList);
bool decreaseBoughtBooks(multiset<Book, bool(*)(const Book&, const Book&)>& shoppingList);
bool increaseTotalSpent(string shopperFirstName, string shopperLastName, string shopperEmail,
	multiset<Book, bool(*)(const Book&, const Book&)>& shoppingList);
