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

    else if(command=="DEL")
    {
        if(tokens.size()!=2)
        {
            cout<<"Usage: DEL <key>\n";
            return;
        }

        if(db.del(tokens[1]))
            cout<<"OK\n";
        else
            cout<<"Key not found\n";
    }

    else if(command=="EXISTS")
    {
        if(tokens.size()!=2)
        {
            cout<<"Usage: EXISTS <key>\n";
            return;
        }

        cout<<(db.exists(tokens[1]) ? "YES" : "NO")<<endl;
    }

    else if(command=="SIZE")
    {
        cout<<db.size()<<endl;
    }

    else if(command=="KEYS")
    {
        vector<string> allKeys=db.keys();

        if(allKeys.empty())
        {
            cout<<"Database Empty\n";
            return;
        }

        for(const auto &key:allKeys)
        {
            cout<<key<<endl;
        }
    }

    else if(command=="CLEAR")
    {
        db.clear();

        cout<<"Database Cleared\n";
    }

    else if(command=="HELP")
    {
        cout<<"\nAvailable Commands\n";

        cout<<"SET <key> <value>\n";
        cout<<"GET <key>\n";
        cout<<"DEL <key>\n";
        cout<<"EXISTS <key>\n";
        cout<<"KEYS\n";
        cout<<"SIZE\n";
        cout<<"CLEAR\n";
        cout<<"HELP\n";
        cout<<"EXIT\n";
    }
    else
    {
        cout<<"Unknown Command\n";
    }
}