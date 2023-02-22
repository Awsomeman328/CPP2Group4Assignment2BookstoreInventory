#include <iostream>
#include <string>
//#include <boost/uuid/detail/md5.hpp>
//#include <boost/algorithm/hex.hpp>
//
//// Function to hash a password using md5
//std::string hash_password(const std::string& password) {
//    boost::uuids::detail::md5 hash;
//    boost::uuids::detail::md5::digest_type digest;
//    hash.process_bytes(password.data(), password.size());
//    hash.get_digest(digest);
//
//    std::string hashed_password;
//    boost::algorithm::hex(digest, digest + 16, std::back_inserter(hashed_password));
//    return hashed_password;
//}


//To test if the function works

/*
int main2() {
    std::string password;
    while (true) {
        std::cout << "Enter a password to hash: ";
        std::getline(std::cin, password);
        if (!password.empty()) {
            break;
        }
        std::cout << "Password cannot be empty. Please try again.\n";
    }
    std::string hashed_password = hash_password(password);
    std::cout << "Hashed password: " << hashed_password << std::endl;
    return 0;
}
*/

//Possible future add-in to the program
//Goes through CSV file and hashes all passwords

/*
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>

using namespace std;

// Function to hash a password using MD5
string hash_password(const string& password) {
    boost::uuids::detail::md5 hash;
    boost::uuids::detail::md5::digest_type digest;
    hash.process_bytes(password.data(), password.size());
    hash.get_digest(digest);

    string hashed_password;
    boost::algorithm::hex(digest, digest + 16, back_inserter(hashed_password));
    return hashed_password;
}

int main() {
    // Open the CSV file containing user data
    ifstream file("users.csv");
    if (!file) {
        cerr << "Error: could not open file" << endl;
        return 1;
    }

    // Read the data from the CSV file
    string line, username, password;
    getline(file, line); // Skip the header row
    while (getline(file, line)) {
        istringstream ss(line);
        getline(ss, username, ',');
        getline(ss, password, ',');
        // Hash the password
        password = hash_password(password);
        // Print the updated data for testing
        cout << username << "," << password << endl;
    }

    return 0;
}
*/