#include "loginscreen.h"
#include <ui_loginscreen.h>

loginscreen::loginscreen() :
    QDialog()
{
    //ui->setupUi(this);
}

loginscreen::~loginscreen()
{
    //delete ui;
}

void loginscreen::logIn()
{
    //QString username = ui->username->text();
    //QString password = QString::fromStdString( hash_password( ui->password->text().toStdString() ) );

    QVector<bool> loginStatus;// = attemptLogin(username, password);

    if (loginStatus.size() == NULL)
    {

        outputToLogFile("loginscreen::logIn() Login Failed! No UserPass pairs of given inputs.");

    }
    else if (loginStatus.size() == 1)
    {

        if (loginStatus[0])
        {
            outputToLogFile("loginscreen::logIn() Login Successful! Admin Access Granted!");
        }
        else
        {
            outputToLogFile("loginscreen::logIn() Login Successful!");
        }

    }
    else
    {

        outputToLogFile("loginscreen::logIn() DB ERROR: Login Attempt Failed! More than 1 UserPass pairs found.");

    }

}





/* old code
 *
 *
 * /* These functions use our old method of using the sqlite3 library. We now use the QtSql library handled within the dbManager Class.
 *
// This takes in a username and password and checks each row of the users.csv file to find a match
// If a match is found it immedeately returns true. If it goes through the whole file and fails to find a match, it returns false.
bool checkUserPassPair(string username, string password)
{
    // This class is a pointer to where our database is. This is how we're going to connect to the database and establish the connection.
    sqlite3* db;

    // This is a char pointer to an error message. When an error occurs &/or there's a problem with the connection, the error message will be stored here.
    char* zErrMsg = 0;

    // This is effectively our return value. This gets used for returning whether or not a function succeeded or failed.
    // Basically there is an enum state within SQLite and this returns the state of whatever function call we make.
    int rc;

    // The first thing we have to do is open the database file. If the provided file name doesn't exist, it will make a new database file using that name.
    sqlite3_open("bookstoreInventory.db", &db);

    // Where we will store the results from our query
    vector<vector<string>> data;


    string query = "SELECT USERNAME, PASSWORD, IS_ADMIN FROM USERS WHERE USERNAME='" + username + "' AND PASSWORD='" + password + "';";
    const char* charQuery = convertStringToCharPointer(&query);

    rc = sqlite3_exec(db, charQuery, callback, &data, &zErrMsg);

    sqlite3_close(db);

    // If the database returns 1 OR MORE results. ... In the future will want to limit it to make sure that it is ONLY 1 result, but fo rnow its fine.
    if (data.size() >= 1)
    {
        // data[i] selects the row, data[0][i] selects the cell, so this checks if the USERNAME of the first result was returned.
        if (data[0][0] == username)
        {
            outputToLogFile("checkUserPassPair");
            return true;
        }
    }
    return false;

}
 *
bool checkUserPassAdminTrio(string username, string password)
{
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;
    sqlite3_open("bookstoreInventory.db", &db);

    vector<vector<string>> data;


    string query = "SELECT USERNAME, PASSWORD, IS_ADMIN FROM USERS WHERE USERNAME='" + username + "' AND PASSWORD='" + password + "' AND IS_ADMIN=1;";
    const char* charQuery = convertStringToCharPointer(&query);

    rc = sqlite3_exec(db, charQuery, callback, &data, &zErrMsg);

    sqlite3_close(db);

    // If the database returns 1 OR MORE results. ... In the future will want to limit it to make sure that it is ONLY 1 result, but fo rnow its fine.
    if (data.size() >= 1)
    {
        // data[i] selects the row, data[0][i] selects the cell, so this checks if the USERNAME of the first result was returned.
        if (data[0][0] == username)
        {
            outputToLogFile("checkUserPassAdminTrio");
            return true;
        }
    }
    return false;
}

vector<Book> searchBooks(string inputToSearch, int searchType)
{
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;

    sqlite3_open("bookstoreInventory.db", &db);

    vector<vector<string>> data;
    vector<Book> booksToReturn;

    string query = "SELECT * FROM BOOKS WHERE "; // Select all records from the Books table where, ...

    // 1:ISBN, 2:Title, 3:Author, 4:Year, 5:Publisher, 6:MSRP, 7:Quantity
    switch (searchType)
    {
    case 1: // ISBN
        query += "ISBN LIKE '%" + inputToSearch + "%';";
        break;
    case 2: // Title
        query += "TITLE LIKE '%" + inputToSearch + "%';";
        break;
    case 3: // Author
        query += "AUTHOR LIKE '%" + inputToSearch + "%';";
        break;
    case 4: // Year
        query += "PUBLICATION_YEAR=" + inputToSearch + ";";
        break;
    case 5: // Publisher
        query += "PUBLISHER LIKE '%" + inputToSearch + "%';";
        break;
    case 6: // MSRP
        query += "MSRP=" + inputToSearch +";";
        break;
    case 7: // Quantity
        query += "QUANTITY_ON_HAND=" + inputToSearch + ";";
        break;
    default:
        // This is actually a REALLY REALLY REALLY BAD IDEA to make a Book Object an error warning, but this will be for testing purposes only hopefully.
        Book b("Bad Switch", "Bad Switch", "Bad Switch", 0, "Bad Switch", 0.0, 0);
        booksToReturn.push_back(b);
        return booksToReturn;
        break;
    }

    const char* charQuery = convertStringToCharPointer(&query);

    rc = sqlite3_exec(db, charQuery, callback, &data, &zErrMsg);

    sqlite3_close(db);
    outputToLogFile("searchBooks");

    // If the database returns 1 OR MORE results.
    if (data.size() >= 1)
    {
        // data[i] selects the row, data[0][i] selects the cell
        for (size_t i = 0; i < data.size(); i++)
        {
            //ISBN, TITLE, AUTHOR, YEAR, PUBLISHER, DESC(optional, only NULLs so far), GENRE(optional, only NULLs so far), MSRP, QUANTITY
            Book b(data[i][0], data[i][1], data[i][2], stoi(data[i][3]), data[i][4], stod(data[i][7]), stoi(data[i][8]));

            booksToReturn.push_back(b);
        }
    }

    return booksToReturn;
}

//functions to add book to inventory
void addBookToInventory(Book bookToAdd)
{
    //ofstream inventory;
    bool validInput = true;
    //inventory.open("..\\books.csv", ios::app);
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;

    int result = sqlite3_open("bookstoreInventory.db", &db);
    if (result == SQLITE_OK)
    {
        if (!validateISBN(bookToAdd.getISBN()))
            validInput = false;
        if (!validateTitle(bookToAdd.getTitle()))
            validInput = false;
        if (!validateAuthor(bookToAdd.getAuthor()))
            validInput = false;
        if (!validatePubYear(bookToAdd.getYear()))
            validInput = false;
        if (!validatePublisher(bookToAdd.getPublisher()))
            validInput = false;

        if (validInput)
        {
            //inventory << bookToAdd.getISBN() << "," << bookToAdd.getTitle() << "," << bookToAdd.getAuthor() << "," << bookToAdd.getYear() << "," << bookToAdd.getPublisher();
            string query = "INSERT INTO BOOKS (ISBN,TITLE,AUTHOR,PUBLICATION_YEAR,PUBLISHER,DESCRIPTION,GENRE,MSRP,QUANTITY_ON_HAND) " \
                "VALUES ('" + bookToAdd.getISBN() + "', '" + bookToAdd.getTitle() + "', '" + bookToAdd.getAuthor() + "'," \
                " " + to_string(bookToAdd.getYear()) + ", '" + bookToAdd.getPublisher() + "', ";

            if (!bookToAdd.getDescription().empty())
            {
                //inventory << "," << bookToAdd.getDescription();
                query += "'" + bookToAdd.getDescription() + "', ";
            }
            else query += "NULL, ";

            if (!bookToAdd.getGenre().empty())
            {
                //inventory << "," << bookToAdd.getGenre();
                query += "'" + bookToAdd.getGenre() + "',";
            }
            else query += "NULL,";

            query += " " + to_string(bookToAdd.getMSRP()) + ", " + to_string(bookToAdd.getQuantity()) + ");";

            const char* charQuery = convertStringToCharPointer(&query);

            //inventory << endl;
            rc = sqlite3_exec(db, charQuery, callback, 0, &zErrMsg);
        }
        else
            cout << "Invalid input" << endl;
    }
    else
        cout << "Unable to open file" << endl;
    //inventory.close();
    sqlite3_close(db);
    outputToLogFile("addBookToInventory");
}
 */

