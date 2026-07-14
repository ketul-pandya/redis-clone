#include "CommandParser.h"

#include <sstream>

using namespace std;

vector<string> CommandParser::parse(const string& input)
{
    stringstream ss(input);

    vector<string> tokens;

    string word;

    while(ss >> word)
    {
        tokens.push_back(word);
    }

    return tokens;
}