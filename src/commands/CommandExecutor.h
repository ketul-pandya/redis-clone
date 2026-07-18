#pragma once

#include <vector>
#include <string>

#include "../storage/DataStore.h"
#include "../logger/Logger.h"

using namespace std;

class CommandExecutor
{
    
private:

    DataStore& db;
    Logger logger;
public:

    CommandExecutor(DataStore& datastore);

    string execute(const vector<string>& tokens);
};