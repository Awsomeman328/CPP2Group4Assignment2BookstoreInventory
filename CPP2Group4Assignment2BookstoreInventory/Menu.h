#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include "MenuItem.h"
#include "book.h"
using namespace std;

class Menu
{
public:
    string menuName = "";
    vector<MenuItem> items;
    bool continueThisMenu = true;

    void addItem(string text, function<void()> action);
    void display();
    int getChoice();
    string trim(const string& str);
    void clearConsole();
    void run();
};

