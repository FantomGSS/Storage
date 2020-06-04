#include "Functions.h"

int main()
{
    string filePathStorage;
    string filePathLogs = LOGS_PATH;
    vector<Log> logs;
    vector<string> lines;
    vector<Product> products;
    Section* sectionKG = new Section[MAX_SECTIONS];
    Section* sectionL = new Section[MAX_SECTIONS];

    cout << INTRODUCTION << endl;
    cout << FILE_OPTIONS << endl;
    cout << STORAGE_OPTIONS << endl;
    bool storageIsOpen = false;
    string command;
    while (1)
    {
        cout << ENTER_COMMAND;
        getline(cin, command);

        commandPattern(storageIsOpen, filePathLogs, filePathStorage, command, lines, logs, products, sectionKG, sectionL);
    }
}