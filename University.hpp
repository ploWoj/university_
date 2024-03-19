#pragma once 

#include <memory>
#include <string>
#include <vector>

#include "Employee.hpp"
#include  "Student.hpp"

class University {
private:
    std::vector<std::unique_ptr<Person>> university_ = {};
public:
    University() = default;
    ~University() = default;

    const std::vector<std::unique_ptr<Person>>& getVector() const;
    void displayBase();
    void addStudent();
    void addStudent(std::string, std::string, std::string, std::string, std::string);
    void addEmployee();
    void addEmployee(std::string, std::string, std::string, std::string, std::string);
    Person* findBySurname(const std::string&);
    Person* findByPesel(const std::string&);
    void sortByPesel();
    void sortBySurname();
    
    void sortBySalary();
    bool validateByPesel(const std::string&);
    void exportDatabase(const std::string&);
    void importDatabase(const std::string&);
    void removeByIndexNumber(size_t);
    void modifySalary(double, const std::string&);
};
