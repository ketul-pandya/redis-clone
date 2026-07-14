#include "CommandExecutor.h"

#include <iostream>

using namespace std;

CommandExecutor::CommandExecutor(DataStore& datastore)
    : db(datastore)
{
}

void CommandExecutor::execute(const vector<string>& tokens)
{
    if(tokens.empty())
        return;

    string command = tokens[0];

    if(command=="SET")
    {
        if(tokens.size()!=3)
        {
            cout<<"Usage: SET <key> <value>\n";
            return;
        }

        db.set(tokens[1],tokens[2]);

        cout<<"OK\n";
    }

    else if(command=="GET")
    {
        if(tokens.size()!=2)
        {
            cout<<"Usage: GET <key>\n";
            return;
        }

        string value;

        if(db.get(tokens[1],value))
            cout<<value<<endl;
        else
            cout<<"(nil)\n";
    }

    else
    {
        cout<<"Unknown Command\n";
    }
}