#include <iostream>
#include <string>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>

// Function to hash a password using md5
std::string hash_password(const std::string& password) {
    boost::uuids::detail::md5 hash;
    boost::uuids::detail::md5::digest_type digest;
    hash.process_bytes(password.data(), password.size());
    hash.get_digest(digest);

    std::string hashed_password;
    boost::algorithm::hex(digest, digest + 16, std::back_inserter(hashed_password));
    return hashed_password;
}




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