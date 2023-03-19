#pragma once
#ifndef UTILITIES_H
#define UTILITIES_H

#include <QDebug>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include "book.h"
using namespace std;

void clearConsole();
string trim(const string& str);
bool isStringInt(const string& str);
bool isStringFloat(const string& str);
int getCurrentYear();
const char* convertStringToCharPointer(string* string);
bool isStringPositiveInt(const string& s);
bool compareBooksByMSRP(const Book& b1, const Book& b2);
void outputToLogFile(string logMessage);

#endif // UTILITIES_H
