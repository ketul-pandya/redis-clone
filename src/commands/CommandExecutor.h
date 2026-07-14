#pragma once

#include <vector>
#include <string>

#include "../storage/DataStore.h"

using namespace std;

class CommandExecutor
{
private:

    DataStore& db;

public:

    CommandExecutor(DataStore& datastore);

    void execute(const vector<string>& tokens);
};