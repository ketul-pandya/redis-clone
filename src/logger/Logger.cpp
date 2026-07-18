#include "Logger.h"

#include <fstream>
#include <ctime>

using namespace std;

void Logger::log(const string& command)
{
    ofstream logFile("../logs/server.log", ios::app);

    if(!logFile.is_open())
        return;

    time_t now = time(nullptr);

    logFile << ctime(&now) << " : " << command << "\n";

    logFile.close();
}