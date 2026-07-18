#include "CommandExecutor.h"

#include <iostream>

using namespace std;

CommandExecutor::CommandExecutor(DataStore& datastore)
    : db(datastore)
{
}

string CommandExecutor::execute(const vector<string>& tokens)
{
    if(tokens.empty())
        return "";

    // Reconstruct the complete command
    string fullCommand;

    for(const auto& token : tokens)
    {
        if(!fullCommand.empty())
            fullCommand += " ";

        fullCommand += token;
    }

    logger.log(fullCommand);

    string command = tokens[0];

    if(command=="SET")
    {
        if(tokens.size()!=3)
            return "Usage: SET <key> <value>";

        db.set(tokens[1],tokens[2]);
        return "OK";
    }

    else if(command=="GET")
    {
        if(tokens.size()!=2)
            return "Usage: GET <key>";

        string value;

        if(db.get(tokens[1],value))
            return value;

        return "(nil)";
    }

    else if(command=="DEL")
    {
        if(tokens.size()!=2)
            return "Usage: DEL <key>";

        if(db.del(tokens[1]))
            return "OK";

        return "Key not found";
    }

    else if(command=="EXISTS")
    {
        if(tokens.size()!=2)
            return "Usage: EXISTS <key>";

        return db.exists(tokens[1]) ? "YES" : "NO";
    }

    else if(command=="SIZE")
    {
        return to_string(db.size());
    }

    else if(command=="KEYS")
    {
        vector<string> allKeys = db.keys();

        if(allKeys.empty())
            return "Database Empty";

        string response;

        for(const auto &key : allKeys)
            response += key + "\n";

        return response;
    }

    else if(command=="CLEAR")
    {
        db.clear();
        return "Database Cleared";
    }

    else if(command=="HELP")
    {
        return
        "SET <key> <value>\n"
        "GET <key>\n"
        "DEL <key>\n"
        "EXISTS <key>\n"
        "EXPIRE <key> <seconds>\n"
        "TTL <key>\n"
        "KEYS\n"
        "SIZE\n"
        "CLEAR\n"
        "HELP\n"
        "EXIT";
    }

    else if(command=="SAVE")
    {
        if(db.saveToFile("database.txt"))
            return "Database Saved";

        return "Save Failed";
    }

    else if(command=="LOAD")
    {
        if(db.loadFromFile("database.txt"))
            return "Database Loaded";

        return "Load Failed";
    }

else if(command=="EXPIRE")
{
    if(tokens.size()!=3)
        return "Usage: EXPIRE <key> <seconds>";

    int seconds = stoi(tokens[2]);

    if(db.expire(tokens[1], seconds))
        return "OK";

    return "Key not found";
}

else if(command=="TTL")
{
    if(tokens.size()!=2)
        return "Usage: TTL <key>";

    return to_string(db.ttl(tokens[1]));
}

else if(command == "COMMAND")
{
    return "OK";
}
    return "Unknown Command";

}