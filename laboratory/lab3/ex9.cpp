#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

class Employee{
private:
    char name[100];
    char surname[100];
    int salary;
    void copy(const Employee & em){
        strcpy(this->name, em.name);
        strcpy(this->surname,em.surname);
        this->salary = em.salary;
    }
public:
    Employee() {} // default constructor

    Employee(char *name, char *surname, int salary = 0) { // constructor
        strcpy(this->name, name);
        strcpy(this->surname,surname);
        this->salary = salary;
    }
    Employee (const Employee & other){ // copy constructor
        copy(other);
    }

    int getSalary() const {
        return salary;
    }

    void printEmployee(){
        cout << "Employee name: " << name << endl;
        cout << "Employee surname: " << surname << endl;
        cout << "Employee salary: " << salary << "$" << endl;
    }
};

class TechCompany {
private:
    char name[100];
    Employee * employee;
    int numEmployees;
    void copy (const TechCompany & tc){
        strcpy(this->name,tc.name);
        this->numEmployees = tc.numEmployees;
        employee = new Employee[this->numEmployees];
        for(int i = 0; i < this->numEmployees; i++){
            this->employee[i] = tc.employee[i];
        }
    }
public:
    TechCompany(char *name = "Ueda SDS") {
        strcpy(this->name,name);
        this->numEmployees = 0;
        employee = new Employee[0];
    }
    TechCompany(const TechCompany & other) {
        copy(other);
    }

    const char *getName() const {
        return name;
    }

    void setName(char * name){
        strcpy(this->name,name);
    }

    Employee *getEmployee(int i) const {
        return &employee[i];
    }

    int getNumEmployees() const {
        return numEmployees;
    }

    void addEmployee(Employee & em){
        Employee * tmp = new Employee[numEmployees + 1];
        for(int i = 0; i < numEmployees; i++){
            tmp[i] = employee[i];
        }
        tmp[numEmployees++] = em;
        delete[] employee;
        employee = tmp;
    }
    void print(){
        cout << "Company name: " << name << endl;
        for(int i = 0; i < numEmployees; i++){
            employee[i].printEmployee();
        }
    }

    friend TechCompany printCompanyWithHighestAverageSalary(TechCompany * companies, int n);
    friend TechCompany printCompanyWithHighestStdSalary(TechCompany * companies, int n);
    friend bool isSameCompany(TechCompany c1, TechCompany c2);
};

TechCompany printCompanyWithHighestAverageSalary(TechCompany * companies, int n){
    TechCompany highestAvgSalaryCompany = companies[0];
    double highestAvgSalary = 0;

    for (int i = 0; i < n; i++) {
        double totalSalary = 0;
        for (int j = 0; j < companies[i].getNumEmployees(); j++) {
            totalSalary += companies[i].getEmployee(j)->getSalary();
        }
        double avgSalary = totalSalary / companies[i].getNumEmployees();
        if (avgSalary > highestAvgSalary) {
            highestAvgSalary = avgSalary;
            highestAvgSalaryCompany = companies[i];
        }
    }
    return highestAvgSalaryCompany;
}

TechCompany printCompanyWithHighestStdSalary(TechCompany * companies, int n){
    TechCompany highestStdSalaryCompany = companies[0];
    double highestStdSalary = 0;

    for (int i = 0; i < n; i++) {
        double totalSalary = 0;
        for (int j = 0; j < companies[i].getNumEmployees(); j++) {
            totalSalary += companies[i].getEmployee(j)->getSalary();
        }
        double avgSalary = totalSalary / companies[i].getNumEmployees();
        double variance = 0;
        for (int j = 0; j < companies[i].getNumEmployees(); j++) {
            double diff = companies[i].getEmployee(j)->getSalary() - avgSalary;
            variance += diff * diff;
        }
        double stdDeviation = sqrt(variance / companies[i].getNumEmployees());
        if (stdDeviation > highestStdSalary) {
            highestStdSalary = stdDeviation;
            highestStdSalaryCompany = companies[i];
        }
    }

    return highestStdSalaryCompany;
}

bool isSameCompany(TechCompany c1, TechCompany c2){
    return !strcmp(c1.getName(),c2.getName());
}

//DO NOT CHANGE main()

int main() {

    const int MAX_COMPANIES = 10;
    const int MAX_EMPLOYEES = 20;

    TechCompany companies[MAX_COMPANIES];

    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        char name[100];
        std::cin >> name;

        TechCompany company(name);

        int m;
        std::cin >> m;

        for (int j = 0; j < m; j++) {
            char name[100];
            char surname[100];
            int salary;

            std::cin >> name;

            std::cin >> surname;

            std::cin >> salary;

            Employee employee(name, surname, salary);

            company.addEmployee(employee);
        }

        companies[i] = company;
    }

    TechCompany copy = companies[0];

    std::cout<<"-->Testing get and set methods for one object and copy constructor"<<std::endl;
    copy.setName("copy");
    std::cout << copy.getName() << std::endl;


    std::cout<<"-->Testing addEmployee function"<<std::endl;
    Employee newEmployee("John", "Doe", 5000);
    copy.addEmployee(newEmployee);
    std::cout << "Number of employee in copy: " << copy.getNumEmployees() << std::endl;


    std::cout<<"-->Testing copy of first employee"<<std::endl;
    Employee firstEmployee = *copy.getEmployee(0);
    firstEmployee.printEmployee();


    std::cout<<"-->Testing methods"<<std::endl;
    TechCompany t = printCompanyWithHighestAverageSalary(companies, n);
    TechCompany t1 = printCompanyWithHighestStdSalary(companies, n);

    std::cout << "Tech company with the highest average salary: " << t.getName() << std::endl;
    std::cout << "Tech company with the highest standard deviation for salaries: " <<t1.getName() << std::endl;

    if (isSameCompany(t, t1)){
        std::cout<<"The tech company: "<<t.getName()<<" has the highest standard deviation and highest average salary"<<std::endl;
    }
    return 0;
}
