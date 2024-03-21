#pragma once 

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "Employee.hpp"
#include  "Student.hpp"


constexpr auto peselSize = 11u;

class University {
private:
    std::vector<std::unique_ptr<Person>> university_ = {};
public:
    std::optional<double> getSalaryIfIs(const std::unique_ptr<Person>& person);
    University() = default;
    ~University() = default;

    const std::vector<std::unique_ptr<Person>>& getVector() const;
    void displayBase(std::ostream& os);
    void addStudent();
    void addStudent(std::string, std::string, std::string, std::string, std::string, size_t);
    void addEmployee();
    void addEmployee(std::string, std::string, std::string, std::string, std::string, double);
    Person* findBySurname(const std::string&);
    Person* findByPesel(const std::string&);
    void sortByPesel();
    void sortBySurname();    
    void sortBySalary();
    bool validationByPesel(const std::string&);
    void exportDatabase(const std::string&);
    void importDatabase(const std::string&);
    void removeByIndexNumber(size_t);
    void removeByPesel(const std::string&);
    void modifySalary(double, const std::string&);


    void importMysql(const std::string&);
    void exportMysql(const std::string&);
};
