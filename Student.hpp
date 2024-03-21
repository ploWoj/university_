#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "Person.hpp"

class Student : public Person {
private:
    size_t indexNumber_{0};

public:
    Student() = default;
    Student(std::string name, std::string surname, std::string address, std::string pesel, std::string gender, size_t indexNumber);
    Student(const Person& person, size_t indexNumber);
    ~Student() = default;
    void setIndex(const size_t);
    
    size_t getIndex() const;

    // void display() const override;

    friend std::ostream& operator<<(std::ostream& os, const Student&);
    friend std::istream& operator>>(std::istream& is, Student&);
};
