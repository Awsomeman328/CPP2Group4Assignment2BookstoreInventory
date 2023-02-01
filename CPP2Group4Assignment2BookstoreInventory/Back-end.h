#pragma once
#include <iostream> // Probably don't need this
#include <vector>
#include "rapidcsv.h"
#include "book.h"


using namespace std;

bool userExists(string username, string password);
vector<Book> readData(string bookTitleToSearch, size_t maxResults = 135680);
vector<Book> readData(string bookTitleToSearch, unsigned int startingIndex, size_t maxResults);
vector<Book> readData(string bookTitleToSearch, Book bookToStartFrom, size_t maxResults = 135680);