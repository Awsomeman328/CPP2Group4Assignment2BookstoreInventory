#pragma once
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include "MenuItem.h"
#include "Utilities.h"
using namespace std;

class Menu
{
private:
    string menuName = "";
    vector<MenuItem> items;
    bool continueThisMenu = true;

public:
    void setMenuName(string newName);
    void setContinueMenu(bool newVal);
    void addItem(string text, function<void()> action);
    void display();
    int getChoice();
    void run();
};

#endif