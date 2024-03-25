#pragma once

#include <iostream>
#include <string>

#include "Person.hpp"

class Student : public Person
{
private:
    size_t indexNumber_{0};

public:
    Student() = default;
    Student(const std::string &name,
            const std::string &surname,
            const std::string &address,
            const std::string &pesel,
            const std::string &gender,
            size_t indexNumber);

    Student(std::string &&name,
            std::string &&surname,
            std::string &&address,
            std::string &&pesel,
            std::string &&gender,
            size_t indexNumber);

    Student(const Person &person, size_t indexNumber);
    Student(Person &&person, size_t indexNumber);

    Student(const Student &) = default;
    Student(Student &&) = default;

    Student &operator=(const Student &) = default;
    Student &operator=(Student &&) = default;

    ~Student() = default;

    void setIndex(const size_t);

    [[nodiscard]] size_t getIndex() const;

    friend std::ostream &operator<<(std::ostream &os, const Student &);
    friend std::istream &operator>>(std::istream &is, Student &);
};