/* These functions use our old method of using the sqlite3 library. We now use the QtSql library handled within the dbManager Class.
 *
bool addNewUser(string username, string password, string isAdmin)
{
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;
    sqlite3_open("bookstoreInventory.db", &db);
    const char* data = "Callback function called";
    vector<vector<string>> head;

    string query = "INSERT INTO USERS (USERNAME,PASSWORD,IS_ADMIN) " \
        "VALUES ('" + username + "', '" + password + "', " + isAdmin + ");";

    const char* charQuery = convertStringToCharPointer(&query);

    rc = sqlite3_exec(db, charQuery, callback, 0, &zErrMsg);

    // check that the user was created sucessfully
    query = "SELECT USERNAME, PASSWORD, IS_ADMIN FROM USERS WHERE USERNAME='" + username + "' AND PASSWORD='" + password + "' AND IS_ADMIN=" + isAdmin + ";";

    charQuery = convertStringToCharPointer(&query);

    rc = sqlite3_exec(db, charQuery, callback, &head, &zErrMsg);

    sqlite3_close(db);

    // If the database returns 1 OR MORE results. ... In the future will want to limit it to make sure that it is ONLY 1 result, but fo rnow its fine.
    if (head.size() >= 1)
    {
        // data[i] selects the row, data[0][i] selects the cell, so this checks if the USERNAME of the first result was returned.
        if (head[0][0] == username && head[0][1] == password && head[0][2] == isAdmin)
        {
            outputToLogFile("addNewUser");
            return true;
        }
    }
    return false;
}

bool changeUsersPassword(string username, string newPassword)
{
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;
    sqlite3_open("bookstoreInventory.db", &db);
    const char* data = "Callback function called";
    vector<vector<string>> head;

    string query = "UPDATE USERS SET PASSWORD='" + newPassword + "' WHERE USERNAME='" + username + "';";

    const char* charQuery = convertStringToCharPointer(&query);

    rc = sqlite3_exec(db, charQuery, callback, 0, &zErrMsg);

    // check that the user was created sucessfully
    query = "SELECT USERNAME, PASSWORD, IS_ADMIN FROM USERS WHERE USERNAME='" + username + "' AND PASSWORD='" + newPassword + "';";

    charQuery = convertStringToCharPointer(&query);

    rc = sqlite3_exec(db, charQuery, callback, &head, &zErrMsg);

    sqlite3_close(db);

    // If the database returns 1 OR MORE results. ... In the future will want to limit it to make sure that it is ONLY 1 result, but fo rnow its fine.
    if (head.size() >= 1)
    {
        // data[i] selects the row, data[0][i] selects the cell, so this checks if the USERNAME of the first result was returned.
        if (head[0][0] == username && head[0][1] == newPassword)
        {
            outputToLogFile("changeUsersPassword");
            return true;
        }
    }
    return false;
}

bool importBooks()
{
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;
    sqlite3_open("bookstoreInventory.db", &db);

    const char* data = "Callback function called";

    string query;
    const char* charQuery;

    size_t i;
    bool isRecordValid;

    rapidcsv::Document doc("import.csv", rapidcsv::LabelParams(0, 0));
    for (i = 0; i < doc.GetRowCount(); i++)
    {
        isRecordValid = true;

        // get data from csv file
        string isbn = doc.GetRowName(i);
        string title = doc.GetCell<string>("Book-Title", i);
        string author = doc.GetCell<string>("Book-Author", i);
        string year = doc.GetCell<string>("Year-Of-Publication", i); // Need to check if valid year
        string publisher = doc.GetCell<string>("Publisher", i);
        string description = doc.GetCell<string>("Description", i);
        string genre = doc.GetCell<string>("Genre", i);
        string msrp = doc.GetCell<string>("MSRP", i); // Need to check if valid price
        string quantity = doc.GetCell<string>("Quantity-On-Hand", i); // need to check if valid quantity

        // Validation ... For now is just assuming that everything is valid, but will want to change this later.
        //if (year.empty()) // Year can be empty/NULL, but give a warning for it.
        //{
            //cout << "[WARNING]: Book " << isbn << " titled '" << title << "' at Row #" << i << "'s [year] cell value is empty!" << endl;
            //year = "NULL";
            //isRecordValid = true;
        //}
        //else if (!isStringPositiveInt(year))
        //{
            //cout << "[ERROR]: Book " << isbn << " titled '" << title << "' at Row #" << i << "'s [year] cell value is not a valid positive Int!" << endl;
            //isRecordValid = false;
        //}
        //else if (stoi(year) > 2023)
        //{
            //cout << "[ERROR]: Book " << isbn << " titled '" << title << "' at Row #" << i << "'s [year] cell value is greater than the current year (2023)!" << endl;
            //isRecordValid = false;
        //}
        else
        //{
            //isRecordValid = true;
        //}

        query = "INSERT INTO BOOKS (ISBN,TITLE,AUTHOR,PUBLICATION_YEAR,PUBLISHER,DESCRIPTION,GENRE,MSRP,QUANTITY_ON_HAND) " \
            "VALUES ('" + isbn + "', '" + title + "', '" + author + "', " + year + ", '" + publisher + "'," \
            " '" + description + "', '" + genre + "', " + msrp + ", " + quantity + "); ";

        // Convert string query into a character pointer
        charQuery = convertStringToCharPointer(&query);

        // Executing another SQL statement
        rc = sqlite3_exec(db, charQuery, callback, 0, &zErrMsg);
    }

    outputToLogFile("importBooks");

    // For now, there is no check to see if the import is successful, it is just assumed that it works. ... But we will want to change this later.
    return true;
}

// In the future, we may want to have this funcion return a bool or int to signal if this function was sucessful or not.
// But for now it is alright, we'll keep it as void for now.
void addNewShopper(string firstName, string lastName, string shopperEmail)
{
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;
    sqlite3_open("bookstoreInventory.db", &db);
    const char* data = "Callback function called";
    vector<vector<string>> head;

    // I'm glad you thought of this, but we don't need this.
    //if table doesnt already exists in db
    //const char* createTableQuery = "CREATE TABLE IF NOT EXISTS SHOPPERS("  \
        //"NAME TEXT NOT NULL," \
        //"EMAIL TEXT NOT NULL," \
        //"TOTAL_SPENT REAL," \
        //"PASSWORD TEXT NOT NULL);";

    // First, we need to check if the given shopper already exists.
    // If it does exist then we don't want to add a new one. If it doesn't exist then we doo want to add this new shopper to the table.

    string query = "SELECT FIRST_NAME, LAST_NAME, EMAIL FROM SHOPPERS " \
        "WHERE FIRST_NAME='" + firstName + "' AND LAST_NAME='" + lastName + "' AND EMAIL='" + shopperEmail + "';";

    const char* charQuery = convertStringToCharPointer(&query);

    rc = sqlite3_exec(db, charQuery, callback, &head, &zErrMsg);

    // If the database returns 1 OR MORE results. ... In the future will want to limit it to make sure that it is ONLY 1 result, but for now it's fine.
    if (head.size() >= 1)
    {
        // If it does exist then we don't want to add a new one. ...
        return;
    }

    query = "INSERT INTO SHOPPERS (FIRST_NAME, LAST_NAME, EMAIL, TOTAL_SPENT) " \
        "VALUES ('" + firstName + "', '" + lastName + "', '" + shopperEmail + "', 0.00);";

    charQuery = convertStringToCharPointer(&query);

    rc = sqlite3_exec(db, charQuery, callback, 0, &zErrMsg);

    // This part of the function is part of the rest of the commented out section below for checking that we sucessfully added the shopper to the table.
     * BUT since this doesn't return a bool yet this check is pointless until that change it made.
     *
    // check that the shopper was created successfully
    //query = "SELECT NAME, EMAIL, TOTAL_SPENT, PASSWORD FROM SHOPPERS WHERE NAME='" + shopperName + "' AND password='" + password + "'";

    //charQuery = convertStringToCharPointer(&query);

    //rc = sqlite3_exec(db, charQuery, callback, &head, &zErrMsg);


    sqlite3_close(db);

    outputToLogFile("addNewShopper");

    // The rest of this function is validating if this query succeeded or not.
     * But since this doesn't return a bool yet, this is useless until that change is made.
     *
    // If the database returns 1 OR MORE results. ... In the future will want to limit it to make sure that it is ONLY 1 result, but for now it's fine.
    //if (head.size() >= 1)
    //{
        // data[i] selects the row, data[0][i] selects the cell, so this checks if the NAME of the first result was returned.
        //if (head[0][0] == shopperName && head[0][1] == email && stod(head[0][2]) == totalSpent && head[0][3] == password)
        //{
            //return true;
        //}
    //}
    //return false;

}
 */
