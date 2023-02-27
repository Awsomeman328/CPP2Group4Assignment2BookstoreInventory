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

bool checkUserPassPair(string username, string password);
vector<Book> searchBooksByTitle(string bookTitleToSearch);
vector<Book> searchBooksByTitle(string bookTitleToSearch, size_t maxResults);
vector<Book> searchBooksByTitle(string bookTitleToSearch, unsigned int startingIndex, size_t maxResults);
vector<Book> searchBooksByTitle(string bookTitleToSearch, Book bookToStartFrom, size_t maxResults);
bool validateISBN(string ISBN);
bool validateTitle(string title);
bool validateAuthor(string author);
bool validatePubYear(int pubYear);
bool validatePublisher(string publisher);
void addBookToInventory(string ISBN, string bookTitle, string bookAuthor, string pubYear, string publisher);
void addBookToInventory(string ISBN, string bookTitle, string bookAuthor, string pubYear, string publisher, string description, string genre);
void addBookToInventory(Book bookToAdd);
void deleteBookFromInventory(string ISBN);
void exportBookList(vector<Book> bookList);
bool addNewUser(string username, string password, string isAdmin);
bool changeUsersPassword(string username, string newPassword);
bool importBooks();
bool checkUserPassAdminTrio(string username, string password);
void addNewShopper(string name, string email);
void purchaseShoppingList(multiset<Book, bool(*)(const Book&, const Book&)> &shoppingList);
double calcTotalPrice(multiset<Book, bool(*)(const Book&, const Book&)> shoppingList);