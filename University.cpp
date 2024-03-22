#include "University.hpp"

#include <cstddef>
#include <functional>
#include <fstream>
#include <optional>

const std::vector<std::unique_ptr<Person>> &University::getVector() const
{
    return university_;
}

void University::displayBase(std::ostream &out)
{
    out << "Employee: \n";
    for (const auto &person_ptr : university_)
    {
        if (const auto employee_ptr{dynamic_cast<Employee *>(person_ptr.get())})
        {
            out << *employee_ptr << '\n';
        }
    }

    out << "Student: \n";
    for (const auto &person_ptr : university_)
    {
        if (const auto student_ptr{dynamic_cast<Student *>(person_ptr.get())})
        {
            out << *student_ptr << '\n';
        }
    }
}

void University::addStudent()
{
    university_.emplace_back(std::make_unique<Student>());
}

void University::addStudent(const std::string &name, const std::string &surname, const std::string &address, const std::string &pesel, const std::string &gender, size_t indexNumber)
{
    if (!findByPesel(pesel))
    {
        university_.emplace_back(std::make_unique<Student>(name, surname, address, pesel, gender, indexNumber));
    }
}

void University::addEmployee()
{
    university_.emplace_back(std::make_unique<Employee>());
}

void University::addEmployee(const std::string &name, const std::string &surname, const std::string &address, const std::string &pesel, const std::string &gender, double salary)
{
    if (!findByPesel(pesel))
    {
        university_.emplace_back(std::make_unique<Employee>(name, surname, address, pesel, gender, salary));
    }
}

Person *University::findBySurname(const std::string &surname)
{
    auto isTheSame = [&surname](std::unique_ptr<Person> &person)
    {
        return person->getSurname() == surname;
    };
    auto it = std::find_if(university_.begin(), university_.end(), isTheSame);

    if (it == university_.end())
    {
        return nullptr;
    }

    Person *person_ptr = it->get();

    return person_ptr;
}

Person *University::findByPesel(const std::string &pesel)
{
    auto isTheSame = [&pesel](std::unique_ptr<Person> &person)
    {
        return person->getPesel() == pesel;
    };

    auto it = std::find_if(university_.begin(), university_.end(), isTheSame);

    if (it == university_.end())
    {
        return nullptr;
    }

    Person *person_ptr = it->get();
    return person_ptr;
}

void University::sortByPesel()
{
    std::sort(university_.begin(), university_.end(),
              [](const std::unique_ptr<Person> &lhs, const std::unique_ptr<Person> &rhs)
              {
                  return lhs->getPesel() > rhs->getPesel();
              });
}

void University::sortBySurname()
{
    std::sort(university_.begin(), university_.end(),
              [](const std::unique_ptr<Person> &lhs, const std::unique_ptr<Person> &rhs)
              {
                  return lhs->getSurname() < rhs->getSurname();
              });
}

std::optional<double> University::getSalaryIfIs(const std::unique_ptr<Person> &person)
{
    if (auto *employee = dynamic_cast<Employee *>(person.get()))
    {
        return employee->getSalary();
    }

    return std::nullopt;
}

void University::sortBySalary()
{
    std::sort(university_.begin(), university_.end(),
              [&](const std::unique_ptr<Person> &lhs, const std::unique_ptr<Person> &rhs)
              {
                  return getSalaryIfIs(lhs).value_or(0.0) > getSalaryIfIs(rhs).value_or(0.0); // || (getSalaryIfIs(lhs).value_or(0.0) == getSalaryIfIs(rhs).value_or(0.0) && lhs->getSurname() < rhs->getSurname());
              });
}

void University::removeByIndexNumber(size_t indexNumber)
{
    size_t i = 0;
    for (const auto &el : university_)
    {
        if (auto s = dynamic_cast<Student *>(el.get()))
        {
            if (s->getIndex() == indexNumber)
            {
                university_.erase(university_.begin() + i);
                break;
            }
        }
        i++;
    }
}

void University::removeByPesel(const std::string &pesel)
{
    auto find = std::find_if(university_.begin(), university_.end(), [&pesel](const std::unique_ptr<Person> &person)
                             { return person->getPesel() == pesel; });

    if (find != university_.end())
    {
        university_.erase(find);
    }
}

