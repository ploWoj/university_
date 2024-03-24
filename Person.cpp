#include "Person.hpp"

std::string getStringToChar(std::istream& in, char delimiter) {
    std::string temp{};
    for (char current_char{}; in >> current_char;) {
        if (current_char == delimiter) {
            in.putback(current_char);
            break;
        }

        temp.push_back(current_char);
    }
    return temp;
}

Person::Person(sconst std::string& name, 
               const std::string& surname, 
               const std::string& address, 
               const std::string& pesel, 
               const std::string& gender)
        : name_(name), 
          surname_(surname), 
          address_(address), 
          pesel_(pesel), 
          gender_(gender) {}

Person::Person(std::string&& name, 
               std::string&& surname, 
               std::string&& address, 
               std::string&& pesel, 
               std::string&& gender)
        :name_(std::move(name)),
         surname_(std::move(surname)), 
         address_(std::move(address)), 
         pesel_(std::move(pesel)), 
         gender_(std::move(gender)) {} 

void Person::setName(const std::string& name) {
    name_ = name;
}

void Person::setSurname(const std::string& surname) {
    surname_ = surname;
}

void Person::setAddress(const std::string& address) {
    address_ = address;
}

void Person::setPesel(const std::string& pesel) {
    pesel_ = pesel;
}

void Person::setGender(const std::string& gender) {
    gender_ = gender;
}

std::string Person::getName() const { 
    return name_;
}

std::string Person::getSurname() const {
    return surname_;
}

std::string Person::getAddress() const {
    return address_;
}

std::string Person::getPesel() const {
    return pesel_;
}

std::string Person::getGender() const {
    return gender_;
}

std::ostream& operator<<(std::ostream& os, const Person& person) {
    os << person.name_  << person.surname_  << person.address_ <<
         person.gender_ ;
    return os;
}

 std::istream& operator>>(std::istream& in, Person& person) {
    char delim1{}, delim2{}, delim3{}, delim4{};
    person.name_ = getStringToChar(in, Person::formatDelimiter);
    in >> delim1;
    person.surname_ = getStringToChar(in, Person::formatDelimiter);
    in >> delim2;
    person.address_ = getStringToChar(in, Person::formatDelimiter);
    in >> delim3;
    person.pesel_ = getStringToChar(in, Person::formatDelimiter);
    in >> delim4;
    person.gender_ = getStringToChar(in, Person::formatDelimiter);

    if (delim1 != Person::formatDelimiter ||
        delim2 != Person::formatDelimiter ||
        delim3 != Person::formatDelimiter ||
        delim4 != Person::formatDelimiter ) {
            in.clear(std::ios_base::failbit);
        }
    return in;
 }

 bool Person::operator==(const Person& person) const {
            return this->name_ == person.name_ && 
                   this->surname_ == person.surname_ && 
                   this->address_ == person.address_ &&
                   this->pesel_ == person.pesel_ &&
                   this->gender_ == person.gender_;
        }

bool Pesel::validatePesel(const std::string& pesel) {
    if (pesel.size() != Pesel::peselSize)
    {
        return false;
    }

    static constexpr std::array<size_t, 10> weightFactors{1, 3, 7, 9, 1, 3, 7, 9, 1, 3};

    size_t checkSum = 0;
    size_t number = 0;

    for (size_t i = 0; i < weightFactors.size(); i++)
    {
        if (!std::isdigit(pesel[i]))
        {
            return false;
        }
        number = pesel[i] - '0';
        checkSum += number * weightFactors[i];
    }

    checkSum = checkSum % weightFactors.size();

    if (checkSum != 0)
    {
        checkSum = weightFactors.size() - checkSum;
    }

    size_t lastNumber = (pesel.back() - '0');

    return checkSum == lastNumber;
}