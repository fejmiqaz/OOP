#include<iostream>
#include<cstring>
using namespace std;

/* To define a MobilePhone class that will store data for a mobile phone:
    model (string of characters no longer than 20 characters)
    model number (integer)
    year of issue (integer)
    For the class, define a default constructor, a constructor with arguments, a copy constructor, a destructor and,
    if necessary, get methods. Also define a function to print class information that will print in the following format
    "(model) (model number) release year: (release year)".
    Then define an Owner class in which the following information is stored:
    name (string of characters no longer than 20 characters)
    last name (string of characters no longer than 20 characters)
    mobile phone (object of class MobilePhone)
    To create a default constructor, a constructor with arguments, a destructor and, if necessary, get methods.
    Also define a function to print information about the class that will print in the following format:
    "(name) (surname) has a mobile phone: (mobile phone information)" */
class MobilePhone{
private:
    string model;
    int modelNumber;
    int yearOfIssue;
public:
    MobilePhone(){}
    MobilePhone(string _model = "Blank", int _modelNumber = 1111, int _yearOfIssue = 2222){
        model = _model;
        modelNumber = _modelNumber;
        yearOfIssue = _yearOfIssue;
    }
    MobilePhone(MobilePhone & other){
        model = other.model;
        modelNumber = other.modelNumber;
        yearOfIssue = other.yearOfIssue;
    }
    ~MobilePhone(){}
    void print(){
        cout << model << " " << modelNumber << " release year: " << yearOfIssue << endl;
    }
};
class Owner{
private:
    string name;
    string surname;
    MobilePhone mobilePhone;
public:
    Owner(string _name = "Blank", string _surname = "Blank", string _model = "Blank",int _modelNumber = 1111, int _yearOfIssue = 2222)
    : mobilePhone(_model, _modelNumber, _yearOfIssue) {
        name = _name;
        surname = _surname;
    }
    ~Owner(){}
    void print(){
        cout << name << " " << surname << " has a mobile phone:" << endl;
        mobilePhone.print();
    }
};
int main(){
    Owner owner[100];
    string name, surname;
    string model;
    int modelNumber, yearOfIssue;
    int n; cin >> n;
    cin.ignore();
    for(int i = 0; i < n; i++){
        cin >> name >> surname >> model;
        cin >> modelNumber >> yearOfIssue;
        cin.ignore();
        owner[i] = Owner(name,surname,model,modelNumber,yearOfIssue);
        owner[i].print();
    }

    return 0;
}