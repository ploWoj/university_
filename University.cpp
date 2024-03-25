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

void University::addStudent(const Student& student)
{
    if (!findByPesel(student.getPesel())) {
        try
        {
            university_.emplace_back(std::make_unique<Student>(student));
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

void University::addStudent(const std::string &name, const std::string &surname, const std::string &address, const std::string &pesel, const std::string &gender, size_t indexNumber)
{
    if (!findByPesel(pesel))
    {   
        try
        {
            university_.emplace_back(std::make_unique<Student>(name, surname, address, pesel, gender, indexNumber));
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
}

void University::addEmployee(const Employee& employee)
{   
    if(!findByPesel(employee.getPesel ())) {
        try
        {
            university_.emplace_back(std::make_unique<Employee>(employee));
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

void University::addEmployee(const std::string &name, const std::string &surname, const std::string &address, const std::string &pesel, const std::string &gender, double salary)
{
    if (!findByPesel(pesel))
    {   
        try
        {
            university_.emplace_back(std::make_unique<Employee>(name, surname, address, pesel, gender, salary));
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
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
        std::cout << "Person with given pesel has already exists.\n";
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
                  return getSalaryIfIs(lhs).value_or(0.0) > getSalaryIfIs(rhs).value_or(0.0) || (getSalaryIfIs(lhs).value_or(0.0) == getSalaryIfIs(rhs).value_or(0.0) && lhs->getSurname() < rhs->getSurname());
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
                std::cout << "Remove successfull\n";
                break;
            } else {
                std::cout << "Given index number does not exists.\n";
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
        std::cout << "Remove successful. \n";
    } else {
        throw std::runtime_error("Given pesel does not exists.\n");
    }

}

void University::exportDatabase(const std::string &fileName)
{
    std::ofstream Database;
    Database.open(fileName);
    if (Database.is_open())
    {
        for (auto &itPerson : university_)
        {
            if (auto itStudent = dynamic_cast<Student *>(itPerson.get()))
            {
                Database << "Student" << ","
                         << itStudent ->getName() << ","
                         << itStudent ->getSurname() << ","
                         << itStudent ->getAddress() << ","
                         << itStudent ->getPesel() << ","
                         << itStudent ->getGender() << ","
                         << itStudent->getIndex() << '\n';
            }
            else if (auto itEmployee = dynamic_cast<Employee *>(itPerson.get()))
            {
                Database << "Employee" << ","
                         << itEmployee ->getName() << ","
                         << itEmployee ->getSurname() << ","
                         << itEmployee ->getAddress() << ","
                         << itEmployee ->getPesel() << ","
                         << itEmployee ->getGender() << ","
                         << itEmployee->getSalary() << '\n';
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
            if (rowLine[0] == "Student")
            {
               addStudent(rowLine[1], rowLine[2], rowLine[3], rowLine[4], rowLine[5], std::stoi(rowLine[6]));
            }
            if (rowLine[0] == "Employee")
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

    std::cout << "All records deleted from table: " << tableName << "\n";
    mysql_free_result(result);
    return true;
}

void University::exportMysql(const std::string &databaseName)
{
    if (university_.empty()) {
        std::cout << "ERROR: there is no rocord to export.\n";
        return;
    }
    
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
        name = person_ptr->getName();
        surname = person_ptr->getSurname();
        address = person_ptr->getAddress();
        pesel = person_ptr->getPesel();
        gender = person_ptr->getGender();

        if (auto student_ptr = dynamic_cast<Student*>(person_ptr.get()))
        {
            posesion = "Student";
            indexNumber = student_ptr->getIndex();
            salary = 0;
        }
        else if (auto employee_ptr = dynamic_cast<Employee*>((person_ptr.get())))
        {
            posesion = "Employee";
            salary = employee_ptr->getSalary();
            indexNumber = 0;
        }
        std::string query = "INSERT INTO people (posesion, name, surname, address, pesel, gender, indexNumber, salary) VALUES ('";
        query += posesion + "', '";
        query += name + "', '";
        query += surname + "', '";
        query += address + "', '";
        query += pesel + "', '";
        query += gender  + "', '"; 
        query += std::to_string(indexNumber) + "', '";
        query += std::to_string(salary) + "')";
        
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
        std::cout << "ERROR: Mysql object could not be created.\nn";
        return;
    }
    
    if (!mysql_real_connect(sql, host, user, password, databaseName.c_str(), port, NULL, 0))
    {
        std::cout << "ERROR: some database info is wrong to do not exists. "
                  << mysql_error(sql) << "\n\n";
        mysql_close(sql);
        return;
    }

    MYSQL_RES *result;
    
    if (mysql_query(sql, "SELECT * FROM university.people"))  {
        std::cout << "ERROR: " << mysql_error(sql) << "\n\n";
        mysql_close(sql);
        return;
    }
    
    result = mysql_store_result(sql);
    
    if (!result) {
        std::cerr << "ERROR: " << mysql_error(sql) << "\n\n";
        mysql_close(sql);
        return;
    }

    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    
    while(row = mysql_fetch_row(result)) {
        std::string person_ptr(row[0]);
        if (person_ptr == "Student" ) {
            addStudent(row[1], row[2], row[3], row[4], row[5], std::stoi(row[6]));
        }
        if (person_ptr == "Employee") {
            addEmployee(row[1], row[2], row[3], row[4], row[5], std::stod(row[6]));
        }
        
        std::cout << '\n';
    }

    mysql_free_result(result);
    mysql_close(sql);
    std::cout << '\n';
} 