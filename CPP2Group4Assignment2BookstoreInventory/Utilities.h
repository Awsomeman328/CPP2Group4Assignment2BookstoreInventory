#pragma once
#ifndef UTILITIES_H
#define UTILITIES_H

#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
#include "Book.h"
using namespace std;

void clearConsole();
string trim(const string& str);
bool isNumber(const string& str);
int getCurrentYear();
const char* convertStringToCharPointer(string* string);
bool isStringPositiveInt(const string& s);
bool compareBooksByMSRP(Book& b1, Book& b2);

#endif
