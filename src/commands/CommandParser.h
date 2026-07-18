#pragma once

#include <string>
#include <vector>

using namespace std;

class CommandParser
{
public:
    vector<string> parse(const string &command);

private:
    vector<string> parseRESP(const string &command);
};