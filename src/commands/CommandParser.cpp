#include "CommandParser.h"

#include <sstream>

using namespace std;

vector<string> CommandParser::parse(const string &command)
{
    // RESP command
    if (!command.empty() && command[0] == '*')
    {
        return parseRESP(command);
    }

    // Plain text command
    vector<string> tokens;
    string token;

    stringstream ss(command);

    while (ss >> token)
    {
        tokens.push_back(token);
    }

    return tokens;
}

vector<string> CommandParser::parseRESP(const string &command)
{
    vector<string> tokens;

    stringstream ss(command);

    string line;

    // Read first line
    getline(ss, line);

    // Example:
    // *3

    while (getline(ss, line))
    {
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }

        if (line.empty())
            continue;

        // Skip bulk length
        if (line[0] == '$')
        {
            continue;
        }

        tokens.push_back(line);
    }

    return tokens;
}