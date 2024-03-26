#include <sstream>
#include <string>
#include "../src/University.hpp"
#include "catch_amalgamated.hpp"
#include <assert.h>

SCENARIO("Should add Students and Employees to the base and display the list",
         "[universitybase][add][display]") {
    GIVEN("A UniversityBase object, a Student and an Employee") {
        University base{};
        Student student{"Jan",        "Kowalski",
                        "Warszawa",   "80102818499",
                       "male", 12345};

        Employee employee{
            "Anna",         "Nowak",
            "Krakow",       "92092312978",
            "female", 7777};

        static std::string str{
            "Employees:\nAnna,Nowak,Krakow,92092312978,female,7777\n"
            "Students:\nJan,Kowalski,Warszawa,80102818499,male,12345\n"};

        WHEN("They are added to the base and displayed to a stream") {
            base.addStudent(student);
            base.addEmployee(employee);

            std::stringstream stream{};
            base.displayBase(stream);

            THEN("The obtained string should match the str string") {
                REQUIRE(stream.str() == str);
            }
        }
    }
}

SCENARIO("Should search by surname string",
        "[universitybase][search][surname]") {
    GIVEN("A student added to university database object") {
        University base{};
        Student student{"Jan",        "Kowalski",
                        "Warszawa",   "80102818499",
                       "male", 12345};
        std::unique_ptr<Student> studentPtr = std::make_unique<Student>(student);
        
        base.addStudent(student);
    WHEN("search_by_surname is called") {
        auto person_ptr = base.findBySurname(student.getPesel());
    THEN("Should return pointet with student data") {
        auto student_ptr = dynamic_cast<Student*>(person_ptr);
        REQUIRE(student_ptr);
        REQUIRE(*student_ptr == *studentPtr.get());
    }
    }
    }
        }