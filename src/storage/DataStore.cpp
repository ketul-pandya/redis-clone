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