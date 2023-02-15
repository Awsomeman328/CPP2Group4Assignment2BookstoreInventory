#pragma once
#include <string>
#include <vector>
#include <functional>
#include "book.h"
using namespace std;

class MenuItem {
public:
    string text;
    function<void()> action;
};