bool University::validationByPesel(const std::string &pesel)
{
    if (pesel.size() != peselSize)
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

void University::exportDatabase(const std::string &fileName)
{
    std::ofstream Database;
    Database.open(fileName);
    if (Database.is_open())
    {
        for (auto &itPerson : university_)
        {
            Database << typeid(*itPerson).name() << ", "
                     << itPerson->getName() << ", "
                     << itPerson->getSurname() << ", "
                     << itPerson->getAddress() << ", "
                     << itPerson->getPesel() << ", "
                     << itPerson->getGender() << ", ";
            if (auto itStudent = dynamic_cast<Student *>(itPerson.get()))
            {
                Database << itStudent->getIndex() << '\n';
            }
            else if (auto itEmployee = dynamic_cast<Employee *>(itPerson.get()))
            {
                Database << itEmployee->getSalary() << '\n';
            }
        }
        Database.close();
    }
    else
        std::cout << "Unable to save file\n";
}

void University::importDatabase(const std::string &fileName)
{
    std::ifstream Database(fileName);
    std::string element;
    std::array<std::string, 7> rowLine = {};
    if (Database.is_open())
    {
        while (Database.peek() != EOF)
        {
            for (size_t i = 0; i < rowLine.size() - 1; i++)
            {
                getline(Database, element, ',');
                rowLine[i] = element;
            }
            getline(Database, element, '\n');
            rowLine[6] = element;
            if (rowLine[0] == "7Student")
            {
                addStudent(rowLine[1], rowLine[2], rowLine[3], rowLine[4], rowLine[5], std::stoi(rowLine[6]));
            }
            if (rowLine[0] == "8Employee")
            {
                addEmployee(rowLine[1], rowLine[2], rowLine[3], rowLine[4], rowLine[5], std::stod(rowLine[6]));
            }
        }
        Database.close();
    }
    else
        std::cout << "Unable to open file";
}

bool deleteAllRecords(MYSQL *mysql, const std::string &tableName)
{

    if (mysql_ping(mysql))
    {
        std::cerr << "ERROR: mysql lost connection: " << mysql_error(mysql) << '\n';
        return false;
    }

    MYSQL_RES *result;
    MYSQL_ROW row;

    if (mysql_query(mysql, "SHOW TABLES"))
    {
        std::cerr << "Error: mysql_query failed! " << mysql_error(mysql) << std::endl;
        return false;
    }

    result = mysql_store_result(mysql);
    if (!result)
    {
        std::cout << "ERROR: " << mysql_error(mysql) << '\n';
        return false;
    }

    char *newTableName;

    if ((row = mysql_fetch_row(result)) != nullptr)
    {
        newTableName = *row;
    }

    std::string query = "TRUNCATE TABLE " + std::string(newTableName);

    if (mysql_query(mysql, query.c_str()))
    {
        std::cerr << "Error: mysql_query failed! " << mysql_error(mysql) << std::endl;
        return false;
    }

    std::cout << "All records deleted from table: " << tableName << std::endl;
    mysql_free_result(result);
    return true;
}

void University::exportMysql(const std::string &databaseName)
{
    MYSQL *sql = mysql_init(NULL);
    if (!sql)
    {
        std::cout << "ERROR: Mysql object could not be created\n";
        return;
    }
    
    if (!mysql_real_connect(sql, host, user, password, databaseName.c_str(), port, NULL, 0))
    {
        std::cout << "ERROR: some database info is wrong to do not exists. \n"
                  << mysql_error(sql) << '\n';
        mysql_close(sql);
        return;
    }

    if (!deleteAllRecords(sql, "university.people"))
    {
        return;
    }

    std::string posesion{};
    std::string name{};
    std::string surname{};
    std::string address{};
    std::string pesel{};
    std::string gender{};
    size_t indexNumber{};
    double salary{};

    std::cout << "Logged in. \n";
    for (auto& person_ptr : university_)
    {
        posesion = typeid(*person_ptr).name();
        name = person_ptr->getName();
        surname = person_ptr->getSurname();
        address = person_ptr->getAddress();
        pesel = person_ptr->getPesel();
        gender = person_ptr->getGender();
        if (auto student_ptr = dynamic_cast<Student*>(person_ptr.get()))
        {
            indexNumber = student_ptr->getIndex();
            salary = 0;
        }
        else if (auto employee_ptr = dynamic_cast<Employee*>((person_ptr.get())))
        {
            indexNumber = 0;
            salary = employee_ptr->getSalary();
        }
        std::string query = "INSERT INTO people (posesion, name, surname, address, pesel, gender, indexNumber, salary) VALUES ('";
        query += posesion;
        query += "', '";
        query += name;
        query += "', '";
        query += surname;
        query += "', '";
        query += address;
        query += "', '";
        query += pesel;
        query += "', '";
        query += gender;
        query += "', ";
        query += std::to_string(indexNumber);
        query += ", ";
        query += std::to_string(salary);
        query += ")";

        if (mysql_ping(sql))
        {
            std::cout << "ERROR: imposible to connect. " << mysql_error(sql) << '\n';
        }
        if (mysql_query(sql, query.c_str()))
        {
            std::cerr << "ERROR: " << mysql_error(sql) << '\n';
            rewind(stdin);
            std::getchar();
        }
    }
    std::cout << "\n Info added correctly\n";
    mysql_close(sql);
}

void University::importMysql(const std::string& databaseName) {
    MYSQL *sql = mysql_init(NULL);

    if (!sql)
    {
        std::cout << "ERROR: Mysql object could not be created\n";
        return;
    }
    
    if (!mysql_real_connect(sql, host, user, password, databaseName.c_str(), port, NULL, 0))
    {
        std::cout << "ERROR: some database info is wrong to do not exists. \n"
                  << mysql_error(sql) << '\n';
        mysql_close(sql);
    }

    MYSQL_RES *result;

    if (mysql_query(sql, "SELECT * FROM university.people"))  {
        std::cout << "ERROR: " << mysql_error(sql) << '\n';
        mysql_close(sql);
    }
    
    result = mysql_store_result(sql);

    if (!result) {
        std::cerr << "ERROR: " << mysql_error(sql) << '\n';
        mysql_close(sql);
    }

    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;

    while((row = mysql_fetch_row(result))) {
        for (int i = 0; i < num_fields; ++i) {
            std::cout << row[i] << " ";
        }
        std::cout << '\n';
    }

    mysql_free_result(result);
    mysql_close(sql);
} 