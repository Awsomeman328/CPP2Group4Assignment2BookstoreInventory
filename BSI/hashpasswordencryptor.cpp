#include "hashpasswordencryptor.h"

// Function to hash a password using md5
string hash_password(const string& password) {
    string hashed_password = MD5(password).hexdigest();
    return hashed_password;
}


