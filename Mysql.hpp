#pragma once 

#include <iostram>
#include <mysql/mysql.h>

#include "Person"

class Mysql {
private:
    Mysql mysql_;
    std::string host_;
    std::string name_;
    std::string password_;
    std::string database_;
    unsigned int port_;

public:
    Mysql(const char* host, const char* name, const char* surname, const char* password, const char* database, unsigned int port)
        : host_(host), name_(name), surname_(surname), password_(password), database_(database), port_(port) {};
    
    ~Mysql();
    
    bool connect();
    bool tableExists(const std::string&);
    bool checkTableContent();
};