#include "Utilities.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void clearConsole() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == string::npos) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}

// This function also returns false if the inputted string is empty.
bool isNumber(const string& str)
{
    if (str.empty()) return false;
    for (char const& c : str) {
        if (isdigit(c) == 0) return false;
    }
    return true;
}

int getCurrentYear() {
    auto now = chrono::system_clock::now();
    auto time = chrono::system_clock::to_time_t(now);
    tm tm;
    localtime_s(&tm, &time);
    int year = tm.tm_year + 1900;
    return year;
}