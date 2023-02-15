#pragma once
#include <vector>
#include "rapidcsv.h"
#include "book.h"

using namespace std;

bool checkUserPassPair(string username, string password);
vector<Book> searchBooksByTitle(string bookTitleToSearch, size_t maxResults);
vector<Book> searchBooksByTitle(string bookTitleToSearch, unsigned int startingIndex, size_t maxResults);
vector<Book> searchBooksByTitle(string bookTitleToSearch, Book bookToStartFrom, size_t maxResults);
void addBookToInventory(string ISBN, string bookTitle, string bookAuthor, string pubYear, string publisher);
void addBookToInventory(string ISBN, string bookTitle, string bookAuthor, string pubYear, string publisher, string description, string genre);
