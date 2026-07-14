#include "DataStore.h"

using namespace std;

bool DataStore::set(const string& key, const string& value)
{
    store_[key] = value;
    return true;
}

bool DataStore::get(const string& key, string& value) const
{
    auto it = store_.find(key);

    if(it == store_.end())
    {
        return false;
    }

    value = it->second;
    return true;
}

bool DataStore::del(const string& key)
{
    return store_.erase(key) > 0;
}

bool DataStore::exists(const string& key) const
{
    return store_.find(key) != store_.end();
}

size_t DataStore::size() const
{
    return store_.size();
}

vector<string> DataStore::keys() const
{
    vector<string> result;

    for (const auto& pair : store_)
    {
        result.push_back(pair.first);
    }

    return result;
}

void DataStore::clear()
{
    store_.clear();
}