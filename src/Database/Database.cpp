#include "Database.h"

#include "Debug.h"

sqlite3* Database::m_db;

void Database::Connect()
{
    int rc = sqlite3_open("test.db", &m_db);
    
    if (rc) 
    {
        std::cout << "Can't open database: " << sqlite3_errmsg(m_db) << std::endl;
        return;
    }
    else
        std::cout << "Opened database successfully\n" << std::endl;
}

void Database::Close()
{
    sqlite3_close(m_db);
}

void Database::Create()
{
    std::string sql = "CREATE TABLE GATES("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "TYPE           TEXT    NOT NULL," \
      "INPUTS         INT     NOT NULL," \
      "OUTPUTS        INT     NOT NULL);";

    /* Execute SQL statement */
    Execute(sql);
}

void Database::Insert()
{
    std::stringstream sstream;
    sstream << "INSERT INTO GATES (";
    std::string sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) ";

    Execute(sql);
}

void Database::Select()
{
    std::string sql = "SELECT * from COMPANY";
    std::string data = "SELECT";
    Execute(sql, data);
    std::cout << data << std::endl;
}

void Database::Execute(std::string query, std::string data)
{ 
    char* errMsg;
    int rc = sqlite3_exec(m_db, query.c_str(), Callback, (void*)data.c_str(), &errMsg);
    
    if( rc != SQLITE_OK )
    {
        std::cout << "SQL error: " <<  errMsg << std::endl;;
        sqlite3_free(errMsg);
    } 
    else
        std::cout << "Operation executed successfully\n" << std::endl;
}

int Database::Callback(void* data, int argc, char** argv, char** azColName) {
    int i;
    if (data == "SELECT")
        std::cout << "Someting" << std::endl;
        
    for(i = 0; i<argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}