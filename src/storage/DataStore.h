#pragma once

#include <bits/stdc++.h>
#include <ctime>

using namespace std;

class DataStore {
public:
    bool set(const string& key, const string& value);

    // Removed const because GET may delete expired keys
    bool get(const string& key, string& value);

    bool del(const string& key);

    bool exists(const string& key);

    bool saveToFile(const string& filename);

    bool loadFromFile(const string& filename);

    vector<string> keys() const;

    void clear();

    size_t size() const;

    // ---------- TTL ----------
    bool expire(const string& key, int seconds);

    int ttl(const string& key);

private:
    unordered_map<string, string> store_;

    // Stores expiry time (Unix timestamp) for keys
    unordered_map<string, time_t> expiry_;

    // Checks if a key has expired and removes it if needed
    bool isExpired(const string& key);
};