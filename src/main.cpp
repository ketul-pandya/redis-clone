#include <iostream>
#include "storage/DataStore.h"

using namespace std;

int main()
{
    DataStore db;

    db.set("name", "Ketul");
    db.set("college", "DEPSTAR");

    string value;

    cout << "Before DELETE\n";

    if(db.get("name", value))
        cout << "Name : " << value << endl;

    cout << "\nDeleting 'name'...\n";

    if(db.del("name"))
        cout << "Deleted successfully\n";
    else
        cout << "Key not found\n";

    cout << "\nAfter DELETE\n";

    if(db.get("name", value))
        cout << value << endl;
    else
        cout << "Name not found\n";

    return 0;
}