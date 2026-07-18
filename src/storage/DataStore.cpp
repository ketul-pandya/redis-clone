#include "DataStore.h"
#include <fstream>
#include <sstream>

using namespace std;

bool DataStore::set(const string& key, const string& value)
{
    store_[key] = value;
    return true;
}

bool DataStore::get(const string& key, string& value)
{
    if (isExpired(key))
    {
        return false;
    }

    auto it = store_.find(key);

    if (it == store_.end())
    {
        return false;
    }

    value = it->second;
    return true;
}

bool DataStore::del(const string& key)
{
    expiry_.erase(key);
    return store_.erase(key) > 0;
}

bool DataStore::exists(const string& key)
{
    if (isExpired(key))
    {
        return false;
    }

    return store_.find(key) != store_.end();
}

size_t DataStore::size() const
{
    size_t count = 0;

    for (const auto& pair : store_)
    {
        auto it = expiry_.find(pair.first);

        if (it != expiry_.end() && time(nullptr) >= it->second)
            continue;

        count++;
    }

    return count;
}

vector<string> DataStore::keys() const
{
    vector<string> result;

    for (const auto& pair : store_)
    {
        auto it = expiry_.find(pair.first);

        if (it != expiry_.end() && time(nullptr) >= it->second)
            continue;

        result.push_back(pair.first);
    }

    return result;
}

void DataStore::clear()
{
    store_.clear();
    expiry_.clear();
}

bool DataStore::saveToFile(const string& filename)
{
    ofstream outFile(filename);

    if (!outFile.is_open())
        return false;

    for (const auto& pair : store_)
    {
        outFile << pair.first << " " << pair.second << "\n";
    }

    outFile.close();

    return true;
}

bool DataStore::loadFromFile(const string& filename)
{
    ifstream inFile(filename);

    if (!inFile.is_open())
        return false;

    store_.clear();

    string key, value;

    while (inFile >> key >> value)
    {
        store_[key] = value;
    }

    inFile.close();

    return true;
}

bool DataStore::isExpired(const string& key)
{
    auto it = expiry_.find(key);

    // Key has no expiry time
    if (it == expiry_.end())
    {
        return false;
    }

    // Expiry time reached
    if (time(nullptr) >= it->second)
    {
        store_.erase(key);
        expiry_.erase(it);
        return true;
    }

    return false;
}

bool DataStore::expire(const string& key, int seconds)
{
    if (!exists(key))
    {
        return false;
    }

    expiry_[key] = time(nullptr) + seconds;
    return true;
}

int DataStore::ttl(const string& key)
{
    if (!exists(key))
    {
        return -2;      // Key doesn't exist
    }

    auto it = expiry_.find(key);

    if (it == expiry_.end())
    {
        return -1;      // No expiry
    }

    return static_cast<int>(it->second - time(nullptr));
}