/* These functions use our old method of using the sqlite3 library. We now use the QtSql library handled within the dbManager Class.
 *
// The logic for being able to specify the number of copies of each book the user is buying is already partically in here,
// but since we currently don't have that support on the front-end it will be disabled for now.
bool decreaseBoughtBooks(multiset<Book, bool(*)(const Book&, const Book&)>& shoppingList)
{
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;

    rc = sqlite3_open("bookstoreInventory.db", &db);

    if (rc)
    {
        // This will probably be changed if it outputs to the command console, ... UNLESS we move over to QT this coming week!
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return false;
    }

    string query;
    string bigQuery = "";
    const char* charQuery;
    vector<vector<string>> head;

    // Make a loop and iterate through each book in the shoppingList
    multiset<Book, bool(*)(const Book&, const Book&)>::iterator shoppingListIterator = shoppingList.begin();
    while (shoppingListIterator != shoppingList.end())
    {
        // Do stuff
        query = "SELECT QUANTITY_ON_HAND FROM BOOKS WHERE ISBN='" + shoppingListIterator->getISBN() + "';";
        charQuery = convertStringToCharPointer(&query);

        rc = sqlite3_exec(db, charQuery, callback, &head, &zErrMsg);

        if (head.size() >= 1)
        {
            // Glad to see there was thought taken into account for figuring out HOW MANY copies of the book the user is buying, ...
            // BUT we don't need to decrease the amount on our end when the database can do it for us.
            // We DO however need to check that the QUANTITY_ON_HAND within the database is not 0, otherwise we have none of that book in our inventory!
            //int currentQuantity = stoi(head[0][0]);
            //int newQuantity = currentQuantity - quantity;
            if (stoi(head[0][0]) <= 0)
            {
                // This will probably be changed if it outputs to the command console, ... UNLESS we move over to QT this coming week!
                cerr << "Error: Book named \"" << shoppingListIterator->getTitle() << "\" has no avalible copies in the inventory." << endl;
                sqlite3_close(db);
                return false;
            }
            bigQuery += "UPDATE BOOKS SET QUANTITY_ON_HAND=QUANTITY_ON_HAND - 1 WHERE ISBN='" + shoppingListIterator->getISBN() + "';\n\n";
        }
        else
        {
            // This will probably be changed if it outputs to the command console, ... UNLESS we move over to QT this coming week!
            cerr << "Error: Book named \"" << shoppingListIterator->getTitle() <<"\" not found in database." << endl;
            sqlite3_close(db);
            return false;
        }
        shoppingListIterator++;
    }

    charQuery = convertStringToCharPointer(&bigQuery);
    rc = sqlite3_exec(db, charQuery, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        // This will probably be changed if it outputs to the command console, ... UNLESS we move over to QT this coming week!
        cerr << "Error updating database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return false;
    }
    else
    {
        // This will for sure going to be changed if it outputs to the command console, ... UNLESS we move over to QT this coming week! Then its more of a maybe.
        //cout << "Successfully updated quantity amount for all books in shopping list." << endl;
        sqlite3_close(db);
        return true;
    }
    outputToLogFile("decreaseBoughtBooks");
}

bool increaseTotalSpent(string shopperFirstName, string shopperLastName, string shopperEmail, multiset<Book, bool(*)(const Book&, const Book&)>& shoppingList)
{
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;

    rc = sqlite3_open("bookstoreInventory.db", &db);

    if (rc)
    {
        // This will probably be changed if it outputs to the command console, ... UNLESS we move over to QT this coming week!
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return false;
    }

    double totalPricePreTax = calcTotalPrice(shoppingList);
    double totalTax = totalPricePreTax * 0.06;
    double totalPricePostTax = totalPricePreTax + totalTax;

    string query = "UPDATE SHOPPERS SET TOTAL_SPENT = TOTAL_SPENT + " + to_string(totalPricePostTax) + " " \
        "WHERE FIRST_NAME='" + shopperFirstName + "' AND LAST_NAME='" + shopperLastName + "' AND EMAIL='" + shopperEmail + "';";
    const char* charQuery = convertStringToCharPointer(&query);

    rc = sqlite3_exec(db, charQuery, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        // This will probably be changed if it outputs to the command console, ... UNLESS we move over to QT this coming week!
        cerr << "Error updating database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return false;
    }
    else
    {
        // This will for sure going to be changed if it outputs to the command console, ... UNLESS we move over to QT this coming week! Then its more of a maybe.
        //cout << "Successfully updated " << shopperFirstName << " " << shopperLastName << "'s total spent." << endl;
        sqlite3_close(db);
        return true;
    }
    outputToLogFile("increaseTotalSpent");
}
 */
