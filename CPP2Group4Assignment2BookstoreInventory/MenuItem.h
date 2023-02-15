#pragma once
#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>
#include <functional>
using namespace std;

class MenuItem {
public:
    string text;
    function<void()> action;
};

#endif