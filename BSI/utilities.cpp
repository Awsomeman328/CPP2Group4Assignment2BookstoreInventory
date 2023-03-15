#include "utilities.h"

/* The following lines are not able to be included in a QT Project.
 * These were remnents from when we used the console as our front-end instead of our GUI.
 * As such, these are probably not needed, ...
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
}*/

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == string::npos) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}

// This function also returns false if the inputted string is empty.
// This function does not work for decimal/floating point numbers, it only works for integers/whole numbers.
bool isStringInt(const string& str)
{
    if (str.empty()) return false;
    for (char const& c : str) {
        if (isdigit(c) == 0) return false;
    }
    return true;
}
// Adjusted function from isStringInt() to check for doubles and floating point numbers.
// Just like its original, this function also returns false if the inputted string is empty.
bool isStringFloat(const string& str)
{
    if (str.empty()) return false;

    unsigned short int numDots = 0;
    for (char const& c : str) {
        if (isdigit(c) == 0)
        {
            if (c == '.') {
                numDots++;
                if (numDots > 1) return false;
            }
            else return false;
        }
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

// This function is to help with Querying the database. Since the SQLite3 library takes character pointers as arguments and not strings,
// this turns a string into a char pointer. This is to help with trying to pass in string variables into queries.
const char* convertStringToCharPointer(string* string) {
    const char* insertQuery = (*string).c_str();
    return insertQuery;
}

bool isStringPositiveInt(const string& s) {
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool compareBooksByMSRP(const Book& b1, const Book& b2)
{
    return (b1.getMSRP() < b2.getMSRP());
}
