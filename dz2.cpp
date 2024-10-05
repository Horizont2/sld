#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Employee {
protected:
    string firstName;
    string lastName;

public:
    Employee(const string& fName, const string& lName)
        : firstName(fName), lastName(lName) {}

    virtual ~Employee() = default;

    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }

    void setFirstName(const string& fName) { firstName = fName; }
    void setLastName(const string& lName) { lastName = lName; }

    virtual double calculateSalary() const = 0;

    virtual void display() const {
        cout << "Ім'я: " << firstName << " Прізвище: " << lastName << endl;
    }
};

class Worker : public Employee {
    double hoursNumber;
    double hourlyRate;

public:
    Worker(const string& fName, const string& lName, double hours, double rate)
        : Employee(fName, lName), hoursNumber(hours), hourlyRate(rate) {}

    double getHoursNumber() const { return hoursNumber; }
    double getHourlyRate() const { return hourlyRate; }

    void setHoursNumber(double hours) { hoursNumber = hours; }
    void setHourlyRate(double rate) { hourlyRate = rate; }

    double calculateSalary() const override {
        const double overtimeRate = 2.0;
        const int standardHours = 40;

        if (hoursNumber > standardHours) {
            double overtime = hoursNumber - standardHours;
            return (standardHours * hourlyRate) + (overtime * hourlyRate * overtimeRate);
        }
        return hoursNumber * hourlyRate;
    }

    void display() const override {
        Employee::display();
        cout << "Години: " << hoursNumber << " Ставка: " << hourlyRate 
             << " Зарплата: " << calculateSalary() << endl;
    }
};

class SalaryWorker : public Employee {
protected:
    double salary;
    double bonus;

public:
    SalaryWorker(const string& fName, const string& lName, double salary, double bonus)
        : Employee(fName, lName), salary(salary), bonus(bonus) {}

    double getSalary() const { return salary; }
    double getBonus() const { return bonus; }

    void setSalary(double salary) { this->salary = salary; }
    void setBonus(double bonus) { this->bonus = bonus; }

    virtual double calculateBonus() const = 0;

    double calculateSalary() const override {
        return salary + calculateBonus();
    }

    void display() const override {
        Employee::display();
        cout << "Ставка: " << salary << " Бонус: " << calculateBonus() 
             << " Зарплата: " << calculateSalary() << endl;
    }
};

class Salesman : public SalaryWorker {
    double planPercentage;

public:
    Salesman(const string& fName, const string& lName, double salary, double bonus, double plan)
        : SalaryWorker(fName, lName, salary, bonus), planPercentage(plan) {}

    double getPlanPercentage() const { return planPercentage; }
    void setPlanPercentage(double plan) { planPercentage = plan; }

    double calculateBonus() const override {
        return bonus * (planPercentage / 100.0);
    }

    void display() const override {
        SalaryWorker::display();
        cout << "Відсоток виконання плану: " << planPercentage << "%" << endl;
    }
};

class Manager : public SalaryWorker {
    int clientCount;

public:
    Manager(const string& fName, const string& lName, double salary, double bonus, int clients)
        : SalaryWorker(fName, lName, salary, bonus), clientCount(clients) {}

    int getClientCount() const { return clientCount; }
    void setClientCount(int clients) { clientCount = clients; }

    double calculateBonus() const override {
        if (clientCount > 200)
            return bonus * 3;
        else if (clientCount > 100)
            return bonus * 2;
        return bonus;
    }

    void display() const override {
        SalaryWorker::display();
        cout << "Кількість клієнтів: " << clientCount << endl;
    }
};

void displayEmployees(const vector<Employee*>& employees) {
    for (const auto& employee : employees) {
        employee->display();
        cout << "----------------------------------" << endl;
    }
}

int main() {
    vector<Employee*> employees;

    employees.push_back(new Worker("Іван", "Іваненко", 45, 100));  // Погодинний працівник
    employees.push_back(new Salesman("Петро", "Петренко", 3000, 500, 75));  // Продавець
    employees.push_back(new Manager("Олена", "Олененко", 5000, 1000, 150));  // Менеджер

    displayEmployees(employees);

    for (auto& employee : employees) {
        delete employee;
    }
    employees.clear();

    return 0;
}
