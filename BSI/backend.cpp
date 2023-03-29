#define _CRT_SECURE_NO_WARNINGS
#include "backEnd.h"

/* A callback function which is meant to be used with the C API(not the C++ API) of SQLite3
// This function is called once per row in the result set and appends each row to a vector
// The 1st argument is what we return
// The 2nd argument is the number of columns in the result set
// the 3rd argument is the row's data
// the 4th argument is the column names
*/
static int callback(void* list, int argCount, char** argValue, char** azColName) {

    /* This is for adding the record returned from the database to this backEnd into this function's first argument.*/
    vector<vector<string>>* head = static_cast<vector<vector<string>>*>(list);
    try {
        vector<string> row = vector<string>();
        for (size_t i = 0; i < argCount; i++)
        {
            if (argValue[i] != NULL) row.push_back(argValue[i]);
            else row.push_back("NULL");
        }
        head->emplace_back(row);
    }
    catch (...) {
        // abort on failure, don't let exception propogate thru sqlite3 call-stack
        return 1;
    }
    return 0;

}

QVector<bool> attemptLogin(QString username, QString password)
{
    dbManager db("bookstoreInventory.db");
    QVector<bool> results = db.checkLogInInfo(username, password);

    //outputToLogFile("attemptLogin");

    return results;
}


// Everything in this function has been commented out. We probably need to fix this function so that it works again!
void deleteBookFromInventory(string Title)
{/*
    rapidcsv::Document doc("..\\users.csv", rapidcsv::LabelParams(0, 0));

    unsigned int index = 0;
    size_t found;

    // This loop goes until we reach the end of the file.
    while (index < doc.GetRowCount())
    {
        found = doc.GetCell<string>("Book-Title", index).find(Title);
        if (found != string::npos)
        {
            doc.RemoveRow(index);
        }
        index++;
    }
    doc.Save();*/
    cout << "Deleting from the inventory failed, ... \n";
}

// We may want to change this function to actually check if the export was successful or not and to then return a bool that signifies this status.
// But for now, we can keep it like this.
void exportBookList(vector<Book> bookList)
{
    ofstream booklist;
    booklist.open("exportedBookList.csv");
    booklist << "ISBN,Book-Title,Book-Author,Year-Of-Publication,Publisher,Description,Genre\n";

    for (unsigned short int i = 0; i < bookList.size(); i++)
    {
        booklist << bookList.at(i).getISBN() << "," << bookList.at(i).getTitle() << "," << bookList.at(i).getAuthor() << "," << bookList.at(i).getYear() << "," << bookList.at(i).getPublisher();
        if (!bookList.at(i).getDescription().empty())
        {
            booklist << "," << bookList.at(i).getDescription();
        }
        if (!bookList.at(i).getGenre().empty())
        {
            booklist << "," << bookList.at(i).getGenre();
        }
        booklist << endl;
    }

    booklist.close();
}

bool validateISBN(string ISBN)
{
    bool validISBN = true;

    if (ISBN.empty() || ISBN.size() > 16)
        validISBN = false;

    for (unsigned short int i = 0; i < ISBN.size(); i++)
    {
        if (!isdigit(ISBN.at(i)) && (ISBN.at(i) != 'X'))
            validISBN = false;
    }

    return validISBN;
}

bool validateTitle(string title)
{
    bool validTitle = true;

    if (title.empty() || title.size() > 255)
        validTitle = false;

    return validTitle;
}

bool validateAuthor(string author)
{
    bool validAuthor = true;

    if (author.empty()|| author.size() >255)
        validAuthor = false;

    return validAuthor;
}


bool validatePubYear(int pubYear)
{
    bool validPubYear = (pubYear >= 0 && pubYear <= 2023);
    return validPubYear;
}

bool validatePublisher(string publisher)
{
    bool validPublisher = !publisher.empty() && publisher.size() <= 255;
    return validPublisher;
}

bool validateDescription(string description)
{
    bool validDescription = description.size() <= 255;
    return validDescription;
}

bool validGenre(string genre)
{
    bool validGenre = genre.size() <= 255;
    return validGenre;
}

bool validMsrp(double msrp)
{
    bool validMsrp = (msrp != NULL && msrp >= 0);
    return validMsrp;
}

bool validQuantity(int quantity)
{
    bool validMsrp = (quantity != NULL && quantity >= 0);
    return validQuantity;
}



// Returns whether the purchase was successful or not.
// For now this function only buys a single copy of each book.
// In the future we will want to add the option/ability to purchase more than 1 copy of each book, but for now it is fine.
bool purchaseShoppingList(string shopperFirstName, string shopperLastName, string shopperEmail,
    multiset<Book, bool(*)(const Book&, const Book&)> &shoppingList)
{
    // Charge customer and decrease our book quantity
    return false; //(increaseTotalSpent(shopperFirstName, shopperLastName, shopperEmail, shoppingList) && decreaseBoughtBooks(shoppingList));
}

double calcTotalPrice(multiset<Book, bool(*)(const Book&, const Book&)> shoppingList)
{
    double totalPrice = 0;
    multiset<Book, bool(*)(const Book&, const Book&)>::iterator shoppingListIterator = shoppingList.begin();
    while (shoppingListIterator != shoppingList.end())
    {
        totalPrice += shoppingListIterator->getMSRP();
        shoppingListIterator++;
    }
    return totalPrice;
}




