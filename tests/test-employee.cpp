#include <sstream>
#include "../src/Employee.hpp"
#include "catch_amalgamated.hpp"
#include <assert.h>

SCENARIO("Should output the Employee to a stream", "[person][stream][output]") {
    GIVEN("A Employee object") {
        Employee employee("Jan", "Kowalski", "Warszawa", "70080837171", "male", 12500.0);
        std::string str{"Jan,Kowalski,Warszawa,70080837171,male, 12500.0"};
        
        WHEN("It's output to a stream") {
            std::stringstream outputStream{};
            outputStream << employee;
            THEN("It should be in CSV format") {
                REQUIRE(outputStream.str() == str);
            }
        }
    }
}

SCENARIO("Should parse the Employee from a stream", "[person][stream][input]") {
    GIVEN("A Employee object") {
        Employee employee("Jan", "Kowalski", "Warszawa", "70080837171", "male", 12500.0);
        std::stringstream stream{"Jan,Kowalski,Warszawa,70080837171,male,12500"};
        
        WHEN("It's parsed from a stream") {
            Employee employeeInput{};
            stream >> employeeInput;

            THEN("It should be in CSV format") {
                REQUIRE(employeeInput == employee);
            }
        }
    }
}