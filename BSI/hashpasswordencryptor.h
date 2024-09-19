#pragma once

#ifndef HASHPASSWORDENCRYPTOR_H
#define HASHPASSWORDENCRYPTOR_H

#include <iostream>
#include <string>
#include "md5.h"

using namespace std;

string hash_password(const string& password);

#endif // HASHPASSWORDENCRYPTOR_H
