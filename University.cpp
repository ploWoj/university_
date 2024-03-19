#include "University.hpp"

const std::vector<std::unique_ptr<Person>>& University::getVector() const {
    return university_;
}