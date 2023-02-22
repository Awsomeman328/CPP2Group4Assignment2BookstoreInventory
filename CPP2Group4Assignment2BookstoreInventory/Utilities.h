#pragma once
#ifndef UTILITIES_H
#define UTILITIES_H

#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
using namespace std;

void clearConsole();
string trim(const string& str);
bool isNumber(const string& str);
int getCurrentYear();
const char* convertStringToCharPointer(string* string);
bool isStringPositiveInt(const string& s);

#endif
