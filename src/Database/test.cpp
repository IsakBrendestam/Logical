#include <iostream>
#include <sqlite3.h> 

#include "Database.h"

int main() {
    Database::Connect();

    //Database::Create();
    //Database::Insert();
    Database::Select();

    Database::Close();

    return 0;
}