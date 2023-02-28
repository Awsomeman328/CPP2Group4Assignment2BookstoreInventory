#include <iostream>
#include <string>
#include "md5.h"

using namespace std;

// Function to hash a password using md5
string hash_password(const string& password) {
    string hashed_password = MD5(password).hexdigest();
    return hashed_password;
}


