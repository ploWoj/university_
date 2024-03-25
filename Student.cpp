#include <utility>

#include "Student.hpp"

Student::Student(const std::string &name,
                 const std::string &surname,
                 const std::string &address,
                 const std::string &pesel,
                 const std::string &gender,
                 size_t indexNumber)
    : Person(name, surname, address, pesel, gender), indexNumber_(indexNumber) {}

Student::Student(std::string &&name,
                 std::string &&surname,
                 std::string &&address,
                 std::string &&pesel,
                 std::string &&gender,
                 size_t indexNumber)
    : Person(std::move(name), std::move(surname), std::move(address), std::move(pesel), std::move(gender)), indexNumber_(indexNumber) {}

Student::Student(const Person &person, size_t indexNumber) : Person(person), indexNumber_(indexNumber) {}

Student::Student(Person &&person, size_t indexNumber) : Person(std::move(person)), indexNumber_(indexNumber) {}

void Student::setIndex(size_t indexNumber)
{
    indexNumber_ = indexNumber;
}

size_t Student::getIndex() const
{
    return indexNumber_;
}

std::ostream &operator<<(std::ostream &out, const Student &student)
{
    out << student.name_ << Person::formatDelimiter
        << student.surname_ << Person::formatDelimiter
        << student.address_ << Person::formatDelimiter
        << student.pesel_ << Person::formatDelimiter
        << student.gender_ << Person::formatDelimiter
        << student.indexNumber_ << Person::formatDelimiter;
    return out;
}
std::istream &operator>>(std::istream &in, Student &student)
{
    char delim{};
    Person person{};
    size_t indexNumber{};
    in >> person >> delim >> indexNumber;
    if (delim != ',')
    {
        in.clear(std::ios_base::failbit);
    }
    student = Student(person, indexNumber);
    return in;
}