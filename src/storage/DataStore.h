#pragma once

#include <bits/stdc++.h>

using namespace std;

class DataStore {
public:
    bool set(const string& key, const string& value);

    bool get(const string& key, string& value) const;

    bool del(const string& key);

    bool exists(const string& key) const;

    vector<string> keys() const;

    void clear();

    size_t size() const;

private:
    unordered_map<string, string> store_;
};