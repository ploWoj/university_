#include <sstream>
#include <string_view>
#include "../src/University.hpp"
#include "catch_amalgamated.hpp"
#include <assert.h>

SCENARIO("Should add Students and Employees to the base and display the list",
         "[universitybase][add][display]")
{
    GIVEN("A UniversityBase object, a Student and an Employee")
    {
        University base{};
        Student student{
            "Jan", "Kowalski",
            "Warszawa", "80102818499",
            "male", 12345};

        Employee employee{
            "Anna", "Nowak",
            "Krakow", "92092312978",
            "female", 7777};

        static constexpr std::string_view str{
            "Employees:\nAnna,Nowak,Krakow,92092312978,female,7777,\n"
            "Students:\nJan,Kowalski,Warszawa,80102818499,male,12345,\n"};

        WHEN("They are added to the base and displayed to a stream")
        {
            base.addStudent(student);
            base.addEmployee(employee);

            std::stringstream stream{};
            base.displayBase(stream);

            THEN("The obtained string should match the str")
            {
                REQUIRE(stream.str() == str);
            }
        }
    }
}

SCENARIO("Should find by surname string",
         "[universitybase][find][surname]")
{
    GIVEN("A student added to university database object")
    {
        University base{};
        Student student{"Jan", "Kowalski",
                        "Warszawa", "80102818499",
                        "male", 12345};

        base.addStudent(student);
        WHEN("findBySurname is called")
        {
            auto person_ptr = base.findBySurname(student.getSurname());
            THEN("Should return pointet with student data")
            {
                auto student_ptr = dynamic_cast<Student *>(person_ptr);
                REQUIRE(student_ptr);
                REQUIRE(*student_ptr == student);
            }
        }
    }
}

SCENARIO("Should search by pesel string",
         "[universitybase][search][pesel]")
{
    GIVEN("A student added to university database object")
    {
        University base{};
        Student student{"Jan", "Kowalski",
                        "Warszawa", "80102818499",
                        "male", 12345};

        base.addStudent(student);
        WHEN("findByPesel is called")
        {
            auto person_ptr = base.findByPesel(student.getPesel());
            THEN("Should return pointet with student data")
            {
                auto student_ptr = dynamic_cast<Student *>(person_ptr);
                REQUIRE(student_ptr);
                REQUIRE(*student_ptr == student);
            }
        }
    }
}

SCENARIO("Should sort the base by pesel", "[universitybase][surname][pesel]")
{
    GIVEN("A base with two Students, whose surnames and pesels vary")
    {
        Student student1{
            "Jan", "Kowalski",
            "Warszawa", "80102818499",
            "male", 12345};

        Student student2{
            "Anna", "Nowak",
            "Krakow", "92092312978",
            "female", 7777};

        University base{};
        base.addStudent(student2);
        base.addStudent(student1);

        static constexpr std::string_view string{
            "Employees:\n"
            "Students:\nAnna,Nowak,Krakow,92092312978,female,7777,\n"
            "Jan,Kowalski,Warszawa,80102818499,male,12345,\n"};
        WHEN("sort_by_pesel is called")
        {
            base.sortByPesel();
            std::stringstream stream{};
            base.displayBase(stream);

            THEN("The list should be sorted")
            {
                REQUIRE(stream.str() == string);
            }
        }
    }
}

SCENARIO("Should remove Student byIndex",
         "[universitybase][erase][index_num]")
{
    GIVEN("A base with two Students")
    {
        Student student1{
            "Jan", "Kowalski",
            "Warszawa", "80102818499",
            "male", 12345};

        Student student2{
            "Anna", "Nowak",
            "Krakow", "92092312978",
            "female", 7777};

        University base{};
        base.addStudent(student2);
        base.addStudent(student1);

        static constexpr std::string_view string{
            "Employees:\n"
            "Students:\nJan,Kowalski,Warszawa,80102818499,male,12345,\n"};
        WHEN("removeByIndex is called")
        {
            base.removeByIndexNumber(student2.getIndex());
            std::stringstream stream{};
            base.displayBase(stream);

            THEN("The list should be sorted")
            {
                REQUIRE(stream.str() == string);
            }
        }
    }
}

SCENARIO("Should change a name by pesel",
         "[universitybase][name][pesel][set]")
{
    GIVEN("A base with an Employee")
    {
        Employee employee{
            "Jan", "Kowalski",
            "Warszawa", "80102818499",
            "male", 17000};

        University base{};
        base.addEmployee(employee);
        std::string newName = "Tomasz";

        static constexpr std::string_view string{
            "Employees:\nTomasz,Kowalski,Warszawa,80102818499,male,17000,\n"
            "Students:\n"};

        WHEN("set new name is called")
        {
            auto person = base.findByPesel(employee.getPesel());
            person->setName(newName);
            std::stringstream stream{};
            base.displayBase(stream);

            THEN("The list should have the changed salary")
            {
                REQUIRE(stream.str() == string);
            }
        }
    }
}