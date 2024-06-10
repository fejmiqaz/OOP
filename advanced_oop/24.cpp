#include<iostream>
#include<cstring>
using namespace std;

class MonthlyInvoice {
protected:
    char name[100];
    int number;
    float price;
    int usedInternet;
public:
    MonthlyInvoice(char *name, int number, float price, int usedInternet) : number(number), price(price),usedInternet(usedInternet) {
        strcpy(this->name, name);
    }
//    MonthlyInvoice(const MonthlyInvoice & other){
//        strcpy(this->name, other.name);
//        this->number = other.number;
//        this->price = other.price;
//        this->usedInternet = other.usedInternet;
//    }
};

class BusinessInvoice : public MonthlyInvoice {
protected:
    bool optics;
    bool cable;
    int freeGB;
public:
    BusinessInvoice(char *name, int number, float price, int usedInternet, bool optics, bool cable, int freeGB) : MonthlyInvoice(name, number, price, usedInternet) {
        this-> optics = true;
        this->cable = false;
        this->freeGB = freeGB;
    }
};

class PrivateInvoice : public MonthlyInvoice {
protected:
    int id[14];


};

int main(){

    return 0;
}