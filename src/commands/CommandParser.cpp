#include "CommandParser.h"
#include <algorithm>
#include <cctype>
#include <sstream>

using namespace std;

vector<string> CommandParser::parse(const string& input)
{
    stringstream ss(input);

    vector<string> tokens;

    string word;

    while(ss >> word)
    {
        if(tokens.empty())
        {
            transform(word.begin(),word.end(),
                    word.begin(),::toupper);
        }

        tokens.push_back(word);
    }

    return tokens;
}