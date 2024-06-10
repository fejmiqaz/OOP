
// your code here
#include<iostream>
#include<exception>
#include<cstring>
using namespace std;

class InvalidDiscountException{
private:
    int invalidValue;
public:
    InvalidDiscountException(int value) : invalidValue(value) {}

    void message() {
        cout << ("Invalid discount value: " + to_string(invalidValue)).c_str();
    }
};

class IceCream{
private:
    char * name;
    char ingredients[100];
    double price;
    int discount;
    void copy(const IceCream & ic){
        this->name = new char[strlen(ic.name)+1];
        strcpy(this->name, ic.name);
        strcpy(this->ingredients,ic.ingredients);
        this->price = ic.price;
        this->discount = ic.discount;
    }
public:
    IceCream(){
        this->discount = 0;
    }
    IceCream(char *name, char * ingredients, double price) {
        this->name = new char[strlen(name)+1];
        strcpy(this->name, name);
        strcpy(this->ingredients, ingredients);
        this->price = price;
        this->discount = discount;
    }
    IceCream(const IceCream & other){
        copy(other);
    }
    ~IceCream(){
        delete [] name;
    }
    IceCream & operator=(const IceCream & other){
        if(this!=&other){
            delete[] name;
            copy(other);
        }
        return * this;
    }

    friend ostream & operator<<(ostream & out, const IceCream & ic){
        out << ic.name << ": " << ic.ingredients  << " " << ic.price;
        if(ic.discount > 0){
            out << "[" << ic.discount << "]" << endl;
        }
        return out;
    }

    friend IceCream operator+(const IceCream & ic, const char * arr){
        IceCream newIceCream(ic);
        char * newName = new char[strlen(ic.name) + strlen((arr) + 2)];
        strcpy(newName, ic.name);
        strcat(newName,"+");
        strcat(newName, arr);
        newIceCream.setName(newName);
        newIceCream.setPrice(ic.getPrice() + 10);
        delete[] newName;
        return newIceCream;
    }

    IceCream & operator++(){
        discount+5;
        return * this;
    }

    void setName(char *name) {
        IceCream::name = name;
    }

    void setDiscount(int discount) {
        if(discount < 0 || discount > 100){
            throw InvalidDiscountException(discount);
        }
        IceCream::discount = discount;
    }

    void setPrice(double price) {
        IceCream::price = price;
    }

    double getPrice() const {
        return price;
    }
};

class IceCreamShop{
private:
    char name[50];
    IceCream * iceCream;
    int n;
    void copy(const IceCreamShop & ic){
        strcpy(this->name, ic.name);
        this->n = ic.n;
        iceCream = new IceCream[this->n];
        for(int i = 0; i < this->n; i++){
            this->iceCream[i] = ic.iceCream[i];
        }
    }
public:
    IceCreamShop(){}
    IceCreamShop(char *name) {
        strcpy(this->name,name);
        this->n = n;
        iceCream = new IceCream[0];
        for(int i = 0; i < this->n; i++){
            this->iceCream[i] = iceCream[i];
        }
    }
    IceCreamShop(const IceCreamShop & other){
        copy(other);
    }
    ~IceCreamShop(){
        delete [] iceCream;
    }


    IceCreamShop & operator+=(const IceCream & ic){
        IceCream * tmp = new IceCream[n+1];
        for(int i = 0; i < n; i++){
            tmp[i] = iceCream[i];
        }
        tmp[n++]=ic;
        delete[] iceCream;
        iceCream = tmp;
        return * this;
    }

    friend ostream & operator <<(ostream & out, const IceCreamShop & other){
        out << other.name;
        for(int i = 0; i < other.n;i++){
            out << other.iceCream[i];
        }
        return out;
    }
};

// DO NOT CHANGE THE MAIN FUNCTION, EXCEPT THE MARKED PART FOR HANDLING WITH THE EXCEPTION

int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
    cin.get();
    if(testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR <<" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if(testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "TESTING EXCEPTION" << endl;

        // your exception handling code

        try {
            cin >> discount;
            ic1.setDiscount(discount);
        } catch (const InvalidDiscountException& e){
            cerr << e.exception() << endl;
        }



    } else if(testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
            cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if(testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
            cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics+=x;
        cout << ics << endl;
        cout << icp << endl;
    }


    return 0;
}

