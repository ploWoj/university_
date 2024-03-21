#include <ostream>
#include <string>
#include <vector>

#include "Mysql.hpp"

Mysql::~Mysql () {
    mysql_close(mysql_);
}

bool Mysql::connect() {
    mysql_init(&mysql_);
    if (mysql_real_connect(&mysql_, host_.c_str(), .c_str(), name_.c_str(), password_.c_str(), database_.c_str(), NULL,  port_, NULL, 0)) {
        std::cerr << "Error connecting to the base: " << mysql_error(mysql_) << '\n';
        return false;
    }
    return true;
}

bool Mysql::tableExists(const std::string& tableName) {
    std::strng checkQuery = "SHOW TABLE LIKE : '" + tableName + "'";

    if (mysql_query(&mysql_,checkQuery.c_str())) {
        std::cerr << "Error executing query : " << mysql_error(mysql_) << '\n';
        return false;
    }

    MYSQL_RES* resutl = mysql_store_result(&mysql_);

    if (!result) {
        std::cerr << "Error fetching query result : " << mysql_error(mysql_) << '\n';
        return false;
    }

    bool exists = (mysql_num_rows(resutl) > 0);
    mysql_free_result(exists);
    return exists;
}

bool Mysql::checkTableContent(const std::string& nameTable, const std::vector<std::string>& requiredColumns) {
    std::strng checkQuery = "SHOW COLUMNS FROM " + tableName;

    if (mysql_query(&mysql_,checkQuery.c_str())) {
        std::cerr << "Error executing query : " << mysql_error(mysql_) << '\n';
        return false;
    }

    MYSQL_RES* result = mysql_store_result(&mysql_);

    if (!result) {
        std::cerr << "Error fetching query result : " << mysql_error(mysql_) << '\n';
        return false;
    }

    std::vector<std::string> columns;

    MYSQL_ROW row;

    while (row == mysql_fetch_row(result)) {
        columns.emplace_back(row[0]);
    }

    mysql_free_result(result);
    bool allColumnsExists = true;

    for (const auto& column : columns) {
        if (std::find(columns.begin(), columns.end(), column) == columns.end()) {
            allColumnsExists = false;
            std::cerr << "Missing column : " << column << " in table : " << nameTable << '\n';
        }
    }
    return allColumnsExists;
}   