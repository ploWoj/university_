#pragma once 

#include <memory>
#include <mysql/mysql.h>
#include <optional>
#include <string>
#include <vector>

#include "Employee.hpp"
#include "Student.hpp"

namespace {
    constexpr char databseTable [] = "university.people";
    constexpr char host []= "localhost";
    constexpr char user [] = "trump";
    constexpr char password []= "Duda1234_5";
    constexpr  int port = 3306;
}

class University {
    
private:
    std::vector<std::unique_ptr<Person>> university_ = {};
public:
    std::optional<double> getSalaryIfIs(const std::unique_ptr<Person>& person);
    University() = default;
    ~University() = default;

    const std::vector<std::unique_ptr<Person>>& getVector() const;
    void displayBase(std::ostream& os = std::cout);
    void addStudent(const Student&);
    void addStudent(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, size_t);
    void addEmployee(const Employee&);
    void addEmployee(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, double);
    Person* findBySurname(const std::string&);
    Person* findByPesel(const std::string&);
    void sortByPesel();
    void sortBySurname();    
    void sortBySalary();
    // bool validationByPesel(const std::string&);
    void exportDatabase(const std::string&);
    void importDatabase(const std::string&);
    void removeByIndexNumber(size_t);
    void removeByPesel(const std::string&);
    void modifySalary(double, const std::string&);
    
    void importMysql(const std::string&);
    void exportMysql(const std::string&);
};
