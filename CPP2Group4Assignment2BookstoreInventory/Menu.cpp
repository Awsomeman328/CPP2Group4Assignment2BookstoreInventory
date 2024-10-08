#include "Menu.h"

void Menu::setMenuName(string newName) { menuName = newName; }
void Menu::setContinueMenu(bool newVal) { continueThisMenu = newVal; }

void Menu::addItem(string text, function<void()> action) {
    MenuItem item;
    item.text = text;
    item.action = action;
    items.push_back(item);
}

void Menu::display() {
    for (int i = 0; i < items.size(); i++) {
        cout << i + 1 << ". " << items[i].text << endl;
    }
}

int Menu::getChoice() {
    int choice;
    string input;
    cout << "Enter your choice: ";
    getline(cin, input);

    // Remove any leading or trailing white space
    input = trim(input);

    // Input validation
    while (input.empty() || !isdigit(input[0]) || stoi(input) < 1 || stoi(input) > items.size() + 1) {
        cout << "Invalid input. Please enter a number between 1 and " << items.size() + 1 << ".\n";
        cout << "Enter your choice: ";
        getline(cin, input);
        input = trim(input);
    }

    return stoi(input);
}

void Menu::run() {
    int choice;
    do {
        //clearConsole(); // I usually do not like doing this while testing the code.
        cout << "\n" << menuName << ":\n";
        display();
        cout << items.size() + 1 << ". Exit\n";
        choice = getChoice();

        if (choice != items.size() + 1) {
            items[choice - 1].action();
            cout << endl;
        }
    } while ((choice != items.size() + 1) && continueThisMenu);
    setContinueMenu(true);
}
