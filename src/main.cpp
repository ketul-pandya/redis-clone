#include <iostream>

#include "storage/DataStore.h"
#include "commands/CommandParser.h"
#include "commands/CommandExecutor.h"

using namespace std;

int main()
{
    DataStore db;

    CommandParser parser;

    CommandExecutor executor(db);

    string input;

    cout<<"Redis Clone v1.0\n";

    while(true)
    {
        cout<<"redis> ";

        getline(cin,input);

        if(input=="EXIT")
            break;

        vector<string> tokens = parser.parse(input);

        executor.execute(tokens);
    }

    cout<<"Goodbye!\n";
}