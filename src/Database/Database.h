#pragma once

#include <sqlite3.h> 
#include <string>
#include <sstream>

struct GateInfo 
{
    int id;
    std::string type;
    int inputs;
    int outputs;
    int xPos;
    int yPos;
};

class Database
{
public:
    static void Connect();
    static void Close();

    static void Create();
    static void Insert();
    static void Select();

    static void Execute(std::string query, std::string data = 0);

    static int Callback(void *NotUsed, int argc, char **argv, char **azColName);

private:

private:
    static sqlite3* m_db;
};