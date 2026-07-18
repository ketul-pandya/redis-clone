#pragma once

#include "../storage/DataStore.h"
#include "../commands/CommandParser.h"
#include "../commands/CommandExecutor.h"

class Server
{
public:
    Server();
    bool start();

private:
    int serverSocket = -1;

    DataStore dataStore;
    CommandParser parser;
    CommandExecutor executor;
};