#pragma once
#include <iostream>
#include <vector>
#include "book.h"
#include "rapidcsv.h"


using namespace std;

vector<Book> readData(string bookTitleToSearch, size_t maxResults = 135680);
vector<Book> readData(string bookTitleToSearch, unsigned int startingIndex, size_t maxResults = 135680);
vector<Book> readData(string bookTitleToSearch, Book bookToStartFrom, size_t maxResults = 135680);